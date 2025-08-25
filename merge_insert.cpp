/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_insert.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:50:50 by totommi           #+#    #+#             */
/*   Updated: 2025/08/25 13:40:36 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge_insert.h"
#include <iostream>
#include <cmath>

/* swaps the index with the next cell */
static void	swap_next_cell(std::vector<int>& v, int pos, size_t size)
{
	int	tmp;

	// std::cout << "swapping '" << v[pos] << "' with '" << v[pos + size] << "'" << std::endl; 
	for (size_t i = 0; i < size; ++i) {
		tmp = v[pos - i];
		v[pos - i] = v[pos - i + size];
		v[pos - i + size] = tmp;
	}
}

/* moves (insert, erase) a cell from a vector to another (just push_back() on the dest)
'pos' is the index of the bigger element of the cell to move */
static void	move_cell(std::vector<int>& dest, std::vector<int>& src, int pos, size_t size)
{
	if (static_cast<size_t>(pos) == src.size() - 1)
	{
		for (size_t i = 0; i < size; ++i) {
			dest.push_back(src[pos - i]);
			src.pop_back();
		}
	}
	else
	{
		for (size_t i = 0; i < size; ++i) {
			dest.push_back(src[pos - i]);
			src.erase(src.begin() + pos - i);
		}
	}
}

static void	push_pend(std::vector<int>& main, std::vector<int>& pend, size_t size)
{
	size_t i = (3 * size) - 1;
	while (i <= main.size() - 1)
	{
		move_cell(pend, main, i, size);
		i += size;	// just size and not 2 * size because main is shrinking
	}
	// for (size_t i = (3 * size) - 1; i < main.size() - 1; i += size) {
	// 	move_cell(pend, main, i, size);
	// }
}

/* low and higth are pointer to the indexes of the lower and higher bound
target is the highest element of the cell to insert 
RRETURNS: the index of the cell, negative if we wanna insert below, positive if above, (-1 for first position)*/
static int	binary_split(const std::vector<int>& main, size_t low, size_t high, int target, size_t size)
{
	size_t	half;

	// if (((low + 1) / size - (high + 1) / size) % 2 == 0)	// if half isn't a precise cell...
	// {
	// 	// choose the lower one
	// } 
	half = (((low + 1) / size + (high + 1) / size) / 2) * size - 1;
	// std::cout << "bound [" << main[low] << ", " << main[high] << "], half '" << main[half] << "'" << std::endl;
	if (target > main[half])
	{
		if (main[half] == main[high])
			return half;
		if (main[half] == main[low])
		{
			if (target > main[high])
				return high;
			else
				return half;
		}
		// low = half;
		return binary_split(main, half, high, target, size);
	}
	else
	{
		if (main[half] == main[low])
			return (half == size - 1) ? -1: -half;
		if (main[half] == main[high])
		{
			if (target < main[low])
				return (low == size - 1) ? -1: -low;
			else
				return -half;
		}
		// high = half;
		return binary_split(main, low, half, target, size);
	}
	std::cout << "Error: binary case" << std::endl;
	return low;	//should never get here
}

/* cell is a ptr to the higher element of the cell (the cell follows on the right)
bound is the index of the higer element of the leftmost cell to consider */
static void insert_part_of_the_sort(std::vector<int>& main, int* cell, size_t bound, size_t size)
{
	if (bound > main.size())
		bound = (main.size() / size) * size - 1;
	// std::cout << "inserting '" << *cell << "' with top bound main[" << bound << "] = " << main[bound] << std::endl;
	int tarcell = binary_split(main, size - 1, bound, *cell, size);
	int	tarpos = (tarcell < 0) ? -tarcell - size : tarcell + 1;
	// const std::vector<int>::iterator b = main.begin();

	if (tarcell == -1)	//insert in first pos
	{
		// std::cout << "inserting beginning" << std::endl;
		for (size_t i = 0; i < size; ++i) {
			main.insert(main.begin(), cell[i]);
		}
	}
	else
	{
		// std::cout << "inserting in elem: " << main[tarpos] << std::endl;
		for (size_t i = 0; i < size; ++i) {
			main.insert(main.begin() + tarpos, cell[i]);
		}
	}
	// std::cout << "-> inserted "; printStuff(main, size);
}

void	merge_insert(std::vector<int>& main, size_t size)
{
	std::vector<int>			pend;
	static const unsigned long	jacobsthal[] = {0, 1, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765, 2863311531, 5726623061, 11453246123};

	// std::cout << "=== CELL SIZE " << size << ": forward ===" << std::endl;
	// printStuff(main);
	for (size_t i = size - 1; i + size < main.size(); i += 2 * size) {
		// std::cout << "'" << main[i] << "' >? '" << main[i + size] << "'" << std::endl;
		if (main[i] > main[i + size])
			swap_next_cell(main, i, size);
	}
	// printStuff(main, size);
	if (size * 2 <= main.size() / 2)
		merge_insert(main, size * 2);
	// std::cout << "=== CELL SIZE " << size << ": reverse ===" << std::endl;
	push_pend(main, pend, size);
	if (pend.size() == 0)
		return ;
	// std::cout << "main: "; printStuff(main, size);
	// std::cout << "pend: "; printStuff(pend, size);
	// 1. pick jacobsthal cell
	int		jacob_cap = 0;
	ssize_t last = -1;
	for (int j = 3; j < 34; ++j)	// all jacobsthal
	{
		// std::cout << "--- Jacob " << jacobsthal[j] << " ---" << std::endl;
		for (ssize_t i = (jacobsthal[j] - 1) * size - size; i > last; i -= size)	// single jacobsthal
		{
			// std::cout << "i " << i << ", last " << last << std::endl;
			if (jacob_cap == 0 && i >= static_cast<ssize_t>(pend.size() - size))
			{
				// last = 0;
				i = (pend.size() / size ) * size - size;
				jacob_cap = 1;
			}
			// 2. inset jacoobsthal pair
			// top bound = 2^j - 1 cells
			// std::cout << "std::pow(2, j) = " << (std::pow(2, j - 1) - 1) << ", size = " << size << std::endl;
			// std::cout << "i " << i << " and ";
			insert_part_of_the_sort(main, &pend[i], (std::pow(2, j - 1) - 1) * size - 1, size);
			// if (i < last)
			// {
			// 	pend.clear();
			// 	return ;
			// }
		}
		if (jacob_cap == 1)
			return ;
		last = (jacobsthal[j] - 1) * size - 1;	// biggest index just inserted
		// 3. iter all pend
	}
	std::cout << "Error: end of jacobsthal" << std::endl;
}

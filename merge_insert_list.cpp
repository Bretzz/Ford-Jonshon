/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_insert_list.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:50:50 by totommi           #+#    #+#             */
/*   Updated: 2025/08/25 20:36:48 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <cmath>
#include <list>

#include <iostream>	// just 2 error prints

/* swaps the index with the next cell */
static void	swap_next_cell(std::list<unsigned int>::iterator pos, size_t size)
{
	unsigned int						tmp;
	std::list<unsigned int>::iterator	prev;

	for (size_t i = 0; i < size; ++i) {
		prev = pos;
		tmp = *pos;
		std::advance(pos, size);
		*prev = *pos;
		*pos = tmp;
		pos = prev;
		std::advance(pos, -1);
	}
}

/* moves (insert, erase) a cell from a vector to another (just push_back() on the dest)
'pos' is the index of the bigger element of the cell to move */
static void	move_cell(std::list<unsigned int>& dest, std::list<unsigned int>& src, std::list<unsigned int>::reverse_iterator pos, size_t size)
{
	if (pos == src.rbegin())
	{
		for (size_t i = 0; i < size; ++i) {
			dest.push_back(*pos);
			if (pos == --src.rend())
			{
				src.pop_back();
				break ;
			}
			src.pop_back();
			pos = src.rbegin();
		}
	}
	else
	{
		for (size_t i = 0; i < size; ++i) {
			std::list<unsigned int>::iterator to_erase = pos.base();
			if (pos != --src.rend())
				std::advance(pos, 1);
			dest.push_back(*to_erase);
			src.erase(to_erase);
			if (pos == --src.rend())
				break;
		}
	}
}

/* Takes all the 'lower' cell except for the first one and move_cell()s them to
the pend */
static void	push_pend(std::list<unsigned int>& main, std::list<unsigned int>& pend, size_t size)
{
	size_t 	i = (3 * size) - 1;

	while (i <= main.size() - 1)
	{
		// Always recalculate a valid iterator from scratch
		std::list<unsigned int>::reverse_iterator pos = main.rbegin();
		std::advance(pos, main.size() - i);

		move_cell(pend, main, pos, size);
		i += size;	// just size and not 2 * size because main is shrinking
	}
}

/* low and higth are pointer to the indexes of the lower and higher bound
target is the highest element of the cell to insert 
RRETURNS: the index of the cell, negative if we wanna insert below, positive if above, (-1 for first position)*/
/* ! ! ! CHECK FOR IMPROVEMENT ! ! !
regarding the various ifs for the return... I think we could do a better job */
static int	binary_split(const std::list<unsigned int>& main, size_t low, size_t high, unsigned int target, size_t size)
{
	size_t	half = (((low + 1) / size + (high + 1) / size) / 2) * size - 1;
	std::list<unsigned int>::const_iterator	main_half = main.begin();
	std::list<unsigned int>::const_iterator	main_high = main.begin();
	std::list<unsigned int>::const_iterator	main_low = main.begin();

	std::advance(main_half, half);
	std::advance(main_high, high);
	std::advance(main_low, low);

	if (target > *main_half)
	{
		if (*main_half == *main_high)
			return half;
		if (*main_half == *main_low)
		{
			if (target > *main_high)
				return high;
			else
				return half;
		}
		return binary_split(main, half, high, target, size);
	}
	else
	{
		if (*main_half == *main_low)
			return (half == size - 1) ? -1: -half;
		if (*main_half == *main_high)
		{
			if (target < *main_low)
				return (low == size - 1) ? -1: -low;
			else
				return -half;
		}
		return binary_split(main, low, half, target, size);
	}
	/* ERROR: BINARY CASE */
	std::cerr << "Error: binary case" << std::endl;
	return -2;
}

/* cell is a ptr to the higher element of the cell (the cell follows on the right)
bound is the index of the higer element of the leftmost cell to consider */
static int insert_part_of_the_sort(std::list<unsigned int>& main, std::list<unsigned int>::iterator cell, size_t bound, size_t size)
{
	if (bound > main.size())
		bound = (main.size() / size) * size - 1;

	int tarcell = binary_split(main, size - 1, bound, *cell, size);
	int	tarpos = (tarcell < 0) ? -tarcell - size : tarcell + 1;
	
	if (tarcell == -2)
		return 1;
	else if (tarcell == -1)
	{
		for (size_t i = 0; i < size; ++i) {
			std::list<unsigned int>::iterator	pos = main.begin();
			main.insert(pos, *cell);
			std::advance(cell, 1);
		}
	}
	else
	{
		std::list<unsigned int>::iterator	pos = main.begin();
		std::advance(pos, tarpos);
		for (size_t i = 0; i < size; ++i) {
			main.insert(pos, *cell);
			std::advance(pos, -1);
			std::advance(cell, 1);
		}
	}
	return 0;
}

/* performs the sort of the elements in 'main' using the Ford-Jonshon Algorithm */
void	merge_insert(std::list<unsigned int>& main, size_t size)
{
	std::list<unsigned int>				pend;
	static const unsigned long			jacobsthal[] = {0, 1, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765, 2863311531, 5726623061, 11453246123};
	std::list<unsigned int>::iterator	pos = main.begin();
	std::list<unsigned int>::iterator	next = main.begin();

	/* FORWARD */
	std::advance(pos, size - 1);
	for (size_t i = size - 1; i + size < main.size(); i += 2 * size) {
		if (i != size - 1)
			std::advance(pos, 2 * size);
		next = pos;
		std::advance(next, size);
		if (*pos > *next)
			swap_next_cell(pos, size);
	}
	if (size * 2 <= main.size() / 2)
		merge_insert(main, size * 2);

	/* BACKWARD */
	int		jacob_cap = 0;
	ssize_t last = -1;

	/* filling pend */
	push_pend(main, pend, size);
	if (pend.size() == 0)
		return ;
	
	/* itering all jacobsthal and insert the correspondig element of the pend */
	for (int j = 3; j < 34; ++j)
	{
		for (ssize_t i = (jacobsthal[j] - 1) * size - size; i > last; i -= size)
		{
			std::list<unsigned int>::iterator pos = pend.begin();
			std::advance(pos, i);
			/* check if the current jacobsthal exceeded the pend limit */
			if (jacob_cap == 0 && i >= static_cast<ssize_t>(pend.size() - size))
			{
				i = (pend.size() / size ) * size - size;
				pos = pend.begin();
				std::advance(pos, i);
				jacob_cap = 1;
			}
			if (insert_part_of_the_sort(main, pos, (std::pow(2, j - 1) - 1) * size - 1, size))
				return ;
		}
		if (jacob_cap == 1)
			return ;
		last = (jacobsthal[j] - 1) * size - 1;	// biggest index just inserted
	}
	/* ERROR: END OF JACOBSTHAL */
	std::cerr << "Error: end of jacobsthal database" << std::endl;
}

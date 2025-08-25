/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_insert_deque.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:50:50 by totommi           #+#    #+#             */
/*   Updated: 2025/08/25 14:03:33 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <cmath>
#include <deque>

/* swaps the index with the next cell */
static void	swap_next_cell(std::deque<unsigned int>& v, int pos, size_t size)
{
	int	tmp;

	for (size_t i = 0; i < size; ++i) {
		tmp = v[pos - i];
		v[pos - i] = v[pos - i + size];
		v[pos - i + size] = tmp;
	}
}

/* moves (insert, erase) a cell from a vector to another (just push_back() on the dest)
'pos' is the index of the bigger element of the cell to move */
static void	move_cell(std::deque<unsigned int>& dest, std::deque<unsigned int>& src, int pos, size_t size)
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

/* Takes all the 'lower' cell except for the first one and move_cell()s them to
the pend */
static void	push_pend(std::deque<unsigned int>& main, std::deque<unsigned int>& pend, size_t size)
{
	size_t i = (3 * size) - 1;
	while (i <= main.size() - 1)
	{
		move_cell(pend, main, i, size);
		i += size;	// just size and not 2 * size because main is shrinking
	}
}

/* low and higth are pointer to the indexes of the lower and higher bound
target is the highest element of the cell to insert 
RRETURNS: the index of the cell, negative if we wanna insert below, positive if above, (-1 for first position)*/
/* ! ! ! CHECK FOR IMPROVEMENT ! ! !
regarding the various ifs for the return... I think we could do a better job */
static int	binary_split(const std::deque<unsigned int>& main, size_t low, size_t high, unsigned int target, size_t size)
{
	size_t	half = (((low + 1) / size + (high + 1) / size) / 2) * size - 1;

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
		return binary_split(main, low, half, target, size);
	}
	/* ERROR: BINARY CASE */
	return low;
}

/* cell is a ptr to the higher element of the cell (the cell follows on the right)
bound is the index of the higer element of the leftmost cell to consider */
static void insert_part_of_the_sort(std::deque<unsigned int>& main, std::deque<unsigned int>::iterator cell, size_t bound, size_t size)
{
	if (bound > main.size())
		bound = (main.size() / size) * size - 1;

	int tarcell = binary_split(main, size - 1, bound, *cell, size);
	int	tarpos = (tarcell < 0) ? -tarcell - size : tarcell + 1;

	if (tarcell == -1)
	{
		for (size_t i = 0; i < size; ++i) {
			main.insert(main.begin(), cell[i]);
		}
	}
	else
	{
		for (size_t i = 0; i < size; ++i) {
			main.insert(main.begin() + tarpos, cell[i]);
		}
	}
}

/* performs the sort of the elements in 'main' using the Ford-Jonshon Algorithm */
void	merge_insert(std::deque<unsigned int>& main, size_t size)
{
	std::deque<unsigned int>			pend;
	static const unsigned long	jacobsthal[] = {0, 1, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765, 2863311531, 5726623061, 11453246123};

	/* FORWARD */
	for (size_t i = size - 1; i + size < main.size(); i += 2 * size) {
		if (main[i] > main[i + size])
			swap_next_cell(main, i, size);
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
			/* check if the current jacobsthal exceeded the pend limit */
			if (jacob_cap == 0 && i >= static_cast<ssize_t>(pend.size() - size))
			{
				i = (pend.size() / size ) * size - size;
				jacob_cap = 1;
			}
			insert_part_of_the_sort(main, pend.begin() + i, (std::pow(2, j - 1) - 1) * size - 1, size);
		}
		if (jacob_cap == 1)
			return ;
		last = (jacobsthal[j] - 1) * size - 1;	// biggest index just inserted
	}
	/* ERROR: END OF JACOBSTHAL */
}

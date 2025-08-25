/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:56:37 by totommi           #+#    #+#             */
/*   Updated: 2025/08/25 20:39:03 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <sys/types.h>
# include <vector>
# include <deque>
# include <list>

# include <iostream> // std::cout

void	merge_insert(std::vector<unsigned int>& v, size_t size = 1);
void	merge_insert(std::deque<unsigned int>& d, size_t size = 1);
void	merge_insert(std::list<unsigned int>& main, size_t size = 1);

template <class T>
static void printStuff(const T& c, int size = 1)
{
	typename T::const_iterator it = c.begin();
	for (size_t i = 0; i < c.size(); ++i)
	{
		if (size != 1 && i % size == size - 1)
			std::cout << "[";
		std::cout << *it;
		if (size != 1 && i % size == size - 1)
			std::cout << "]";
		std::cout << " ";
		std::advance(it, 1);
	}
}

# include <stdio.h>	// std::cin
# include <cstdlib>	// atoi

template <class C>
void	populateContainer(C& c, char *argv[], int argc = 2)
{
	typedef typename C::value_type T;  // this gets the element type
	unsigned int i = 0;

	if (argc == 1)
	{
		T	x;
		while (std::cin >> x) {
    		c.push_back(x);
		}
	}
	else if (argc == 2)
	{
		while (argv[0][i] != '\0')
		{
			c.push_back(std::atoi(&argv[0][i]));
			while (argv[0][i] != '\0' && std::isdigit(argv[0][i]))
				++i;
			while (argv[0][i] != '\0' && std::isspace(argv[0][i]))
				++i;
		}
	}
	else
	{
		while (argv[i] != NULL)
		{
			c.push_back(std::atoi(argv[i]));
			++i;
		}
	}
}

template <class C>
void	populateContainer(C& c, const std::string& str)
{
	unsigned int i = 0;

	while (str[i] != '\0')
	{
		c.push_back(std::atoi(&str[i]));
		while (str[i] != '\0' && std::isdigit(str[i]))
			++i;
		while (str[i] != '\0' && std::isspace(str[i]))
			++i;
	}
}

#include <algorithm>

template <class C>
int	check4duplicatesFast(C& c)
{
	std::sort(c.begin(), c.end());
	for (size_t i = 1; i < c.size(); ++i)
	{
		if (c[i] == c[i - 1])
		{
			std::cerr << "Error: duplicate '" << c[i] << "'" << std::endl;
			return 1;
		}
	}
	return 0;
}

#endif
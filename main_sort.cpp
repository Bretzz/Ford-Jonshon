/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_sort.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:38:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/08/25 20:39:55 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>

int main(int argc, char *argv[])
{
	std::vector<unsigned int>	v;

	/* INTROSORT */
	populateContainer(v, argv + 1, argc);		// header's functions
	// if (check4duplicates(v))					// header's functions
	// 	return 1;
	std::sort(v.begin(), v.end());
	printStuff(v);								// header's functions
    return 0;
}

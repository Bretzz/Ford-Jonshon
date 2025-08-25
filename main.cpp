/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:51:50 by totommi           #+#    #+#             */
/*   Updated: 2025/08/25 01:20:02 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge_insert.h"
#include <vector>
#include <iostream>
#include <cstdlib>

void	populateVector(std::vector<int>& v, char *argv[], int argc = 2)
{
	unsigned int i = 0;

	if (argc == 1)
	{
		int	x;
		while (scanf("%d", &x) == 1) {	// maybe forbidden
    		v.push_back(x);
		}
	}
	else if (argc == 2)
	{
		while (argv[0][i] != '\0')
		{
			// std::cout << "pushing '" << argv[0][i] << "'..." << std::endl;
			v.push_back(std::atoi(&argv[0][i]));
			while (argv[0] != '\0' && std::isdigit(argv[0][i]))
				++i;
			while (argv[0] != '\0' && std::isspace(argv[0][i]))
				++i;
		}
	}
	else
	{
		while (argv[i] != NULL)
		{
			v.push_back(std::atoi(argv[i]));
			++i;
		}
	}
}

int	main(int argc, char *argv[])
{
	std::vector<int> v;

	// std::cout << "check 1 number and 2 numbers" << std::endl;
	populateVector(v, argv + 1, argc);
	// std::cout << "INIZIO" << std::endl;
	// std::cout << argv[1] << std::endl;
	// printStuff(v);
	merge_insert(v);
	printStuff(v);
	return 0;
}
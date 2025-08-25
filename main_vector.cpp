/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:51:50 by totommi           #+#    #+#             */
/*   Updated: 2025/08/25 20:39:59 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int argc, char *argv[])
{
	std::vector<unsigned int>	v;

	/* VECTOR */
	populateContainer(v, argv + 1, argc);		// header's functions
	// if (check4duplicates(v))					// header's functions
	// 	return 1;
	merge_insert(v);
	printStuff(v);								// header's functions
	return 0;
}

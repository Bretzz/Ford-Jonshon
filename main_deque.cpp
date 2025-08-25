/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_deque.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:51:50 by totommi           #+#    #+#             */
/*   Updated: 2025/08/25 17:19:03 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge_insert.h"

int	main(int argc, char *argv[])
{
	std::deque<unsigned int>	d;

	/* DQUE */
	populateContainer(d, argv + 1, argc);		// header's functions
	// if (check4duplicates(d))					// header's functions
	// 	return 1;
	merge_insert(d);
	printStuff(d);								// header's functions
	return 0;
}

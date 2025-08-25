/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_list.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:51:50 by totommi           #+#    #+#             */
/*   Updated: 2025/08/25 17:18:57 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge_insert.h"

int	main(int argc, char *argv[])
{
	std::list<unsigned int>	l;

	/* VECTOR */
	populateContainer(l, argv + 1, argc);		// header's functions
	// if (check4duplicates(v))					// header's functions
	// 	return 1;
	merge_insert(l);
	printStuff(l);								// header's functions
	return 0;
}

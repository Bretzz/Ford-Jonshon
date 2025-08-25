/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_sort.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:38:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/08/25 16:41:04 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge_insert.h"
#include <algorithm>

int main(int argc, char *argv[])
{
	std::vector<unsigned int>	v;

	populateContainer(v, argv + 1, argc);		// header's functions
	std::sort(v.begin(), v.end());
	printStuff(v);								// header's functions
    return 0;
}

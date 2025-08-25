/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_insert.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:56:37 by totommi           #+#    #+#             */
/*   Updated: 2025/08/25 00:32:19 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MERGE_INSERT_H
# define MERGE_INSERT_H

# include <sys/types.h>
# include <iostream>
# include <vector>

void	merge_insert(std::vector<int>& v, size_t size = 1);

template <class T>
static void printStuff(const T& c, int size = 1)
{
	for (size_t i = 0; i < c.size(); ++i)
	{
		if (size != 1 && i % size == size - 1)
			std::cout << "[";
		std::cout << c[i];
		if (size != 1 && i % size == size - 1)
			std::cout << "]";
		std::cout << " ";
	}
}

#endif
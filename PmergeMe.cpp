/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:24:17 by topiana-          #+#    #+#             */
/*   Updated: 2025/08/25 14:35:31 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <vector>

# ifndef RAND_SEED
#  define RAND_SEED 1234
# endif

static void fillRandNums(std::vector<unsigned int>& v, unsigned long n)
{
	unsigned long i = 0;

	std::cout << "Generating sequence of " << n << "numbers... ";
	while (i < n) {
		unsigned int r = 1 + (std::rand() % 4294967296);
		size_t j = 0;
		while (j < v.size()) {
			if (r == v[j])
				break ;
			++j;
		}
		if (j == v.size())
			++i;
	}
	std::cout << "DONE" << std::endl;
}

/* executes all the files passed writing to their stdin
a sequence of random numbers betwee 1 and 4294967296,
checking for the time of execution */
int	main(void)
{
	std::srand(RAND_MAX);	/* seeding the rand */

	std::vector<unsigned int>	nums;
	fillRandNums(nums, 100000);
}

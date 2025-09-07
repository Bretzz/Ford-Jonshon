/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:24:17 by topiana-          #+#    #+#             */
/*   Updated: 2025/09/07 19:12:31 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <vector>

# ifndef RAND_SEED
#  define RAND_SEED 1234
# endif

void	populateString(std::string& s, char *argv[], int argc = 2)
{
	unsigned int i = 0;

	if (argc == 2)
	{
		s.assign(argv[0]);
	}
	else
	{
		while (argv[i] != NULL)
		{
			s.append(argv[i]);
			s.append(" ");
			++i;
		}
	}
}

#include <sstream>	// string stream

static void fillRandNums(std::string& s, unsigned long n)
{
	unsigned long 				i = 0;
	std::vector<unsigned int>	v;
	std::stringstream			stream;

	std::cout << "Generating sequence of " << n << " numbers... "; std::cout.flush();
	while (i < n) {
		unsigned int r = 1 + (std::rand() % 2147483647);
		size_t j = 0;
		while (j < v.size()) {
			if (r == v[j])
				break ;
			++j;
		}
		if (j == v.size())
		{
			stream << r << " ";
			v.push_back(r);
			++i;
		}
	}
	s.assign(stream.str());
	std::cout << " DONE" << std::endl;
}

#include <cstdio>
#include <unistd.h>
#include <sys/time.h>	// gettimeofday

static long long nowUs(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return static_cast<long long>(tv.tv_sec) * 1000000 + tv.tv_usec;
}

int strcount(const std::string& str, int c)
{
	int		count = 0;
	size_t	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
			++count;
		++i;
	}
	return count;
}

#include <algorithm> // std::replace

/* executes the program found at 'execpath' and prints the time */
static int	timedExec(const std::string& execpath, std::string ARG, const char separator = ' ')
{
	/* formatting requierements */
	std::replace(ARG.begin(), ARG.end(), ' ', separator);

	// open a process for writing
	FILE* pipe = popen((execpath + " > " + execpath + ".out" + " 2>&1").c_str(), "w");
	
	if (!pipe) {
		std::perror("popen failed");
		return 1;
	}

	const long long start = nowUs();		/* CLOCK IN */


	// Send data to the process
	write(pipe->_fileno, ARG.c_str(), ARG.length());

	/* MERGING... */

	// Close pipe and wait for the process to finish
	int status = pclose(pipe);
	
	const long long end = nowUs();		/* CLOCK OUT */

	if (!WIFEXITED(status)) {
		std::cout << "Process terminated abnormally." << std::endl;
	}

	// Time to process a range of 3000 elements with std::[..] : 62.14389 us
	std::cout << "Time to process a range of " << strcount(ARG, ' ') + 1 << " elements with std::" << execpath.substr(execpath.find('_') + 1) << " : " << (end - start) << " us (" << (end - start) / 1000 << " ms)" << std::endl;
	return 0;
}

/* '1 2 3' */
static int	normalize(std::string& str)
{
	size_t	i = 0;
	int		f = 0;	// 0 = spaces, 1 = nums

	while (str[i] != '\0')
	{
		if (str[i] != ' ' && !std::isdigit(str[i]))
		{
			std::cerr << "Error: invalid input '" << str[i] << "'" << std::endl;
			return 1;
		}
		if (f == 0)
		{
			if (str[i] == ' ')
			{
				str.erase(str.begin() + i);
				continue ;
			}
			if (str[i] != ' ')
				f = 1;
		}
		else if (f == 1)
		{
			if (str[i] == ' ')
				f = 0;
		}
		++i;
	}
	if (*(str.end() - 1) == ' ')
		str.resize(str.size() - 1);
	return 0;
}

static void	printLargeStr1(const std::string& lstr)
{
	std::cout << lstr.substr(0, 20);
	if (lstr[19] == ' ')
		return ;
	std::cout << lstr.substr(20, lstr.find(' ', 19) - 19);
}

static void	printLargeStr2(const std::string& lstr)
{
	size_t	i = lstr.size() - 21;
	while (i > 0 && lstr.at(i) != ' ')
		--i;
	std::cout << lstr.substr(i);
}

/* prints 50 chars lstr, 20 after, without breaking numbers */
static void	printLargeStr(const std::string& lstr)
{
	if (lstr.size() <= 40)
	{
		std::cout << lstr << std::endl;
		return ;
	}
	printLargeStr1(lstr);
	std::cout << "[...]";
	printLargeStr2(lstr);
	std::cout << std::endl;
}

std::string raw_getline(std::istream& in) {
    std::string line;
    std::getline(in, line);  // C++98-compatible
    return line;
}

#include <fstream>

static int	sortCheck(void)
{
	int				err = 0;
	std::string		sorted;
	std::ifstream	file;

	/* VERIFICATION */
	file.open("./PmergeMe_sort.out");
	if (file){
		std::getline(file, sorted);
		file.close();
	}
	else
	{
		std::cerr << "Error: opening verification output file" << std::endl;
		return 1;
	}

	std::string	out;
	
	/* VECTOR */
	file.open("./PmergeMe_vector.out");
	if (file){
		std::getline(file, out);
		if (sorted != out)
		{
			std::cout << "Vector isn't sorted correctly" << std::endl;
			++err;
		}
		file.close();
	}
	else
	{
		if (errno != ENOENT)
			std::cerr << "Error: opening list output file" << std::endl;
	}

	/* DEQUE */
	file.open("./PmergeMe_deque.out");
	if (file){
		std::getline(file, out);
		if (sorted != out)
		{
			std::cout << "Deque isn't sorted correctly" << std::endl;
			++err;
		}
		file.close();
	}
	else
	{
		if (errno != ENOENT)
			std::cerr << "Error: opening list output file" << std::endl;
	}

	/* LIST */
	file.open("./PmergeMe_list.out");
	if (file){
		std::getline(file, out);
		if (sorted != out)
		{
			std::cout << "List isn't sorted correctly" << std::endl;
			++err;
		}
		file.close();
	}
	else
	{
		if (errno != ENOENT)
			std::cerr << "Error: opening list output file" << std::endl;
	}

	if (err == 0)
	{
		std::cout << "✅ Output is correctly sorted!" << std::endl;
		return 0;
	}
	return 1;
}

#include "PmergeMe.hpp" // populateContainer, check4Duplicates

static int	checkDups(const std::string& nums)
{
	std::vector<unsigned int>	v;

	populateContainer(v, nums.c_str());
	return check4duplicates(v);
}

/* check if there is a number bigger than 2147483647 */
static int	checkMax(const std::string& nums)
{
	unsigned int	len;

	len = 0;
	for (size_t i = 0; i < nums.length(); ++i) {
		if (std::isspace(nums[i]))
			len = 0;
		else
			++len;
		if (len > 10)
		{
			std::cout << "Error: Input number too big: " << nums.substr(i - len + 1, len) << std::endl;
			return 1;
		}
		if (len == 10 && std::atol(&nums[i - len]) > 2147483647)
		{
			std::cout << "Error: Input number too big: " << nums.substr(i - len, len) << std::endl;
			return 1;
		}
	}
	return 0;
}

/* executes all the files passed writing to their stdin
a sequence of random numbers betwee 1 and 4294967296,
checking for the time of execution */
int	main(int argc, char *argv[])
{
	std::srand(RAND_SEED);	/* seeding the rand */

	std::string	nums;

	if (argc == 1)
		fillRandNums(nums, 3000);				// no input, generate one
	else
		populateString(nums, argv + 1, argc);	// given input

	/* NORMALIZE STR */
	if (normalize(nums))
		return 1;
	
	std::cout << "normalized" << std::endl;

	/* CHECK >2147483647 */
	if (checkMax(nums))
		return 1;

	/* CHECK DUPICATES */
	if (checkDups(nums))
		return 1;

	/* CLEAR OUTPUT FILES */
	std::remove("./PmergeMe_deque.out");
	std::remove("./PmergeMe_vector.out");
	std::remove("./PmergeMe_list.out");
	std::remove("./PmergeMe_sort.out");

	/* PRINT BEFORE */
	std::cout << "Before : "; std::cout.flush();
	printLargeStr(nums);
	
	/* EXEC SORTINGS */
	timedExec("./PmergeMe_deque", nums);
	timedExec("./PmergeMe_vector", nums);
	if (strcount(nums, ' ') <= 20000)
		timedExec("./PmergeMe_list", nums);
	timedExec("./PmergeMe_fortran", nums);
	timedExec("./PmergeMe_sort", nums);

	/* PRINT AFTER */
	std::ifstream file("./PmergeMe_vector.out");
	if (file){
		std::cout << "After: "; std::cout.flush();
		printLargeStr(raw_getline(file));
		file.close();
	}
	else
	{
		std::cerr << "Error: opening output file" << std::endl;
		return 1;
	}

	/* CHECK OUTPUT VALIDITY */
	sortCheck();
	return 0;
}

/*
= SUBJECT OUTPUT =
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::[..] : 0.00031 us
Time to process a range of 5 elements with std::[..] : 0.00014 us
*/

#include "includes/ether.hpp"

//c++ -Wextra -Werror -Wall -g test_buffer.cpp

int	tester(bool test_edo_bool);

int	main()
{
	bool	test_edo_bool = false;
	return (tester(test_edo_bool));
}

int	test_ale(std::string file, std::vector<char *> &packages, size_t size);
int test_edo();

int	tester(bool test_edo_bool)
{
	size_t				size = 255;
	std::vector<char *>	packages(0);

	for (int i = 0; i != 1000; i++)
	{
		if (test_edo_bool == false)
			test_ale("srcs/main.cpp", packages, size);//qui tutto ok
		else
			test_edo();
	}
	if (test_edo_bool == true)
		return (0);
	for (std::vector<char *>::iterator it = packages.begin(); it != packages.end(); it++)
		delete [] (*it);//crasha alla seconda chiamata di delete
	return (0);
}

//-------------------------------------------------------------------------

int test_edo()
{
    std::vector<char>   pack(0);
    int                 bytes = 1;
    size_t              total = 0;
    size_t              size = 1024;
    char                buff[size];
    int                 fd = open("srcs/main.cpp", O_RDONLY);
    
    if (fd == -1)
    {
        std::cout << "no file\n";
        return (0);
    }
    bytes = read(fd, buff, size);
    while (bytes > 0)
    {
        pack.insert(pack.end(), buff, buff + bytes);
        bytes = read(fd, buff, size);
        total += bytes;
    }
    size = total;
    return (0);
}

//-------------------------------------------------------------------------

void	alloc(std::vector<char *> &packages, size_t pos, size_t len);
void	create(int fd, std::vector<char *> &packages, size_t &size);
void	test_print(std::string name, std::vector<char *> &packages, size_t &size);

int	test_ale(std::string file, std::vector<char *> &packages, size_t size)
{
	int	fd = open(file.c_str(), O_RDONLY);
	if (fd == -1)
		return (1);
	create(fd, packages, size);
	test_print(file, packages, size);
	close(fd);
	return (0);
}

/*
	prende il vector di pacchetti
	alloca solo se c'è bisogno
*/
void	alloc(std::vector<char *> &packages, size_t pos, size_t len)
{
	//std::cout << "requested pos: " << pos;
	if (pos < packages.size() && packages[pos] != NULL)
	{
		packages[pos][0] = 0;
		return ;
	}
	//std::cout << "\n\033[31m|ALLOCAZIONE numero" << pos << "!|\n\033[0m";
	if (pos < packages.size())
		packages[pos] = new char[len + 2];
	else
		packages.push_back(new char[len + 2]);
}

/*
	legge tutto l'fd, lo scrive sul vector di pacchetti
*/
void	create(int fd, std::vector<char *> &packages, size_t &size)
{
	int		bytes = 1;
	size_t	total = 0;
	size_t	i = 0;

	if (fd == -1)
		return (std::cout << "no file\n", (void)0);
	alloc(packages, 0, size);
	bytes = read(fd, packages[0], size - 1);//seconda chiamata, legge spazzatura
	while (bytes > 0)
	{
		total += bytes;
		alloc(packages, ++i, size);
		bytes = read(fd, packages[i], size);
	}
	size = total;
	if (i < packages.size())
		packages[i][0] = 0;
}

void	test_print(std::vector<char *> &packages, size_t &size);

void	test_print(std::string name, std::vector<char *> &packages, size_t &size)
{
	return ;
	std::cout << name << " \033[32mPRINT\n--------------\033[0m\n";
	test_print(packages, size);
	std::cout << name << " \033[32mEND\n--------------\033[0m\n";
}

void	test_print(std::vector<char *> &packages, size_t &size)
{
	int	n_package = 0;

	return ;
	std::cout << "size: " << size << std::endl;
	for (std::vector<char *>::iterator it = packages.begin(); it != packages.end(); it++)
	{
		if ((*it)[0] == 0)
			break ;
		std::cout << "\n\033[33mpackage number \033[0m" << n_package++ << std::endl;
		for (int i = 0; (*it)[i]; i++)
			std::cout << (*it)[i];
	}
	std::cout << std::endl;
	
}

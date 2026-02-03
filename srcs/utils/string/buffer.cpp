#include "../../../includes/ether.hpp"

//c++ -Wextra -Werror -Wall -g test_buffer.cpp

static void	alloc_packets(std::vector<char *> &packets, size_t pos, size_t len);
//static void	print_packets(std::vector<char *> &packets, size_t &size);

int	ft_recv(int fd, std::vector<char *> &packets, size_t packet_size)
{
	int		bytes = 1;
	size_t	total = 0;
	size_t	i = 0;

	if (fd == -1)
		return (-1);
	alloc_packets(packets, 0, packet_size);
	bytes = recv(fd, packets[0], packet_size - 1, 0);
	while (bytes > 0)
	{
		if (bytes == -1)
			return (-1);
		total += bytes;
		alloc_packets(packets, ++i, packet_size);
		bytes = read(fd, packets[i], packet_size - 1);
	}
	if (i < packets.size())
		packets[i][0] = 0;
	return (total);
}

void	ft_to_string(std::vector<char *> &packets, std::string &request_buff)
{
	for (std::vector<char *>::iterator it = packets.begin(); it != packets.end(); it++)
	{
		if ((*it)[0] == 0)
			break ;
		request_buff += (*it);
	}
}

//allocs only when needed
static void	alloc_packets(std::vector<char *> &packets, size_t pos, size_t len)
{
	if (pos < packets.size() && packets[pos] != NULL)
	{
		packets[pos][0] = 0;
		return ;
	}
	if (pos < packets.size())
		packets[pos] = new char[len + 2];
	else
		packets.push_back(new char[len + 2]);
}

/*
static void	print_packets(std::vector<char *> &packets, size_t &size)
{
	int	n_package = 0;

	std::cout << "size: " << size << std::endl;
	std::cout << "number of packets: " << size << std::endl;
	for (std::vector<char *>::iterator it = packets.begin(); it != packets.end(); it++)
	{
		if ((*it)[0] == 0)
			break ;
		std::cout << "\n\033[33mpackage number \033[0m" << n_package++ << std::endl;
		for (int i = 0; (*it)[i]; i++)
			std::cout << (*it)[i];
	}
	std::cout << std::endl;
}*/

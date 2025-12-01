
#include "hpp/Server.hpp"
#include "../includes/ether.hpp"

static void	print_fd(struct pollfd *p)
{
	for (int i = 0; i < 6; i++)
	{
		std::cout << i << std::endl;
		std::cout << "fd:\t" << p[i].fd << "\nevents:\t" << p[i].events << std::endl;
		std::cout << "revents:\t" << p[i].revents << std::endl << std::endl;
	}
}

int main() //da aggiungere ac e av
{
	int ready;
	int	times = 10;

	(void)ready;
	try
	{
		Server server;
		while (times--)
		{
			ready = poll(server.getAddrs(), server.getAddrSize(), -1);
			if (ready < 0)
				std::cout << "Mannaggia alla madonna poll non va\n";
			// std::cout << "ARRIBA ANDALE ANDALE" << std::endl;
			print_fd(server.getAddrs());
			if (server.getAddrs()[0].revents & POLLIN)
			{
				std::cout << "Mega Rayquaza\n";
				server.addSocket(); // aggiunge al vector il nuovo socket del client
				std::cout << "ARRIVA 2" << std::endl;
			}
			std::cout << "ARRIVA 3" << std::endl;
			server.checkForConnection();
			sleep(1);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
//
}
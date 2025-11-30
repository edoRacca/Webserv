
#include <iostream>
#include <string>
#include <poll.h>
#include <sys/socket.h>

int main()
{
	// @brief socket(DOMAIN, TYPE, PROTOCOL)
	// se PROTOCOL == 0 allora viene scelto in automatico
	// restituisce il file descriptor oppure -1 in caso di errori
	int server_fd = socket(AF_INET, SOCK_STREAM, 0); // La flag CALZA_STREAM è importante
	if (!server_fd)
		std::cout << "Palle sudate non e andato a buon fine" << std::endl;
	
}

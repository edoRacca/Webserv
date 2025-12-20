#include "../../includes/ether.hpp"


//On success: 	returns the length of the ip address.
//On failure:	returns 0.
int	valid_ip_address(std::string addr)
{
	size_t	dots;
	int		len;

	dots = 0;
	for (len = 0; addr[len] && addr[len] != ':'; len++)
	{
		if (addr[len] != '.' && std::isdigit(addr[len]) == 0)
			return (false);
		dots += (addr[len] == '.');
	}
	if (dots != 3)
		return (false);
	if (addr.find_first_of(".:\0", 1) > 3)
		return (false);
	for (int i = 4; i; i--)
	{
		if (std::atoi(addr.c_str()) > UINT8_MAX || (std::atoi(addr.c_str()) != 0 && addr[0] == '0'))
			return (false);
		while (addr[0] != '.' && addr[0] != ':' && !addr.empty())
			addr.erase(0, 1);
		if (addr[0] == '.' && addr.find_first_of(".:\0", 1) > 3)
			return (false);
		if (addr[1] && (addr[1] == '.' || addr[1] == ':'))
			return (false);
		addr.erase(0, 1);
	}
	return (len);
}

// listen 127.0..:9090
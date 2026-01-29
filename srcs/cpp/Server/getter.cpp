#include "../../hpp/Server.hpp"

// NOTE - restituisce il vettore di strutture di poll sotto forma di array
struct pollfd *Server::getAddrs(void)
{
	return (this->_addrs.data());
}

size_t	Server::getAddrSize(void) const
{
	return (this->_addrs.size());
}

int	Server::getServerNum() const
{
	return (this->_server_num);
}

SrvNameMap		&Server::getSrvNameMap() const
{
	return (*this->_srvnamemap);
}

const std::string	&Server::getProtectedFiles() const
{
	return (this->_protected_files);
}

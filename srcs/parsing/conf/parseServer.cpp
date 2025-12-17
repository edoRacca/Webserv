#include "../../../includes/ether.hpp"
#include "../../hpp/Conf.hpp"

//NOTE - Allowed server instructions
/*
	//FIXME - aggiungere
*/
void	confParseServer(Conf &conf, std::vector<std::string> list, int line)
{
	(void)conf, (void)list, (void)line;
	//gestire i vari casi
	std::cerr << "\033[31mConf server, line " << line << ":\t\
	unrecognized instruction:\t" << list[0] << "\n\033[0m";
}

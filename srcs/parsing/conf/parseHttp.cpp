#include "../../../includes/ether.hpp"
#include "../../hpp/Conf.hpp"

//NOTE - Allowed http instructions
/*
	//FIXME - aggiungere
*/
void	confParseHttp(Conf &conf, std::vector<std::string> list, int line)
{
	(void)conf, (void)list, (void)line;
	std::cerr << "\033[31mConf http, line " << line << ":\t\
	unrecognized instruction:\t" << list[0] << "\n\033[0m";
}

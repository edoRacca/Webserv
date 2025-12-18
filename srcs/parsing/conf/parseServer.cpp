#include "../../../includes/ether.hpp"
#include "../../hpp/Conf.hpp"

//NOTE - Allowed server instructions
/*
	//FIXME - aggiungere gestione parametri (vedi struttura.md)
*/
void	confParseServer(Conf &conf, std::vector<std::string> list, int line)
{
	(void)conf, (void)list, (void)line;
	//gestire i vari casi
	if (list[0] == "server_name")
		;//
	else if (list[0] == "listen")
		;//
	else if (list[0] == "root")
		;//
	else if (list[0] == "index")
		;//
	else if (list[0] == "client_max_body_size")
		;//
	else
	{
		std::cerr << "\033[31mConf server, line " << line << ":\t\
		unrecognized instruction:\t" << list[0] << "\n\033[0m";
	}
}

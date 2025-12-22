#include "../../../includes/ether.hpp"
#include "../../hpp/Conf.hpp"

void		instructionError(std::vector<std::string>&list, int line, std::string s);
void		instructionWarning(std::vector<std::string> &list, int line, std::string s);

//NOTE - Allowed http instructions
/*
	//FIXME - aggiungere
*/
void	confParseHttp(Conf &conf, std::vector<std::string> list, int line)
{
	(void)conf, (void)list, (void)line;
	instructionError(list, line, "unrecognized instruction");
}

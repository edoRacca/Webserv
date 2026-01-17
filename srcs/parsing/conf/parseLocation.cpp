#include "../../../includes/ether.hpp"
#include "../../hpp/Conf.hpp"

void		instructionError(std::vector<std::string>&list, int line, std::string s);
void		instructionWarning(std::vector<std::string> &list, int line, std::string s);
static void	parseAlias(Conf &conf, std::vector<std::string> &list, int line);
static void	parseRoot(Conf &conf, std::vector<std::string> &list, int line);
static void parseCgiParam(Conf &conf, std::vector<std::string> &list, int line);
static void parseReturn(Conf &conf, std::vector<std::string> &list, int line);

//NOTE - Allowed location instructions
/*
	//FIXME - aggiungere
*/
void	confParseLocation(Conf &conf, std::vector<std::string> list, int line)
{
	if (list[0] == "alias")
		parseAlias(conf, list, line);
	else if(list[0] == "root")
		parseRoot(conf, list, line);
	else if (list[0] == "fastcgi_param")
		parseCgiParam(conf, list, line);
	else if (list[0] == "return")
		parseReturn(conf, list, line);
	else if (list[0] == "autoindex")
		conf.getLocationBlock().autoindex = true;
	else if (list[0] == "error_page")
		; // da gestire come return -> error_page <code> [uri error page]
	else
		instructionError(list, line, "unrecognized instruction");
}

static void	parseAlias(Conf &conf, std::vector<std::string> &list, int line)
{
	if (list.size() != 2)
		instructionError(list, line, "wrong parameters number for alias instruction");
	if (valid_directory(list[1]) == false)
		instructionError(list, line, "invalid alias path");
	if (*list[1].rbegin() != '/')
		instructionError(list, line, "alias must finish with /");
	conf.getLocationBlock().alias = list[1];
}

static void	parseRoot(Conf &conf, std::vector<std::string> &list, int line)
{
	if (list.size() != 2)
		instructionError(list, line, "wrong parameters number for root instruction");
	if (valid_directory(list[1]) == false)
		instructionError(list, line, "invalid root path");
	conf.getLocationBlock().root = list[1];
}

static void parseCgiParam(Conf &conf, std::vector<std::string> &list, int line)
{
	size_t	type_size;
	size_t	path_size;

	if (list.size() != 3)
		instructionError(list, line, "wrong parameters number for fastcgi_params instruction");
//		.cgi	/path.cgi
//		1)	controllare che sia estensione valida (eseguibile compilato, python, php)
	if (list[1] != ".php" && list[1] != ".py" && list[1] != "exec")
		instructionError(list, line, "invalid CGI extension");
//		2)	controllare che path finisca con cgi
	type_size = list[1].size();
	path_size = list[2].size();
	if (path_size < type_size)
		instructionError(list, line, "invalid CGI path");
	if (list[1] != list[2].substr(path_size - type_size, type_size))
		instructionError(list, line, "CGI extension doesn't match path");
//		3)	controllare che path esista
	if (valid_file(list[2]) == false)
		instructionError(list, line, "invalid CGI path");
	std::pair<std::string, std::string> p(list[1], list[2]);
	conf.getLocationBlock().cgiparam.push_back(p);
}

/*
return code [text]
return code URL
return URL
return code

return 12
*/

static bool checkValidCode(int code)
{
	int	valid_codes[] = VALID_HTTP_CODES;
	
}

static void parseReturn(Conf &conf, std::vector<std::string> &list, int line)
{
	bool is_code_valid = charFinder(list[1], std::isdigit);
	bool code;

	if (list.size() < 2 || list.size() > 3)
		instructionError(list, line, "return needs this syntax:	return code [text] |"\
		"return code URL | return URL | return code\n");
	if (list.size() == 2) //URL o code
	{
		if (!is_code_valid || !code)
		{
			conf.getLocationBlock().ret_uri = list[1];
			conf.getLocationBlock().ret_code = 302;
		}
		else if (code >= 300 && code < 309)
			instructionError(list, line, "return code between 300 and 308 must have an uri\n");
		else
			conf.getLocationBlock().ret_code = code;
		return ;
	}
	if (code >= 300 && code < 309)
		instructionError(list, line, "return code between 300 and 308 must have an uri\n");
		// conf.getLocationBlock().ret_code = code;
		// conf.getLocationBlock().ret_uri = list[2];
}

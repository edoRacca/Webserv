
#include "../../../includes/ether.hpp"
#include "../../hpp/Conf.hpp"

int	newOpenBlock(Conf &conf, std::vector<std::string> &list, int *i)
{
	if (list.size() != 1)
		throw Conf::ConfException("Error in format configuration in line " + *i);
	if (list[0] == "http" && conf.getHttp() == false)
		conf.setHttp(true);
	else
		throw Conf::ConfException("Impossible to open http block into another in line " + *i);
	return (1);
}

void	parseMain(Conf &conf, std::ifstream &fd) 
{
	std::string					line;
	std::string					token;
	std::vector<std::string>	list;
	int i = 0;

	(void)conf;
	while (std::getline(fd, line))
	{
		i++;
		while (!line.empty())
		{
			std::cout << "\033[33mLine " << i << ": " << line << "\033[0m" << std::endl;
			line = removeWhitespaces(line);
			if (line[0] == '{')
				newOpenBlock(conf, list, &i);
			// else if (line[0] == '}')
				// newOpenBlock();
			// else if (line[0] == ';')
				// newOpenBlock();
			else 
				token = line.substr(0, find_first_special_char(line));
			if (!token.empty())
				list.push_back(token);
			if (!list.empty())
				std::cout << "\033[34mlist: " << (*list.rbegin()) << "\033[0m" << std::endl;
			line = line.substr(find_first_special_char(line));
			token = "";
		}
	}
	for (size_t i = 0; i < list.size(); ++i) 
    	std::cout << list[i] << " \n";
}

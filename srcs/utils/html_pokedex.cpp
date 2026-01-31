#include "../../includes/ether.hpp"

//NOTE - Ale: continuo domani

/*
#define ID_DATA 0 
#define ID_FIELD 1 
#define ID_HREF 2
#define ID_STATIC 3
#define HTML_NUMBER 4
#define HTML_FILES "data.html", "field.html", "href_val.html", "static_val.html"

static std::string	parse_data(std::ifstream html_files[4], std::string &output);
static bool			get_files(std::ifstream html_files[4]);

std::string	createHtmlPokedex(std::string &key, std::string &output)
{
	std::ifstream	html_files[4];
	std::string		html;

	if (get_files(html_files))
		return ("<p>missing files!</p>");
	std::getline(html_files[ID_DATA], html, '\0');
	find_and_replace(html, "{KEY}", key);
	find_and_replace(html, "{DATA}", parse_data(html_files, output));
	return (html);
}

//open html files
static bool	get_files(std::ifstream html_files[4])
{
	std::string		html_path("www/cgi-bin/pokedex/html/");
	std::string		html_names[] = {HTML_FILES, NULL};

	for (int i = 0; i != HTML_NUMBER; i++)
	{
		html_files[i].open(html_path.append(html_names[i]));
		if (html_files[i].fail())
		{
			std::cerr << "cannot open " << html_names[i] << "\n";
			return (1);
		}
	}
	return (0);
}

static std::string	parse_data(std::ifstream html_files[4], std::string &output)
{
	std::stringstream			output_stream;
	std::string					html_str[4];
	std::string					data;
	std::string					line;
	std::string					field;
	std::vector<std::string>	values;

	std::getline(html_files[ID_FIELD], html_str[ID_FIELD], '\0');
	output_stream << output;
	while (std::getline(output_stream, line, '|'))
	{
		if (line == "|" || line.find(':') == std::string::npos)
			continue ;
		field = line.substr(0, line.find(':'));
		line.erase(0, field.length() + 1);
		vect_split(values, line, ',');
		find_and_replace(data, "{FIELD}", field);
		find_and_replace(data, "{HTML_VAL}", );
	}
}*/


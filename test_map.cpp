#include <map>
#include <string>
#include <iostream>

int	main1(void)
{
	std::map<std::string, std::string>	map;

	map["gay1"] = "";
	map["gay2"] = "";
	map["gay3"] = "";

	if (map.find("gay1") != map.end())
		std::cout << "gay1 c'e" << std::endl;
	else
		std::cout << "gay1 assente" << std::endl;
	if (map.find("gay4") != map.end())
		std::cout << "gay4 c'e" << std::endl;
	else
		std::cout << "gay4 assente" << std::endl;
	return (0);
}

/*
Host: localhost:8080
User-Agent: curl/8.17.1-DEV
Accept: /
Content-Length: 10
Content-Type: application/x-www-form-urlencoded
*/
int	main2(void)
{
	std::map<std::string, std::string>	map;

	map["Host"] = "Gabibbo";
	map["User-Agent"] = "";
	map["Accept"] = "";
	map["Content-Length"] = "";
	map["Content-Type"] = "";

	if (map.find("Host") != map.end())
		std::cout << map["Host"]  << std::endl;
	else
		std::cout << "gay1 assente" << std::endl;
	return (0);
}

/*
Host: localhost:8080
User-Agent: curl/8.17.1-DEV
Accept: /
Content-Length: 10
Content-Type: application/x-www-form-urlencoded
*/
int	main(int ac, char **av)
{
	std::map<std::string, std::string>	map;

	if (ac < 2)
		return (std::cout << "inserisci un field come Host: localhost:8080\n", 1);
	map["Host"] = "";
	map["User-Agent"] = "";
	map["Accept"] = "";
	map["Content-Length"] = "";
	map["Content-Type"] = "";

	std::string	s(av[1]);
	if (map.find(s.substr(0, s.find(':'))) != map.end())
		std::cout << "gay1 c'e" << std::endl;
	else
		std::cout << "gay1 assente" << std::endl;
	//aggiungi chiave
	return (0);
}

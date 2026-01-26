#include "../../includes/ether.hpp"

//returns 1 if directory is valid, else 0
bool	valid_directory(std::string directory)
{
	DIR		*dir_fd;
	bool	valid = true;

	if (directory == "/")
		return (valid);
	directory = directory.substr(directory[0] == '/');
	dir_fd = opendir(directory.c_str());
	valid = (dir_fd != NULL);
	return (closedir(dir_fd), valid);
}

//returns 1 if directory is valid, else 0
bool	valid_file(std::string file)
{
	file = file.substr(file[0] == '/');
	std::ifstream	fd(file.c_str());

	return (fd.fail() == 0);
}

//SECTION - request uri modifiers

void	add_root_alias(std::string &file, std::string root, std::string alias)
{
	std::cout << "append_root_alias" << std::endl;
	std::cout << "BEFORE" << file << std::endl;

	if (alias.empty() == false)
	{
		if (file.find(alias) != std::string::npos)
			file.replace(0, alias.length(), alias);

	}
	else if (root.empty() == false)
	{
		if (root)
		file = root + file;
	}
	else
		std::cout << "no root or alias\n";
	std::cout << "AFTER" << file << std::endl;
}

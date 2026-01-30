
#include "../../includes/ether.hpp"
#include "../hpp/Request.hpp"

typedef struct s_conf_server	t_conf_server;
typedef struct s_conf_location	t_conf_location;

//SECTION - app root/alias to a file

//DO NOT USE THIS USE OTHERS OVERLOAD
void	url_rooting(std::string &file, std::string &root)
{
	// std::cout << "append_root_alias" << std::endl;
	// std::cout << "BEFORE " << file << std::endl;

	if (root.empty() == true)
		return (std::cout << "no root\n", (void)0);
	normalize_url(&root);
	file = root + file;
	return ;
}

//append root or alias to a file
//this overload appends SERVER root
std::string	url_rooting(std::string file, t_conf_server &srv)
{
	url_rooting(file, srv.root);
	return (file);
}

//append root or alias to a file
//this overload appends: 
// if (srv.location.count(loc) == OK) --> append LOCATION alias/root
// else append SERVER root
std::string	url_rooting(std::string file, t_conf_server &srv, std::string loc)
{
	if (srv.location.count(loc) != 0)
	{
		if (srv.location[loc].alias == true)
			file.clear();
		url_rooting(file, srv.location[loc].root);
	}
	else
		url_rooting(file, srv.root);
	return (file);
}

//append root or alias to a file
//this overload appends LOCATION alias/root
std::string	url_rooting(std::string file, t_conf_location &loc)
{
	if (loc.alias == true)
		file.clear();
	url_rooting(file, loc.root);
	return (file);
}

//SECTION - normalize_url

//normalize an url in this form: /dir/dir/file/
//@url: address of url
//----------------------
//@ret: void
void	normalize_url(std::string *url)
{
	if ((*url)[0] == '/')
		(*url).erase(0, 1);
	if ((*url).rbegin()[0] != '/')
		(*url).push_back('/');
}

//normalize an url in this form: /dir/dir/file/
//@url: copy of url
//----------------------
//@ret: new url
std::string	normalize_url(std::string url)
{
	normalize_url(&url);
	return (url);
}

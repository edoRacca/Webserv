#include "../../hpp/Server.hpp"

static void execute_delete(Client &client, std::string &body, std::fstream *file);
static int	check_delete(Client &client, std::string &body, Server &srv, std::fstream *file);

void	Server::deleteMethod(Client &client, std::string &body, std::fstream *file)
{
	if (check_delete(client, body, *this, file) != 0)
		return ;
	(*file).close();
	execute_delete(client, body, file);
}

static int	check_delete(Client &client, std::string &body, Server &srv, std::fstream *file)
{
	int					status_code;
	bool				dns;
	bool				autoindex;
	std::string			url;
	const std::string	&protected_files(srv.getProtectedFiles());

	status_code = client.getRequest().getStatusCode();
	dns = client.getRequest().getDnsErrorBool();
	autoindex = client.getRequest().getAutoIndexBool();
	url = client.getRequest().getUrl();
	if (status_code != 200 || dns == true || autoindex == true)
	{
		if (body.empty() == true)
			body = file_opener(*file);
	}
	else if (protected_files.find(url) != std::string::npos)
	{
		(*file).close();
		(*file).open("www/var/errors/403.html");
		body = file_opener(*file);
		client.getRequest().fail(HTTP_CE_FORBIDDEN);
	}
	else
		return (0);
	return (1);
}

static void execute_delete(Client &client, std::string &body, std::fstream *file)
{
	std::string url;
	
	url = client.getRequest().getUrl();
	if (url.rbegin()[0] == '/')
		url.erase(url.find_last_of('/'), 1);
	if (std::remove(url.c_str()) == 0)//file cancellato
	{
		(*file).open("www/var/2xx.html");
		body = file_opener(*file, "delete_method: cannot open file on success");
		find_and_replace(body, "{MSG}", "file " + url + " deleted successfully!");
		find_and_replace(body, "{CODE}", HTTP_OK_NO_CONTENT);
		return ;
	}//cancellazione fallita
	if (valid_directory(url))
	{
		client.getRequest().fail(HTTP_CE_FORBIDDEN);
		(*file).open("www/var/errors/special/403_DirNotEmpty.html");
	}
	else
	{
		client.getRequest().fail(HTTP_SE_INTERNAL);
		(*file).open("www/var/errors/special/500_CannotDeleteFile.html");
	}
	body = file_opener(*file, "delete_method: cannot open file on error");
}

int	Server::postMethod()
{
	return (0);
}

#include "../../hpp/Server.hpp"

dirent	*findUrlDirectory(std::string url);

//NOTE - crea una struct pollfd con l'fd del client, dato da accept()
struct pollfd	setupPollFd(int client)
{
	struct pollfd s;

	s.fd = client;
	s.events = POLLIN;
	s.revents = 0;
	return (s);
}

// NOTE - crea un socket listen per il server che vogliamo creare
struct pollfd	createServerSock(int port_n)
{
	struct sockaddr_in	address;
	int					server_fd;
	struct pollfd		srv;
	int					opt = 1;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
		throw std::runtime_error("\033[31mSocket ha fallito.\033[0m");
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;// 7F000001 
	address.sin_port = htons(port_n);
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	fcntl(server_fd, F_SETFL, O_NONBLOCK);
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) != 0)
	{
		close(server_fd);
		return (CONNECTION_FAIL);
	}
	if (listen(server_fd, MAX_CONNECTION) != 0)
	{
		close(server_fd);
		throw std::runtime_error("\033[31mIl server ha le orecchie tappate.\033[0m");
	}
	srv.fd = server_fd;
	srv.events = POLLIN;
	srv.revents = 0;
	return (srv);
}

std::string	fileToString(std::string filename)
{
	std::ifstream	fd(filename.c_str());
	std::string		file;

	if (fd.fail())
		abort();
	std::getline(fd, file, '\0');
	return (file);
}


/*
	@client: reference to client object
	@body: reference to response body

	exece
*/
void	Server::deleteMethod(Client &client, std::string &body)
{
	std::string		url = client.getRequest().getUrl();
	std::fstream	file;
	int				status_code;
	bool			dns;
	bool			autoindex;

	std::cout << "\033[31mMETHOD DELETE\033[0m\nbody:" << body << "\nurl:" << url << "\n";
	status_code = client.getRequest().getStatusCode();
	dns = client.getRequest().getDnsErrorBool();
	autoindex = client.getRequest().getAutoIndexBool();
	if (status_code != 200 || dns == true || autoindex == true)
	{
		std::cout << "fail" << std::endl;
		if (body.empty() == false)
			body = file_opener(file);
		return ;
	}
	std::cout << "Url in delete method: " << url << std::endl;
	if (this->_protected_files.find(url) != std::string::npos)
	{
		// std::cout << "Non si fa!" << 
		client.getRequest().fail(HTTP_CE_FORBIDDEN);
		file.open("www/var/errors/403.html");
		return ;
	}
	if (url.rbegin()[0] == '/')
		url.erase(url.find_last_of('/'), 1);
	if (std::remove(url.c_str()) == 0)//file cancellato
	{
		file.open("www/var/2xx.html");
		body = file_opener(file, "delete_method: cannot open file on success");
		find_and_replace(body, "{MSG}", "file " + url + " deleted successfully!");
		find_and_replace(body, "{CODE}", HTTP_OK_NO_CONTENT);
		return ;
	}//cancellazione fallita
	if (valid_directory(url))
	{
		client.getRequest().setStatusCode(HTTP_CE_FORBIDDEN);
		file.open("www/var/errors/special/403_DirNotEmpty.html");
	}
	else
	{
		client.getRequest().setStatusCode(HTTP_SE_INTERNAL);
		file.open("www/var/errors/special/500_CannotDeleteFile.html");
	}
	body = file_opener(file, "delete_method: cannot open file on error");
}
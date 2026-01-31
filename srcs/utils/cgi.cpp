#include "../../includes/ether.hpp"
#include "../hpp/Client.hpp"
#include <sys/wait.h>

static void		run_cmd(char *const argv[], std::string &output);
static void		get_argv(Client &client, std::string argv[2]);

void	run_script(Client &client, std::string &body)
{
	std::string	argv_str[2];

	std::cout << "run_script\n";
	get_argv(client, argv_str);
	char const	*argv[3] = {argv_str[0].c_str(), argv_str[1].c_str(), NULL};
	std::cout << "cmd: " << argv[0] << "\n";
	std::cout << "arg: " << argv[1] << "\n";
	run_cmd((char *const *)argv, body);
	//std::cout << "cgi output: " << body << "\n";
	if (client.getLocConf().script_type == "pokedex")
		;//createHtmlPokedex();
	else
		std::cout << "script_type undefined. no html created." << std::endl;
	//std::cout << "html result : " << body << "\n";
}

static void		get_argv(Client &client, std::string argv[2])
{
	std::string	url = client.getRequest().getUrl();

	if (url.find('?'))
	{
		argv[0] = url.substr(0, url.find_last_of('?'));
		argv[1] = url.substr(url.find_last_of('?') + 1, url.length());
		find_and_replace(argv[1], "value=", "");
	}
	else
	{
		argv[0] = client.getLocConf().cgiparam[0].second;
		argv[1] = url.substr(url.find_last_of('/') + 1, url.length());
	}
}

static void	run_cmd(char *const argv[], std::string &output)
{
	std::string			url;
	int					pipe_fd[2];

	pid_t	pid;
	if (pipe(pipe_fd) != 0)
		return (std::cout << "run_script fatal error\n", (void)0);
	pid = fork();
	if (pid == -1)
		return (std::cout << "run_script fatal error\n", (void)0);
	else if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execve(argv[0], argv, NULL);
		std::cerr << "run_script fatal error\n";
		exit(1);//FIXME - exit non è ammesso, bisogna uccidere figlio con kill
	}
	close(pipe_fd[1]);
	wait(NULL);
	std::string	filename("/dev/fd/" + ft_to_string(pipe_fd[0]));
	std::cout << filename << std::endl;
	std::ifstream	output_fd(filename.c_str(), std::ios_base::in);
	std::getline(output_fd, output, '\0');
	close(pipe_fd[0]);
}

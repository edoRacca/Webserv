#include "../../includes/ether.hpp"
#include "../hpp/Client.hpp"
#include <sys/wait.h>

static void			run_cmd(char *const argv[], std::string &output);
static std::string	get_arg(std::string &url);

void	run_script(Client &client, std::string &body)
{
	std::string	output;
	std::string cmd;
	std::cout << "run_script\n";

	std::string	url = client.getRequest().getUrl();
	if (url.find('?'))
		cmd = url.substr(0, url.find_last_of('?'));
	else
		cmd = client.getLocConf().cgiparam[0].second;
	std::cout << "cmd: " << cmd << std::endl;
	std::string	arg_string = get_arg(url);
	const char	*arg = arg_string.c_str();
	char const	*argv[3] = {cmd.c_str(), arg, NULL};
	std::cout << "cmd: " << argv[0] << "\n";
	std::cout << "arg: " << argv[1] << "\n";
	run_cmd((char *const *)argv, output);
	std::cout << output << "\n";
	body = output;
	(void)body;
}

static std::string	get_arg(std::string &url)
{
	char	trim_char;

	if (url.find('?'))
		trim_char = '?';
	else
		trim_char = '/';
	std::string	arg_string(url.substr(url.find_last_of(trim_char) + 1, url.length()));
	find_and_replace(arg_string, "value=", "");
	return (arg_string);
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
		std::cout << "run_script fatal error\n";
		exit(1);
	}
	close(pipe_fd[1]);
	wait(NULL);
	std::string	filename("/dev/fd/" + ft_to_string(pipe_fd[0]));
	std::cout << filename << std::endl;
	std::ifstream	output_fd(filename.c_str(), std::ios_base::in);
	std::getline(output_fd, output, '\0');
	close(pipe_fd[0]);
}

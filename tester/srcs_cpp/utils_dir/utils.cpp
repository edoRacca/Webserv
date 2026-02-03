#include "../tester.hpp"

void	run_cmd(char *const argv[], std::string &output, int second);

void	run_cmd(char *const argv[], std::string &output, int second)
{
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
		//free
		execve(argv[0], argv, NULL);
		std::cerr << "run_cmd fatal error\n";
		std::exit(1);
	}
	close(pipe_fd[1]);
	sleep(second);
	kill(pid, SIGINT);
	std::string	filename("/dev/fd/" + ft_to_string(pipe_fd[0]));
	std::cout << filename << std::endl;
	std::ifstream	output_fd(filename.c_str(), std::ios_base::in);
	std::getline(output_fd, output, '\0');
	close(pipe_fd[0]);
}

void	erase_space(std::string &s)
{
	size_t	i;
	size_t	j;

	i = s.find_first_of(" \f\n\r\t\v");
	while (i != s.npos)
	{
		j = s.find_first_not_of(" \f\n\r\t\v", i);
		if (j == s.npos)
			j = s.length();
		j -= i;
		s.erase(i, j);
		i = s.find_first_of(" \f\n\r\t\v", i);
	}
}

static int	get_file_input(std::string filename, std::string &input);
static int	get_file_output(std::string filename, std::string &output);

int		update_result(std::string filename, std::string &output)
{
	std::fstream	fd;
	std::string		temp;
	std::string		file_input;

	if (get_file_input(filename, file_input) != 0)
		return (1);
	fd.open(filename, std::ios_base::trunc);
	if (fd.fail())
	{
		std::cerr << "cannot update " << filename << std::endl;
		return (1);
	}
	fd << file_input << output;
	return (0);
}

int		compare_result(std::string filename, std::string &output)
{
	std::fstream	fd;
	std::string		temp;
	std::string		file_input;
	std::string		file_output;

	if (get_file_output(filename, file_output) != 0)
		return (1);
	erase_space(file_output);
	if (output == file_output)
		return (0);
	std::cout << "ERROR LOG: test " << filename << "\n";
	std::cout << "CORRECT: " << file_output << "\n";
	std::cout << "OUTPUT: " << output << "\n";
	return (2);
}

static int	get_file_input(std::string filename, std::string &input)
{
	std::fstream	fd(filename);
	std::string		temp;

	if (fd.fail())
	{
		std::cerr << "fail to open " << filename << std::endl;
		return (1);
	}
	std::getline(fd, temp, '!');
	input += temp;
	std::getline(fd, temp, '\n');
	input += temp;
	return (0);
}

static int	get_file_output(std::string filename, std::string &output)
{
	std::fstream	fd(filename);
	std::string		temp;

	if (fd.fail())
	{
		std::cerr << "fail to open " << filename << std::endl;
		return (1);
	}
	std::getline(fd, temp, '!');
	std::getline(fd, temp, '\n');
	std::getline(fd, output, '\0');
	return (0);
}

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>

typedef struct s_diff
{
	char	*bf;
	char	*tmp;
	char	*filename;
	int		filesize;
	int		fd;
	int		tmplen;
	int		left;
}		t_diff;

static int	files_constructor(t_diff *f1, t_diff *f2);
static int	stat_syscall(int ac, char **av, t_diff *f1, t_diff *f2);
static char	*itoa(int n, int *len);
static bool	ft_getline(t_diff *f);
static int	bin_strcmp(char *tmp1, char *tmp2, int len1, int len2);
static void	print_diff(t_diff *f1, t_diff *f2, int newline_counter);
static int	end(t_diff *f1, t_diff *f2, int ecode);

int	main(int ac, char **av)
{
	t_diff	f1;
	t_diff	f2;
	int		newline_counter;

	if (stat_syscall(ac, av, &f1, &f2) != 0)
		return (1);
	if (files_constructor(&f1, &f2) != 0)
		return (1);
	newline_counter = 0;
	for (;f1.left > 0;)
	{
		if (ft_getline(&f1) != 0)
			return (end(&f1, &f2, 4));
		if (ft_getline(&f2) != 0)
			return (end(&f1, &f2, 5));
		if (bin_strcmp(f1.tmp, f2.tmp, f1.tmplen, f2.tmplen))
			print_diff(&f1, &f2, newline_counter);
		free(f1.tmp);
		f1.tmp = NULL;
		free(f2.tmp);
		f2.tmp = NULL;
		newline_counter++;
	}
	end(&f1, &f2, 0);
}

static int	files_constructor(t_diff *f1, t_diff *f2)
{
	f1->fd = open(f1->filename, O_RDONLY);
	f2->fd = open(f2->filename, O_RDONLY);
	if (!f1->fd || !f2->fd)
		return (end(f1, f2, 1));
	f1->bf = malloc(f1->filesize + 3);
	f2->bf = malloc(f2->filesize + 3);
	if (!f1->bf || !f2->bf)
		return (end(f1, f2, 4));
	if (read(f1->fd, f1->bf, f1->filesize) != f1->filesize)
		return (end(f1, f2, 2));
	if (read(f2->fd, f2->bf, f2->filesize) != f2->filesize)
		return (end(f1, f2, 3));
	f1->left = f1->filesize + 3;
	f2->left = f2->filesize + 3; 
	f1->bf[f1->filesize] = 'E';
	f2->bf[f2->filesize] = 'E';
	f1->bf[f1->filesize + 1] = 'O';
	f2->bf[f2->filesize + 1] = 'O';
	f1->bf[f1->filesize + 2] = 'F';
	f2->bf[f2->filesize + 2] = 'F';
	return (0);
}

static int	stat_syscall(int ac, char **av, t_diff *f1, t_diff *f2)
{
	struct stat f1_stat;
	struct stat f2_stat;

	if (ac != 3)
		return (write(1, "you must pass two args: path/file1 path/file2\n", 46));
	f1_stat = (struct stat){0};
	f2_stat = (struct stat){0};
	if (stat(av[1], &f1_stat))
	{
		write(1, av[1], strlen(av[1]));
		return (write(1, " is invalid\n", 12));
	}
	if (stat(av[2], &f2_stat))
	{
		write(1, av[2], strlen(av[2]));
		return (write(1, " is invalid\n", 12));
	}
	f1->filename = av[1];
	f2->filename = av[2];
	f1->filesize = f1_stat.st_size;
	f2->filesize = f2_stat.st_size;
	return (0);
}

static bool	ft_getline(t_diff *f)
{
	int	endline;

	if (f->left == 0)
		return (0);
	endline = 0;
	while (f->bf[endline] != '\n' && \
	f->bf[endline] != 'E' && f->bf[endline] != 'O' && f->bf[endline] != 'F')
	{
		++endline;
	}
	f->tmplen = endline;
	++endline;
	f->left -= endline;
	f->tmp = malloc(endline);
	if (!f->tmp)
		return (1);
	for (int i = 0; i != endline; i++)
		f->tmp[i] = f->bf[i];
	for (int i = 0; i != f->left; i++)
		f->bf[i] = f->bf[i + endline];
	return (0);
}

static int	bin_strcmp(char *tmp1, char *tmp2, int len1, int len2)
{
	int	i;

	if (!tmp1 && !tmp2)
		return (0);
	else if (!tmp1)
		return (-1);
	else if (!tmp2)
		return (1);
	for (i = 0; i != len1 && i != len2; i++)
	{
		if (tmp1[i] != tmp2[i])
			return (tmp1[i] - tmp2[i]);
	}
	return (tmp1[i] - tmp2[i]);
}

static void	print_diff(t_diff *f1, t_diff *f2, int newline_counter)
{
	char	*temp;
	int		len;

	temp = itoa(newline_counter, &len);
	write(1, "diff in line: ", 14);
	write(1, temp, len);
	write(1, "\n", 1);
	free(temp);
	temp = calloc(100, sizeof(char));
	write(1, "Our: |", 6);
	write(1, f1->tmp, f1->tmplen);
	write(1, "|\nOri: |", 8);
	write(1, f2->tmp, f2->tmplen);
	write(1, "|\nhexa dump:\n", 13);
	for (int i = 0; i != f1->tmplen; i++)
	{
		sprintf(temp, "%d", f1->tmp[i]);
		write(1, temp, strlen(temp));
		write(1, " ", 1);
	}
	write(1, "\n---\n", 5);
	for (int i = 0; i != f2->tmplen; i++)
	{
		sprintf(temp, "%d", f2->tmp[i]);
		write(1, temp, strlen(temp));
		write(1, " ", 1);
	}
	write(1, "|\n---------------\n", 18);
	free(temp);
}

static int	end(t_diff *f1, t_diff *f2, int ecode)
{
	close(f1->fd);
	close(f2->fd);
	free(f1->bf);
	free(f2->bf);
	switch (ecode)
	{
		case 1:
			printf("cannot open file\n");
			break ;
		case 2:
			printf("cannot read file 1 to the end\n");
			break ;
		case 3:
			printf("cannot read file 2 to the end\n");
			break ;
		case 4:
			printf("malloc failure\n");
			break ;
	}
	return (ecode);
}

static void	reverse(char *str, int len)
{
	int i = 0;
	int j = len - 1;
	char tmp;

	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

static char	*itoa(int n, int *len)
{
	char	*str;
	int		i = 0;
	int		sign;
	long	nb;

	nb = n;
	sign = 0;
	if (nb < 0)
	{
		sign = 1;
		nb = -nb;
	}
	str = malloc(12);
	if (!str)
		return NULL;
	while (nb > 0)
	{
		str[i++] = (nb % 10) + '0';
		nb /= 10;
	}
	if (i == 0)
		str[i++] = '0';
	if (sign)
		str[i++] = '-';
	str[i] = '\0';
	reverse(str, i);
	if (len)
		*len = i;
	return str;
}

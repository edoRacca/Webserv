#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
#include <fcntl.h>
#include <stdbool.h>

#define FILE_1 "../PORNO_EMMA_WATSON.ico"
#define FILE_2 "../www/var/favicon.ico"
#define SIZE 233816

typedef struct s_diff
{
	int		fd;
	char	bf[SIZE + 3];
	char	*tmp;
	int		tmplen;
	int		left;
}		t_diff;

static char	*ft_itoa(int num, int *len);
static bool	ft_getline(t_diff *f);
static int	bin_strcmp(char *tmp1, char *tmp2, int len1, int len2);
static void	print_diff(t_diff *f1, t_diff *f2, int newline_counter);
static int	end(t_diff *f1, t_diff *f2, int ecode);

int	main()
{
	t_diff	f1;
	t_diff	f2;
	int		newline_counter;

	f1 = (t_diff){0};
	f2 = (t_diff){0};
	f1.fd = open(FILE_1, O_RDONLY);
	f2.fd = open(FILE_2, O_RDONLY);
	newline_counter = 0;
	if (!f1.fd || !f2.fd)
		return (end(&f1, &f2, 1));
	if (read(f1.fd, f1.bf, SIZE) != SIZE)
		return (end(&f1, &f2, 2));
	if (read(f2.fd, f2.bf, SIZE) != SIZE)
		return (end(&f1, &f2, 3));
	f1.left = SIZE, f2.left = SIZE; 
	f1.bf[SIZE] = 'E', f2.bf[SIZE] = 'E';
	f1.bf[SIZE + 1] = 'O', f2.bf[SIZE + 1] = 'O';
	f1.bf[SIZE + 2] = 'F', f2.bf[SIZE + 2] = 'F';
	for (;f1.left > 0;)
	{
		if (ft_getline(&f1) != 0)
			return (end(&f1, &f2, 4));
		if (ft_getline(&f2) != 0)
			return (end(&f1, &f2, 5));
		if (bin_strcmp(f1.tmp, f2.tmp, f1.tmplen, f2.tmplen))
			print_diff(&f1, &f2, newline_counter);
		free(f1.tmp);
		free(f2.tmp);
		newline_counter++;
	}
	end(&f1, &f2, 0);
}

/*
			h_len = header.tellg();
			bytes -= (int)h_len; //161 -> left
			//request.setBodyLen(request.getBodyLen() - )
			for (int i = 0; i != bytes; i++)
				buf[i] = buf[i + h_len];
*/
static bool	ft_getline(t_diff *f)
{
	int	endline;//h_len

	endline = 0;
	while (f->bf[endline] != '\n' && \
	f->bf[endline] != 'E' && f->bf[endline] != 'O' && f->bf[endline] != 'F')
	{
		++endline;
	}
	f->tmplen = endline;
	f->tmp = malloc(endline);
	if (!f->tmp)
		return (1);
	for (int i = 0; i != endline; i++)
		f->tmp[i] = f->bf[i];
	f->left -= endline;//trim
	for (int i = 0; i != f->left; i++)
		f->bf[i] = f->bf[i + endline];
	return (0);
}

static int	bin_strcmp(char *tmp1, char *tmp2, int len1, int len2)
{
	int	i;

	for (i = 0; i != len1 && i != len2; i++)
	{
		if (tmp1[i] != tmp2[i])
			return (tmp1[i] - tmp2[i]);
	}
	return (tmp1[i] - tmp2[i]);
}

static void	print_diff(t_diff *f1, t_diff *f2, int newline_counter)
{
	char	*char_counter;
	int		counter_len;

	write(1, "\033[31mdiff in line\033[0m ", 22);
	char_counter = ft_itoa(newline_counter, &counter_len);
	write(1, char_counter, counter_len);
	free(char_counter);
	write(1, ":\n", 2);
	write(1, "f1: |", 5);
	write(1, f1->tmp, f1->tmplen);
	write(1, "|\nf2: |", 7);
	write(1, f2->tmp, f2->tmplen);
	write(1, "|\n---------------\n", 18);
}

static int	end(t_diff *f1, t_diff *f2, int ecode)
{
	close(f1->fd), close(f2->fd);
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
	}
	return (ecode);
}

static char	*ft_itoa(int num, int *len)
{
	int		temp_num;
	int		index;
	char	*str;

	index = 0;
	temp_num = num;
	while ((temp_num > 9) || (temp_num < -9))
	{
		index++;
		temp_num /= 10;
	}
	if (num == 0)
		index = 1;
	*len = index;
	str = calloc(20, 1);
	if (!str)
		return (NULL);
	str[0] = '0';
	while (num != 0)
	{
		if (num < 0)
			str[index--] = (((num % 10) * -1) + 48);
		else
			str[index--] = ((num % 10) + 48);
		num /= 10;
	}
	return (str);
}

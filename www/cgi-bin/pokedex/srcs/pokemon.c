#include "pokedex.h"

static void	print_field(char **field);
static void	hypertext(int href_flag, char *val);
static void	pkmn_id(char ***data);

int	main(int ac, char **av)
{
	char	***data;

	if (ac == 1)
		return (ft_printf("Please give a valid pokemon name\n"));
	STR(pokemon, av[1]);
	pokemon.m->str_upper(&pokemon);
	if (daft_init("www/cgi-bin/pokedex/media", "SETTINGS.md") != 0)
		daft_init("media", "SETTINGS.md");
	daft_swap(POKEDEX);
	data = daft_get(pokemon.buff);
	if (!data)
	{
		ft_printf("pokemon %s not found.\n", pokemon.buff);
		return (str_terminate(), daft_quit(), 1);
	}
	pkmn_id(data);
	for (int i = 0; data[i]; i++)
		print_field(data[i]);
	return (str_terminate(), daft_quit(), 0);
}

static void	print_field(char **field)
{
	static const char	*href_keys[] = {HREF_KEYS};
	char				*key;
	int					href_flag;

	key = field[0];
	href_flag = NO_HREF;
	ft_printf("|%s:", key);
	for (int i = 0; href_keys[i]; i++)
	{
		if (ft_strncmp(key, href_keys[i], INT_MAX) == 0)
			href_flag = i;
	}
	for (int i = 1; field[i]; i++)
		ft_printf("?%p-%d-%p?%s,", hypertext, href_flag, field[i], field[i]);
}

static void	hypertext(int href_flag, char *val)
{
	if (href_flag == NO_HREF)
		return ;
	for (int i = 0; val[i]; i++)
	{
		if (val[i] < 'A' || val[i] > 'Z')
			return ;
	}
	if (href_flag <= RANGE_MOVE)
		href_flag = ID_MOVE;
	else if (href_flag <= RANGE_PKMN)
		href_flag = ID_PKMN;
	else
		return (ft_printf("pokemon.cgi: enum error\n"), (void)0);
	ft_printf("@%d", href_flag);
}

static void	pkmn_id(char ***data)
{
	int	i;

	for (i = 0; data[i]; i++)
	{
		if (ft_strncmp("ID", data[i][0], INT_MAX) == 0)
			break ;
	}
	if (!data[i])
		return (ft_printf("|not_found"), (void)0);
	ft_printf("{%d}%s", ID_PKMN, data[i][1]);
}

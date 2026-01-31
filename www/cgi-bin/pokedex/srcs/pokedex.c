#include "../all.h"

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
	for (int i = 0; data[i]; i++)
	{
		ft_printf("%s: ", data[i][0]);
		for (int j = 1; data[i][j]; j++)
			ft_printf("%s, ", data[i][j]);
		ft_printf("\b\b  \n");
	}
	return (str_terminate(), daft_quit(), 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:03:20 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/28 11:31:22 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

char	*entries[] = {"NAME", "TYPE", "STATS", "GENDER_RATIO", "GROWTH", \
						"BASE_EXP", "EVS", "CATCHRATE", "BASE_HAPPINESS", \
					"ABILITIES", "HIDDEN_ABILITIES", "MOVES", "TUTOR_MOVES", \
					"TUTOR_MOVES", "EGGGROUP", "HATCH_STEPS", "HEIGHT", "HEIGHT", \
					"COLOR", "SHAPE", "HABITAT", "CATEGORY", "POKEDEX", \
					"GENERATION", "EVOLUTIONS", NULL, NULL, NULL, NULL, NULL};

int	main(int ac, char **av)
{
	char	***data;
	if (ac == 1)
		return (ft_printf("Please give a valid pokemon name\n"));
	STR(pokemon, av[1]);
	pokemon.m->str_upper(&pokemon);
	daft_init("media", "SETTINGS.md");
	daft_swap(POKEDEX);
	data = daft_get(pokemon.buff);
	if (!data)
		ft_printf("pokemon %s not found.\n", pokemon.buff);
	for (int i = 0; data[i]; i++)
	{
		ft_printf("%s: ", entries[i]);
		for (int j = 0; data[i][j]; j++)
			ft_printf("%s, ", data[i][j]);
		ft_printf("\b\b \n");
	}
}

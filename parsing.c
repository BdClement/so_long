/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:35:01 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/17 13:47:42 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Cette fonction verifie que l'argument envoye est bien au format .ber
void	check_arg_format(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '.')
		{
			if (arg[i + 1] == 'b' && arg[i + 2] == 'e'
				&& arg[i + 3] == 'r' && arg[i + 4] == '\0')
				return ;
		}
		i++;
	}
	ft_printf("L'argument fourni n'est pas au format adequat\n");
	exit(EXIT_FAILURE);
}

// Cette fonction verifie si la map envoye est bien delimitee par des murs
void	check_map_wall(char **map, t_map *map_info)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		if (i == 0 || i == map_info->map_nb_line - 1)
		{
			while (map[i][j] != '\0')
			{
				if (map[i][j] != '1')
					map_info->wall_around = 1;
				j++;
			}
		}
		else
			if (map[i][0] != '1' || map[i][map_info->map_len - 1] != '1')
				map_info->wall_around = 1;
		i++;
	}
}

// Cette fonction verifie si la map est bien rectangle
void	check_map_rectangle(t_solong *solong, t_map *map_info)
{
	int	i;

	i = 1;
	map_info->map_len = ft_strlen(solong->map[0]);
	if (map_info->map_len > 40 || map_info->map_nb_line > 21)
		map_info->map_to_big = 1;
	while (solong->map[i] != NULL)
	{
		if (map_info->map_len != (int)ft_strlen(solong->map[i]))
			map_info->is_rectangle = 1;
		i++;
	}
	if (map_info->map_len == map_info->map_nb_line)
		map_info->is_rectangle = 1;
}

// Cette fonction est la fonction qui determine si il existe
// Un chemin valise dans la map fourni
// Pour cela, elle duplique la map d'origine a l'aide de map_dup
// Et remplie toutes les cases accessibles d'un 'X'
// Si il reste des items ou l'exit alors il n'existe pas de chemin valide
void	check_valid_items(t_solong *solong, t_map *map_info)
{
	map_dup(solong, map_info);
	fill_map_copy(map_info, map_info->start_pos.x, map_info->start_pos.y);
	if (map_info->item_accessible == map_info->item
		&& map_info->exit_accessible == 1)
		map_info->valid_items = 0;
}

// Cette fonction appelle toutes les fonctions de checks une a une
// Et affiche des messages d'erreurs si besoin
void	check_map(t_solong *solong, t_map *map_info)
{
	int	error;

	error = 0;
	init_map_struct(map_info);
	map_info->map_nb_line = solong->map_nb_line;
	get_map_info(solong->map, map_info);
	if (map_info->start != 1 || map_info->exit != 1 || map_info->item == 0
		|| map_info->not_allowed == 1)
		error = 1;
	check_map_rectangle(solong, map_info);
	if (map_info->is_rectangle == 0)
		check_map_wall(solong->map, map_info);
	if (map_info->is_rectangle == 1 || map_info->wall_around == 1)
		error = 1;
	check_valid_items(solong, map_info);
	if (map_info->valid_items == 1 || map_info->map_to_big == 1)
		error = 1;
	solong->nb_item = map_info->item;
	solong->cur = map_info->start_pos;
	if (error == 1)
	{
		free_map(solong->map);
		free_map(map_info->map_copy);
		display_error_message(*map_info);
	}
}

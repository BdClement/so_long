/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:35:01 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/08 16:43:00 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Peut bouger dans le main ??
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

void	init_map_struct(t_map *map_info)
{
	map_info->exit = 0;
	map_info->item = 0;
	map_info->start = 0;
	map_info->wall_around = 0;
	map_info->valid_items = 0;
	map_info->not_allowed = 0;
	map_info->map_len = 0;
	map_info->map_nb_line = 0;
}

void	get_map_info(char **map, t_map *map_info)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'C'
				&& map[i][j] != 'E' && map[i][j] != 'P')
				map_info->not_allowed++;
			if (map[i][j] == 'C')
				map_info->item++;
			else if (map[i][j] == 'E')
				map_info->exit++;
			else if (map[i][j] == 'P')
				map_info->start++;
			j++;
		}
		i++;
	}
}

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

void	check_map_rectangle(t_solong *solong, t_map *map_info)
{
	int	i;

	i = 1;
	map_info->map_len = ft_strlen(solong->map[0]);
	while (solong->map[i] != NULL)
	{
		if (map_info->map_len != (int)ft_strlen(solong->map[i]))
			map_info->is_rectangle = 1;
		i++;
	}
	if (map_info->map_len == map_info->map_nb_line)
		map_info->is_rectangle = 1;
}

//é
void	display_error_message(t_map map_info)
{
	ft_printf("Error\n");
	// Message en cs de doublons ??
	if (map_info.not_allowed == 1)
		ft_printf("La map contient des carcateres non autorisés\n");
	if (map_info.exit != 1 || map_info.start != 1)
		ft_printf("La map doit contenir UNE sortie, UNE position de départ\n");
	if (map_info.item == 0)
		ft_printf("La map doit contenir au moins un objet a collecter\n");
	if (map_info.is_rectangle == 1)
		ft_printf("La map n'est pas de forme rectangulaire\n");
	if (map_info.is_rectangle == 0 && map_info.wall_around == 1)
		ft_printf("La map n'est pas fermée en etant encadrée par des mur\n");
	if (map_info.valid_items == 1)
		ft_printf("Il n'existe pas de chemin valide pour cette map\n");
	exit(EXIT_FAILURE);
}

// Verifie si la map est rectangle
// Si elle contient 1 seule sortie, 1 seule position de depart et
// Au moins un item
// Si elle ne contient rien d'autres que ces elements
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
	if	(map_info->is_rectangle == 0)
		check_map_wall(solong->map, map_info);
	if (map_info->is_rectangle == 1 || map_info->wall_around == 1)
		error = 1;
	// Rajouter si Backtracking !
	// + Si Doublons ??
	if (error == 1)
	{
		display_error_message(*map_info);
		//Free ou l'include dans la fontcion display_error par manque de place!!
	}
}

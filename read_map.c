/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:14:50 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/17 12:25:17 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Cette fonction recupere le nombre de ligne que contient la map
// Pour pouvoir malloc un char** pour la recuperer
void	get_mapline_number(t_solong *solong)
{
	int		fd;
	char	*str;

	fd = open(solong->map_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		str = get_next_line(fd, 0);
		if (str == NULL)
		{
			free(str);
			break ;
		}
		free(str);
		solong->map_nb_line++;
	}
	close(fd);
}

// Cette fonction recupere la map et la stocke dans un char **
// Qui est dans la structure t_solong
void	get_map(t_solong *solong)
{
	int		i;
	int		fd;
	char	*str;

	i = 0;
	fd = open(solong->map_path, O_RDONLY);
	solong->map = malloc(sizeof(char *) * (solong->map_nb_line + 1));
	if (solong->map == NULL)
		perror("Error");
	solong->map[solong->map_nb_line] = NULL;
	while (1)
	{
		str = get_next_line(fd, 0);
		if (str == NULL)
		{
			free(str);
			break ;
		}
		solong->map[i] = ft_dup(str);
		free(str);
		i++;
	}
	close(fd);
}

// Cette fonction recolte le nombre d'exit, d'item, et de position de depart
// Ainsi que les coordonnees du la positon de depart
// Elle detecte egalement si des caracteres
// Autres que ceux autorises sont presents
void	get_map_info(char **map, t_map *map_info)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i] != NULL)
	{
		j = -1;
		while (map[i][++j] != '\0')
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'C'
				&& map[i][j] != 'E' && map[i][j] != 'P')
				map_info->not_allowed++;
			if (map[i][j] == 'C')
				map_info->item++;
			else if (map[i][j] == 'E')
				map_info->exit++;
			else if (map[i][j] == 'P')
			{
				map_info->start++;
				map_info->start_pos.x = j;
				map_info->start_pos.y = i;
			}
		}
	}
}

// Cette fonction remplie la copie de la map originale
// Pour verifier que tout les items et la sortie sont accessibles
// Elle recupere le nombre d'item et d'exit rencontre
void	fill_map_copy(t_map *map_info, int x, int y)
{
	if (map_info->map_copy[y][x] == '1' || map_info->map_copy[y][x] == 'X')
		return ;
	if (map_info->map_copy[y][x] == 'C')
		map_info->item_accessible++;
	else if (map_info->map_copy[y][x] == 'E')
		map_info->exit_accessible++;
	map_info->map_copy[y][x] = 'X';
	fill_map_copy(map_info, x + 1, y);
	fill_map_copy(map_info, x - 1, y);
	fill_map_copy(map_info, x, y + 1);
	fill_map_copy(map_info, x, y - 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:22:22 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/19 13:25:40 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Initialise la strucure principale
void	init_struct(t_solong *solong, char *map_path)
{
	solong->map = NULL;
	solong->map_nb_line = 0;
	solong->moves = 1;
	solong->collected = 0;
	solong->nb_item = 0;
	solong->put_exit_back = 0;
	solong->all_collected = 0;
	solong->map_path = map_path;
	get_mapline_number(solong);
	get_map(solong);
}

//Initialise la structure qui recolte les caracteristiques de la map
void	init_map_struct(t_map *map_info)
{
	map_info->exit = 0;
	map_info->item = 0;
	map_info->start = 0;
	map_info->wall_around = 0;
	map_info->is_rectangle = 0;
	map_info->valid_items = 1;
	map_info->not_allowed = 0;
	map_info->map_len = 0;
	map_info->map_nb_line = 0;
	map_info->map_to_big = 0;
	map_info->map_copy = NULL;
	map_info->exit_accessible = 0;
	map_info->item_accessible = 0;
}

// Cette fonction gere uniquement le ramassage d'un item
void	collected(t_solong *solong, int y, int x)
{
	solong->collected++;
	solong->map[y][x] = '0';
}

// Cette fonction duplique une chaine de carcteres
// En retirant le "\n" recuperer a partir de GNL
char	*ft_dup(char *str)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(sizeof(char) * ft_strlen(str));
	if (dup == NULL)
		return (NULL);
	while (1)
	{
		if (str[i] == '\n')
		{
			dup[i] = '\0';
			break ;
		}
		dup[i] = str[i];
		i++;
	}
	return (dup);
}

// Cette fonction realise une copie de la map pour verifier
// si un chemin valide existe
// Free de la copy de map a faire egalement
// Attention a la derniere iteration peut etre malloc(0) dans strdup
void	map_dup(t_solong *solong, t_map *map_info)
{
	int	i;

	i = 0;
	map_info->map_copy = malloc(sizeof(char *) * (solong->map_nb_line + 1));
	if (map_info->map_copy == NULL)
	{
		perror("Error");
		free_map(solong->map);
		exit(EXIT_FAILURE);
	}
	map_info->map_copy[solong->map_nb_line] = NULL;
	while (i < solong->map_nb_line)
	{
		map_info->map_copy[i] = ft_strdup(solong->map[i]);
		i++;
	}
}

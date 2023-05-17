/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:48:18 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/17 14:55:05 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_images(t_solong *solong)
{
	int	width;
	int	height;

	width = 64;
	height = 64;
	solong->perso = mlx_xpm_file_to_image(solong->mlx_ptr,
			"./img/perso.xpm", &width, &height);
	solong->item = mlx_xpm_file_to_image(solong->mlx_ptr,
			"./img/item.xpm", &width, &height);
	solong->door = mlx_xpm_file_to_image(solong->mlx_ptr,
			"./img/door.xpm", &width, &height);
	solong->ground = mlx_xpm_file_to_image(solong->mlx_ptr,
			"./img/ground.xpm", &width, &height);
	solong->wall = mlx_xpm_file_to_image(solong->mlx_ptr,
			"./img/wall.xpm", &width, &height);
}

void	put_image(t_solong *solong, int i, int j)
{
	if (solong->map[i][j] == '1')
		mlx_put_image_to_window(solong->mlx_ptr,
			solong->win, solong->wall, j * 64, i * 64);
	else if (solong->map[i][j] == '0')
		mlx_put_image_to_window(solong->mlx_ptr,
			solong->win, solong->ground, j * 64, i * 64);
	else if (solong->map[i][j] == 'P')
		mlx_put_image_to_window(solong->mlx_ptr,
			solong->win, solong->perso, j * 64, i * 64);
	else if (solong->map[i][j] == 'C')
		mlx_put_image_to_window(solong->mlx_ptr,
			solong->win, solong->item, j * 64, i * 64);
	else if (solong->map[i][j] == 'E')
		mlx_put_image_to_window(solong->mlx_ptr,
			solong->win, solong->door, j * 64, i * 64);
}

// Faire fonction pour gagner la place
// Confusion J == X et Y == I
void	display_map(t_solong *solong)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	get_images(solong);
	while (solong->map[i] != NULL)
	{
		j = 0;
		while (solong->map[i][j] != '\0')
		{
			put_image(solong, i, j);
			j++;
		}
		i++;
	}
}

// Cette fonction affiche les messages d'erreurs necessaires
// Et quitte le programme proprement
void	display_error_message(t_map map_info)
{
	ft_printf("Error\n");
	if (map_info.not_allowed == 1)
		ft_printf("La map contient des carcateres non autorisés\n");
	if (map_info.exit != 1 || map_info.start != 1)
		ft_printf("La map doit contenir UNE sortie, UNE position de départ\n");
	if (map_info.item == 0)
		ft_printf("La map doit contenir au moins un objet a collecter\n");
	if (map_info.is_rectangle == 1)
		ft_printf("La map n'est pas de forme rectangulaire\n");
	if (map_info.map_to_big == 1)
		ft_printf("La map est trop grande \n");
	if (map_info.is_rectangle == 0 && map_info.wall_around == 1)
		ft_printf("La map n'est pas fermée en etant encadrée par des mur\n");
	if (map_info.valid_items == 1)
		ft_printf("Il n'existe pas de chemin valide pour cette map\n");
	exit(EXIT_FAILURE);
}

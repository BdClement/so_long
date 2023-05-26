/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:49:11 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/19 13:29:41 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Cette fonction free un **char
void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		free(map[i++]);
	free(map);
}

// Cette fonction est un intermediaire a passer a mlx_hook
// pour quitter proprement en cas de ESC ou X
int	ft_exit(t_solong *solong)
{
	clean(solong);
	return (0);
}

// Cette fonction permet de quitter proprement le programme
void	clean(t_solong *solong)
{
	free_map(solong->map);
	free_map(solong->map_copy);
	if (solong->perso != NULL)
		mlx_destroy_image(solong->mlx_ptr, solong->perso);
	if (solong->wall != NULL)
		mlx_destroy_image(solong->mlx_ptr, solong->wall);
	if (solong->item != NULL)
		mlx_destroy_image(solong->mlx_ptr, solong->item);
	if (solong->door != NULL)
		mlx_destroy_image(solong->mlx_ptr, solong->door);
	if (solong->ground != NULL)
		mlx_destroy_image(solong->mlx_ptr, solong->ground);
	mlx_loop_end(solong->mlx_ptr);
	mlx_destroy_window(solong->mlx_ptr, solong->win);
	mlx_destroy_display(solong->mlx_ptr);
	free(solong->mlx_ptr);
	exit(EXIT_SUCCESS);
}

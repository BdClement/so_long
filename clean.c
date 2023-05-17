/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:49:11 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/16 19:03:02 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		free(map[i++]);
	free(map);
}

int	ft_exit(t_solong *solong)
{
	clean(solong);
	return (0);
}

void	clean(t_solong *solong)
{
	free_map(solong->map);
	free_map(solong->map_copy);
	mlx_destroy_image(solong->mlx_ptr, solong->perso);
	mlx_destroy_image(solong->mlx_ptr, solong->wall);
	mlx_destroy_image(solong->mlx_ptr, solong->item);
	mlx_destroy_image(solong->mlx_ptr, solong->door);
	mlx_loop_end(solong->mlx_ptr);
	mlx_destroy_image(solong->mlx_ptr, solong->ground);
	mlx_destroy_window(solong->mlx_ptr, solong->win);
	mlx_destroy_display(solong->mlx_ptr);
	free(solong->mlx_ptr);
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:47:27 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/12 19:59:01 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void	init_struct(t_solong *solong, char *map_path)
// {
// 	solong->map = NULL;
// 	solong->map_nb_line = 0;
// 	solong->map_path = map_path;
// 	get_mapline_number(solong);
// 	get_map(solong);// Free solong->map (char **)
// }

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		free(map[i++]);
	free(map);
}

void	get_images(t_solong *solong)
{
	int	width;
	int	height;

	width = 64;
	height = 64;
	solong->perso = mlx_xpm_file_to_image(solong->mlx_ptr, "./img/perso.xpm", &width, &height);
	solong->item = mlx_xpm_file_to_image(solong->mlx_ptr, "./img/item.xpm", &width, &height);
	solong->door = mlx_xpm_file_to_image(solong->mlx_ptr, "./img/door.xpm", &width, &height);
	solong->ground = mlx_xpm_file_to_image(solong->mlx_ptr, "./img/ground.xpm", &width, &height);
	solong->wall = mlx_xpm_file_to_image(solong->mlx_ptr, "./img/wall.xpm", &width, &height);
}

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
			if (solong->map[i][j] == '1')
				mlx_put_image_to_window(solong->mlx_ptr, solong->win, solong->wall, j * 64, i * 64);
			else if (solong->map[i][j] == '0')
				mlx_put_image_to_window(solong->mlx_ptr, solong->win, solong->ground, j * 64, i * 64);
			else if (solong->map[i][j] == 'P')
				mlx_put_image_to_window(solong->mlx_ptr, solong->win, solong->perso, j * 64, i * 64);
			else if (solong->map[i][j] == 'C')
				mlx_put_image_to_window(solong->mlx_ptr, solong->win, solong->item, j * 64, i * 64);
			else if (solong->map[i][j] == 'E')
				mlx_put_image_to_window(solong->mlx_ptr, solong->win, solong->door, j * 64, i * 64);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_solong	solong;
	t_map		map_info;
	// int	width;
	// int	height;
	// void	*perso;

	// width = 64;
	// height = 64;
	if (argc == 2)
	{
		check_arg_format(argv[1]);
		init_struct(&solong, argv[1]);
		check_map(&solong, &map_info);
		// free_map(solong.map);
		// free_map(map_info.map_copy);
		solong.mlx_ptr = mlx_init();
		solong.win = mlx_new_window(solong.mlx_ptr, map_info.map_len * 64, map_info.map_nb_line * 64, "SoLong");
		display_map(&solong);
		// perso = mlx_xpm_file_to_image(solong.mlx_ptr, "./img/perso.xpm", &width, &height);
		// mlx_put_image_to_window(solong.mlx_ptr, solong.win, perso, 0, 0);
		mlx_loop(solong.mlx_ptr);
	}
	else
		ft_printf("Le nombre d'arguments fourni est incorrect\n");
	return (0);
}

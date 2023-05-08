/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:47:27 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/08 14:14:40 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "./Libft/Includes/libft.h"
// #include "./minilibx-linux/mlx.h"
// #include <stdio.h>
// valgrind --leak-check=full --track-fds=yes --trace-children=yes
#include "so_long.h"

void	init_struct(t_solong *solong, char *map_path)
{
	solong->map = NULL;
	solong->map_nb_line = 0;
	solong->map_path = map_path;
	get_mapline_number(solong);
	get_map(solong);// Free solong->map (char **)
}

int	main(int argc, char **argv)
{
	t_solong	solong;
	t_map		map_info;

	if (argc == 2)
	{
		check_arg_format(argv[1]);
		init_struct(&solong, argv[1]); // Free a faire
		check_map(&solong, &map_info);
		// get_map(&solong, argv);
		// window.mlx_ptr = mlx_init();
		// window.win = mlx_new_window(window.mlx_ptr, 512, 500, "42 Test");
		// mlx_loop(window.mlx_ptr);
	}
	else
		ft_printf("Le nombre d'arguments fourni est incorrect\n");
	return (0);
}

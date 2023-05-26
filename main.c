/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:47:27 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/19 12:56:57 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_solong	solong;
	t_map		map_info;

	if (argc == 2)
	{
		check_arg_format(argv[1]);
		init_struct(&solong, argv[1]);
		check_map(&solong, &map_info);
		solong.map_copy = map_info.map_copy;
		solong.mlx_ptr = mlx_init();
		solong.win = mlx_new_window(solong.mlx_ptr, map_info.map_len * 64,
				map_info.map_nb_line * 64, "SoLong");
		display_map(&solong);
		mlx_key_hook(solong.win, move, &solong);
		mlx_hook(solong.win, KeyPress, KeyPressMask, 0, 0);
		mlx_hook(solong.win, DestroyNotify, StructureNotifyMask,
			ft_exit, &solong);
		mlx_loop(solong.mlx_ptr);
	}
	else
		ft_printf("Le nombre d'arguments fourni est incorrect\n");
	return (0);
}

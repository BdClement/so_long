/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:55:46 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/08 16:01:48 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./Libft/Includes/libft.h"
# include "./Libft/Includes/ft_printf.h"
# include "./Libft/Includes/get_next_line.h"
# include "./minilibx-linux/mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_solong
{
	void	*mlx_ptr;
	void	*win;
	char	*map_path;
	char	**map;
	int		map_nb_line;
}				t_solong;

typedef struct s_map
{
	int	start;
	int	exit;
	int	item;
	int	wall_around;
	int	valid_items;
	int	is_rectangle;
	int	not_allowed;
	int	map_len;
	int	map_nb_line;
}				t_map;

void	check_arg_format(char *arg);
void	init_struct(t_solong *solong, char *map_path);
void	init_map_struct(t_map *map_info);
void	get_mapline_number(t_solong *solong);
char	*ft_dup(char *str);
void	get_map(t_solong *solong);
void	check_map(t_solong *solong, t_map *map_info);
void	get_map_info(char **map, t_map *map_info);
void	display_error_message(t_map map_info);

#endif

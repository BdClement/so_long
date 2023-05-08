/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:14:50 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/08 12:54:58 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

//Malloc de mon solong->map a FREE !
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
	// i = 0;
	// while (solong->map[i] != NULL)
	// 	ft_printf("%s\n", solong->map[i++]);
	// i = 0;
	// while (solong->map[i] != NULL)
	// 	free(solong->map[i++]);
	// free(solong->map);
	close(fd);
}

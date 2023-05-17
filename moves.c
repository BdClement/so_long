/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:44:02 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/17 14:53:46 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Cette fonction deplace le personnage en bas
// 1- Affiche la position quittee par le joueur
// 2- Check si la nouvelle position est differente de 1 ou de 0
// En comptant le nombre d'items collectes et en gerant le cas ou
// le personnage se deplace sur l'exit (2 cas possible : Fin de jeu ou
// remettre l'exit au prochain move)
// 3- Affiche le personnage a la nouvelle position
// 4- Affihche le nombre de coups
// 5- Clean dans le cas ou le jeu est termine
void	go_up(t_solong *solong)
{
	if (solong->put_exit_back == 1)
	{
		mlx_put_image_to_window(solong->mlx_ptr, solong->win,
			solong->door, solong->cur.x * 64, solong->cur.y * 64);
		solong->put_exit_back = 0;
	}
	else
		mlx_put_image_to_window(solong->mlx_ptr, solong->win,
			solong->ground, solong->cur.x * 64, solong->cur.y * 64);
	if (solong->map[solong->cur.y - 1][solong->cur.x] == 'C')
		collected(solong, solong->cur.y - 1, solong->cur.x);
	else if (solong->map[solong->cur.y - 1][solong->cur.x] == 'E')
	{
		if (solong->collected == solong->nb_item)
			solong->put_exit_back = 2;
		else
			solong->put_exit_back = 1;
	}
	mlx_put_image_to_window(solong->mlx_ptr, solong->win,
		solong->perso, solong->cur.x * 64, (solong->cur.y - 1) * 64);
	solong->cur.y--;
	ft_printf("Nombre de coups : %d\n", solong->moves++);
	if (solong->put_exit_back == 2)
		clean(solong);
}

// Cette fonction deplace le personnage en bas
// 1- Affiche la position quittee par le joueur
// 2- Check si la nouvelle position est differente de 1 ou de 0
// En comptant le nombre d'items collectes et en gerant le cas ou
// le personnage se deplace sur l'exit (2 cas possible : Fin de jeu ou
// remettre l'exit au prochain move)
// 3- Affiche le personnage a la nouvelle position
// 4- Affihche le nombre de coups
// 5- Clean dans le cas ou le jeu est termine
void	go_down(t_solong *solong)
{
	if (solong->put_exit_back == 1)
	{
		mlx_put_image_to_window(solong->mlx_ptr, solong->win,
			solong->door, solong->cur.x * 64, solong->cur.y * 64);
		solong->put_exit_back = 0;
	}
	else
		mlx_put_image_to_window(solong->mlx_ptr, solong->win,
			solong->ground, solong->cur.x * 64, solong->cur.y * 64);
	if (solong->map[solong->cur.y + 1][solong->cur.x] == 'C')
		collected(solong, solong->cur.y + 1, solong->cur.x);
	else if (solong->map[solong->cur.y + 1][solong->cur.x] == 'E')
	{
		if (solong->collected == solong->nb_item)
			solong->put_exit_back = 2;
		else
			solong->put_exit_back = 1;
	}
	mlx_put_image_to_window(solong->mlx_ptr, solong->win,
		solong->perso, solong->cur.x * 64, (solong->cur.y + 1) * 64);
	solong->cur.y++;
	ft_printf("Nombre de coups : %d\n", solong->moves++);
	if (solong->put_exit_back == 2)
		clean(solong);
}

// Cette fonction deplace le personnage a gauche
// 1- Affiche la position quittee par le joueur
// 2- Check si la nouvelle position est differente de 1 ou de 0
// En comptant le nombre d'items collectes et en gerant le cas ou
// le personnage se deplace sur l'exit (2 cas possible : Fin de jeu ou
// remettre l'exit au prochain move)
// 3- Affiche le personnage a la nouvelle position
// 4- Affihche le nombre de coups
// 5- Clean dans le cas ou le jeu est termine
void	go_left(t_solong *solong)
{
	if (solong->put_exit_back == 1)
	{
		mlx_put_image_to_window(solong->mlx_ptr, solong->win,
			solong->door, solong->cur.x * 64, solong->cur.y * 64);
		solong->put_exit_back = 0;
	}
	else
		mlx_put_image_to_window(solong->mlx_ptr, solong->win,
			solong->ground, solong->cur.x * 64, solong->cur.y * 64);
	if (solong->map[solong->cur.y][solong->cur.x - 1] == 'C')
		collected(solong, solong->cur.y, solong->cur.x - 1);
	else if (solong->map[solong->cur.y][solong->cur.x - 1] == 'E')
	{
		if (solong->collected == solong->nb_item)
			solong->put_exit_back = 2;
		else
			solong->put_exit_back = 1;
	}
	mlx_put_image_to_window(solong->mlx_ptr, solong->win,
		solong->perso, (solong->cur.x - 1) * 64, solong->cur.y * 64);
	solong->cur.x--;
	ft_printf("Nombre de coups : %d\n", solong->moves++);
	if (solong->put_exit_back == 2)
		clean(solong);
}

// Cette fonction deplace le personnage a droite
// 1- Affiche la position quittee par le joueur
// 2- Check si la nouvelle position est differente de 1 ou de 0
// En comptant le nombre d'items collectes et en gerant le cas ou
// le personnage se deplace sur l'exit (2 cas possible : Fin de jeu ou
// remettre l'exit au prochain move)
// 3- Affiche le personnage a la nouvelle position
// 4- Affihche le nombre de coups
// 5- Clean dans le cas ou le jeu est termine
void	go_right(t_solong *solong)
{
	if (solong->put_exit_back == 1)
	{
		mlx_put_image_to_window(solong->mlx_ptr, solong->win,
			solong->door, solong->cur.x * 64, solong->cur.y * 64);
		solong->put_exit_back = 0;
	}
	else
		mlx_put_image_to_window(solong->mlx_ptr, solong->win,
			solong->ground, solong->cur.x * 64, solong->cur.y * 64);
	if (solong->map[solong->cur.y][solong->cur.x + 1] == 'C')
		collected(solong, solong->cur.y, solong->cur.x + 1);
	else if (solong->map[solong->cur.y][solong->cur.x + 1] == 'E')
	{
		if (solong->collected == solong->nb_item)
			solong->put_exit_back = 2;
		else
			solong->put_exit_back = 1;
	}
	mlx_put_image_to_window(solong->mlx_ptr, solong->win,
		solong->perso, (solong->cur.x + 1) * 64, solong->cur.y * 64);
	solong->cur.x++;
	ft_printf("Nombre de coups : %d\n", solong->moves++);
	if (solong->put_exit_back == 2)
		clean(solong);
}

// Cette fonction rassemble tout les mouvements possible
// Et appelle la fonction concernee en fonction de la touche
// W =119  A=97 S=115  D=100
int	move(int keycode, t_solong *solong)
{
	if (keycode == 0xFF1B)
		ft_exit(solong);
	if (keycode == 119 && solong->map[solong->cur.y - 1][solong->cur.x] != '1')
		go_up(solong);
	else if (keycode == 115
		&& solong->map[solong->cur.y + 1][solong->cur.x] != '1')
		go_down(solong);
	else if (keycode == 97
		&& solong->map[solong->cur.y][solong->cur.x - 1] != '1')
		go_left(solong);
	else if (keycode == 100
		&& solong->map[solong->cur.y][solong->cur.x + 1] != '1')
		go_right(solong);
	if (solong->collected == solong->nb_item && solong->all_collected == 0)
	{
		solong->all_collected = 1;
		ft_printf("Tout les items ont été collectés. Il faut sortir \n");
	}
	return (keycode);
}

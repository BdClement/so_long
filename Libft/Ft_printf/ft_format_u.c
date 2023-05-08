/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:09:27 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/05 13:28:38 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_printf.h"

// Calcul la taille de nb_naked avec unsigned int
int	count_len_uint(unsigned int nb, t_arg format)
{
	int	size;

	size = 0;
	if (nb == 0 && format.dot == 1 && format.precision == 0)
		return (0);
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

// Compte la taille du nombre habille
// Nombre habille = nombre + precision + 1 si '+' ou 'space'
int	count_len_total_uint(unsigned int nb, t_arg format)
{
	int	len_total;

	len_total = 0;
	if (count_len_uint(nb, format) < format.precision)
		len_total = format.precision;
	else
		len_total = count_len_uint(nb, format);
	return (len_total);
}

//Calcule la taille totale de ce que l'on va afficher pour un unsigned int
int	size_printed_uint(t_arg format, unsigned int nb)
{
	int	size;
	int	nb_len;

	size = 0;
	nb_len = count_len_uint(nb, format);
	if (nb_len > format.width)
		size = nb_len;
	else
		size = format.width;
	if (format.precision > format.width)
	{
		if (count_len_uint(nb, format) < format.precision)
			size = format.precision;
	}
	return (size);
}

void	ft_putnbr_u(unsigned int nb, int *len)
{
	unsigned int	n;
	char			c;

	n = nb;
	if (n > 9)
	{
		ft_putnbr_u(n / 10, len);
	}
	c = '0' + (n % 10);
	write(1, &c, 1);
	(*len)++;
}

/** @brief Affiche un unsigned int (conversion si neagtif)
 * On gere d'abord le cas du nombre 0 avec precision 0
 - On affiche les espace de surplus de largeur minimal avant ou apres le nombre
 - On affiche (taille Total - taille total du nombre) 0 si le flag 0 est present
 - On affiche le nombre
 */
void	print_format_u(t_arg format, va_list arg, int *len)
{
	unsigned int	nb;
	int				len_total;

	nb = (unsigned int)va_arg(arg, int);
	len_total = count_len_total_uint(nb, format);
	if (nb == 0 && format.dot == 1 && format.precision == 0)
	{
		ft_put_space(size_printed_uint(format, nb) - len_total, len);
		return ;
	}
	if (format.minus == 0 && format.zero == 0)
		ft_put_space(size_printed_uint(format, nb) - len_total, len);
	if (format.zero == 1)
		ft_put_zero(size_printed_uint(format, nb) - len_total, len);
	if (count_len_uint(nb, format) < len_total)
		ft_put_zero(len_total - count_len_uint(nb, format), len);
	ft_putnbr_u(nb, len);
	if (format.minus == 1)
		ft_put_space(size_printed_uint(format, nb) - len_total, len);
}

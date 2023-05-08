/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:00:39 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/05 13:28:30 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_printf.h"

// calcul la taille du nombre en base 16
int	count_len_ptr(unsigned long nb)
{
	int	size;

	size = 0;
	if (nb == 0)
		return (5);
	while (nb > 0)
	{
		nb /= 16;
		size++;
	}
	return (size);
}

//Calcul la taille totale du nombre en haxadecimal c'est a dire
// + ou space + 0x + precision + taille du nombre
int	count_len_total_ptr(unsigned long nb, t_arg format)
{
	int	len_total;

	len_total = count_len_ptr(nb);
	if (nb == 0)
		return (5);
	if (nb != 0)
		len_total += 2;
	if (format.precision > count_len_ptr(nb))
		len_total += format.precision - count_len_ptr(nb);
	if (format.plus == 1 || format.space == 1)
		len_total++;
	return (len_total);
}

void	ft_put_ptr(unsigned long nb, char *base, int *len)
{
	unsigned long	n;

	n = nb;
	if (n >= 16)
		ft_put_ptr(n / 16, base, len);
	write(1, &base[n % 16], 1);
	(*len)++;
}

void	ft_print_ptr(unsigned long nb, int *len, t_arg format)
{
	unsigned long	n;

	n = nb;
	if (n == 0)
	{
		write(1, "(nil)", 5);
		(*len) += 5;
		return ;
	}
	else
	{
		write(1, "0x", 2);
		(*len) += 2;
	}
	if (format.precision > count_len_ptr(nb))
		ft_put_zero(format.precision - count_len_ptr(nb), len);
	ft_put_ptr(n, "0123456789abcdef", len);
}

/**
 * @brief Affiche l'argument en haxadecimal
 * D'abord on compte la taille totale de ce que lon va afficher
 * On affiche les espaces correspondant au surplus de la largeur minimale
 * On affiche le signe ou espace des flags '+' ou ' '
 * Et on affiche largument ou l'inverse
 */
void	print_format_p(t_arg format, va_list arg, int *len)
{
	unsigned long	adress;
	int				len_total_ptr;
	int				size_printed;

	adress = va_arg(arg, unsigned long);
	len_total_ptr = count_len_total_ptr(adress, format);
	if (len_total_ptr < format. width)
		size_printed = format.width;
	else
		size_printed = len_total_ptr;
	if (format.minus == 1)
	{
		print_sign_ptr(adress, format, len);
		ft_print_ptr(adress, len, format);
	}
	ft_put_space(size_printed - len_total_ptr, len);
	if (format.minus == 0)
	{
		print_sign_ptr(adress, format, len);
		ft_print_ptr(adress, len, format);
	}
}

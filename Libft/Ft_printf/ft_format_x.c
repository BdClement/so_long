/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:16:47 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/05 13:28:42 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_printf.h"

// Calcul la taille de nb_naked en base 16
int	count_len_hexa(unsigned int nb, t_arg format)
{
	int	size;

	size = 0;
	if (nb == 0 && format.dot == 1 && format.precision == 0)
		return (0);
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 16;
		size++;
	}
	return (size);
}

// Calcul la taille totale a afficher pour un UI en hexa
int	size_printed_hexa(t_arg format, unsigned int nb)
{
	int	size;
	int	nb_len;

	size = 0;
	nb_len = count_len_hexa(nb, format);
	if (nb == 0 && format.dot == 1 && format.precision == 0)
		return (format.width);
	if (format.sharp == 1 && nb != 0)
		nb_len += 2;
	if (nb_len > format.width)
		size = nb_len;
	else
		size = format.width;
	if (format.precision > format.width
		&& count_len_hexa(nb, format) < format.precision)
			size = format.precision;
	return (size);
}

// Compte la taille du nombre habille
// Nombre habille = nombre + precision + 2 si '#'
int	count_len_total_hexa(unsigned int nb, t_arg format)
{
	int	len_total;

	len_total = 0;
	if (nb == 0 && format.dot == 1 && format.precision == 0)
		return (0);
	if (count_len_hexa(nb, format) < format.precision)
		len_total = format.precision;
	else
		len_total = count_len_hexa(nb, format);
	if (format.sharp == 1 && nb != 0)
		len_total += 2;
	return (len_total);
}

void	print_body_hexa(t_arg format, unsigned int nb, int *len)
{
	int	nb_dressed;
	int	size_printed;

	nb_dressed = count_len_total_hexa(nb, format);
	size_printed = size_printed_hexa(format, nb);
	if (format.specifier == 'x' && nb != 0 && format.sharp == 1)
		ft_putstr("0x", len);
	else if (format.specifier == 'X' && nb != 0 && format.sharp == 1)
		ft_putstr("0X", len);
	if (format.zero == 1)
		ft_put_zero(size_printed - nb_dressed, len);
	ft_put_zero(format.precision - count_len_hexa(nb, format), len);
	if (format.specifier == 'x')
		ft_put_hexa(nb, "0123456789abcdef", len);
	else if (format.specifier == 'X')
		ft_put_hexa(nb, "0123456789ABCDEF", len);
}

void	print_format_x(t_arg format, va_list arg, int *len)
{
	unsigned int	nb;
	int				nb_dressed;
	int				size_printed;

	nb = va_arg(arg, unsigned int);
	nb_dressed = count_len_total_hexa(nb, format);
	size_printed = size_printed_hexa(format, nb);
	if (nb == 0 && format.dot == 1 && format.precision == 0)
	{
		ft_put_space(size_printed, len);
		return ;
	}
	if (format.minus == 0 && format.zero == 0 && nb_dressed >= format.precision)
		ft_put_space(size_printed - nb_dressed, len);
	print_body_hexa(format, nb, len);
	if (format.minus == 1)
		ft_put_space(size_printed - nb_dressed, len);
}

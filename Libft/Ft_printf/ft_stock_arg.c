/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:39:39 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/05 13:28:57 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_printf.h"

//Initialise la strucure
void	struct_init(t_arg *format)
{
	format->specifier = 0;
	format->zero = 0;
	format->minus = 0;
	format->dot = 0;
	format->sharp = 0;
	format->space = 0;
	format->plus = 0;
	format->width = 0;
	format->precision = 0;
}

// Compte la largeur minimale
// Count rajoute pour cas comme %- #00.9p
void	count_width(const char *str, t_arg *format)
{
	int	count;
	int	width;

	width = 0;
	count = 0;
	while (is_specifier(*str) != 1 && (*str) != '.')
	{
		if ((*str) == '0')
			format->zero = 1;
		while ((*str) > 47 && (*str) < 58)
		{
			width = (width * 10) + ((*str) - 48);
			str++;
			count++;
		}
		if (count != 0)
		{
			format->width = width;
			return ;
		}
		str++;
	}
}

// Compte la precision
void	count_precision(const char *str, t_arg *format)
{
	int	count;

	count = 0;
	while (is_specifier(*str) != 1)
	{
		if ((*str) == '.')
		{
			format->dot = 1;
			str++;
			while ((*str) > 47 && (*str) < 58)
			{
				count = (count * 10) + ((*str) - 48);
				str++;
			}
			format->precision = count;
		}
		str++;
	}
}

//Remplis la strucure avec les elements contenus dans l'argument
//On remet format.zero a 0 si il est combine a une precision
void	read_format(const char *str, t_arg *format)
{
	count_width(str, format);
	count_precision(str, format);
	while (is_specifier(*str) != 1)
	{
		if ((*str) == ' ')
			format->space = 1;
		else if ((*str) == '#')
			format->sharp = 1;
		else if ((*str) == '-')
			format->minus = 1;
		else if ((*str) == '+')
			format->plus = 1;
		str++;
	}
	format->specifier = *str;
	if (format->zero == 1 && format->dot == 1)
		format->zero = 0;
}

// compte la taille de l'argument pour pouvoir avancer au caractere suivant
int	size_of_arg(const char *str)
{
	int	size;

	size = 0;
	while (is_specifier((*str++)) != 1)
		size++;
	return (size);
}

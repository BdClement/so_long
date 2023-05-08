/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:12:01 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/05 13:34:54 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_printf.h"

// int	ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	if (s == NULL)
// 		return (0);
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

int	count_len_total_str(char *str, t_arg format)
{
	int	len_total;
	int	strlen;

	len_total = 0;
	if (str == NULL)
		strlen = 6;
	else
		strlen = ft_strlen(str);
	if (format.dot == 1 && strlen > format.precision)
		len_total = format.precision;
	else
		len_total = strlen;
	return (len_total);
}

void	ft_putstr(char *str, int *len)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		(*len) += 6;
		return ;
	}
	while (str[i] != '\0')
	{
		write(1, str + i, 1);
		i++;
	}
	(*len) += i;
}

/**
 * @brief Affiche seulement les caracteres d'une chaine
 * autorise par la precision.
 * - On compte d'abord la taille de la chaine
 * - Puis on affiche les caracteres autorise
 * - Ou lensemble de la chaine avec un putstr simple
 */
void	ft_putstr_precision(char *str, int *len, t_arg format)
{
	int	i;
	int	size_str;

	i = 0;
	if (str != NULL)
		size_str = ft_strlen(str);
	else
		size_str = 6;
	if (format.dot == 1 && format.precision < size_str)
	{
		if (str == NULL)
		{
			if (format.precision >= 6)
				ft_putstr(str, len);
			return ;
		}
		while (str[i] != '\0' && i < format.precision)
		{
			write(1, str + i, 1);
			i++;
		}
		(*len) += i;
	}
	else
		ft_putstr(str, len);
}

/**
 * @brief Affiche une chaine de caracteres
 * Si la largeur est plus grande que la taille totale :
 * On affiche les espaces correspondant au surplus de la largeur minimale
 * ou a la precision plus grande que la chaine elle meme
 * Puis on affiche la chaine de caractere grace a ft_putstr_precision
 */
void	print_format_s(t_arg format, va_list arg, int *len)
{
	char	*str;
	int		size_str;

	str = va_arg(arg, char *);
	size_str = count_len_total_str(str, format);
	if (format.width > size_str)
	{
		if (format.minus == 1)
			ft_putstr_precision(str, len, format);
		ft_put_space(format.width - size_str, len);
		if (format.dot == 1)
			ft_put_space(count_len_total_str(str, format) - format.precision,
				len);
		if (format.minus == 0)
			ft_putstr_precision(str, len, format);
	}
	else
		ft_putstr_precision(str, len, format);
}

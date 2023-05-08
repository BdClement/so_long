/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:08:37 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/05 13:28:18 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_printf.h"

void	ft_putchar(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

void	print_format_c(t_arg format, va_list arg, int *len)
{
	char	c;
	int		i;

	i = 0;
	c = va_arg(arg, int);
	if (format.width > 1)
	{
		if (format.minus == 1)
			ft_putchar(c, len);
		while (i++ < format.width - 1)
			ft_putchar(' ', len);
		if (format.minus == 0)
			ft_putchar(c, len);
	}
	else
		ft_putchar(c, len);
}

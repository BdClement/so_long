/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:13:52 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/05 13:28:48 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_printf.h"

void	ft_putnbr(int nb, int *len)
{
	int		n;
	char	c;

	n = nb;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*len) += 11;
		return ;
	}
	if (n < 0)
	{
		n = n * (-1);
		write(1, "-", 1);
		(*len)++;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10, len);
	}
	c = '0' + (n % 10);
	write(1, &c, 1);
	(*len)++;
}

// Detemine si le caractere est un specifier ou non
int	is_specifier(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'X')
		return (1);
	else if (c == 'd' || c == 'd' || c == 'i')
		return (1);
	else if (c == 'u' || c == 'x' || c == '%')
		return (1);
	return (0);
}

// Afficher des spaces nb fois pour eviter de faire des boucles
void	ft_put_space(int nb, int *len)
{
	int	i;

	i = 0;
	if (nb <= 0)
		return ;
	while (i++ < nb)
		ft_putchar(' ', len);
}

// Afficher des 0 nb fois pour eviter de faire des boucles
void	ft_put_zero(int nb, int *len)
{
	int	i;

	i = 0;
	if (nb <= 0)
		return ;
	while (i++ < nb)
		ft_putchar('0', len);
}

void	ft_put_hexa(unsigned int nb, char *base, int *len)
{
	long unsigned int	n;

	n = nb;
	if (n >= 16)
		ft_put_hexa(n / 16, base, len);
	write(1, &base[n % 16], 1);
	(*len)++;
}

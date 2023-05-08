/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:12:46 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/05 13:28:53 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_printf.h"

// Affiche le + ou ' ' des flags correspondants
void	print_sign_ptr(unsigned long nb, t_arg format, int *len)
{
	if (format.plus == 1 && nb > 0)
		ft_putchar('+', len);
	if (format.space == 1 && nb > 0)
		ft_putchar(' ', len);
}

//Affiche le signe (si il le faut) avant d'afficher le corps du nombre
void	print_sign(t_arg format, int nb, int *len)
{
	if (nb < 0)
		ft_putchar('-', len);
	else if (nb >= 0 && format.plus == 1)
		ft_putchar('+', len);
	else if (nb >= 0 && format.space == 1)
		ft_put_space(1, len);
}

int	print_arg(va_list arg, const char *str, int *len)
{
	t_arg	format;

	struct_init(&format);
	read_format(str, &format);
	if (format.specifier == '%')
		ft_putchar('%', len);
	else if (format.specifier == 'c')
		print_format_c(format, arg, len);
	else if (format.specifier == 's')
		print_format_s(format, arg, len);
	else if (format.specifier == 'p')
		print_format_p(format, arg, len);
	else if (format.specifier == 'u')
		print_format_u(format, arg, len);
	else if (format.specifier == 'd' || format.specifier == 'i')
		print_format_di(format, arg, len);
	else if (format.specifier == 'x' || format.specifier == 'X')
		print_format_x(format, arg, len);
	return (size_of_arg(str));
}

// Test si on est pas arriver a '\0' a cause des bonus et avance le pointeur
//en fin de boucle
int	ft_printf(const char *str, ...)
{
	int		len;
	va_list	arg;

	len = 0;
	va_start(arg, str);
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		if (*str != '%')
			ft_putchar(*str, &len);
		else
		{
			str++;
			str += print_arg(arg, str, &len);
		}
		str++;
	}
	va_end(arg);
	return (len);
}

// #include <stdio.h>

// int main()
// {
// 	int i,j;

// 	i = 0;
// 	j = 0;
// 	i = ft_printf("%c\n", 'a');
// 	j = printf("%c\n", 'a');
// 	printf("Valeur de fpt = %d\nValeur de pirntf = %d\n", i, j);
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:16:00 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/05 13:33:55 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_arg
{
	char	specifier;
	int		zero;
	int		minus;
	int		dot;
	int		sharp;
	int		space;
	int		plus;
	int		width;
	int		precision;

}					t_arg;

int		ft_printf(const char *str, ...);
void	ft_putchar(char c, int *len);
void	ft_putnbr(int nb, int *len);
void	ft_putnbr_u(unsigned int nb, int *len);
void	ft_putstr(char *str, int *len);
void	ft_put_hexa(unsigned int nb, char *base, int *len);
void	ft_put_ptr(unsigned long nb, char *base, int *len);
void	ft_print_ptr(unsigned long nb, int *len, t_arg format);
int		is_flag(char c);
int		size_of_arg(const char *str);
void	read_format(const char *str, t_arg *format);
void	count_precision(const char *str, t_arg *format);
void	count_width(const char *str, t_arg *format);
void	struct_init(t_arg *format);
int		is_specifier(char c);
// int		ft_strlen(const char *s);
void	print_format_c(t_arg format, va_list arg, int *len);
void	ft_putstr_precision(char *str, int *len, t_arg format);
void	print_format_s(t_arg format, va_list arg, int *len);
void	print_format_p(t_arg format, va_list arg, int *len);
int		count_len_uint(unsigned int nb, t_arg format);
int		count_len_int(int nb, t_arg format);
int		count_len_hexa(unsigned int nb, t_arg format);
void	ft_put_space(int nb, int *len);
void	ft_put_zero(int nb, int *len);
int		size_printed_uint(t_arg format, unsigned int nb);
int		size_printed_hexa(t_arg format, unsigned int nb);
int		size_printed_int(t_arg format, int nb);
void	print_format_u(t_arg format, va_list arg, int *len);
int		count_len_totalint(int nb, t_arg format);
int		count_len_total_str(char *str, t_arg format);
int		count_len_total_uint(unsigned int nb, t_arg format);
int		count_len_total_hexa(unsigned int nb, t_arg format);
void	print_sign(t_arg format, int nb, int *len);
void	print_body(t_arg format, int nb, int *len);
void	print_format_di(t_arg format, va_list arg, int *len);
void	print_body_hexa(t_arg format, unsigned int nb, int *len);
void	print_format_x(t_arg format, va_list arg, int *len);
int		print_arg(va_list arg, const char *str, int *len);
int		count_len_ptr(unsigned long nb);
int		count_len_total_ptr(unsigned long nb, t_arg format);
void	print_sign_ptr(unsigned long nb, t_arg format, int *len);

#endif

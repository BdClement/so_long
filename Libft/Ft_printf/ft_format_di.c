/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:03:25 by clbernar          #+#    #+#             */
/*   Updated: 2023/05/05 13:28:26 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_printf.h"

// Calcul la taille de nb_naked avec int
int	count_len_int(int nb, t_arg format)
{
	int	size;

	size = 0;
	if (nb == 0 && format.dot == 1 && format.precision == 0)
		return (0);
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

// Compte la taille du nombre habille
// Nombre habille = nombre + precision + 1 si + ou space
int	count_len_totalint(int nb, t_arg format)
{
	int	len_total;

	len_total = 0;
	if (count_len_int(nb, format) < format.precision)
		len_total = format.precision;
	else
		len_total = count_len_int(nb, format);
	if ((format.plus == 1 || format.space == 1) && nb >= 0)
		len_total++;
	if (nb < 0)
		len_total++;
	return (len_total);
}

//@brief Calcule la taille totale de ce que l'on va afficher pour int
int	size_printed_int(t_arg format, int nb)
{
	int	size;
	int	nb_len;

	size = 0;
	nb_len = count_len_int(nb, format);
	if ((format.plus == 1 && nb >= 0) || (format.space == 1 && nb >= 0))
		nb_len++;
	if (format.sharp == 1)
		nb_len += 2;
	if (nb_len > format.width)
		size = nb_len;
	else
		size = format.width;
	if (format.precision > format.width)
	{
		if (count_len_int(nb, format) <= format.precision)
			size = format.precision;
		if (count_len_int(nb, format) <= format.precision && nb < 0)
			size++;
		if ((format.plus == 1 && nb >= 0) || (format.space == 1 && nb >= 0))
			size++;
		if (format.sharp == 1)
			size += 2;
	}
	return (size);
}

/**
 * @brief [Pareil que pour print_format_di on gere dabord le cas 0 precision 0
 * c'est a dire quon affiche ici les espaces correspondants a la largeur minimale
 * puisqu'on ne le fait pas dans print_format_di a cause du return empechant
 * d'afficher le 0 = format.width - largeur minimal au cas ou un signe a deja
 * ete affiche avant]
 * Affiche le corps du nombre c'est a dire
 * le nombre + precision + des 0 si demande par le drapeau 0
 * Le nombre est toujours affiche en positif puisque le signe a deja ete affiche
 * @param format Structure contenant les elements de l'argument
 * @param nb
 * @param len
 */
void	print_body(t_arg format, int nb, int *len)
{
	int	nb_naked;
	int	nb_dressed;

	nb_naked = count_len_int(nb, format);
	nb_dressed = count_len_totalint(nb, format);
	if (nb == 0 && format.dot == 1 && format.precision == 0)
	{
		ft_put_space(format.width - nb_dressed, len);
		return ;
	}
	if (nb < 0 && format.precision > format.width)
		nb_dressed -= 1;
	if (format.zero == 1)
		ft_put_zero(size_printed_int(format, nb) - nb_dressed, len);
	if (format.precision > nb_naked)
		ft_put_zero(format.precision - nb_naked, len);
	if (nb == -2147483648)
	{
		ft_putstr("2147483648", len);
		return ;
	}
	if (nb < 0)
		nb = nb * (-1);
	ft_putnbr(nb, len);
}

// Retirer 1 a nb_dressed seulement si nb
//negatif et precision>width Regarder pourquoi?
/**
 * @brief On gere d'abord le cas 0 avec precision de 0
 *  en affichant le signe avant ou apres le corps, qui est dans ce cas
 * les espaces de la largeur minimale, en fonction du flag '-'
 * On affiche les espace soit avant soit apres en fonction du flag '-'
 *On affiche le signe puis le corps du nombre
 */
void	print_format_di(t_arg format, va_list arg, int *len)
{
	int	nb;
	int	nb_dressed;
	int	size_printed;

	nb = va_arg(arg, int);
	nb_dressed = count_len_totalint(nb, format);
	size_printed = size_printed_int(format, nb);
	if (nb == 0 && format.dot == 1 && format.precision == 0)
	{
		if (format.minus == 1)
			print_sign(format, nb, len);
		print_body(format, nb, len);
		if (format.minus == 0)
			print_sign(format, nb, len);
		return ;
	}
	if (format.minus == 0 && format.zero == 0
		&& nb_dressed >= format.precision)
		ft_put_space(size_printed - nb_dressed, len);
	print_sign(format, nb, len);
	print_body(format, nb, len);
	if (format.minus == 1)
		ft_put_space(size_printed - nb_dressed, len);
}

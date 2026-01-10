/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:20:34 by aghergut          #+#    #+#             */
/*   Updated: 2026/01/10 12:11:47 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putuint(unsigned int value, int length)
{
	char	c;

	if (length > 0)
	{
		ft_putuint(value / 10, length - 1);
		c = (value % 10) + '0';
		write(1, &c, 1);
	}
}

static int	ft_precu(t_flags *flags, unsigned int n, int num_len)
{
	int	total_len;
	int	print_len;

	print_len = num_len;
	if (flags->prec && flags->precw > num_len)
		print_len = flags->precw;
	if (flags->prec && !flags->precw && !n)
		print_len = 0;
	total_len = print_len;
	if (!flags->left)
		total_len += ft_fill(flags->width, print_len, ' ');
	ft_fill(flags->precw, num_len, '0');
	if (!(flags->prec && flags->precw == 0 && n == 0))
		ft_putuint(n, num_len);
	if (flags->left)
		total_len += ft_fill(flags->width, print_len, ' ');
	return (total_len);
}

int	ft_printu(t_flags *flags, unsigned int number)
{
	char	pad_char;
	int		num_len;
	int		total_len;

	num_len = ft_numlen(number);
	if (flags->prec)
		return (ft_precu(flags, number, num_len));
	total_len = num_len;
	if (!flags->left)
	{
		if (flags->zpad)
			pad_char = '0';
		else
			pad_char = ' ';
		total_len += ft_fill(flags->width, num_len, pad_char);
	}
	ft_putuint(number, num_len);
	if (flags->left)
		total_len += ft_fill(flags->width, num_len, ' ');
	return (total_len);
}

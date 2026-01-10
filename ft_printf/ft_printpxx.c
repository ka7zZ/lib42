/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpxx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:18:55 by aghergut          #+#    #+#             */
/*   Updated: 2026/01/10 13:15:49 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nullcase(t_flags *flags)
{
	int	width;
	int	length;

	width = 0;
	length = 5;
	if (!flags->left)
		width += ft_fill(flags->width, length, ' ');
	width += write(1, "(nil)", 5);
	if (flags->left)
		width += ft_fill(flags->width, length, ' ');
	return (width);
}

static int	ft_precpxx(t_flags *flags, unsigned long long mem, int len, char f)
{
	int	total_len;

	if (flags->precw < len)
		flags->precw = len;
	total_len = flags->precw + flags->alt;
	if (!flags->left)
		total_len += ft_fill(flags->width, total_len, ' ');
	ft_flagalt(flags, f);
	ft_fill(flags->precw, len, '0');
	if (!(mem == 0 && flags->prec == 0 && flags->precw == 0))
		ft_gethex(mem, f);
	else if (flags->width > 0)
		write (1, " ", 1);
	if (flags->left)
		total_len += ft_fill(flags->width, total_len, ' ');
	return (total_len);
}

static int	ft_hex_output(t_flags *flags, unsigned long long mem, char type)
{
	int	len;
	int	print_len;
	
	len = ft_memlen(mem);
	if (mem == 0)
		len = 1;
	if (type == 'p')
		flags->alt = 2;
	else if (mem == 0)
		flags->alt = 0;
	print_len = len + flags->alt;
	if (!flags->left && !flags->zpad)
		print_len += ft_fill(flags->width, print_len, ' ');
	ft_flagalt(flags, type);
	if (flags->zpad)
		print_len += ft_fill(flags->width, print_len, ' ');
	if (mem == 0)
		write(1, "0", 1);
	else
		ft_gethex(mem, type);
	if (flags->left)
		print_len += ft_fill(flags->width, print_len, ' ');
	return (print_len);
}

int	ft_printpxx(va_list *args, t_flags *flags, char type)
{
	unsigned long long	mem;

	if (type == 'p')
	{
		mem = (unsigned long long)va_arg(*args, void *);
		if (mem == 0)
			return (ft_nullcase(flags));
		flags->alt = 2;
	}
	else
	{
		mem = (unsigned int)va_arg(*args, unsigned int);
		if (flags->alt && mem != 0)
			flags->alt = 2;
		else
			flags->alt = 0;
	}
	if (flags->prec)
		return (ft_precpxx(flags, mem, ft_memlen(mem), type));
	return (ft_hex_output(flags, mem, type));
}

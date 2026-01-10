/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:18:21 by aghergut          #+#    #+#             */
/*   Updated: 2026/01/10 17:58:10 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_nullcase(t_flags *flags)
{
	int	width;
	int	print_len;

	width = 0;
	print_len = 6;
	if ((flags->prec && flags->precw < 6))
		print_len = 0;
	if (!flags->left)
		width += ft_fill(flags->width, print_len, ' ');
	if (print_len > 0)
		width += write(1, "(null)", 6);
	if (flags->left)
		width += ft_fill(flags->width, print_len, ' ');
	return (width);
}

int	ft_printstr(t_flags *flags, char *content)
{
	int	len;
	int print_len;

	if (!content)
		return (ft_nullcase(flags));
	len = ft_strlen(content);
	print_len = len;
	if (flags->prec && flags->precw < len)
		print_len = flags->precw;
	len = print_len;
	if (!flags->left)
		len = ft_fill(flags->width, print_len, ' ');
	write(1, content, print_len);
	if (flags->left)
		len += ft_fill(flags->width, print_len, ' ');
	return (len);
}

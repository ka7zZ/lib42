/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:16:59 by aghergut          #+#    #+#             */
/*   Updated: 2026/01/10 13:03:55 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_parse_values(va_list *args, t_flags *flags, char type)
{
	if (type == 'c')
		return (ft_printchar(flags, (char)va_arg(*args, int)));
	if (type == 's')
		return (ft_printstr(flags, va_arg(*args, char *)));
	if (ft_strchr("pxX", type))
		return (ft_printpxx(args, flags, type));
	if (type == 'u')
		return (ft_printu(flags, va_arg(*args, unsigned int)));
	if (type == 'd' || type == 'i')
		return (ft_printint(flags, va_arg(*args, int), type));
	if (type == '%')
		return (ft_printchar(flags, '%'));
	return (0);
}

static int	ft_parse_main(va_list *args, t_flags *flags, const char *format)
{
	int	width;

	width = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			ft_memset(flags, 0, sizeof(t_flags));
			format = ft_flagadd(args, flags, format);
			if (*format)
				width += ft_parse_values(args, flags, *format);
		}
		else
		{
			write(1, &*format, 1);
			width++;
		}
		format++;
	}
	return (width);
}

int	ft_printf(const char *format, ...)
{
	va_list	pv;
	t_flags	flags;
	int		width;

	va_start(pv, format);
	width = ft_parse_main(&pv, &flags, format);
	va_end(pv);
	return (width);
}

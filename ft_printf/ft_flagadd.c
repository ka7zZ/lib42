/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:18:36 by aghergut          #+#    #+#             */
/*   Updated: 2026/01/09 12:29:53 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	*get_width(va_list *args, int *width, const char *f)
{
	*width = 0;
	if (*f == '*')
	{
		*width = va_arg(*args, int);
		f++;
	}
	while (ft_isdigit(*f))
	{
		*width = *width * 10 + (*f - '0');
		f++;
	}
	return (f);
}

static const char	*ft_wflags(va_list *args, t_flags *flags, const char *f)
{
	while (*f == '-')
	{
		flags->left = 1;
		f++;
		
	}
	if (*f == '0')
	{
		if (flags->left == 0)
			flags->zpad = 1;
		f++;
	}	
	if ((ft_isdigit(*f)) || *f == '*')
	{
		f = get_width(args, &flags->width, f);
		if (flags->width < 0)
		{
			flags->width *= -1;
			flags->left = 1;
			flags->zpad = 0;
		}
	}
	return (f);
}

static const char	*ft_addprec(va_list *args, t_flags *flags, const char *f)
{
	if (*f == '.')
	{
		f++;
		if (*f == '*' && !flags->prec)
		{
			flags->precw = va_arg(*args, int);
			f++;
		}
		while (ft_isdigit(*f))
		{
			flags->precw = flags->precw * 10 + (*f - '0');
			f++;
		}
		flags->prec = 1;
	}
	return (f);
}

const char	*ft_flagadd(va_list *args, t_flags *flags, const char *format)
{
	while (ft_strchr("# +", *format))
	{
		if (*format == '#')
			flags->alt = 2;
		else if (*format == '+')
		{
			flags->sign = 1;
			flags->space = 0;
		}
		else if (*format == ' ')
		{
			if (flags->sign == 1)
				flags->space = 0;
			else
				flags->space = 1;
		}
		format++;
	}
	format = ft_wflags(args, flags, format);
	format = ft_addprec(args, flags, format);
	return (format);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:22:14 by aghergut          #+#    #+#             */
/*   Updated: 2026/01/10 17:57:54 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_printhex(unsigned long long n, char *base)
{
	size_t	base_length;

	base_length = ft_strlen(base);
	if (n >= base_length)
	{
		ft_printhex(n / base_length, base);
		n = n % base_length;
	}
	ft_putchar_fd(base[n], 1);
}

int	ft_gethex(unsigned long long n, char type)
{
	int					count;
	unsigned long long	temp;
	char				*base;

	count = 0;
	temp = n;
	if (type == 'p' || type == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n == 0)
		return (0);
	ft_printhex(temp, base);
	while (n > 0)
	{
		n /= 16;
		count++;
	}
	return (count);
}

int	ft_fill(int cond1, int cond2, char fill)
{
	int	temp;

	temp = cond2;
	if (cond1 > temp)
	{
		while (cond1 > temp++)
			write(1, &fill, 1);
		return (cond1 - cond2);
	}
	return (0);
}

int	ft_memlen(unsigned long long mem)
{
	int	base_len;
	int	count;

	base_len = 16;
	count = 0;
	while (mem > 0)
	{
		mem /= base_len;
		count++;
	}
	return (count);
}

int	ft_numlen(long n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

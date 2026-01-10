/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:31:15 by aghergut          #+#    #+#             */
/*   Updated: 2026/01/10 12:44:52 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strtoint.h"

static int	count_digits(int value)
{
	int	len;

	if (value == 0)
		return (1);
	len = 0;
	if (value < 0)
	{
		len = 1;
		value = value * -1;
	}
	while (value != 0)
	{
		value /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int value)
{
	char    *number;
	int		len;

	if (value == -2147483648)
		return (ft_strdup("-2147483648"));
	len = count_digits(value);
	number = ft_calloc(len + 1, sizeof(char));
	if (!number)
		return (NULL);
	if (value < 0)
	{
		number[0] = '-';
		value = value * -1;
	}
	if (value == 0)
		number[0] = '0';
	while (value)
	{
		number[--len] = (value % 10) + '0';
		value = value / 10;
	}
	return (number);
}

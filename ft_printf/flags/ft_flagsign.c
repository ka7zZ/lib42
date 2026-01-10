/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagsign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:58:59 by aghergut          #+#    #+#             */
/*   Updated: 2026/01/10 17:58:28 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_flagsign(t_flags *flags, char type, int n)
{
	if (flags->sign == 1 && ft_strchr("pid", type))
	{
		if (type == 'p' || n >= 0)
		{
			write(1, "+", 1);
			return (1);
		}
		if (n < 0)
		{
			write(1, "-", 1);
			return (1);
		}
	}
	else
		flags->sign = 0;
	return (0);
}

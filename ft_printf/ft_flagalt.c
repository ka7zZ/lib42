/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagalt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:58:12 by aghergut          #+#    #+#             */
/*   Updated: 2026/01/10 13:23:16 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_flagalt(t_flags *flags, char type)
{
	if (type == 'p')
		write(1, "0x", 2);
	if (type == 'x' && flags->alt > 0)
		write(1, "0x", 2);
	if (type == 'X' && flags->alt > 0)
		write(1, "0X", 2);
	return (2);
}

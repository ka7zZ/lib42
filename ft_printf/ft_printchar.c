/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:20:09 by aghergut          #+#    #+#             */
/*   Updated: 2026/01/10 13:14:50 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(t_flags *flags, char ch)
{
	if (flags->zpad)
		ft_fill(flags->width, 1, ' ');
	ft_putchar_fd(ch, 1);
	if (flags->left)
		ft_fill(flags->width, 1, ' ');
    if (flags->width)
        return(flags->width);
	return (1);
}

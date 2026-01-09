/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:14:34 by aghergut          #+#    #+#             */
/*   Updated: 2026/01/09 13:27:31 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

void	ft_putuint(unsigned int value, int length)
{
	char	c;

	if (length > 0)
	{
		ft_putuint(value / 10, length - 1);
		c = (value % 10) + '0';
		write(1, &c, 1);
	}
}

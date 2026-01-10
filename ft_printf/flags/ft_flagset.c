/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:13:48 by aghergut          #+#    #+#             */
/*   Updated: 2026/01/10 17:58:26 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_flagset(t_flags *flags)
{
	flags->alt = 0;
	flags->sign = 0;
	flags->space = 0;
	flags->left = 0;
	flags->zpad = 0;
	flags->prec = 0;
	flags->precw = 0;
	flags->width = 0;
}

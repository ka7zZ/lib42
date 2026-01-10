/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:34:32 by aghergut          #+#    #+#             */
/*   Updated: 2026/01/10 11:41:05 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*cast_dst;
	const unsigned char	*cast_src;
	size_t				i;

	if (!dst || !src)
		return (NULL);
	cast_dst = (unsigned char *)dst;
	cast_src = (const unsigned char *)src;
	if (cast_dst <= cast_src)
	{
		i = 0;
		while (i < n)
		{
			cast_dst[i] = cast_src[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
			cast_dst[n] = cast_src[n];
	}
	return (dst);
}

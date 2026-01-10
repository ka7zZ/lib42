/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapitem_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 10:49:39 by aghergut          #+#    #+#             */
/*   Updated: 2026/01/10 11:24:56 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

int	ft_mapitem_add(char ***map_ref, char *item)
{
	char	**new;

	if (!map_ref)
		return (0);
	if (*map_ref == NULL)
	{
		*map_ref = ft_mapnew(item);
		if (*map_ref == NULL)
			return (0);
		return (1);
	}
	new = create_new(*map_ref, item);
	if (!new)
		return (0);
	ft_mapfree(map_ref);
	*map_ref = new;
	return (1);
}

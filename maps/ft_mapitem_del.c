/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapitem_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:16:51 by aghergut          #+#    #+#             */
/*   Updated: 2026/01/10 11:27:42 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

int	ft_mapitem_del(char ***map_ref, size_t del_idx)
{
	char	**new_map;
	size_t	length;

	if (!map_ref || !*map_ref)
		return (0);
	length = ft_mapsize(*map_ref);
	if (del_idx >= length)
		return (0);
	new_map = (char **)malloc(length * sizeof(char *));
	if (!new_map)
		return (0);
	if (!copy_elements(*map_ref, new_map, del_idx))
		return (free(new_map), 0);
	ft_mapfree(map_ref);
	*map_ref = new_map;
	return (1);
}

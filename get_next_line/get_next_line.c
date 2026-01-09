/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:05:02 by aghergut          #+#    #+#             */
/*   Updated: 2026/01/09 14:12:45 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_append_nodes(t_list **lst, int fd, int *reading)
{
	char	*line;

	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (ft_lstclear(lst, free), 0);
	while (*reading > 0)
	{
		*reading = read(fd, line, BUFFER_SIZE);
		if (*reading < 0)
			return (free(line), ft_lstclear(lst, free), *lst = NULL, -1);
		if (*reading == 0)
			break ;
		line[*reading] = '\0';
		if (line && ft_strlen(line) > 0)
			ft_lstadd_back(lst, ft_lstnew(ft_strdup(line)));
		if (ft_strchr(line, '\n'))
			break ;
	}
	return (free(line), *reading);
}

static char	*ft_line(t_list **h, t_list *buf, char *res)
{
	size_t	idx;
	char	*ptr;
	char	*temp;

	while (*h)
	{
		buf = (*h)->next;
		temp = (char *)(*h)->content;
		if (temp && ft_strchr(temp, '\n'))
		{
			idx = ft_strchr(temp, '\n') - temp + 1;
			res = ft_strjoin_free(res, ft_substr(temp, 0, idx));
			ptr = ft_substr(temp, idx, ft_strlen(temp) - idx);
			free(temp);
			(*h)->content = ptr;
			if (ptr && !*ptr)
				return (free(ptr), free(*h), *h = buf, res);
			return (res);
		}
		else
			res = ft_strjoin_free(res, temp);
		free(*h);
		*h = buf;
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static t_list	*head[OPEN_MAX];
	char			*buffer;
	int				reading;

	if (fd < 0 || BUFFER_SIZE < 1 || fd >= OPEN_MAX)
		return (NULL);
	reading = 1;
	if ((!head[fd] || ft_strchr(head[fd]->content, '\n') == NULL) && \
		ft_append_nodes(&head[fd], fd, &reading) < 0)
		return (ft_lstclear(&head[fd], free), head[fd] = NULL, NULL);
	if (!head[fd])
		return (NULL);
	buffer = ft_line(&head[fd], NULL, NULL);
	if (!buffer || !*buffer)
	{
		if (buffer)
			free(buffer);
		return (ft_lstclear(&head[fd], free), head[fd] = NULL, NULL);
	}
	return (buffer);
}

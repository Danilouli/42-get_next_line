/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schmurz <schmurz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:04:26 by schmurz           #+#    #+#             */
/*   Updated: 2017/12/19 15:44:57 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	size_t	ft_strchri(char *str, int c)
{
	size_t	i;

	if (!str || !*str)
		return (0);
	if ((char)c == '\0')
		return (ft_strlen(str));
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (i);
		i += 1;
	}
	return (i);
}

static	char	*ft_strjoindel(char **s1, char *s2)
{
	char	*str;

	str = ft_strjoin(*s1, s2);
	if (s1)
		ft_memdel((void **)s1);
	return (str);
}

static	t_list	*ft_lstfindoradd(t_list **list, int fd)
{
	t_list	*search;

	search = *list;
	while (search)
	{
		if ((int)(search->content_size) == fd)
			break ;
		search = search->next;
	}
	if (!search)
	{
		ft_lstadd(list, ft_lstnew(NULL, fd));
		(*list)->content_size = fd;
		search = *list;
	}
	return (search);
}

int				get_next_line(const int fd, char **line)
{
	int				r;
	char			*buf;
	static	t_list	*list;
	t_list			*currfd;

	if (fd < 0 || !line || BUFF_SIZE < 1 || read(fd, "", 0) < 0 ||
			!(buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	currfd = ft_lstfindoradd(&list, fd);
	while ((r = read(fd, buf, BUFF_SIZE)))
	{
		buf[r] = '\0';
		currfd->content = ft_strjoindel((char **)&(currfd->content), buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	if (!currfd->content || (r < BUFF_SIZE && !ft_strlen(currfd->content)))
		return (0);
	*line = (currfd->content) ?
	ft_strndup(currfd->content, ft_strchri(currfd->content, '\n')) : NULL;
	(line && *line && ft_strlen(*line) < ft_strlen(currfd->content)) ?
	ft_strcpy(currfd->content, ft_strchr(currfd->content, '\n') + 1) :
	ft_strclr(currfd->content);
	return (1);
}

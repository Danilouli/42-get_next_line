/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schmurz <schmurz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:04:26 by schmurz           #+#    #+#             */
/*   Updated: 2017/12/19 14:25:09 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strchri(char *str, int c)
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

char	*ft_strjoinadd(char **s1, char *s2)
{
	char	*str;

	str = ft_strjoin(*s1, s2);
	if (s1)
		ft_memdel((void **)s1);
	return (str);
}

t_list	*ft_lstfind(t_list **list, int fd)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		ft_lstadd(list, ft_lstnew(NULL, fd));
		(*list)->content_size = fd;
		tmp = *list;
	}
	return (tmp);
}

int		get_next_line(const int fd, char **line)
{
	int				ret;
	char			*buf;
	static	t_list	*list;
	t_list			*current;

	if (fd < 0 || BUFF_SIZE < 1 || read(fd, "", 0) < 0 ||
			!(buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	current = ft_lstfind(&list, fd);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		current->content = ft_strjoinadd((char **)&current->content, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	if (ret < BUFF_SIZE && !ft_strlen(current->content))
		return (0);
	*line = (current->content) ?
	ft_strndup(current->content, ft_strchri(current->content, '\n')) : NULL;
	(ft_strlen(*line) < ft_strlen(current->content)) ?
	ft_strcpy(current->content, ft_strchr(current->content, '\n') + 1) :
	ft_strclr(current->content);
	return (1);
}

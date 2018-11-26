/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <tlesven@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/16 12:48:44 by tlesven           #+#    #+#             */
/*   Updated: 2018/11/26 14:36:16 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "libft.h"

void				ft_freeeread(t_read *fdlst)
{
	ft_strdel(&fdlst->read);
	free(fdlst);
	fdlst = NULL;
}

void				ft_newread(t_read *fdlst)
{
	int		ret;
	char	*tmp;
	char	*tmp2;
	char	buf[BUFF_SIZE];

	if ((ret = read(fdlst->fd, buf, BUFF_SIZE)) < 0)
	{
		fdlst->status = -1;
		return ;
	}
	if (ret < BUFF_SIZE)
		fdlst->status = 1;
	fdlst->len += ret;
	if (!fdlst->read)
		fdlst->read = ft_strndup((char*)buf, ret);
	else
	{
		tmp2 = ft_strndup(buf, ret);
		tmp = ft_strjoin(fdlst->read, tmp2);
		ft_strdel(&tmp2);
		ft_strdel(&fdlst->read);
		fdlst->read = tmp;
	}
	if (!fdlst->read)
		fdlst->status = -1;
}

static	t_read		*ft_newfd(int fd)
{
	t_read			*lst;

	if (!(lst = (t_read *)ft_memalloc(sizeof(t_read))))
		return (NULL);
	lst->fd = fd;
	lst->len = 0;
	lst->read = NULL;
	lst->status = 2;
	lst->next = NULL;
	lst->index = 0;
	ft_newread(lst);
	if (!lst->read)
	{
		free(lst);
		return (NULL);
	}
	return (lst);
}

void				ft_findendline(t_read *fdlst, char **line)
{
	int		i;

	i = fdlst->index;
	while (!ft_strchr(&fdlst->read[i], '\n'))
	{
		if (fdlst->status == 1)
		{
			if (fdlst->index < fdlst->len)
			{
				*line = ft_strndup(&fdlst->read[fdlst->index],
						fdlst->len - fdlst->index);
				fdlst->index = fdlst->len + 1;
			}
			else
				fdlst->status = 0;
			return ;
		}
		ft_newread(fdlst);
	}
	while (fdlst->read[i] != '\n')
		i++;
	*line = ft_strndup(&fdlst->read[fdlst->index], i - fdlst->index);
	fdlst->index = i + 1;
	return ;
}

int					get_next_line(int fd, char **line)
{
	static t_read	*start = NULL;
	t_read			*fdlst;

	if (fd < 0 || fd == 1 || BUFF_SIZE < 1)
		return (-1);
	if (!start)
	{
		if (!(start = ft_newfd(fd)))
			return (-1);
	}
	fdlst = start;
	while (fdlst->fd != fd)
	{
		if (!fdlst->next)
		{
			if (!(fdlst->next = ft_newfd(fd)))
				return (-1);
		}
		fdlst = fdlst->next;
	}
	ft_findendline(fdlst, line);
	if (fdlst->status >= 1)
		return (1);
	return (0);
}

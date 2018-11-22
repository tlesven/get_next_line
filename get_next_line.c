/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <tlesven@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/16 12:48:44 by tlesven           #+#    #+#             */
/*   Updated: 2018/11/22 21:22:09 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>
/*static	t_read		*ft_freeread(t_read *red, t_read *prev, t_read **start)
{
	if (!prev)
		*start = red->next;
	else
		prev->next = red->next;
	free(red->read);
	free(red);
	if (!prev)
		return (*start);
	else
		return (prev->next);
}*/
/*
static	t_read		*ft_newread(int fd)
{
	t_read			*red;
	void			*tmp;
	int				ret;

	if (!(red = (t_read *)ft_memalloc(sizeof(t_read))))
		return (NULL);
	if (!(tmp = ft_memalloc(sizeof(char) * BUFF_SIZE)))
	{
		ft_memdel((void**)&red);
		return (NULL);
	}
	if ((ret = read(fd, tmp, BUFF_SIZE)) < 0)
	{
		ft_memdel((void**)&red);
		ft_memdel((void**)&tmp);
		return (NULL);
	}
	red->read = (char *)tmp;
	red->fd = fd;
	red->size = ret;
	red->next = NULL;
	red->index = 0;
	return (red);
}
*/
/*int					ft_print(int n, t_read **tab, t_read **s, char **l)
{
	char			*tmpstr;
	int				index;

	if (!tab[0])
		return (-1);
	index = (tab[0])->index;
	if (n == -1 || !(tmpstr = ft_strnew((n + 1))))
		return (-1);
	*l = tmpstr;
	while (n--)
	{
		*tmpstr++ = (tab[0])->read[index++];
		if (index == (tab[0])->size)
		{
			tab[0] = ft_freeread(tab[0], tab[1], s);
			index = 0;
		}
	}
	*tmpstr = 0;
	if (!tab[0] || (index == tab[0]->size && tab[0]->size < BUFF_SIZE))
		return (0);
	tab[0]->index = index + 1;
	if (tab[0]->index == tab[0]->size)
		tab[0] = ft_freeread(tab[0], tab[1], s);
	return (1);
}
*/
/*int					ft_findendl(int fd, t_read *red)
{
	int				index;
	int				size;
	t_read			*tmplst;

	size = 0;
	index = red->index;
	while (red->read[index] != '\n' && index < red->size)
	{
		index++;
		size++;
		if (index == red->size && red->size == BUFF_SIZE)
		{
			if (!(tmplst = ft_newread(fd)))
				return (-1);
			tmplst->next = red->next;
			red->next = tmplst;
			red = tmplst;
			index = 0;
		}
	}
	return (size);
}
*/
/**
 **  tab[0] is red;
 **  tab[1[ is backred
 *

int					get_next_line2(int fd, char **line)
{
	static t_read	*start = NULL;
	t_read			*tab[2];

	if (fd < 0 || fd == 1 || BUFF_SIZE < 1)
		return (-1);
	tab[1] = NULL;
	if (!start)
		start = ft_newread(fd);
	if (!start)
		return (-1);
	tab[0] = start;
	while (tab[0]->fd != fd)
	{
		if (!tab[0]->next)
		{
			if (!(tab[0]->next = ft_newread(fd)))
				return (-1);
		}
		tab[1] = tab[0];
		tab[0] = tab[0]->next;
	}
	return (ft_print(ft_findendl(fd, tab[0]), tab, &start, line));
}
*/

void				ft_newread(t_read *fdlst)
{
	int		ret;
	char	*tmp;
	char	buf[BUFF_SIZE + 1];

	//ft_putendl("nextwreqd");
	//if (ret = read(fdlst->fd, buf, BUFF_SIZE) < 0);
	if ((ret = read(fdlst->fd, buf, BUFF_SIZE)) < 0)
	{
		fdlst->read = NULL;
		return ;
	}
	if (ret < BUFF_SIZE)
		fdlst->status = 1;
//	printf("ret: %d\n", ret);
	fdlst->len += ret;
	if (!fdlst->read)
	{
		fdlst->read = ft_strndup((char*)buf, ret);
	}
	else
	{
		tmp = ft_strjoin(fdlst->read, ft_strndup((char*)buf, ret));
		ft_strdel(&fdlst->read);
		fdlst->read = tmp;
	}
	//ft_memdel(&buf);
	return ;
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

void	ft_findendline(t_read *fdlst, char **line)
{
	int		i;
	i = fdlst->index;
	while (!ft_strchr(&fdlst->read[i], '\n'))
	{
		if (fdlst->status == 1)
		{
			//fdlst->status = 0;
			//printf("index: %d \n len: %d \n", fdlst->index, fdlst->len);
			if( fdlst->index < fdlst->len)
			{
				*line = ft_strndup(&fdlst->read[fdlst->index], fdlst->len - fdlst->index);
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
	//*line = "coucou";
	fdlst->index = i + 1;
	return ;
}

int				get_next_line(int fd, char **line)
{
	static t_read	*start = NULL;
	t_read			*fdlst;

	if (fd < 0 || fd == 1 || BUFF_SIZE < 1)
		return (-1);
	if(!start)
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
	//ft_newread(fdlst);
	//*line = "coucou";
	ft_findendline(fdlst, line);
	if(fdlst->status >= 1)
		return (1);
	//ft_strdel(&fdlst->read);
	return (0);//renvoyer le bon truc 
}


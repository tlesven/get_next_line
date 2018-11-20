/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <tlesven@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/16 12:48:44 by tlesven           #+#    #+#             */
/*   Updated: 2018/11/20 20:24:36 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

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

void				ft_newread(int fd, char *rad)
{
	int		ret;
	void	*buf;

	buf = ft_memalloc(sizeof(char) * BUFF_SIZE);
	ret = read(fd, buf, BUFF_SIZE);
}

static	t_read		*ft_newfd(int fd)
{
	t_read			*lst;
	void			*buf;
	int				ret;

	if (!(lst = (t_read *)ft_memalloc(sizeof(t_read))))
		return (NULL);
	if (!(buf = ft_memalloc(sizeof(char) * BUFF_SIZE)))
	{
		ft_memdel((void**)&lst);
		return (NULL);
	}
	if ((ret = read(fd, buf, BUFF_SIZE)) < 0)
	{
		ft_memdel((void**)&lst);
		ft_memdel((void**)&buf);
		return (NULL);
	}
	lst->read = (char *)buf;
	lst->fd = fd;
	lst->len = ret;
	lst->next = NULL;
	lst->index = 0;
	return (lst);
}

int ft_findendline(t_read *fdlst)
{
	char	*endline;

	while (!(endline = ft_strchr(fdlst->read, '\n')))
	{
		
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static t_read	*start = NULL;
	t_read			*fdlst;
	(void)line;

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
	return (0);//renvoyer le bon truc 
}


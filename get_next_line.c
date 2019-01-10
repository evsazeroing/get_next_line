/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjacks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 20:04:18 by kjacks            #+#    #+#             */
/*   Updated: 2019/01/10 20:15:08 by kjacks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*get_str(char **jlst_data)
{
	char	*res;
	char	*tmp;
	size_t	i;

	i = 0;
	if (!(tmp = ft_strdup(*jlst_data)))
		return (NULL);
	while (tmp[i] != '\n' && tmp[i])
		i++;
	if (!(res = ft_strnew(i)))
		return (NULL);
	ft_strncpy(res, *jlst_data, i);
	ft_strdel(jlst_data);
	if (i < ft_strlen(tmp))
	{
		if (!(*jlst_data = ft_strdup(tmp + i + 1)))
			return (NULL);
	}
	else
	{
		if (!(*jlst_data = ft_strdup("\0")))
			return (NULL);
	}
	ft_strdel(&tmp);
	return (res);
}

static char		*concat_free(char **jlst_data, char *buf)
{
	char	*res;
	size_t	i;

	i = ft_strlen(*jlst_data) + ft_strlen(buf);
	if (!(res = ft_strnew(i)))
		return (NULL);
	ft_strcpy(res, *jlst_data);
	ft_strcat(res, buf);
	ft_strdel(jlst_data);
	return (res);
}

static t_file	*search_fd(t_file **slst, int fd)
{
	t_file	*tmp;

	tmp = *slst;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!(tmp = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	if (!(tmp->data = ft_strnew(0)))
		return (NULL);
	tmp->fd = fd;
	tmp->next = *slst;
	*slst = tmp;
	return (tmp);
}

int				get_next_line(const int fd, char **line)
{
	static t_file	*slst;
	t_file			*jlst;
	int				r;
	char			buf[BUFF_SIZE + 1];

	if (BUFF_SIZE < 1 || fd < 0 || !line || (read(fd, buf, 0) < 0)
			|| !(jlst = search_fd(&slst, fd)))
		return (-1);
	r = 0;
	while (!(ft_strchr(jlst->data, '\n'))
			&& (r = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[r] = '\0';
		if (!(jlst->data = concat_free((char **)&jlst->data, buf)))
			return (-1);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (r < BUFF_SIZE && !(ft_strlen(jlst->data)))
		return (0);
	if (!(*line = get_str((char **)&jlst->data)))
		return (-1);
	return (1);
}

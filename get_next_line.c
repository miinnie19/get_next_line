/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaidoo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 20:32:50 by mnaidoo           #+#    #+#             */
/*   Updated: 2017/07/25 12:35:00 by mnaidoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

static	int		ft_read_buffer(int const fd, char **line)
{
	char		*buff;
	int			ret;
	char		*tmp;

	if (!(buff = (char *)malloc(sizeof(*buff) * (BUFF_SIZE + 1))))
		return (-1);
	ret = read(fd, buff, BUFF_SIZE);
	if (ret > 0)
	{
		buff[ret] = '\0';
		tmp = ft_strjoin(*line, buff);
		free(*line);
		*line = tmp;
	}
	return (ret);
}

int				get_next_line(int const fd, char **line)
{
	static char		*str;
	char			*newl;
	int				ret;

	if ((!str && (str = (char *)malloc(sizeof(*str))) == NULL) || !line
			|| fd < 0 || BUFF_SIZE < 0)
		return (-1);
	newl = ft_strchr(str, '\n');
	while (newl == NULL)
	{
		ret = ft_read_buffer(fd, &str);
		if (ret == 0)
		{
			if (ft_strlen(str) == 0)
				return (0);
			str = ft_strjoin(str, "\n");
		}
		if (ret < 0)
			return (-1);
		else
			newl = ft_strchr(str, '\n');
	}
	*line = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(newl));
	str = ft_strdup(newl + 1);
	return (1);
}

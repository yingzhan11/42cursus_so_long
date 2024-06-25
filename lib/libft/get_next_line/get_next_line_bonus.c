/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:58:42 by yzhan             #+#    #+#             */
/*   Updated: 2024/06/05 15:07:57 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_buf(int fd, char *read_buf)
{
	ssize_t	chars;
	char	*tmp;

	chars = 1;
	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (ft_free(&read_buf));
	while (!read_buf || (read_buf && chars > 0 && !ft_strchr(read_buf, '\n')))
	{
		chars = read(fd, tmp, BUFFER_SIZE);
		if (chars < 0)
		{
			free (tmp);
			return (ft_free(&read_buf));
		}
		if (chars == 0)
			break ;
		tmp[chars] = '\0';
		read_buf = ft_strjoin(read_buf, tmp);
	}
	free (tmp);
	if (ft_strlen(read_buf, '\0') > 0)
		return (read_buf);
	return (NULL);
}

static char	*ft_get_oneline(char *read_buf)
{
	size_t	len;
	char	*oneline;

	len = ft_strlen(read_buf, '\n');
	if (read_buf[len] == '\n')
		len++;
	oneline = ft_substr(read_buf, 0, len);
	if (!oneline)
		return (NULL);
	return (oneline);
}

static char	*ft_to_nextline(char *read_buf)
{
	size_t	start;
	size_t	len;
	char	*before_n;
	char	*after_n;

	before_n = ft_strchr(read_buf, '\n');
	if (!before_n)
	{
		after_n = NULL;
		return (ft_free(&read_buf));
	}
	else
		start = (before_n - read_buf) + 1;
	if (!read_buf[start])
		return (ft_free(&read_buf));
	len = ft_strlen(read_buf, '\0') - start;
	after_n = ft_substr(read_buf, start, len);
	ft_free(&read_buf);
	if (!after_n)
		return (NULL);
	return (after_n);
}

char	*get_next_line(int fd)
{
	static char	*read_buf[OPEN_MAX];
	char		*oneline;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	read_buf[fd] = ft_read_buf(fd, read_buf[fd]);
	if (!read_buf[fd])
		return (NULL);
	oneline = ft_get_oneline(read_buf[fd]);
	if (!oneline)
		return (ft_free(&read_buf[fd]));
	read_buf[fd] = ft_to_nextline(read_buf[fd]);
	return (oneline);
}

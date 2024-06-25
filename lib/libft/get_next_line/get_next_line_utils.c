/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:36:40 by yzhan             #+#    #+#             */
/*   Updated: 2024/06/05 14:54:40 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	free (*str);
	*str = NULL;
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	size_t		i;

	i = 0;
	while (s[i] != 0)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	length;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = 0;
	}
	length = ft_strlen(s1, '\0') + ft_strlen(s2, '\0');
	new_str = (char *)malloc(sizeof(char) * (length + 1));
	if (!new_str)
		return (ft_free(&s1));
	i = 0;
	j = 0;
	while (s1[i] != 0)
		new_str[i++] = s1[j++];
	j = 0;
	while (s2[j] != 0)
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	return (free (s1), new_str);
}

size_t	ft_strlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	*ft_substr(char const *src, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	src_len;

	if (!src)
		return (0);
	if (start >= ft_strlen(src, '\0'))
	{
		dst = (char *)malloc(sizeof(char));
		if (!dst)
			return (NULL);
		dst[0] = '\0';
		return (dst);
	}
	src_len = ft_strlen(src, '\0');
	if (len > (src_len - start))
		len = src_len - start;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len && start < src_len && src[start])
		dst[i++] = src[start++];
	dst[i] = '\0';
	return (dst);
}

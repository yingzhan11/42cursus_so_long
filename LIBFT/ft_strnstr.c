/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:27:01 by yzhan             #+#    #+#             */
/*   Updated: 2024/04/22 13:35:14 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n_len;
	char	*h;
	char	*f;

	n_len = ft_strlen(needle);
	i = 0;
	if (needle[i] == 0)
		return ((char *)haystack);
	while (*haystack != 0 && (i + n_len) <= len)
	{
		h = (char *)haystack;
		f = (char *)needle;
		while (*h == *f && *f != 0)
		{
			h++;
			f++;
		}
		if (*f == 0)
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return (NULL);
}

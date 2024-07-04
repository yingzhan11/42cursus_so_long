/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:09:28 by yzhan             #+#    #+#             */
/*   Updated: 2024/05/01 13:22:28 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		length;
	int		i;
	char	*dst;

	length = 0;
	i = 0;
	while (s1[length] != '\0')
		length++;
	dst = (char *)malloc((length + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (s1[i] != 0)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

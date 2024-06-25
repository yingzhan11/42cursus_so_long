/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:11:24 by yzhan             #+#    #+#             */
/*   Updated: 2024/04/22 13:33:56 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	chr;
	int		i;

	chr = c;
	i = 0;
	while (s[i] != 0 && s[i] != chr)
		i++;
	if (s[i] == chr)
		return ((char *)(s + i));
	return (NULL);
}

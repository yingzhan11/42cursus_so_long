/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:50:43 by yzhan             #+#    #+#             */
/*   Updated: 2024/04/24 12:25:44 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_putchr(char *str, int n, int count)
{
	int	i;

	if (n >= 0)
	{
		i = count - 1;
		while (i >= 0)
		{
			str[i--] = (n % 10) + '0';
			n = n / 10;
		}
		str[count] = '\0';
	}
	else
	{
		i = count;
		n = -n;
		while (i > 0)
		{
			str[i--] = (n % 10) + '0';
			n = n / 10;
		}
		str[i] = '-';
		str[count + 1] = '\0';
	}
	return (str);
}

static int	ft_count(int n)
{
	int	count;

	count = 1;
	while ((n / 10) != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*str;

	count = ft_count(n);
	if (n >= 0)
		str = (char *)malloc(sizeof(char) * (count + 1));
	else
		str = (char *)malloc(sizeof(char) * (count + 2));
	if (!str)
		return (NULL);
	if (n == -2147483648)
	{
		n = -2147483647;
		str = ft_putchr(str, n, count);
		str[count] = '8';
		return (str);
	}
	str = ft_putchr(str, n, count);
	return (str);
}

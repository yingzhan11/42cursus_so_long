/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:32:29 by yzhan             #+#    #+#             */
/*   Updated: 2024/05/09 11:10:52 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_convert_digit(long nb, int base, char *hex)
{
	int	len;

	len = 0;
	if (nb >= base)
	{
		len = ft_convert_digit(nb / base, base, hex);
		if (len == -1)
			return (-1);
		if (ft_print_char(hex[nb % base]) != 1)
			return (-1);
		len++;
	}
	else if (nb < base)
	{
		if (ft_print_char(hex[nb]) != 1)
			return (-1);
		len++;
	}
	return (len);
}

int	ft_print_digit(long nb, int base, int uplow)
{
	int		len;
	char	*hex;

	len = 0;
	if (uplow == 1)
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (nb < 0)
	{
		if (write (1, "-", 1) != 1)
			return (-1);
		len = ft_convert_digit(-nb, base, hex);
		if (len == -1)
			return (-1);
		len += 1;
	}
	else
	{
		len = ft_convert_digit(nb, base, hex);
		if (len == -1)
			return (-1);
	}
	return (len);
}

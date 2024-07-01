/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:37:25 by yzhan             #+#    #+#             */
/*   Updated: 2024/05/09 11:26:33 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hex_ptr(uintptr_t nb, int len)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (nb >= 16)
	{
		len = ft_hex_ptr(nb / 16, len);
		if (len == -1)
			return (-1);
		if (ft_print_char(hex[nb % 16]) != 1)
			return (-1);
		len++;
	}
	else if (nb < 16)
	{
		if (ft_print_char(hex[nb % 16]) != 1)
			return (-1);
		len++;
	}
	return (len);
}

int	ft_print_pointer(void *ptr)
{
	int	len;

	if (write(1, "0x", 2) != 2)
		return (-1);
	len = 0;
	len += ft_hex_ptr((uintptr_t)ptr, len);
	if (len == -1)
		return (-1);
	else
		return (len + 2);
}

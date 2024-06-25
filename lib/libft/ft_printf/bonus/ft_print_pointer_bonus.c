/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:33:33 by yzhan             #+#    #+#             */
/*   Updated: 2024/05/23 14:57:27 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

//func to convre pointer into string
static void	ft_convert_pointer(t_data *data, uintptr_t nb)
{
	if (nb >= 16)
	{
		ft_convert_pointer(data, nb / 16);
		data->fmt.nb_str[data->fmt.nb_len++] = LOW_HEX[nb % 16];
	}
	else if (nb < 16)
	{
		data->fmt.nb_str[data->fmt.nb_len++] = LOW_HEX[nb % 16];
	}
}

//func to print pointer
void	ft_print_pointer(t_data *data, void *ptr)
{
	ft_convert_pointer(data, (uintptr_t)ptr);
	ft_pad_zeros(data);
	ft_pad_spaces(data);
	if (data->fmt.left)
	{
		ft_putsign(data);
		ft_putchar('0', data->fmt.pad_zero, data);
		ft_putstr(data->fmt.nb_str, data->fmt.nb_len, data);
		ft_putchar(' ', data->fmt.pad_space, data);
	}
	else
	{
		ft_putchar(' ', data->fmt.pad_space, data);
		ft_putsign(data);
		ft_putchar('0', data->fmt.pad_zero, data);
		ft_putstr(data->fmt.nb_str, data->fmt.nb_len, data);
	}
}

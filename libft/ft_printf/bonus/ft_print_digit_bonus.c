/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digit_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:30:15 by yzhan             #+#    #+#             */
/*   Updated: 2024/05/23 14:58:10 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

//convert number into a string
static void	ft_itoa_base(t_data *data, long nb)
{
	int	base;

	base = data->fmt.base;
	if (nb < 0)
	{
		nb = -nb;
		data->fmt.is_negative = 1;
	}
	if (nb >= base)
	{
		ft_itoa_base(data, nb / base);
		ft_itoa_base(data, nb % base);
	}
	else if (nb < base)
	{
		if (data->fmt.is_upper == 1)
			data->fmt.nb_str[data->fmt.nb_len++] = UP_HEX[nb];
		else
			data->fmt.nb_str[data->fmt.nb_len++] = LOW_HEX[nb];
		data->fmt.nb_str[data->fmt.nb_len] = '\0';
	}
}

//func to print all digit, "diuxX"
void	ft_print_digit(t_data *data, long nb)
{
	if (nb == 0 && data->fmt.precision == 0)
		data->fmt.nb_str[data->fmt.nb_len] = '0';
	else
		ft_itoa_base(data, nb);
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

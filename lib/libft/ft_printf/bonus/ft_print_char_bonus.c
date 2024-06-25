/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:28:59 by yzhan             #+#    #+#             */
/*   Updated: 2024/05/22 10:51:15 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

//func to print char
void	ft_print_char(t_data *data, int c)
{
	if (data->fmt.width > 1)
	{
		if (data->fmt.left == 1)
		{
			ft_putchar((char)c, 1, data);
			ft_putchar(' ', data->fmt.width - 1, data);
		}
		else
		{
			if (data->fmt.zero == 1)
				ft_putchar('0', data->fmt.width - 1, data);
			else
				ft_putchar(' ', data->fmt.width - 1, data);
			ft_putchar((char)c, 1, data);
		}
	}
	else
		ft_putchar((char)c, 1, data);
}

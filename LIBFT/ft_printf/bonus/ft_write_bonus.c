/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:56:27 by yzhan             #+#    #+#             */
/*   Updated: 2024/05/23 14:56:53 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_write_buf(t_data *data)
{
	data->len += write(1, data->buf, data->buf_index);
	my_memset(data->buf, 0, BUF_SIZE);
	data->buf_index = 0;
}

void	ft_putbuf(t_data *data, char c)
{
	if (data->buf_index == BUF_SIZE)
	{
		ft_write_buf(data);
	}
	data->buf[data->buf_index++] = c;
}

void	ft_putchar(char c, int n, t_data *data)
{
	if (n <= 0)
		return ;
	while (n--)
	{
		ft_putbuf(data, c);
	}
}

void	ft_putstr(char *s, int precision, t_data *data)
{
	if (precision <= 0)
		return ;
	while (precision-- && *s)
	{
		ft_putbuf(data, *s++);
	}
}

int	ft_putsign(t_data *data)
{
	if ((my_strchr("xX", data->fmt.specifier) && data->fmt.hash
			&& data->fmt.nb_str[0] != '0') || data->fmt.specifier == 'p')
	{
		if (data->fmt.is_upper)
			ft_putstr("0X", 2, data);
		else
			ft_putstr("0x", 2, data);
	}
	else if (data->fmt.is_signed)
	{
		if (data->fmt.is_negative)
			ft_putchar('-', 1, data);
		else if (!data->fmt.is_negative)
		{
			if (data->fmt.plus)
				ft_putchar('+', 1, data);
			else if (!data->fmt.plus && data->fmt.space)
				ft_putchar(' ', 1, data);
		}
	}
	return (1);
}

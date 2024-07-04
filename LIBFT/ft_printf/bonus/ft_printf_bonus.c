/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:14:09 by yzhan             #+#    #+#             */
/*   Updated: 2024/05/21 17:10:42 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

//check specifier and call print functions
static int	ft_check_specifier(t_data *data)
{
	char	specifier;

	specifier = data->fmt.specifier;
	if (specifier == 'c')
		ft_print_char(data, va_arg(data->ap, int));
	else if (specifier == 's')
		ft_print_str(data, va_arg(data->ap, char *));
	else if (specifier == 'd' || specifier == 'i')
		ft_print_digit(data, (long)va_arg(data->ap, int));
	else if (my_strchr("uxX", specifier))
		ft_print_digit(data, (long)va_arg(data->ap, unsigned int));
	else if (specifier == 'p')
		ft_print_pointer(data, va_arg(data->ap, void *));
	else if (specifier == '%')
		ft_print_char(data, '%');
	return (data->len);
}

//check format and write result
static int	ft_check_format(t_data *data)
{
	while (*data->s)
	{
		if (*data->s == '%')
		{
			if (!*(++data->s))
			{
				ft_write_buf(data);
				return (data->len);
			}
			if (ft_parse_format(data) == -1)
				ft_putbuf(data, *data->s);
			else
				ft_check_specifier(data);
		}
		else
			ft_putbuf(data, *data->s);
		data->s++;
	}
	ft_write_buf(data);
	return (data->len);
}

int	ft_printf(const char *format, ...)
{
	t_data	data;

	va_start(data.ap, format);
	data.s = format;
	data.len = 0;
	data.buf_index = 0;
	data.buf = malloc(BUF_SIZE * sizeof(char));
	if (data.buf == NULL)
		return (-1);
	my_memset(data.buf, 0, BUF_SIZE * sizeof(char));
	ft_check_format(&data);
	va_end(data.ap);
	free(data.buf);
	return (data.len);
}

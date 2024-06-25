/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:20:02 by yzhan             #+#    #+#             */
/*   Updated: 2024/05/23 15:33:29 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

//check each flag, and marked as 1 if there is
static void	ft_parse_flag(t_data *data)
{
	char	flag;

	while (my_strchr(FLAGS, *data->s))
	{
		flag = *data->s;
		if (flag == '-')
			data->fmt.left = 1;
		else if (flag == '+')
			data->fmt.plus = 1;
		else if (flag == ' ')
			data->fmt.space = 1;
		else if (flag == '#')
			data->fmt.hash = 1;
		else if (flag == '0')
			data->fmt.zero = 1;
		data->s++;
	}
}

//get the value of width or precision
static void	ft_get_value(t_data *data, int *value)
{
	int	i;

	i = 0;
	if (*data->s == '*')
	{
		*value = va_arg(data->ap, int);
		data->s++;
		return ;
	}
	while (my_strchr(NUMBERS, *data->s))
	{
		i = (i * 10) + (*data->s - '0');
		data->s++;
	}
	*value = i;
}

//check base and hex base for numbers and pointer
static void	ft_check_nb(t_data *data)
{
	if (my_strchr("diu", data->fmt.specifier))
	{
		data->fmt.base = 10;
		if (data->fmt.specifier != 'u')
			data->fmt.is_signed = 1;
	}
	else if (my_strchr("xXp", data->fmt.specifier))
	{
		data->fmt.base = 16;
		if (data->fmt.specifier == 'X')
			data->fmt.is_upper = 1;
	}
}

//parse format and specifier
int	ft_parse_format(t_data *data)
{
	my_memset(&data->fmt, 0, sizeof(t_format));
	data->fmt.precision = -1;
	while ((!my_strchr(SPECIFIERS, *data->s) || !(data->s))
		&& my_strchr("-+ #0123456789.*", *data->s))
	{
		if (my_strchr(FLAGS, *data->s))
			ft_parse_flag(data);
		else if (my_strchr(NUMBERS, *data->s) || *data->s == '*')
			ft_get_value(data, &data->fmt.width);
		else if (*data->s == '.' && *(++data->s))
			ft_get_value(data, &data->fmt.precision);
	}
	if (!my_strchr(SPECIFIERS, *data->s) || !(data->s))
		return (-1);
	data->fmt.specifier = *data->s;
	ft_check_nb(data);
	return (1);
}

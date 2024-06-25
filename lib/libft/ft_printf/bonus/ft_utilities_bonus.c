/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:17:43 by yzhan             #+#    #+#             */
/*   Updated: 2024/05/23 15:00:46 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	my_strchr(const char *s, char c)
{
	if (s == NULL)
		return (0);
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL || !*s)
		return (0);
	while (s[i] != 0)
		i++;
	return (i);
}

//to refresh data and buffer
void	my_memset(void *p, unsigned char c, size_t len)
{
	unsigned char	*s;

	s = (unsigned char *)p;
	while (len)
	{
		*s++ = c;
		len--;
	}
}

//count how many zeros need to be padding for number and pointer
void	ft_pad_zeros(t_data *data)
{
	if (data->fmt.precision >= 0)
	{
		if (data->fmt.precision >= data->fmt.nb_len)
			data->fmt.pad_zero = data->fmt.precision - data->fmt.nb_len;
		return ;
	}
	if (data->fmt.zero)
	{
		if (data->fmt.left)
			return ;
		if (data->fmt.width > data->fmt.nb_len)
			data->fmt.pad_zero = data->fmt.width - data->fmt.nb_len;
		if (data->fmt.specifier == 'u')
			return ;
		else if ((my_strchr("xX", data->fmt.specifier) && data->fmt.hash
				&& data->fmt.nb_str[0] != '0') || data->fmt.specifier == 'p')
			data->fmt.pad_zero -= 2;
		else if (data->fmt.is_negative || (!data->fmt.is_negative
				&& (data->fmt.plus || data->fmt.space)))
			data->fmt.pad_zero--;
		if (data->fmt.pad_zero < 0)
			data->fmt.pad_zero = 0;
	}
}

//count how many spaces need to be padding for number and pointer
void	ft_pad_spaces(t_data *data)
{
	int		width;
	char	specifier;

	width = data->fmt.width;
	specifier = data->fmt.specifier;
	data->fmt.pad_space = width - data->fmt.pad_zero - data->fmt.nb_len;
	if (my_strchr("uxXp", specifier))
	{
		if ((my_strchr("xX", specifier) && data->fmt.hash
				&& data->fmt.nb_str[0] != '0') || specifier == 'p')
		{
			data->fmt.pad_space -= 2;
		}
	}
	else if (data->fmt.is_negative || (!data->fmt.is_negative
			&& (data->fmt.plus || data->fmt.space)))
	{
		data->fmt.pad_space--;
	}
	if (data->fmt.pad_space < 0)
		data->fmt.pad_space = 0;
}

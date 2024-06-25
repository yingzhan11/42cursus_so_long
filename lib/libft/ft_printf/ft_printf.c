/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:49:19 by yzhan             #+#    #+#             */
/*   Updated: 2024/05/14 14:26:00 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_specifier(char spec, va_list ap)
{
	int	len;

	len = 0;
	if (spec == 'c')
		len = ft_print_char(va_arg(ap, int));
	else if (spec == 's')
		len = ft_print_str(va_arg(ap, char *));
	else if (spec == 'p')
		len = ft_print_pointer(va_arg(ap, void *));
	else if (spec == 'd' || spec == 'i')
		len = ft_print_digit((long)(va_arg(ap, int)), 10, 1);
	else if (spec == 'u')
		len = ft_print_digit((long)(va_arg(ap, unsigned int)), 10, 1);
	else if (spec == 'x')
		len = ft_print_digit((long)(va_arg(ap, unsigned int)), 16, 1);
	else if (spec == 'X')
		len = ft_print_digit((long)(va_arg(ap, unsigned int)), 16, 2);
	else
		len = write(1, &spec, 1);
	return (len);
}

static int	ft_check_format(const char *format, va_list ap, int len)
{
	int		i;
	int		j;

	j = 0;
	while (format[j] != '\0')
	{
		if (format[j] == '%')
		{
			if (!format[j + 1])
				return (len);
			i = ft_check_specifier(format[++j], ap);
			if (i == -1)
				return (-1);
			len += i;
		}
		else
		{
			if (ft_print_char(format[j]) != 1)
				return (-1);
			len++;
		}
		j++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;

	va_start(ap, format);
	len = 0;
	len = ft_check_format(format, ap, len);
	va_end(ap);
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:13:45 by yzhan             #+#    #+#             */
/*   Updated: 2024/05/23 15:00:55 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

# define BUF_SIZE 4096
# define SPECIFIERS "cspdiuxX%"
# define FLAGS "-+ 0#"
# define NUMBERS "0123456789"
# define LOW_HEX "0123456789abcdef"
# define UP_HEX "0123456789ABCDEF"

//tmp data for each %, need to be refresh
typedef struct s_format
{
	int			left;
	int			plus;
	int			space;
	int			zero;
	int			hash;
	int			width;
	int			precision;
	char		specifier;
	int			is_signed;
	int			is_negative;
	int			base;
	int			is_upper;
	char		nb_str[64];
	int			nb_len;
	int			pad_space;
	int			pad_zero;
}	t_format;

//const data
typedef struct s_data
{
	const char	*s;
	int			len;
	va_list		ap;
	t_format	fmt;
	char		*buf;
	int			buf_index;
}	t_data;

//printf
int		ft_printf(const char *format, ...);
int		ft_parse_format(t_data *data);
void	ft_print_char(t_data *data, int c);
void	ft_print_str(t_data *data, char *s);
void	ft_print_digit(t_data *data, long nb);
void	ft_print_pointer(t_data *data, void *ptr);

//utilities
int		my_strchr(const char *s, char c);
int		ft_strlen(const char *s);
void	my_memset(void *p, unsigned char c, size_t len);
void	ft_pad_zeros(t_data *data);
void	ft_pad_spaces(t_data *data);

//write function
void	ft_write_buf(t_data *data);
void	ft_putbuf(t_data *data, char c);
void	ft_putchar(char c, int n, t_data *data);
void	ft_putstr(char *s, int precision, t_data *data);
int		ft_putsign(t_data *data);

#endif

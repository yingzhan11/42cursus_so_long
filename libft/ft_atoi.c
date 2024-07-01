/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:54:55 by yzhan             #+#    #+#             */
/*   Updated: 2024/05/01 13:20:40 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int		i;
	int		minus;
	long	num;
	long	check;

	i = 0;
	num = 0;
	minus = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			minus = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		check = (str[i++] - '0') + (num * 10);
		if (check / 10 != num && minus == 1)
			return (-1);
		if (check / 10 != num && minus == -1)
			return (0);
		num = check;
	}
	return ((int)num * minus);
}

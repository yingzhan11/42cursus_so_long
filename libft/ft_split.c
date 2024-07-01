/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:16:51 by yzhan             #+#    #+#             */
/*   Updated: 2024/05/02 17:59:34 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	is_new;
	int	count;

	i = 0;
	is_new = 1;
	count = 0;
	while (s && s[i] != 0)
	{
		if (s[i] == c)
			is_new = 1;
		else if ((s[i] != c) && is_new == 1)
		{
			is_new = 0;
			count++;
		}
		i++;
	}
	return (count);
}

static int	ft_word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != 0 && s[i] != c)
		i++;
	return (i);
}

static char	*ft_word_dup(char const *s, int word_len)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = (char *)malloc(sizeof(*s) * (word_len + 1));
	if (!tmp)
		return (NULL);
	while (s[i] != 0 && i < word_len)
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

static void	*ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**split;
	int		i;
	int		j;
	int		word_len;

	words = ft_count_word(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split || !s)
		return (NULL);
	i = 0;
	j = 0;
	while (j < words)
	{
		while (s[i] == c)
			i++;
		word_len = ft_word_len(s + i, c);
		split[j] = ft_word_dup((s + i), word_len);
		if (!split[j])
			return (ft_free(split));
		j++;
		i += word_len;
	}
	split[j] = 0;
	return (split);
}

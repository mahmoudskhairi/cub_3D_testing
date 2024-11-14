/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:08:04 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/10/09 13:02:22 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char *ws)
{
	size_t	nbr;

	nbr = 0;
	while (*s)
	{
		while (ft_strchr(ws, *s))
		{
			s++;
			if (*s == '\0')
				return (nbr);
		}
		while (*s && !ft_strchr(ws, *s))
			s++;
		nbr++;
	}
	return (nbr);
}

static size_t	word_len(const char *s, char *ws)
{
	size_t	i;

	i = 0;
	while (*(s + i) && !ft_strchr(ws, *(s + i)))
		i++;
	return (i);
}

static void	freef(char **array, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(*(array + j));
		j++;
	}
	free(array);
}

static char	**ft_result(char **res, const char *s, char *ws, size_t words)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < words)
	{
		while (ft_strchr (ws, *(s + i)))
			i++;
		*(res + j) = ft_substr(s, i, word_len((s + i), ws));
		if (!(*(res + j)))
		{
			freef(res, j);
			return (NULL);
		}
		while (*(s + i) && !ft_strchr(ws, *(s + i)))
			i++;
		j++;
	}
	*(res + j) = 0;
	return (res);
}

char	**ft_split_ws(const char *s, char *ws, int *wc)// "\n\t\r\b "
{
	char	**res;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, ws);
	// if (!wc)
		*wc = words;
	res = (char **)malloc((words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res = ft_result(res, s, ws, words);
	return (res);
}

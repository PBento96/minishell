/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:20:55 by pda-silv          #+#    #+#             */
/*   Updated: 2024/09/27 12:34:03 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Splits string s into substings using c as a delimiter and returns an array
// with those new strings.

static size_t	ft_countstr(char const *s, char c)
{
	size_t	n;
	bool	in;

	n = 0;
	while (*s)
	{
		in = false;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			if (!in)
			{
				n++;
				in = true;
			}
			s++;
		}
	}
	return (n);
}

static int	ft_newstr(char **strings, int pos, size_t size)
{
	int	i;

	i = 0;
	strings[pos] = ft_calloc(size, sizeof(char));
	if (!strings[pos])
	{
		while (i < pos)
		{
			free(strings[i]);
			i++;
		}
		return (1);
	}
	return (0);
}

static int	ft_divstr(char **strings, char const *s, char c)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		if (len)
		{
			if (ft_newstr(strings, i, len + 1))
				return (1);
			ft_strlcpy(strings[i], s - len, len + 1);
			i++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	size_t	n;

	if (!s)
		return (NULL);
	n = ft_countstr(s, c);
	strings = ft_calloc(n + 1, sizeof(char *));
	if (!strings)
		return (NULL);
	strings[n] = NULL;
	if (ft_divstr(strings, s, c))
	{
		free(strings);
		return (NULL);
	}
	return (strings);
}

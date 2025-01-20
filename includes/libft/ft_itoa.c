/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:27:17 by pda-silv          #+#    #+#             */
/*   Updated: 2024/09/27 12:35:16 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Converts int n to a string, returns NULL if invalid.

static size_t	ft_digits(int n)
{
	size_t	d;

	d = 0;
	if (n == INT_MIN)
		return (11);
	if (n < 0)
	{
		d++;
		n = -n;
	}
	if (!n)
		d++;
	while (n)
	{
		n /= 10;
		d++;
	}
	return (d);
}

static int	ft_negative(char *str, int *n)
{
	int	ret;

	ret = 1;
	str[0] = '-';
	if (*n == INT_MIN)
	{
		str[1] = '2';
		*n = 147483648;
		ret++;
	}
	else
		*n = -*n;
	return (ret);
}

static void	ft_tostr(char *str, int *i, int n)
{
	if (n == 0)
		return ;
	ft_tostr(str, i, n / 10);
	str[(*i)++] = n % 10 + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	int		i;

	i = 0;
	len = ft_digits(n);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	if (n == 0)
	{
		str[0] = '0';
		str[1] = 0;
	}
	if (n < 0)
	{
		i = ft_negative(str, &n);
	}
	ft_tostr(str, &i, n);
	if (n)
		str[i] = '\0';
	return (str);
}

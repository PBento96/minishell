/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:26:33 by pda-silv          #+#    #+#             */
/*   Updated: 2024/09/24 23:24:33 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_prtf(t_data *data, const char *s, int len)
{
	if (len < 0)
		return (OK);
	if (write(STDOUT_FILENO, s, len) != len)
		return (NOK);
	data->len += len;
	return (OK);
}

void	ft_bzero_prtf(void *s, size_t n)
{
	char	*str;

	str = (char *)s;
	while (n--)
		str[n] = '\0';
}

char	*ft_strchr_prtf(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (0);
}

size_t	ft_strlen_prtf(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s + len))
		len++;
	return (len);
}

int	ft_atoi_prtf(t_data *data)
{
	int	i;

	i = 0;
	while (ft_strchr_prtf("0123456789", *data->ptr))
	{
		i = (i * 10) + (*data->ptr - '0');
		data->ptr++;
	}
	return (i);
}

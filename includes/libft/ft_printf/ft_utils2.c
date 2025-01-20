/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:59:18 by pda-silv          #+#    #+#             */
/*   Updated: 2024/09/24 23:25:34 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putcharn(t_data *data, char c, int len)
{
	if (len < 0)
		return (OK);
	while (len--)
	{
		if (write(STDOUT_FILENO, &c, 1) != 1)
			return (NOK);
		data->len++;
	}
	return (OK);
}

char	ft_getchar(t_data *data, unsigned long n)
{
	if (data->format.upper)
		return (BASE_UPPER[n]);
	return (BASE_LOWER[n]);
}

int	ft_itoa_prtf(t_data *data, t_num *num, unsigned long tmp)
{
	if (tmp >= data->format.base)
	{
		ft_itoa_prtf(data, num, tmp / data->format.base);
	}
	num->str[num->ptr] = ft_getchar(data, (tmp % data->format.base));
	num->ptr++;
	return (OK);
}

size_t	ft_strlcpy_prtf(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (!size)
		return (ft_strlen_prtf(src));
	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen_prtf(src));
}

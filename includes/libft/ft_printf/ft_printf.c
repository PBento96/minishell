/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:08:02 by pda-silv          #+#    #+#             */
/*   Updated: 2024/09/24 23:22:03 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	t_data	data;

	va_start(data.args, format);
	data.len = 0;
	data.ptr = format;
	while (*data.ptr)
	{
		if (*data.ptr == '%' && *(++data.ptr))
		{
			if (ft_parser(&data))
				return (NOK);
			if (ft_render(&data))
				return (NOK);
		}
		else
			if (ft_putstr_prtf(&data, data.ptr, 1))
				return (NOK);
		data.ptr++;
	}
	va_end(data.args);
	return (data.len);
}

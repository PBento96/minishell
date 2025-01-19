/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:22:26 by pda-silv          #+#    #+#             */
/*   Updated: 2024/09/24 23:23:49 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parser(t_data *data)
{
	ft_bzero_prtf(&data->format, sizeof(t_format));
	data->format.precision = -1;
	ft_setflags(data);
	ft_getvalue(data, &data->format.width);
	if (data->format.width < 0)
	{
		data->format.justified = true;
		data->format.width = -data->format.width;
	}
	if (*data->ptr == '.' && *(++data->ptr))
		ft_getvalue(data, &data->format.precision);
	if (!ft_strchr_prtf(SPECIFIERS, *data->ptr))
		return (NOK);
	data->format.specifier = *data->ptr;
	if (ft_strchr_prtf("diu", data->format.specifier))
		data->format.base = DEC;
	else if (ft_strchr_prtf("pxX", data->format.specifier))
	{
		data->format.base = HEX;
		if (data->format.specifier == 'X')
			data->format.upper = true;
	}
	return (OK);
}

void	ft_setflags(t_data *data)
{
	while (ft_strchr_prtf(FLAGS, *data->ptr))
	{
		if (*data->ptr == '-')
			data->format.justified = true;
		if (*data->ptr == '+')
			data->format.plus = true;
		if (*data->ptr == ' ')
			data->format.space = true;
		if (*data->ptr == '#')
			data->format.hash = true;
		if (*data->ptr == '0')
			data->format.zero = true;
		data->ptr++;
	}
}

void	ft_getvalue(t_data *data, int *value)
{
	if (*data->ptr == '*')
	{
		*value = va_arg(data->args, int);
		data->ptr++;
		return ;
	}
	*value = ft_atoi_prtf(data);
}

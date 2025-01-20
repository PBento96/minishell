/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:49:19 by pda-silv          #+#    #+#             */
/*   Updated: 2024/09/24 23:26:49 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_render(t_data *data)
{
	if (data->format.specifier == '%')
	{
		if (ft_putstr_prtf(data, "%", 1))
			return (NOK);
	}
	else if (data->format.specifier == 'c')
	{
		if (ft_render_chr(data, (char)va_arg(data->args, int)))
			return (NOK);
	}
	else if (data->format.specifier == 's')
	{
		if (ft_render_str(data, va_arg(data->args, char *)))
			return (NOK);
	}
	else if (ft_strchr_prtf("diupxX", data->format.specifier))
	{
		if (ft_render_num(data))
			return (NOK);
	}
	else
		return (NOK);
	return (OK);
}

int	ft_render_chr(t_data *data, char c)
{
	if (data->format.width > 1)
	{
		if (data->format.justified)
		{
			if (ft_putstr_prtf(data, &c, 1))
				return (NOK);
			if (ft_putcharn(data, ' ', data->format.width - 1))
				return (NOK);
		}
		else
		{
			if (ft_putcharn(data, ' ', data->format.width - 1))
				return (NOK);
			if (ft_putstr_prtf(data, &c, 1))
				return (NOK);
		}
	}
	else
	{
		if (ft_putstr_prtf(data, &c, 1))
			return (NOK);
	}
	return (OK);
}

int	ft_render_str(t_data *data, char *s)
{
	if (!s)
	{
		s = "(null)";
		if (data->format.precision < 6 && data->format.precision >= 0)
			s = "";
	}
	ft_strpad(data, s);
	if (data->format.justified)
	{
		if (ft_strpre(data, s))
			return (NOK);
		if (ft_printpad(data, ' '))
			return (NOK);
	}
	else
	{
		if (ft_printpad(data, ' '))
			return (NOK);
		if (ft_strpre(data, s))
			return (NOK);
	}
	return (OK);
}

void	ft_strpad(t_data *data, char *s)
{
	if (data->format.width > 0)
	{
		if (data->format.precision >= 0)
		{
			if (data->format.precision > (int)ft_strlen_prtf(s))
				data->format.padding_len = data->format.width
					- ft_strlen_prtf(s);
			else
				data->format.padding_len = data->format.width
					- data->format.precision;
		}
		else
			data->format.padding_len = data->format.width - ft_strlen_prtf(s);
	}
}

int	ft_strpre(t_data *data, char *s)
{
	if (data->format.precision < (int)ft_strlen_prtf(s)
		&& data->format.precision >= 0 && data->format.base != HEX)
	{
		if (ft_putstr_prtf(data, s, data->format.precision))
			return (NOK);
	}
	else
	{
		if (ft_putstr_prtf(data, s, (int)ft_strlen_prtf(s)))
			return (NOK);
	}
	return (OK);
}

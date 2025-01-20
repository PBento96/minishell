/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:39:34 by pda-silv          #+#    #+#             */
/*   Updated: 2024/09/24 23:26:15 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_render_ptr(t_data *data, t_num *num)
{
	if (data->format.specifier != 'p')
	{
		if (ft_itoa_prtf(data, num, (unsigned int)num->value.uint64))
			return (NOK);
	}
	else
	{
		if (num->value.uint64)
		{
			if (ft_itoa_prtf(data, num, (unsigned long)num->value.uint64))
				return (NOK);
		}
		else
		{
			data->format.is_null_ptr = true;
			if (data->format.precision < 0)
				data->format.width += 5;
			if (ft_render_str(data, "(nil)"))
				return (NOK);
		}
	}
	return (OK);
}

int	ft_numlenpad(t_data *data, t_num *num)
{
	int	len;

	len = (int)ft_strlen_prtf(num->str);
	if (data->format.precision > len)
	{
		len = data->format.precision - len;
		if (ft_putcharn(data, '0', len))
			return (NOK);
	}
	return (OK);
}

int	ft_numjust(t_data *data, t_num *num)
{
	if (!data->format.justified && data->format.padding_len
		&& !data->format.zero)
	{
		if (ft_printpad(data, ' '))
			return (NOK);
	}
	if (data->format.specifier != 'p' || num->value.uint64)
		ft_printsign(data, num);
	if (data->format.padding_len && data->format.zero
		&& !data->format.justified && ft_printpad(data, '0'))
		return (NOK);
	if (ft_numlenpad(data, num))
		return (NOK);
	if (ft_putstr_prtf(data, num->str, (int)ft_strlen_prtf(num->str)))
		return (NOK);
	if (data->format.justified && data->format.padding_len
		&& !data->format.zero)
	{
		if (ft_printpad(data, ' '))
			return (NOK);
	}
	return (OK);
}

void	ft_numpre(t_data *data, char *s)
{
	if (data->format.width > 0)
	{
		if (data->format.precision >= 0 && data->format.base != HEX)
		{
			if (data->format.precision > (int)ft_strlen_prtf(s))
				data->format.padding_len = data->format.width
					- data->format.precision;
			else
				data->format.padding_len = data->format.width
					- ft_strlen_prtf(s);
		}
		else
			data->format.padding_len = data->format.width - ft_strlen_prtf(s);
	}
	if (data->format.precision >= 0)
		data->format.zero = false;
}

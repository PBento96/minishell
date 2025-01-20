/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:06:55 by pda-silv          #+#    #+#             */
/*   Updated: 2024/09/24 23:24:27 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_render_num(t_data *data)
{
	t_num	num;

	ft_bzero_prtf(&num, sizeof(t_num));
	if (ft_strchr_prtf("di", data->format.specifier))
	{
		num.sign = true;
		num.value.int64 = (long)va_arg(data->args, int);
		if (num.value.int64 < 0)
		{
			num.value.uint64 = -num.value.int64;
			num.absoluted = true;
		}
	}
	else if (data->format.specifier == 'p')
		num.value.uint64 = (unsigned long)va_arg(data->args, void *);
	else
		num.value.uint64 = (unsigned long)va_arg(data->args, unsigned int);
	if (ft_render_ptr(data, &num))
		return (NOK);
	if (!data->format.precision && !num.value.uint64)
		num.str[0] = 0;
	if (ft_numpad(data, &num))
		return (NOK);
	return (OK);
}

int	ft_numpad(t_data *data, t_num *num)
{
	if (data->format.specifier == 'p' && !num->value.uint64)
		return (OK);
	ft_numpre(data, num->str);
	if (num->absoluted || data->format.plus)
		data->format.padding_len--;
	if (data->format.hash && num->value.uint64)
		data->format.padding_len -= 2;
	if (data->format.padding_len && data->format.zero)
	{
		if (data->format.precision > (int)ft_strlen_prtf(num->str))
			data->format.padding_len -= data->format.precision
				- (int)ft_strlen_prtf(num->str);
	}
	if (ft_strchr_prtf("xX", data->format.specifier))
	{
		if (data->format.width > (int)ft_strlen_prtf(num->str))
			data->format.padding_len = data->format.width
				- (int)ft_strlen_prtf(num->str);
		if (data->format.precision > (int)ft_strlen_prtf(num->str))
			data->format.padding_len -= data->format.precision
				- (int)ft_strlen_prtf(num->str);
	}
	if (ft_numjust(data, num))
		return (NOK);
	return (OK);
}

int	ft_printpad(t_data *data, char c)
{
	if (data->format.specifier == 'p')
	{
		if (data->format.is_null_ptr)
			data->format.padding_len -= 5;
		else
			data->format.padding_len -= 2;
	}
	if (data->format.padding_len < 0)
		data->format.padding_len = 0;
	if (ft_putcharn(data, c, data->format.padding_len))
		return (NOK);
	return (OK);
}

int	ft_printsign(t_data *data, t_num *num)
{
	if (num->absoluted)
	{
		if (ft_putstr_prtf(data, "-", 1))
			return (NOK);
	}
	else if (data->format.base == DEC)
	{
		if (data->format.plus)
		{
			if (ft_putstr_prtf(data, "+", 1))
				return (NOK);
		}
		else if (data->format.space)
		{
			if (ft_putstr_prtf(data, " ", 1))
				return (NOK);
		}
	}
	else if ((data->format.hash && num->value.uint64)
		|| data->format.specifier == 'p')
	{
		if (ft_hexsign(data))
			return (NOK);
	}
	return (OK);
}

int	ft_hexsign(t_data *data)
{
	if (data->format.upper)
	{
		if (ft_putstr_prtf(data, "0X", 2))
			return (NOK);
	}
	else
	{
		if (ft_putstr_prtf(data, "0x", 2))
			return (NOK);
	}
	return (OK);
}

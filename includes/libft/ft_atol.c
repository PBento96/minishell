/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:17:11 by pda-silv          #+#    #+#             */
/*   Updated: 2024/09/27 14:18:21 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Converts str to an long, returns 0 if invalid.

long	ft_atol(const char *str)
{
	long	ret;
	bool	is_neg;

	ret = 0;
	is_neg = false;
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			is_neg = true;
		str++;
	}
	while (*str)
	{
		if (*str < 48 || *str > 57)
			break ;
		ret = ret * 10 + *str - 48;
		str++;
	}
	if (is_neg)
		ret = -ret;
	return (ret);
}

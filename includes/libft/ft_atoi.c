/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 08:47:32 by pda-silv          #+#    #+#             */
/*   Updated: 2024/05/07 15:50:55 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Converts str to an integer, returns 0 if invalid.

int	ft_atoi(const char *str)
{
	int	ret;
	int	is_neg;

	ret = 0;
	is_neg = 0;
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			is_neg = 1;
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

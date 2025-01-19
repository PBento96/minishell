/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:51:58 by pda-silv          #+#    #+#             */
/*   Updated: 2024/05/07 16:24:50 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Creates a copy of string str1. Returns NULL in case of failure.

char	*ft_strdup(const char *str1)
{
	size_t	len;
	char	*str2;
	char	*ptr;

	len = ft_strlen(str1);
	str2 = malloc((len + 1) * sizeof(char));
	if (!str2)
		return (0);
	ptr = str2;
	while (*str1)
		*str2++ = *str1++;
	*str2 = 0;
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:01:38 by pda-silv          #+#    #+#             */
/*   Updated: 2024/05/07 16:17:18 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Copies n bytes from src to dest. If the memories overlap, it copies from the
// last byte to the first.

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (!dest && !src)
		return (0);
	d = (char *)dest;
	s = (const char *)src;
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
		return (dest);
	}
	while (n--)
		d[n] = s[n];
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:15:28 by pda-silv          #+#    #+#             */
/*   Updated: 2024/05/11 17:21:38 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//  Returns a substring from string s begining at start and of max size len.

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	if (len > ft_strlen((char *)(s + start)))
		len = ft_strlen((char *)(s + start));
	str = malloc((unsigned int)(len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len && i + start < ft_strlen(s))
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = 0;
	return (str);
}

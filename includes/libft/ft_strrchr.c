/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:23:21 by pda-silv          #+#    #+#             */
/*   Updated: 2024/05/07 16:34:41 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Finds the last occurence of c in string s.

char	*ft_strrchr(const char *s, int c)
{
	char	*p;

	p = 0;
	while (*s)
	{
		if (*s == (unsigned char)c)
			p = (char *)s;
		s++;
	}
	if ((unsigned char)c == *s)
		p = (char *)s;
	return (p);
}

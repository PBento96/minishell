/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:19:47 by pda-silv          #+#    #+#             */
/*   Updated: 2024/09/27 15:28:57 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Sets n number of bytes to 0 starting at s.

void	ft_bzero(void *ptr, size_t n)
{
	char	*temp;

	temp = (char *)ptr;
	while (n--)
		temp[n] = '\0';
}

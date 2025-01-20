/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:15:09 by pda-silv          #+#    #+#             */
/*   Updated: 2024/10/03 10:11:07 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dlstsize(t_dlist *lst)
{
	int		c;
	t_dlist	*ptr;

	if (!lst)
		return (0);
	c = 1;
	ptr = ft_dlstfirst(lst);
	while (ptr->next)
	{
		ptr = ptr->next;
		c++;
	}
	return (c);
}

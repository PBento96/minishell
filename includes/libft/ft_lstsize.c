/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:15:09 by pda-silv          #+#    #+#             */
/*   Updated: 2024/05/09 17:03:28 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns the size of linked list lst.

int	ft_lstsize(t_list *lst)
{
	int		c;
	t_list	*ptr;

	if (!lst)
		return (0);
	c = 1;
	ptr = lst;
	while (ptr->next)
	{
		ptr = ptr->next;
		c++;
	}
	return (c);
}

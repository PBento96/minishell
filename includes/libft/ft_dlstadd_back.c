/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:17:38 by pda-silv          #+#    #+#             */
/*   Updated: 2024/10/07 17:25:58 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*ptr;

	if (*lst)
	{
		ptr = ft_dlstlast(*lst);
		ptr->next = new;
		new->prev = ptr;
	}
	else
		*lst = new;
}

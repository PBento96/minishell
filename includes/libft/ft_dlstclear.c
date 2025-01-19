/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:19:46 by pda-silv          #+#    #+#             */
/*   Updated: 2024/10/03 10:19:04 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*ptr;
	t_dlist	*next;

	ptr = ft_dlstfirst(*lst);
	while (ptr)
	{
		next = ptr->next;
		ft_dlstdelone(ptr, del);
		ptr = next;
	}
	*lst = NULL;
}

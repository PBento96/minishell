/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstlast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:16:35 by pda-silv          #+#    #+#             */
/*   Updated: 2024/10/03 10:02:32 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	t_dlist	*ptr;

	if (!lst)
		return (lst);
	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

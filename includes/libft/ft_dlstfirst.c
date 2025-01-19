/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstfirst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:16:35 by pda-silv          #+#    #+#             */
/*   Updated: 2024/10/03 10:00:39 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstfirst(t_dlist *lst)
{
	t_dlist	*ptr;

	if (!lst)
		return (lst);
	ptr = lst;
	while (ptr->prev)
		ptr = ptr->prev;
	return (ptr);
}

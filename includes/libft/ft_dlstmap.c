/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:30:19 by pda-silv          #+#    #+#             */
/*   Updated: 2024/10/03 10:15:11 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_dlist	*new;
	t_dlist	*head;
	void	*temp;

	head = NULL;
	lst = ft_dlstfirst(lst);
	while (lst)
	{
		temp = f(lst->content);
		if (!temp)
		{
			ft_dlstclear(&head, del);
			return (NULL);
		}
		new = ft_dlstnew(temp);
		if (!new)
		{
			ft_dlstclear(&head, del);
			del(temp);
			return (NULL);
		}
		ft_dlstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}

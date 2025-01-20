/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_mid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:17:38 by pda-silv          #+#    #+#             */
/*   Updated: 2024/10/03 10:26:44 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_mid(t_dlist *prev, t_dlist *next, t_dlist *new)
{
	prev->next = new;
	new->prev = prev;
	new->next = next;
	next->prev = new;
}

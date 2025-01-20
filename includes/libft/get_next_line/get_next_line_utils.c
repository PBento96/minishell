/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:36:40 by pda-silv          #+#    #+#             */
/*   Updated: 2024/09/24 23:20:51 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list_gnl	*ft_lst_last(t_list_gnl *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

bool	ft_newline(t_list_gnl *buffers)
{
	int	i;

	if (!buffers)
		return (false);
	while (buffers)
	{
		i = 0;
		while (buffers->str[i] && i < BUFFER_SIZE)
		{
			if (buffers->str[i] == '\n')
				return (true);
			i++;
		}
		buffers = buffers->next;
	}
	return (false);
}

int	ft_line_len(t_list_gnl *buffers)
{
	int	i;
	int	len;

	if (!buffers)
		return (0);
	len = 0;
	while (buffers)
	{
		i = 0;
		while (buffers->str[i])
		{
			if (buffers->str[i] == '\n')
				return (++len);
			i++;
			len++;
		}
		buffers = buffers->next;
	}
	return (len);
}

void	ft_clear_buffer(t_list_gnl **buffers, t_list_gnl *new)
{
	t_list_gnl	*temp;

	if (!*buffers)
		return ;
	while (*buffers)
	{
		temp = (*buffers)->next;
		free((*buffers)->str);
		free(*buffers);
		*buffers = temp;
	}
	*buffers = NULL;
	if (new->str[0])
		*buffers = new;
	else
	{
		free (new->str);
		free (new);
	}
}

void	ft_join_gnl(t_list_gnl *buffers, char *line)
{
	int	i;
	int	j;

	if (!buffers)
		return ;
	j = 0;
	while (buffers)
	{
		i = 0;
		while (buffers->str[i])
		{
			if (buffers->str[i] == '\n')
			{
				line[j++] = '\n';
				line[j] = '\0';
				return ;
			}
			line[j++] = buffers->str[i++];
		}
		buffers = buffers->next;
	}
	line[j] = '\0';
}

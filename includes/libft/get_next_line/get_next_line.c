/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:36:42 by pda-silv          #+#    #+#             */
/*   Updated: 2024/09/24 23:21:03 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list_gnl	*buffers[FD_MAX];
	char				*line;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	ft_read_file(buffers, fd);
	if (!buffers[fd])
		return (NULL);
	line = ft_render_line(buffers[fd]);
	ft_reset_buffers(&buffers[fd]);
	return (line);
}

void	ft_read_file(t_list_gnl **buffers, int fd)
{
	int		len;
	char	*buffer;

	while (!ft_newline(buffers[fd]))
	{
		buffer = malloc (sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		len = read(fd, buffer, BUFFER_SIZE);
		if (len < 1)
		{
			free(buffer);
			return ;
		}
		buffer[len] = '\0';
		ft_new_buffer(buffers, buffer, fd);
	}
}

void	ft_new_buffer(t_list_gnl **buffers, char *buffer, int fd)
{
	t_list_gnl	*new;
	t_list_gnl	*last;

	new = malloc(sizeof(t_list_gnl));
	if (!new)
		return ;
	new->next = NULL;
	new->str = buffer;
	last = ft_lst_last(buffers[fd]);
	if (!last)
		buffers[fd] = new;
	else
		last->next = new;
}

char	*ft_render_line(t_list_gnl *buffers)
{
	int		len;
	char	*line;

	if (!buffers)
		return (NULL);
	len = ft_line_len(buffers);
	line = malloc (sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	ft_join_gnl(buffers, line);
	return (line);
}

void	ft_reset_buffers(t_list_gnl **buffers)
{
	t_list_gnl	*last;
	t_list_gnl	*new;
	int			i;
	int			j;

	new = malloc (sizeof(t_list_gnl));
	if (!new)
		return ;
	new->next = NULL;
	new->str = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!new->str)
	{
		free(new);
		return ;
	}
	last = ft_lst_last(*buffers);
	i = 0;
	j = 0;
	while (last->str[i] && last->str[i] != '\n')
		i++;
	while (last->str[i] && last->str[++i])
		new->str[j++] = last->str[i];
	new->str[j] = '\0';
	ft_clear_buffer(buffers, new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:36:44 by pda-silv          #+#    #+#             */
/*   Updated: 2024/09/27 11:47:52 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_MAX
#  define FD_MAX 4096
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_list_gnl
{
	char				*str;
	struct s_list_gnl	*next;
}	t_list_gnl;

// get_next_line
void		ft_new_buffer(t_list_gnl **buffers, char *buffer, int fd);
char		*ft_render_line(t_list_gnl *buffers);
void		ft_read_file(t_list_gnl **buffers, int fd);
void		ft_reset_buffers(t_list_gnl **buffers);

// get_next_line_bonus
t_list_gnl	*ft_lst_last(t_list_gnl *lst);
bool		ft_newline(t_list_gnl *buffers);
int			ft_line_len(t_list_gnl *buffers);
void		ft_clear_buffer(t_list_gnl **buffers, t_list_gnl *new);
void		ft_join_gnl(t_list_gnl *buffers, char *line);

#endif
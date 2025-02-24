/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:37:51 by pda-silv          #+#    #+#             */
/*   Updated: 2025/02/20 11:26:52 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_shutdown(t_data **data, int retval)
{
	ft_printf("Exiting Minishell...\n");
	ft_free((void **)(*data)->input);
	ft_free((void **) data);
	exit(retval);
}

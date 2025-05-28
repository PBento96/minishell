/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:23:36 by pda-silv          #+#    #+#             */
/*   Updated: 2025/04/29 22:22:01 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Starts with the Beauty of ASCII Art */
static void	ft_header(void)
{
	ft_printf(C_BRT_GREEN "\n");
	ft_printf("  _ _ ___         _      _    _        _ _ \n");
	ft_printf(" | | |_  )  _ __ (_)_ _ (_)__| |_  ___| | |\n");
	ft_printf(" |_  _/ /  | '  \\| | ' \\| (_-< ' \\/ -_) | |\n");
	ft_printf("   |_/___| |_|_|_|_|_||_|_/__/_||_\\___|_|_|\n");
	ft_printf("\n\tProject by joseferr & pda-silv\n\n" RESET_COLOR);
}

static int	ft_init_data(t_data **data)
{
	*data = ft_calloc(1, sizeof(t_data));
	if (!data)
	{
		perror("calloc");
		return (NOK);
	}
	return (OK);
}

static char	**ft_envdup(char **env)
{
	int		count;
	char	**copy;
	int		i;

	count = 0;
	while (env[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	ft_initilaize(t_data **data, char **env)
{
	ft_header();
	if (ft_init_data(data))
		return (NOK);
	(*data)->env = ft_envdup(env);
	if (!(*data)->env)
		return (NOK);
	return (OK);
}

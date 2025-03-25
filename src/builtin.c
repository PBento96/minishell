/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:48 by joseferr          #+#    #+#             */
/*   Updated: 2025/03/25 19:47:21 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/************************/
/*Checks for the -n flag*/
/************************/
int	is_valid_echo_flag(const char *flag)
{
	const char	*ch = flag + 1;

	while (*ch != '\0')
	{
		if (*ch != 'n')
			return (0);
		ch++;
	}
	return (1);
}

/**********************/
/*Echo Builtin Command*/
/**********************/
void ft_echo(char **cmd_args)
{
	int newline;
	int i;

	newline = 1;
	i = 1;
	while (cmd_args[i] && cmd_args[i][0] == '-' && is_valid_echo_flag(cmd_args[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd_args[i])
	{
		ft_printf("%s", cmd_args[i]);
		if (cmd_args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
}

/*********************/
/*PWD Builtin Command*/
/*********************/
void	ft_pwd(t_data *data)
{
	ft_printf("%s\n", data->cwd);
}

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
	{
		ft_printf("%s\n", data->env[i]);
		i++;
	}
}

/***********************************/
/*Check and Execute Builtin Command*/
/***********************************/
void	ft_execute_builtin(t_data *data, char **cmd_args)
{
	char	*cmd;
	size_t	len;

	cmd = cmd_args[0];
	len = ft_strlen(cmd) + 1;
	printf("Executing builtin\n");
	if (!ft_strncmp(OP_EXT, cmd, len))
		ft_exit(data, cmd_args);
	if (!ft_strncmp(OP_PWD, cmd, len))
		ft_pwd(data);
	if (!ft_strncmp(OP_ECHO, cmd, len))
		ft_echo(cmd_args);
	if (!ft_strncmp(OP_ENV, cmd, len))
		ft_env(data);
	if (!ft_strncmp(OP_EXP, cmd, len))
		ft_export(data, cmd_args);
	if (!ft_strncmp(OP_UNS, cmd, len))
		ft_unset(data, cmd_args);
	if (!ft_strncmp(OP_CD, cmd, len))
		ft_cd(data, cmd_args);
}

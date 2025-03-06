/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:39:13 by pda-silv          #+#    #+#             */
/*   Updated: 2025/03/06 19:21:08 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

/* Input first spa treatment                   */
/* Closes the input if it ends with newline    */
/* If there's no input just shows newline      */
/* Adds input to command history               */
/* It now needs to parse and exec the input    */

void	ft_process_input(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i] != '\n' && data->input[i] != '\0')
		i++;
	if (data->input[i] == '\n')
		data->input[i] = '\0';
	if (ft_strlen(data->input) == 0)
	{
		ft_free((void **) &(data->input));
		return ;
	}
	add_history(data->input);
	ft_tokenize_input(data);
	ft_execute(data);
	ft_free((void **) &(data->input));
}

static void	ft_iohandler(t_data *data)
{
	ft_printf("%d", g_signal);
	if (!getcwd(data->cwd, sizeof(data->cwd)))
	{
		perror("getcwd");
		ft_shutdown(&data, ERR_IO);
	}
	ft_printf(C_BLUE"%s > "RESET_COLOR, data->cwd);
	data->input = readline("");
	if (!data->input)
	{
		perror("readline");
		ft_shutdown(&data, ERR_IO);
	}
	ft_process_input(data);
}

static void	ft_sighandler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGINT || signum == SIGQUIT || signum == SIGTERM)
		g_signal = SIGTERM;
}

/* Should start signal handling before running loop */

int	main(int argc, char **argv, char **env)
{
	struct sigaction	sa;
	t_data				*data;

	(void)argc;
	(void)argv;
	if (ft_initilaize(&data, env))
		ft_shutdown(&data, NOK);
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaddset(&sa.sa_mask, SIGTERM);
	sa.sa_sigaction = &ft_sighandler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	while (!g_signal)
		ft_iohandler(data);
	ft_shutdown(&data, OK);
}

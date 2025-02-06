/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:39:13 by pda-silv          #+#    #+#             */
/*   Updated: 2025/02/06 20:52:10 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Input first spa treatment                   */
/* Closes the input if it ends with newline    */
/* If there's no input just shows newline      */
/* Adds input to command history               */
/* It now needs to parse and exec the input    */

void	ft_process_input(t_data *data)
{
	int			i;

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
	ft_print_commands(data->commands, data->cmd_count);
	ft_free((void **) &(data->input));
}

static void	ft_iohandler(t_data *data)
{
    if (!getcwd(data->cwd, sizeof(data->cwd)))
    {
        perror("getcwd");
        ft_shutdown(&data, ERR_IO);
    }
	ft_printf("%s > ", data->cwd);
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
	t_data	*data;

	(void)info;
	data = (t_data *)context;
	if (signum == SIGINT || signum == SIGQUIT)
		ft_shutdown(&data, OK);
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
	sa.sa_sigaction = &ft_sighandler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, (void *)data);
	sigaction(SIGQUIT, &sa, (void *)data);
	while (true)
		ft_iohandler(data);
	ft_shutdown(&data, OK);
}

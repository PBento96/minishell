/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:39:13 by pda-silv          #+#    #+#             */
/*   Updated: 2025/05/27 12:16:25 by joseferr         ###   ########.fr       */
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
	if (!ft_is_quotes_balanced(data->input))
	{
		ft_printf(C_RED"Invalid Input - Unclosed Quotes\n"RESET_ALL);
		data->status = 1;
		if (data->input)
			ft_free((void **)&data->input);
		return ;
	}
	add_history(data->input);
	if (!ft_replace_tabs(data->input))
	{
		ft_free((void **) &(data->input));
		return ;
	}
	if (!ft_tokenize_input(data))
		ft_execute(data);
	ft_free((void **) &(data->input));
}

static void	ft_iohandler(t_data *data)
{
	char	prompt[MAX_CWD_SIZE + 20];

	if (!getcwd(data->cwd, sizeof(data->cwd)))
	{
		perror("getcwd");
		ft_shutdown(&data, ERR_IO);
	}
	ft_strlcpy(prompt, "", sizeof(prompt));
	ft_strlcat(prompt, C_BLUE, sizeof(prompt));
	ft_strlcat(prompt, data->cwd, sizeof(prompt));
	ft_strlcat(prompt, " > "RESET_COLOR, sizeof(prompt));
	data->input = readline(prompt);
	if (!data->input)
		ft_shutdown(&data, OK);
	ft_process_input(data);
}

static void	ft_sighandler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	g_signal = signum;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/* Adds a tab character when TAB is pressed instead of autocompletion */
static int	ft_tab_handler(int count, int key)
{
	(void)count;
	if (key == '\t')
	{
		rl_insert_text("\t");
		return (0);
	}
	return (1);
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
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
	rl_bind_key('\t', &ft_tab_handler);
	while (true)
		ft_iohandler(data);
	ft_shutdown(&data, OK);
}

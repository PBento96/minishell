/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:39:13 by pda-silv          #+#    #+#             */
/*   Updated: 2025/01/21 10:39:09 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Input first spa treatment                   */
/* Closes the input if it ends with newline    */
/* If there's no input just shows newline      */
/* Adds input to command history               */
/* It now needs to parse and exec the input    */

void	ft_process_input(char *input, char **env)
{
	int	i;

	i = 0;
	(void)env;
	while (input[i] != '\n' && input[i] != '\0')
		i++;
	if (input[i] == '\n')
		input[i] = '\0';
	if (ft_strlen(input) == 0)
	{
		free(input);
		printf("\n");
		return ;
	}
	add_history(input);
	ft_parse_and_exec_cmd(input, env);
	free(input);
}

char	*ft_get_user_input(void)
{
	char	*input;

	input = readline("");
	if (input == NULL)
		exit(EXIT_FAILURE);
	return (input);
}

/* Shows prompt with working directory */

void	ft_print_prompt(void)
{
	char	cwd[MAX_INPUT_SIZE];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	ft_printf("Minishell:%s> ", cwd);
}

static void	ft_sighandler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGINT || signum == SIGQUIT)
		exit(EXIT_FAILURE);
}

/* Should start signal handling before running loop */

int	main(int argc, char **argv, char **env)
{
	int					running;
	char				*input;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	running = 1;
	ft_header();
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_sigaction = &ft_sighandler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	while (running)
	{
		ft_print_prompt();
		input = ft_get_user_input();
		ft_process_input(input, env);
	}
	ft_printf("Exiting Minishell\n");
	return (EXIT_SUCCESS);
}

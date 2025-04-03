

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


#include "minishell.h"

/*********************/
/*PWD Builtin Command*/
/*********************/
void	ft_pwd(t_data *data)
{
	ft_printf("%s\n", data->cwd);
}


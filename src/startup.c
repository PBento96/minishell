/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:23:36 by pda-silv          #+#    #+#             */
/*   Updated: 2025/01/21 09:43:14 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_header(void)
{
	ft_printf(C_BRT_GREEN "\n");
	ft_printf("  _ _ ___         _      _    _        _ _ \n");
	ft_printf(" | | |_  )  _ __ (_)_ _ (_)__| |_  ___| | |\n");
	ft_printf(" |_  _/ /  | '  \\| | ' \\| (_-< ' \\/ -_) | |\n");
	ft_printf("   |_/___| |_|_|_|_|_||_|_/__/_||_\\___|_|_|\n");
	ft_printf("\n\tProject by joseferr & pda-silv\n\n" RESET_COLOR);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ansi.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:26:36 by pda-silv          #+#    #+#             */
/*   Updated: 2024/11/27 13:31:44 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ANSI_H
# define FT_ANSI_H

# define C_BLACK		"\033[30m"
# define C_RED			"\033[31m"
# define C_GREEN		"\033[32m"
# define C_YELLOW		"\033[33m"
# define C_BLUE			"\033[34m"
# define C_MAGENTA		"\033[35m"
# define C_CYAN			"\033[36m"
# define C_WHITE		"\033[37m"
# define C_BRT_BLACK	"\033[90m"
# define C_BRT_RED		"\033[91m"
# define C_BRT_GREEN	"\033[92m"
# define C_BRT_YELLOW	"\033[93m"
# define C_BRT_BLUE		"\033[94m"
# define C_BRT_MAGENTA	"\033[95m"
# define C_BRT_CYAN		"\033[96m"
# define C_BRT_WHITE	"\033[97m"

# define BG_BLACK		"\033[40m"
# define BG_RED			"\033[41m"
# define BG_GREEN		"\033[42m"
# define BG_YELLOW		"\033[43m"
# define BG_BLUE		"\033[44m"
# define BG_MAGENTA		"\033[45m"
# define BG_CYAN		"\033[46m"
# define BG_WHITE		"\033[47m"
# define BG_BRT_BLACK	"\033[100m"
# define BG_BRT_RED		"\033[101m"
# define BG_BRT_GREEN	"\033[102m"
# define BG_BRT_YELLOW	"\033[103m"
# define BG_BRT_BLUE	"\033[104m"
# define BG_BRT_MAGENTA	"\033[105m"
# define BG_BRT_CYAN	"\033[106m"
# define BG_BRT_WHITE	"\033[107m"

# define T_BOLD			"\033[1m"
# define T_DIM			"\033[2m"
# define T_ITALIC		"\033[3m"
# define T_UNDER		"\033[4m"
# define T_BLINK		"\033[5m"
# define T_REVERSE		"\033[7m"
# define T_HIDDEN		"\033[8m"
# define T_STRIKE		"\033[9m"

# define RESET_ALL		"\033[0m"
# define RESET_COLOR	"\033[39m"
# define RESET_BG		"\033[49m"
# define RESET_BOLD		"\033[21m"
# define RESET_DIM		"\033[22m"
# define RESET_ITALIC	"\033[23m"
# define RESET_UNDER	"\033[24m"
# define RESET_BLINK	"\033[25m"
# define RESET_REVERSE	"\033[27m"
# define RESET_HIDDEN	"\033[28m"
# define RESET_STRIKE	"\033[29m"

#endif

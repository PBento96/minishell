/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:51:01 by pda-silv          #+#    #+#             */
/*   Updated: 2024/09/27 11:48:19 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define BASE_LOWER "0123456789abcdef"
# define BASE_UPPER "0123456789ABCDEF"

# define SPECIFIERS "cspdiuxX%"
# define FLAGS "-+ #0"

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>

typedef enum e_base
{
	DEC = 10,
	HEX = 16
}	t_base;

typedef enum e_retval
{
	OK = 0,
	NOK = -1
}	t_retval;

typedef union u_union64
{
	long			int64;
	unsigned long	uint64;
}	t_union64;

typedef struct s_num
{
	t_union64	value;
	char		str[32];
	int			ptr;
	bool		absoluted;
	bool		sign;
}	t_num;

typedef struct s_format
{
	t_base	base;
	int		width;
	int		precision;
	int		padding_len;
	char	specifier;
	bool	justified;
	bool	plus;
	bool	space;
	bool	zero;
	bool	hash;
	bool	upper;
	bool	is_null_ptr;
}	t_format;

typedef struct s_data
{
	va_list		args;
	const char	*ptr;
	t_format	format;
	int			len;
}	t_data;

// ft_parser
int		ft_parser(t_data *data);
void	ft_setflags(t_data *data);
void	ft_getvalue(t_data *data, int *value);

// ft_render
int		ft_render(t_data *data);
int		ft_render_chr(t_data *data, char c);
int		ft_render_str(t_data *data, char *s);
void	ft_strpad(t_data *data, char *s);
int		ft_strpre(t_data *data, char *s);
int		ft_render_num(t_data *data);
int		ft_numpad(t_data *data, t_num *num);
int		ft_printpad(t_data *data, char c);
int		ft_printsign(t_data *data, t_num *num);
int		ft_hexsign(t_data *data);
int		ft_render_ptr(t_data *data, t_num *num);
int		ft_numlenpad(t_data *data, t_num *num);
int		ft_numjust(t_data *data, t_num *num);
void	ft_numpre(t_data *data, char *s);
int		ft_handle_null_ptr(t_data *data);

// ft_utils
int		ft_putstr_prtf(t_data *data, const char *s, int len);
void	ft_bzero_prtf(void *s, size_t n);
char	*ft_strchr_prtf(const char *s, int c);
size_t	ft_strlen_prtf(const char *s);
int		ft_atoi_prtf(t_data *data);
int		ft_putcharn(t_data *data, char c, int len);
char	ft_getchar(t_data *data, unsigned long n);
int		ft_itoa_prtf(t_data *data, t_num *num, unsigned long tmp);
size_t	ft_strlcpy_prtf(char *dst, const char *src, size_t size);

#endif
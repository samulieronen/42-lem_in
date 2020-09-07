/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:13:51 by seronen           #+#    #+#             */
/*   Updated: 2020/02/27 13:30:18 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define ALLSYM "cspdiouxXf#-+ .%*0123456789hLlz"
# define FORMAT "cspdiouxXf%"
# define LENMOD "lhLz"
# include <stdarg.h>
# include "libft.h"

typedef struct	s_printf
{
	char		format;

	int			printed;

	int			hash;
	int			plus;
	int			minus;
	int			space;
	int			zero;
	int			star;
	int			dot;
	int			width;
	int			precision;
	int			widthst;
	int			precisionst;
	int			fprecision;
	int			sign;
	char		*length;
}				t_printf;

int				ft_printf(const char *format, ...);
int				print_str(va_list arg, t_printf *node);
int				print_char(va_list arg, t_printf *node);
int				print_ptr(va_list arg, t_printf *node);
int				print_dec(va_list arg, t_printf *node);
int				print_octal(va_list arg, t_printf *node);
int				print_unsig(va_list arg, t_printf *node);
int				print_hex(va_list arg, t_printf *node);
int				print_float(va_list arg, t_printf *node);
int				print_percentage(t_printf *node);
char			*width(char *str, t_printf *node, char c, int nb);
char			*precision(char *str, t_printf *node, int nb);
char			*manage_plus_minus(t_printf *node, char *str);
char			*handle_space(t_printf *node, char *str);
int				save_length(char flag, t_printf *node);
int				save_precision(t_printf *node, char flag);
int				save_width(t_printf *node, char flag);
char			*strnew_char(size_t nb, char c);
char			*addchar(char *str, char c);
t_printf		*init_node_start(void);
int				init_node(t_printf *node);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:46:41 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/28 16:41:54 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
# include "datatypes.h"
#ifndef PARSER_H
# define PARSER_H

# define SEMI_COL -1
# define BLANK -2
# define PIPE -3
# define AND -4
# define OR -5
# define BOTH_FDS -6
# define CLOSE_FD -7
# define HEREDOC -8
# define QUOTE -9
# define D_QUOTE -10
# define OUT_RED_OP -11
# define IN_RED_OP -12
# define APP_OUT_RED_OP -13
# define HEREDOC_OP -14
# define FD_AGGR -15
# define UQ_ESCAPE -16
# define Q_ESCAPE -17
# define DOLLAR -18
# define TILDE -19
# define BG -20
# define IS_REDIRECTION str[i] == -11 || str[i] == -12 || str[i] == -13
# define _OR ||
# define _AND &&
# define _EQ ==
# define _NEQ !=
# define S -1
# define P -3
# define O -11
# define R -12
# define B -20
# define A -13
# define H -14
# define L line
# define TCO(i, _O, C) L[i] C -4 _O L[i] C -5 _O L[i] C -13 _O L[i] C -14
# define OCO(i, _O, C) L[i] C S _O L[i] C P _O L[i] C O _O L[i] C R _O L[i] C B
# define IS_OPERATOR(i, _O, C) TCO(i, _O, C) _O OCO(i, _O, C)
# define IS_REDIR_OP(i, _O, C) L[i] C O _O L[i] C R _O L[i] C A _O L[i] C H
# define NOT_ESCAPED(i)  L[(i - 1 > 0) ? i - 1 : 0] != UQ_ESCAPE
# define AT(i) (i - 1 > 0) ? i - 1 : 0
# define NEQ_ESCAPE(i) L[AT(i)] != -16 && L[AT(i)] != -17
# define LEFT_OPR 0b00000001
# define RIGHT_OPR 0b00000010
# define PARAMS (void *)head, (void *)&curr, (void *)tail
# define APPEND(type) append_lst(PARAMS, type)
# define SETFLAG(type) set_flag(curr, token[j], type)

/* 
** 
*/ 

// t_shell			*init_shell(void);
// t_shell			*get_shell_cfg(t_shell *new);
void			ft_sigint_handler();
void			ft_sigcunt();
char			*pre_parse(char *line);
void			mark_operators(char *line);
int				get_bg_jobs(char *line);
void			mark_bg_op(char *line);
t_job			*parse();
int				get_input(char **line, char *p, char *eof);
void			check_wildcard_c(char **line);
int				dquotes_checker(char **line, char *dq, int *i, int *j);
int				squotes_checker(char **line, char *q, int *i);
int				check_syntax_errors(char *line);
t_job			*get_jobs(char **cmd_chain, int	bg);
t_process		*get_process_list(char *cmd_chain, char type);
void			append_lst(void **h, void **c, void **t, char type);
int				set_flag(void *curr, int flag, char type);
char			*skip_operators(char type, char *token, int *start, int *j);
int				get_list_node(char type, void **curr, char *str);
char			*check_redirections(char *str, t_process *cmd);
char			escape_char(char c);
int				get_redir_fds(t_redir *curr, char *str, int *i);
void			get_redir_file(t_redir *curr, char *str, int *i);
char			*get_heredoc(char *str, int *i, int *hd_fd);
int				is_not_blank(char *line, int j, int i);
void			apply_globbing(char **line);
int				get_glob_buffer(char *gl_pattern, char **args);
void			apply_expansions(char **args);
void			search_and_expand(char **s1, char c);
int				apply_glob_expansion(char *gl_pattern, char **args);
void			quotes_delimiter(char **tmp);
int				is_not_blank(char *line, int j, int i);
char			*get_esc_char(char *str, char c);
char			*get_substring(char *str, int *k, char type);
void			expand_dollar(char *dollar, char **args, int *j);
void			expand_tilde(char **args, int *j);
void			quoted_escape(char **arg);
void			remove_quotes(char **args);
void			remove_escapes(char **str, char escape);

#endif

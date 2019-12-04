/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:18:09 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/04 17:21:28 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "shell.h"
# define COUNT 1000
# define INTERN 1
# define ALIAS 2
# define COMMANDS 3
# define ANYHASH 4
# define EXPORTED 0
# define INCLUDE_UNEXPORTED 1
# define EXPORTED_ONLY 2
# define KEYS_ONLY 4

typedef int		    t_function(char **args);
typedef int		    t_testfunction();

t_function			*ft_is_builtin(char *arg);
void				ft_init_builtins(char **env);
char				*ft_getenv(char *key);

/*
** ft_serialize_env():
** @param {exportd}: [INCLUDE_UNEXPORTED | EXPORTED_ONLY]
** get a (char **) version of the envirenment , return value may
** include unexported intern variables when `INCLUDE_UNEXPORTED` is specified
*/

char				**ft_serialize_env(char exported);

int	    			ft_export(char **args);

int	    			ft_set(void);
int	    			ft_unset(char **args);
/*
** intern
*/

char				ft_isintern(char *cmd);
int					ft_getinterns(t_params *params, t_process *process);
void				ft_cpyenv(t_params *p);
void				ft_add_to_tmp_map(t_params *p, char *key, char *value);

/*
** HASHMAP
*/

int					ft_hash_calc(char *key);
void				ft_empty(char freeall);
void				ft_init_hash(void);
void				ft_hashdelete_one(char *key, char type);
int	    			ft_hash(char **args);
void				ft_print_hash_list(void);
t_map				*ft_addtohashmap(char *key, char *value, char type);
t_map				*ft_getbykey(char *key, char type);
char				*ft_getvlaue_bykey(char *key, char type);
void				ft_get_kv(char *str, char **key, char **val);


int	    			ft_cd(char **args);

int	    			ft_exit(char **argv);

int	    			ft_type(char **args);

int	                ft_fc(char *args);

int		            ft_test(char **args);
/*
** ALIAS 
*/

void	            ft_show_aliases(char *key);
int	                ft_alias(char **args);
int	    	        ft_unalias(char **cmd);
void	            ft_insert_at(t_job *job, t_process *proc, size_t index);
int	                ft_handle_alias(t_job *job);

int	                ft_echo(char **args);

int	    			ft_fg(char **arg);
int 				ft_bg(char **arg);
int 				ft_jobs(char **args);

#endif

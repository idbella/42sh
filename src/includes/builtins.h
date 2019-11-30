/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:18:09 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/30 15:03:26 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# define COUNT 1000
# define INTERN 1
# define ALIAS 2
# define COMMANDS 3
# define ANYHASH 4
# define EXPORTED 0
# define INCLUDE_UNEXPORTED 1
# define EXPORTED_ONLY 0
# include "shell.h"

typedef void		*t_function();

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

void				ft_export(char **args);

void				ft_set(void);
void	            ft_unset(char **args);
/*
** intern
*/

char				ft_isintern(char *cmd);

/*
** HASHMAP
*/

int					ft_hash_calc(char *key);
void				ft_empty(char freeall);
void				ft_init_hash(void);
void				ft_hashdelete_one(char *key, char type);
void				ft_hash(char **args);
void				ft_print_hash_list(void);
t_map				*ft_addtohashmap(char *key, char *value, char type);
t_map				*ft_getbykey(char *key, char type);
char				*ft_getvlaue_bykey(char *key, char type);
void				ft_get_kv(char *str, char **key, char **val);


void		ft_exit(char **argv);

#endif

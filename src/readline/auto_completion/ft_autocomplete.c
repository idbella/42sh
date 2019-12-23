/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autocomplete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:31:52 by oherba            #+#    #+#             */
/*   Updated: 2019/12/23 18:35:19 by oherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_free_auto_lst(t_auto **lst)
{
	if ((*lst))
	{
		if ((*lst)->next)
			ft_free_auto_lst(&(*lst)->next);
		ft_strdel(&((*lst)->str));
		free(*lst);
		*lst = NULL;
	}
}

char	*ft_take_new_line(char *input, t_init *init, int *cursor, char *line)
{
	char *str;
	char	c;
	int		i;
	int		len;

	i = 0;
	len = 0;
	str = NULL;
	while (*cursor > 0)
	{
		c = line[*cursor];
		if (c == SEMI_COL || c == PIPE || c == OR || c == AND || c == BG)
		{
			i = 1;
			break;
		}
		(*cursor)--;
	}
	if (i == 1)
	{
		len = init->s_cursor - *cursor - (int)ft_promptlen(init->promt);
		str = ft_strsub(input, *cursor + 1, len);
	}
	(*cursor)++;
	return (str); 
}

int		ft_if_empty_first_word(char *line, t_init *init , int cursor)
{
	int		i;
	int		new_cursor;
	
	i = 0;
	new_cursor = init->s_cursor - cursor - (int)ft_promptlen(init->promt);
	if (new_cursor == 0 && line[new_cursor] == '\0')
		return (1);
	while(new_cursor > 0)
	{	
		if (line[new_cursor] != ' ' && line[new_cursor] != '\t')
			return (0);
		new_cursor--;
	}
	return (1);
}

int		ft_cursor_position(char *s, int cursor)
{
	int start;
	int end;

	start = 0;
	end = 0;
	while (ft_isspace(*s))
	{
		start++;
		s++;
	}
	end = start;
	while (*s && !ft_isspace(*s))
	{
		end++;
		s++;
	}
	if (cursor >= start && cursor <= end)
		return (1);
	return (0);
}

int		ft_is_cursor_in_first_word(t_init *init, char *line, int cursor)
{
	int		new_cursor;

	new_cursor = 0;
	if (ft_if_empty_first_word(line, init, cursor + 1) == 1)	
		return (1);
	new_cursor = init->s_cursor - cursor - (int)ft_promptlen(init->promt) - 1;
	if (ft_cursor_position(line, new_cursor) == 1)
		return (1);
	return(0);		
}

int		ft_is_first_cmd(char *input, t_init *init)
{
	char	*line;
	int		cursor;
	char	*new_line;

	new_line = NULL;
	cursor = init->s_cursor - (int)ft_promptlen(init->promt);
	line = ft_strdup(input);
	mark_operators(line);
	mark_bg_op(line);
	if (line[cursor] == '\0')
		cursor--;
	new_line = ft_take_new_line(input, init, &cursor, line);
	if (new_line)
	{
		if (ft_is_cursor_in_first_word(init, new_line, cursor) == 1)
		{
			ft_strdel(&new_line);
			ft_strdel(&line);
			return (1);
		}
		ft_strdel(&new_line);
	} 
	ft_strdel(&line);
	return(0);
}

int		ft_is_first_word_42(char *line, t_init *init)
{
	int		i;
	int		j;

	j = 0;
	i = init->s_cursor - ft_promptlen(init->promt);
	if (init->out_put[init->s_cursor] == '\0' && init->s_cursor == (int)ft_promptlen(init->promt))
		return (0);
	i--;
	while(i > 0)
	{
		if (line[i] != ' ' && line[i] != '\t')
			j = 1;
		i--;
	}
	if (j == 0)
		return (2);
	if (ft_cursor_position(line, init->s_cursor - (int)ft_promptlen(init->promt)) == 1)
		return (0);
	if (ft_is_first_cmd(line, init) == 1)
		return (0);
	return(1);
}

void	ft_move_cursor_right(t_init *init)
{
	if (init->s_cursor < init->s_l)
	{
		init->s_cursor++;
		tputs(tgetstr("nd", NULL), 0, my_putchar);
	}
}

void	ft_move_cursor_left(t_init *init)
{
	if (init->s_cursor > (int)ft_promptlen(init->promt))
	{
		init->s_cursor--;
		tputs(tgetstr("le", NULL), 0, my_putchar);
	}
}

void	ft_move_left_word(t_init *init, char *tmp)
{
	char 	c;
	
	if (tmp[init->s_cursor] == BLANK)
	{
		if (init->s_cursor > (int)ft_promptlen(init->promt))
		{
			init->s_cursor--;
			tputs(tgetstr("le", NULL), 0, my_putchar);
		}
		//ft_move_cursor_left(init);
	}
		c = tmp[init->s_cursor];
		while (init->s_cursor > (int)ft_promptlen(init->promt) && 
			c != BLANK && c != PIPE && c != OR &&
			 c != AND && c != SEMI_COL && c != BG)
		{
			// ft_move_cursor_left(init);
			if (init->s_cursor > (int)ft_promptlen(init->promt))
			{
				init->s_cursor--;
				tputs(tgetstr("le", NULL), 0, my_putchar);
			}	
			c = tmp[init->s_cursor];
		}
}

void	ft_move_right_word(t_init *init, char *tmp)
{
	char 	c;

	c = tmp[init->s_cursor];
	if (c == BLANK || c == PIPE || c == OR ||
		c == AND || c == SEMI_COL || c == BG)
	{
		//ft_move_cursor_right(init);
		if (init->s_cursor < init->s_l)
		{
			init->s_cursor++;
			tputs(tgetstr("nd", NULL), 0, my_putchar);
		}
	}			
	c = tmp[init->s_cursor];
	while (init->s_cursor < init->s_l &&
		c != BLANK && c != PIPE && c != OR && 
		c != AND && c != SEMI_COL && c != BG)
	{
		//ft_move_cursor_right(init);
		if (init->s_cursor < init->s_l)
		{
			init->s_cursor++;
			tputs(tgetstr("nd", NULL), 0, my_putchar);
		}
		c = tmp[init->s_cursor];
	}
}
void	ft_move_by_word(int flg, t_init *init)
{
	char 	*tmp;
	//char	c;

	tmp = ft_strdup(init->out_put);
	mark_operators(tmp);
	mark_bg_op(tmp);
	if (flg == 1)
	{
		ft_move_left_word(init, tmp);
		// if (tmp[init->s_cursor] == BLANK)
		// 	ft_move_cursor_left(init);
		// c = tmp[init->s_cursor];
		// while (init->s_cursor > (int)ft_promptlen(init->promt) && 
		// 	c != BLANK && c != PIPE && c != OR &&
		// 	 c != AND && c != SEMI_COL && c != BG)
		// {
		// 	ft_move_cursor_left(init);
		// 	c = tmp[init->s_cursor];
		// }
	}
	else if (flg == 4)
	{
		ft_move_right_word(init, tmp);
		// c = tmp[init->s_cursor];
		// if (c == BLANK || c == PIPE || c == OR ||
		//  c == AND || c == SEMI_COL || c == BG)
		// 	ft_move_cursor_right(init);
		// c = tmp[init->s_cursor];
		// while (init->s_cursor < init->s_l &&
		// 		c != BLANK && c != PIPE && c != OR && 
		// 		c != AND && c != SEMI_COL && c != BG)
		// {
		// 	ft_move_cursor_right(init);
		// 	c = tmp[init->s_cursor];
		// }
	}
	ft_strdel(&tmp);
}

char	*ft_take_to_complte_42(t_init *init)
{
	char	*str;
	int		start;
	int		end;

	str = NULL;
	ft_move_by_word(1, init);
	start = init->s_cursor;
	ft_move_by_word(4, init);
	end = init->s_cursor;
	if (start != (int)ft_promptlen(init->promt))
	{
		start += 1;
		str = ft_strsub(init->out_put, start, end - start);
	}
	else
		str = ft_strsub(init->out_put, start, end - start);
	return (str);
}

char	ft_keyexist(t_auto *lst, char *key)
{
	while (lst)
	{
		if (ft_strequ(lst->str, key))
			return (1);
		lst =lst->next;
	}
	return (0);
}

t_auto	*add_to_auto_42(t_auto *lst, char *str)
{
	t_auto	*new;
	t_auto	*tmp;

	if (ft_keyexist(lst, str))
		return (lst);
	tmp = lst;
	if (lst == NULL)
	{
		new = malloc(sizeof(t_auto) * 1);
		new->str = ft_strdup(str);
		new->next = NULL;
		new->prev = NULL;
		return (new);
	}
	else
	{
		while (lst->next)
			lst = lst->next;
		new = malloc(sizeof(t_auto) * 1);
		new->str = ft_strdup(str);
		new->next = NULL;
		new->prev = lst;
		lst->next = new;
		return (tmp);
	}
}

char	**ft_catpath(void)
{
	char **array;
	char *path;
	
	array = NULL;
	path = ft_getenv("PATH");
	if (!path)
		return (NULL);
	array = ft_strsplit(path, ':');
	return (array);
}

t_auto	*ft_get_completion_path_42(t_init *init)
{
	t_auto			*lst;
	char 			**str;
	DIR				*dir;
	struct dirent	*drt;
	char 			**tmp;

	lst = NULL;
	str = ft_catpath();
	tmp = str;
	if (str == NULL)
		return(NULL);
	while (*str)
	{
		if (!(dir = opendir(*str)))
			return (NULL);
		while ((drt = readdir(dir)))
		{
			if (!ft_strncmp(drt->d_name, init->to_complete, ft_strlen(init->to_complete)))
				lst = add_to_auto_42(lst, drt->d_name);
		}
		closedir(dir);
		str++;
	}
	ft_free_array(tmp);
	return(lst);
}

t_auto		*ft_get_completion_built_42(t_init *init, t_auto **lst)
{
	int		len;
	int		i;
	char	**alias;

	i = 0;
	len = ft_strlen(init->to_complete);
	while (i < BUILTINS_COUNT)
	{
		if (ft_strncmp(get_shell_cfg(0)->builtins[i].key, init->to_complete, len) == 0)
			*lst = add_to_auto_42(*lst, get_shell_cfg(0)->builtins[i].key);
		i++;
	}
	alias = ft_getaliaskeys();
	i = 0;
	while (alias && alias[i])
	{
		if (ft_strncmp(alias[i], init->to_complete, len) == 0)
			*lst = add_to_auto_42(*lst, alias[i]);
		i++;
	}
	ft_free_array(alias);
	return(*lst);
}

int		ft_is_var(char *to_complete)
{
	int i;
	int n;
	char 	*tmp;
 
	i = 0;
	n = 0;
	tmp = ft_strdup(to_complete);
	mark_operators(tmp);
	mark_bg_op(tmp);
	if (ft_strlen(to_complete) == 1 && to_complete[0] == '$')
	{
		free(tmp);
		return (1);
	}
	while (tmp[i])
	{
		if (tmp[i] == DOLLAR)
			n++;
		i++;
	}
	ft_strdel(&tmp);
	return (n);
}

t_auto	*ft_get_completion_env_var_42(t_init *init)
{
	t_auto	*lst;
	char	**env;
	int		len;
	int		i;
	int		n;
	char	*to_complete;

	to_complete = init->to_complete;
	n = ft_is_var(to_complete);
	i = 0;
	lst = NULL;
	if (n == 1)
	{
		env = ft_serialize_env(INCLUDE_UNEXPORTED | KEYS_ONLY);
		while (to_complete[i] && to_complete[i] != '$')
			i++;
		if (to_complete[i] && to_complete[i] == '$' && to_complete[i + 1] == '{')
			i++;
		to_complete = &(to_complete[i + 1]);
		i = 0;
		len = ft_strlen(to_complete);
		while (env[i])
		{
			if (ft_strncmp(env[i], to_complete, len) == 0)
				lst = add_to_auto_42(lst, env[i]);
			i++;
		}
		ft_free_array(env);
	}
	return (lst);
}


int		ft_max_len_lst_42(t_auto	*lst, int *lst_len)
{
	int			i;
	size_t		max;

	max = 0;
	i = 0;
	*lst_len = 0;
	while(lst)
	{
		if (ft_strlen(lst->str) > max)
			max = ft_strlen(lst->str);
		lst = lst->next;
		(*lst_len)++;
	}
	return (max);
}

int		ft_8_42(int l)
{
	int	i;

	i = 0;
	while (i <= l)
		i += 8;
	return (i);
}

char	**ft_convert_lst_to_tab(t_auto *lst, int lst_len)
{
	char	**tabl;
	int 	i;

	i = 0;
	tabl = NULL;
	if (!(tabl = (char **)ft_memalloc(sizeof(char *) * (1 + lst_len))))
		return (NULL);
	while (lst)
	{
		tabl[i] = ft_strdup(lst->str);
		lst = lst->next;
		i++;
	}
	return(tabl);
}

void	ft_put_2(char *t, int i)
{
	int	j;

	j = ft_strlen(t);
	ft_putstr(t);
	while (j < i)
	{
		ft_putchar(' ');
		j++;
	}
}

void	ft_print_tab(char **t, int b, int m, int n)
{
	int i;
	int j;

	i = 0;
	ft_putchar('\n');
	while (i < b)
	{
		j = i;
		while (j < m)
		{
			ft_put_2(t[j], n);
			j += b;
		}
		if (i < b - 1)
			ft_putchar('\n');
		i++;
	}
}

void	ft_ls_print_42(t_auto *lst, int print_len, int lst_len)
{
	struct winsize	info;
	int				a;
	int				b;
	char			**table;
	
	if (!(table = ft_convert_lst_to_tab(lst, lst_len)))
		return ;
	ioctl(0, TIOCGWINSZ, &info);
	if (!print_len)
		return;
	a = info.ws_col / print_len;
	if (!a)
		return;
	b = lst_len / a;
	if ((lst_len % a) != 0)
		b++;
	ft_print_tab(table, b, lst_len, print_len);
	ft_free_array(table);
}


void	ft_completion_display(t_init *init , char *completion)
{
	int i;
	int j;
	int k;

	i = 0;
	j = init->s_cursor;
	k = ft_strlen(completion) - 1;
	while (i < k)
	{
		if (j < init->s_l)
			tputs(tgetstr("nd", NULL), 0, my_putchar);
		j++;
		i++;
	}	
}

void	replace_the_auto_comlete_42(t_init *init, char *completion)
{
	int i;
	int j;
	char	*tmp;

	j = 0;
	i = init->s_cursor - 1;
	tmp =  ft_strdup(init->out_put);
	mark_operators(tmp);
	mark_bg_op(tmp);
	while (i > (int)ft_promptlen(init->promt)  && tmp[i] != BLANK &&
	 tmp[i] != PIPE && tmp[i] != OR && tmp[i] != AND && 
	 tmp[i] != SEMI_COL && tmp[i] != BG)
		i--;
	ft_strdel(&tmp);
	if (i != (int)ft_promptlen(init->promt))
		i += 1;
	if (init->s_cursor > (int)ft_promptlen(init->promt))
	{
		j = init->s_cursor;
		while (j > i)
		{
			del_char_of_line(&init->out_put, init);
			i++;
		}
	}
	ft_cat_string_of_line(init, completion);
	ft_completion_display(init , completion);
}

t_auto	*ft_search_complete_dir_42(char *to_complete, char *directory)
{
    DIR *dir;
    struct dirent *lst;
	t_auto	*auto_lst;
	char	*name;

	auto_lst = NULL;
    if (!(dir = opendir(directory)))
        return (NULL);
    while ((lst = readdir(dir)))
    {
		name = lst->d_name;
		if ((*to_complete != '.' && *name == '.') || ft_strequ("..", name) || ft_strequ(".", name))
			continue ;
		if (ft_strncmp(lst->d_name, to_complete , ft_strlen(to_complete)) == 0)
			auto_lst = add_to_auto_42(auto_lst, lst->d_name);
	}
    closedir(dir);
	return(auto_lst);
}

void	ft_print_one_completion(t_init *init, char *to_complete)
{
	char	*completion;
	int		i;
	char	*str;

	i = 0;
	completion = NULL;
	str = NULL;
	if(ft_is_var(to_complete) == 1)
	{
		while (to_complete[i] && to_complete[i] != '$')
			i++;
		if (to_complete[i] && to_complete[i] == '$' && to_complete[i + 1] == '{')
			i++;
		str = ft_strsub(to_complete, 0, i + 1);
		completion = ft_strjoin(str, (init->completion_lst->str));
		ft_strdel(&str);	
	}
	else
		completion = ft_strdup(init->completion_lst->str);
	replace_the_auto_comlete_42(init, completion);
	ft_strdel(&completion);
}


int		ft_path_dir(char **to_complete, char **old_to_complete, char **path)
{
	char 	*home_dir;
	struct stat st;
	char 		*tmp;

	tmp = NULL;
	if ((*to_complete)[0] == '~')
	{
		if ((home_dir = ft_getenv("HOME")))
		{
			*(old_to_complete) = ft_strdup(*to_complete);
			*to_complete = ft_strjoin(home_dir, &((*to_complete)[1]));
		}
	}
	if ((!stat(*to_complete, &st) && (S_ISDIR(st.st_mode))))
	{
		*path = ft_strdup(*to_complete);
		ft_strdel(old_to_complete);
			return(2);
	}
	return(0);
}

int		ft_check_if_is_dir(char **path,char	**old_to_complete, char **new_to_complete, char **tilda)
{
	struct stat st;
	int			i;

	i = 0;
	if (!stat(*path, &st))
	{
		if (S_ISDIR(st.st_mode))
		{
			if (*old_to_complete)
			{
				i = ft_strlen(*old_to_complete) - ft_strlen(*new_to_complete);
				*tilda = ft_strsub(*old_to_complete, 0, i);
				ft_strdel(old_to_complete);
			}
			return(1);
		}
	}
	return (0);
}

int		ft_if_is_dir(char *to_complete, char **path, char **new_to_complete, char **tilda)
{
	int		i;
	char	*old_to_complete;
	int		n;
	
	old_to_complete = NULL;
	i = 0;
	if (ft_path_dir(&to_complete, &old_to_complete, path) == 2)
	{
		if (get_shell_cfg(0)->init->to_complete != to_complete)
			free(to_complete);
		return (2);
	}
	*new_to_complete = ft_strrchr(to_complete, '/');
	if (*new_to_complete == NULL)
	{
		if (get_shell_cfg(0)->init->to_complete != to_complete)
			free(to_complete);
		return (0);
	}
	else
	{
		(*new_to_complete)++;
		i = ft_strlen(to_complete) - ft_strlen(*new_to_complete);
		*path = ft_strsub(to_complete, 0, i);
	}
	n = ft_check_if_is_dir(path, &old_to_complete, new_to_complete, tilda);
	if (get_shell_cfg(0)->init->to_complete != to_complete)
		free(to_complete);
	return (n);
}

int		ft_if_is_dir_2(char **to_complete, char **path, char **new_to_complete, char **tilda)
{
	int		i;
	char	*old_to_complete;
	char	*tmp;
	int		n;
	
	tmp = *to_complete;
	old_to_complete = NULL;
	i = 0;
	if (ft_path_dir(to_complete, &old_to_complete, path) == 2)
	{
		if (tmp != *to_complete)
			free(tmp);
		return (2);
	}
	*new_to_complete = ft_strrchr(*to_complete, '/');
	if (*new_to_complete == NULL)
	{
		if (tmp != *to_complete)
			free(tmp);
		return (0);
	}
	else
	{
		(*new_to_complete)++;
		i = ft_strlen(*to_complete) - ft_strlen(*new_to_complete);
		*path = ft_strsub(*to_complete, 0, i);
	}
	n = ft_check_if_is_dir(path, &old_to_complete, new_to_complete, tilda);
	if (tmp != *to_complete)
		free(tmp);
	return (n);
}

void	ft_print_max_completion(t_init *init, char *to_complete, char *max_completion)
{
	int		i;
	char	*completion;
	char	*str;
	char	*path;
	char 	*tilda;

	i = 0;
	completion = NULL;
	str = NULL;
	tilda = NULL;
	if(ft_is_var(to_complete) == 1)
	{
		while (to_complete[i] && to_complete[i] != '$')
			i++;
		str = ft_strsub(to_complete, 0, i + 1);
		completion = ft_strjoin(str, (max_completion));
		ft_strdel(&str);
		ft_strdel(&to_complete);
	}
	else if (ft_if_is_dir_2(&to_complete, &path, &str, &tilda) == 1)
	{
		if (tilda)
			completion = ft_strjoin(tilda, max_completion);
		else
			completion = ft_strjoin(path, max_completion);
		ft_strdel(&path);
		ft_strdel(&tilda);
		ft_strdel(&to_complete);
	}
	else
	{
		completion = ft_strdup(max_completion);
		ft_strdel(&to_complete);
	}
	replace_the_auto_comlete_42(init, completion);
	ft_strdel(&completion);
}

char	*ft_min_completion(t_auto *lst)
{	
	char	*str;
	size_t		min_len;

	str = lst->str;
	min_len = ft_strlen(lst->str);
	while (lst)
	{
		if (ft_strlen(lst->str) < min_len)
		{
			min_len = ft_strlen(lst->str);
			str = lst->str;
		}
		lst = lst->next;
	}
	return (str);
}

int		ft_char_exist(t_auto *lst, int i, char 	*min_completion)
{
	int	n;

	n = 0;
	while(lst)
	{
		if (lst->str[i] != min_completion[i])
			return (0);
		lst = lst->next;
	}
	return (1);
}

char	*ft_max_completion(t_auto *lst)
{
	char	*min_cplt;
	int		i;
	char	*str;

	i = 0;
	min_cplt = ft_min_completion(lst);
	while (min_cplt && min_cplt[i])
	{
		if (ft_char_exist(lst, i, min_cplt))
			i++;
		else
			break;
	}
	if (i)
	{
		str = ft_strsub(min_cplt, 0, i);
		return (str);
	}
	return (NULL);
} 



void	ft_print_completion_posibilities(t_init *init, int lst_len, int max_len)
{
	int			print_len;
	int			tmp_cursor;

	max_len = ft_max_len_lst_42(init->completion_lst, &lst_len);
	print_len = ft_8_42(max_len);  
	tmp_cursor = init->s_cursor;
	ft_ls_print_42(init->completion_lst, print_len, lst_len);
	ft_putchar('\n');
	ft_putstr(init->out_put);
	tmp_cursor = ft_strlen(init->out_put) - tmp_cursor;
	while(tmp_cursor > 0)
	{
		tputs(tgetstr("le", NULL), 0, my_putchar);
		tmp_cursor--;
	}
}

void	ft_print_completion_42(t_init *init)
{
	int			max_len;
	int			lst_len;
	char		*min_completion;
	char		*old_to_complete;
	
	if (init->completion_lst == NULL)
		return ;
	max_len = ft_max_len_lst_42(init->completion_lst, &lst_len);
	if (lst_len == 1)
		ft_print_one_completion(init, init->to_complete);
	else if (lst_len > 1)
	{
		// init->auto_comlpetion = 1;
		min_completion = ft_max_completion(init->completion_lst);
		if (min_completion)
		{
			old_to_complete = ft_take_to_complte_42(init);
			ft_print_max_completion(init, old_to_complete, min_completion);
			ft_strdel(&min_completion);
		}
		ft_print_completion_posibilities(init, lst_len, max_len);
	}
}


void	ft_one_dir_completion( t_init *init,char *path, char *tilda)
{
	char 	*tmp;

	tmp = NULL;
	tmp = init->completion_lst->str;
	if (tilda)
		init->completion_lst->str = ft_strjoin(tilda, init->completion_lst->str);
	else
		init->completion_lst->str = ft_strjoin(path, init->completion_lst->str);
	free(tmp);
}



void	ft_is_direct_path_dir(char *to_complete, t_init *init, char	*path, char *tilda)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = ft_strlen(to_complete);
	if (to_complete[i - 1] != '/')
	{
		tmp = ft_strjoin(to_complete, "/");
		init->completion_lst = add_to_auto_42(init->completion_lst, tmp);
		ft_strdel(&tmp);
	}
	else
	{
		init->completion_lst = ft_search_complete_dir_42("", path);
			if (!(init->completion_lst))
				return;
		ft_max_len_lst_42(init->completion_lst, &i);
		if (i == 1)
		{
			dprintf(open("/dev/ttys003",O_WRONLY|O_RDONLY),"\nkikatani \n");
			ft_one_dir_completion(init, path, tilda);
		}
	}
	
}

void	ft_get_completion_dir_42(t_init *init)
{
	char	*path;
	char	*new_completion;
	int		n;
	int		i;
	char 	*tilda;

	path = NULL;
	new_completion = NULL;
	tilda = NULL;
	i = 0;
	n = ft_if_is_dir(init->to_complete,&path, &new_completion, &tilda);
	if (n == 2)
		ft_is_direct_path_dir(init->to_complete, init, path, tilda);
	else if (n == 1)
	{
		init->completion_lst = ft_search_complete_dir_42(new_completion, path);
		ft_max_len_lst_42(init->completion_lst, &i);
		if (i == 1)
			ft_one_dir_completion(init, path, tilda);
	}
	else
		init->completion_lst = NULL;
	ft_strdel(&tilda);
	ft_strdel(&path);
}

void	ft_get_completion_42(t_init *init, char from)
{
	if (from == 'C')
	{
		init->completion_lst = ft_get_completion_path_42(init);
		init->completion_lst = ft_get_completion_built_42(init, &(init->completion_lst));
	}
	else if (from == 'V')
		init->completion_lst = ft_get_completion_env_var_42(init);
	else if (from == 'D')
		ft_get_completion_dir_42(init);
}


void	ft_get_completion_as_cmd(t_init *init)
{
	ft_get_completion_42(init, 'D');
	if (init->completion_lst == NULL)
	{
		ft_get_completion_42(init, 'V'); 
		if (init->completion_lst == NULL)
			if (init->to_complete != NULL)
				ft_get_completion_42(init, 'C');
	}
}

void	ft_get_completion_from_x(t_init *init, char *line)
{
	char	*tmp;
	int		ret;

	//tmp = to_complete;
	ret = ft_is_first_word_42(line, init);
	if (ret != 1)
	{
		if (ret == 2)
		{
			tmp = init->to_complete;
			init->to_complete = ft_strtrim(init->to_complete);
			ft_strdel(&tmp);
		}
		ft_get_completion_as_cmd(init);
		//dprintf(open("/dev/ttys003",O_WRONLY|O_RDONLY),"\ni am the fucking first word   tototo = --%s---\n", to_complete);
	}
	else
	{
		//dprintf(open("/dev/ttys003",O_WRONLY|O_RDONLY),"\nlast  word   tototo = ---%s--- \n", to_complete);
		ft_get_completion_42(init, 'D');
		if (init->completion_lst == NULL)
		{
			ft_get_completion_42(init, 'V');
			if (init->completion_lst == NULL)
			{
				init->completion_lst = ft_search_complete_dir_42(init->to_complete, ".");
				if (init->completion_lst == NULL)
					return ;
			}
		}
	}
}

void	ft_autocomplete_42(t_init *init)
{
	char	*line;

	init->completion_lst = NULL;
	int len = ft_strlen(init->promt);
	line = &(init->out_put[len]);
	init->to_complete = ft_take_to_complte_42(init);
	ft_get_completion_from_x(init, line);
	ft_print_completion_42(init);
	ft_strdel(&init->to_complete);
	ft_free_auto_lst(&(init->completion_lst));
	init->completion_lst = NULL;
}

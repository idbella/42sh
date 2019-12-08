/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autocomplete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:31:52 by oherba            #+#    #+#             */
/*   Updated: 2019/12/08 19:57:18 by oherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


void	ft_next_completion(t_init *init)
{
	if (init->auto_comlpetion == 1)
	{
		//dprintf(open("/dev/ttys003",O_WRONLY|O_RDONLY),"\ni am the next completion\n");
		init++;
		init--;
	}
}

void	ft_prev_completion(t_init *init)
{
	if (init->auto_comlpetion == 1)
	{
		//dprintf(open("/dev/ttys003",O_WRONLY|O_RDONLY),"\ni am the prev completion\n");
		init++;
		init--;
	}
}

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

int		ft_is_first_word_42(char *line)
{
	int		i;

	i = 0;
	while(line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			return(1);
		i++;
	}
	return(0);
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
	if (init->s_cursor > 5)
	{
		init->s_cursor--;
		tputs(tgetstr("le", NULL), 0, my_putchar);
	}
}

void	ft_string_cmd(int flg, t_init *init)
{
	if (flg == 1)
	{
		if (init->out_put[init->s_cursor] == ' ')
			ft_move_cursor_left(init);
		while (init->s_cursor > 5 && init->out_put[init->s_cursor] != ' ')
			ft_move_cursor_left(init);
	}
	else if (flg == 4)
	{
		if (init->out_put[init->s_cursor] == ' ')
			ft_move_cursor_right(init);
		while (init->s_cursor < init->s_l &&
				init->out_put[init->s_cursor] != ' ')
			ft_move_cursor_right(init);
	}
}

char	*ft_take_to_complte_42(t_init *init)
{
	char	*str;
	int		start;
	int		end;

	str = NULL;
	ft_string_cmd(1, init);
	start = init->s_cursor;
	ft_string_cmd(4, init);
	end = init->s_cursor;
	if (start != 5)
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
	if ((path = ft_getenv("PATH")))
	{
		////////
	}
	else
		return (NULL);
	array = ft_strsplit(path, ':');
	return (array);
}

t_auto	*ft_get_completion_path_42(char *to_complete)
{
	t_auto			*lst;
	char 			**str;
	DIR				*dir;
	struct dirent	*drt;
	int				len;

	lst = NULL;
	str = ft_catpath();
	if (str == NULL)
		return(NULL);
	while (*str)
	{
		if (!(dir = opendir(*str)))
			return (NULL);
		while ((drt = readdir(dir)))
		{
			len = ft_strlen(to_complete);
			if (ft_strncmp(drt->d_name, to_complete, len) == 0)
				lst = add_to_auto_42(lst, drt->d_name);
		}	
		str++;
	}
	return(lst);
}

t_auto	*ft_get_completion_built_42(char *to_complete, t_auto **lst)
{
	int		len;
	int		i;
	char 	**alias;

	i = 0;
	len = ft_strlen(to_complete);
	while (i < BUILTINS_COUNT)
	{
		if (ft_strncmp(get_shell_cfg(0)->builtins[i].key, to_complete, len) == 0)
			*lst = add_to_auto_42(*lst, get_shell_cfg(0)->builtins[i].key);
		i++;
	}
	alias = ft_getaliaskeys();
	i = 0;
	while (alias && alias[i])
	{
		if (ft_strncmp(alias[i], to_complete, len) == 0)
			*lst = add_to_auto_42(*lst, alias[i]);
		i++;
	}
	return(*lst);
}

int		ft_is_var(char *to_complete)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (to_complete[i])
	{
		if (to_complete[i] == '$')
			n++;
		i++;
	}
	return (n);
}

t_auto	*ft_get_completion_env_var_42(char *to_complete)
{
	t_auto	*lst;
	char	**env;
	int		len;
	int		i;
	int		n;

	n = ft_is_var(to_complete);
	i = 0;
	lst = NULL;
	if (n == 1)
	{
		env = ft_serialize_env(INCLUDE_UNEXPORTED | KEYS_ONLY);
		while (to_complete[i] && to_complete[i] != '$')
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
	a = info.ws_col / print_len;
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

	j = 0;
	i = init->s_cursor - 1;
	while ((i > 5  && init->out_put[i] != ' ' ))
		i--;
	if (i != 5)
		i += 1;
	if (init->s_cursor > 5)
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
		dprintf(open("/dev/ttys003",O_WRONLY|O_RDONLY),"\n+++...---%s---+...++\n",to_complete);
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
	if (ft_is_var(to_complete) == 1)
		{
			while (to_complete[i] && to_complete[i] != '$')
				i++;
			str = ft_strsub(to_complete, 0, i + 1);
			completion = ft_strjoin(str, (init->completion_lst->str));
			ft_strdel(&str);
			replace_the_auto_comlete_42(init, completion);
			
		}
		else
			completion = ft_strdup(init->completion_lst->str);
		replace_the_auto_comlete_42(init, completion);
		ft_strdel(&completion);
}

void	ft_print_completion_42(t_init *init, char *to_complete)
{
	int			max_len;
	int			lst_len;
	int			print_len;
	
	init->completion_lst_position = init->completion_lst;
	if (init->completion_lst == NULL)
		return ;
	max_len = ft_max_len_lst_42(init->completion_lst, &lst_len);
	if (lst_len == 1)
		ft_print_one_completion(init, to_complete);
	else if (lst_len > 1)
	{
		init->auto_comlpetion = 1;
		print_len = ft_8_42(max_len);
		///tputs(tgetstr("sc", NULL), 0, my_putchar);
		ft_ls_print_42(init->completion_lst, print_len, lst_len);
		///tputs(tgetstr("rc", NULL), 0, my_putchar);
		ft_putchar('\n');
		ft_putstr(init->out_put);
	}

}

int		ft_is_dir(char *to_complete, char **path, char **new_to_complete)
{
	struct stat st;
	int		i;
	char	*tmp_to_free_new_tocmplt;

	i = 0;
	stat(to_complete, &st);
	if (S_ISDIR(st.st_mode))
		return(2);
	*new_to_complete = ft_strrchr(to_complete, '/');
	if (*new_to_complete == NULL)
		return (0);
	else
	{
		tmp_to_free_new_tocmplt = to_complete;
		(*new_to_complete)++;
		i = ft_strlen(to_complete) - ft_strlen(*new_to_complete);
		dprintf(open("/dev/ttys003",O_WRONLY|O_RDONLY),"\nnewtocm : ---%s---\n", *new_to_complete);
		*path = ft_strsub(to_complete, 0, i);
		dprintf(open("/dev/ttys003",O_WRONLY|O_RDONLY),"\npath : ---%s---\n", *path);
		ft_strdel(&tmp_to_free_new_tocmplt);
	}
	stat(*path, &st);
	if (S_ISDIR(st.st_mode))
		return(1);
	return (0);
}




void	ft_get_completion_dir_42(char *to_complete, t_init *init)
{
	char	*path;
	char	*new_completion;
	int		n;
	int		lst_len;
	char 	*tmp;

	n = 0;
	lst_len = 0;
	path = NULL;
	new_completion = NULL;
	tmp = NULL;
	n = ft_is_dir(to_complete,&path, &new_completion);
	if (n == 2)
	{
		dprintf(open("/dev/ttys003",O_WRONLY|O_RDONLY),"\npath : ---is dir should be compa---\n");
		init->completion_lst = ft_search_complete_dir_42("", to_complete);
		ft_print_completion_42(init, to_complete);
	}
	else if (n == 1)
	{
		init->completion_lst = ft_search_complete_dir_42(new_completion, path);
		ft_max_len_lst_42(init->completion_lst, &lst_len);
		if (lst_len == 1)
		{
			tmp = init->completion_lst->str;
			init->completion_lst->str = ft_strjoin(path, init->completion_lst->str);
			free(tmp);
		}
		ft_print_completion_42(init, to_complete);
	}
}

void	ft_get_completion_42(char *to_complete, t_init *init, char from)
{
	if (from == 'C')
	{
		init->completion_lst = ft_get_completion_path_42(to_complete);
		init->completion_lst = ft_get_completion_built_42(to_complete, &(init->completion_lst));
	}
	else if (from == 'V')
		init->completion_lst = ft_get_completion_env_var_42(to_complete);
	else if (from == 'D')
		ft_get_completion_dir_42(to_complete, init);
}

void	ft_autocomplete_42(t_init *init)
{
	char	*to_complete;
	char	*s;
	char 	*tmp;

	to_complete = NULL;
	tmp = NULL;
	s = &(init->out_put[5]);
	while (ft_isspace(*s))
		s++;
	if (init->completion_lst != NULL)
	{
		ft_free_auto_lst(&(init->completion_lst));
		init->completion_lst = NULL;
	}
	to_complete = ft_take_to_complte_42(init);
	if (ft_is_first_word_42(s) == 0)
	{
		ft_get_completion_42(to_complete, init, 'D');
		if (init->completion_lst == NULL)
		{
			ft_get_completion_42(to_complete, init, 'V'); 
			if (init->completion_lst == NULL)
				if (to_complete != NULL)
					ft_get_completion_42(to_complete, init, 'C');
			ft_print_completion_42(init, to_complete);
		}
	}
	else
	{
		ft_get_completion_42(to_complete, init, 'D');
		if (init->completion_lst == NULL)
		{
			ft_get_completion_42(to_complete, init, 'V');
			if (init->completion_lst == NULL)
			{
				init->completion_lst = ft_search_complete_dir_42(to_complete, ".");
				if (init->completion_lst == NULL)
					return ;
			}
			ft_print_completion_42(init, to_complete);
		}
	}
	ft_free_auto_lst(&(init->completion_lst));
	init->completion_lst = NULL;
}

//did the autocomplete output is sorted
////the initialisation of the init->auto_completion in the read_line
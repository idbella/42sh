/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:55:42 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/10 21:56:52 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char *get_last_arg(t_init *init, char *str)
{
    t_history *tmp;

    tmp = init->last_history;
    if (ft_strcmp(str, "!") == 0)
    { 
        return (ft_strdup(tmp->str));
    }
    while (tmp)
    {
        if (ft_strncmp(tmp->str, str, ft_strlen(str)) == 0)
            return (ft_strdup(tmp->str));
        tmp = tmp->prvet;
    }
    return (NULL);
}
static char *get_first_arg(t_init *init, char *str)
{
    t_history *tmp;

    tmp = init->history;
    while (tmp)
    {
        if (ft_strncmp(tmp->str, str + 1, ft_strlen(str + 1)) == 0)
            return (ft_strdup(tmp->str));
        tmp = tmp->next;
    }
    return (NULL);
}
static char *get_history_index(t_init *init, int i)
{
    t_history *tmp;

    tmp = init->last_history;
    while (tmp)
    {
        if (i == 1)
            return (ft_strdup(tmp->str));
        tmp = tmp->prvet;
        i--;
    }
    return (NULL);
}
static char *get_index(t_init *init, int i)
{
    t_history *tmp;

    tmp = init->last_history;
    while (tmp)
    {
        if (tmp->index == i)
            return (ft_strdup(tmp->str));
        tmp = tmp->prvet;
    }
    return (NULL);
}

static int get_(char *str)
{
    int a;
    int i;

    i = 0;
    if (str[i] == '-')
        i++;
    if (str[i] == '!')
        return (1);
    a = ft_isdigit(str[i]);
    while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
    {
        if (a == 1 && ft_isdigit(str[i]) == 0)
            return (i);
        if (a == 0 && ft_isdigit(str[i]) == 1)
            return (i);
        i++;
    }
    return (i);
}

static char *ft_get_data(t_init *init, char *str)
{
    char *t;

    t  = NULL;
    if (str[0] == '-' && ft_isdigit(str[1]))
    {
        t = get_history_index(init, ft_atoi(&str[1]));
        return (t);
    }
     else if (str[0] == '-' && !ft_isdigit(str[1]))
    {

        t = get_first_arg(init, str);ft_putendl(t);
        return (t);
    }
    else if (ft_isdigit(str[0]))
    {//get_first_arg(t_init *init, char *str)
        t = get_index(init, ft_atoi(&str[0]));
        return (t);
    }
    else
        t = get_last_arg(init, str);
    return (t);
}

static char *ft_join__(char *str, char *new, int index, int j)
{
    char *tmp = NULL;
    char *line = NULL;
    char *tmp_2 = NULL;

    tmp = ft_strdup(&str[j]);
    
    line = ft_strsub(str, 0, index);
    tmp_2 = ft_strjoin(line, new);
     ft_strdel(&new);
    ft_strdel(&line);
    line = ft_strjoin(tmp_2, tmp);
    ft_strdel(&tmp_2);
    ft_strdel(&tmp);
    return (line);
}

char *ft_expansion(t_init *init, char *str)
{
    char *tmp = NULL;
    char *new = NULL;
    char *tmp_2 = NULL;
    int i;
    int j;

    i = 0;
    while (str[i])
    {
        if (str[i] == '!' && str[i + 1])
        {
            j = get_(&str[i + 1]);
            tmp = ft_strsub(str, i + 1, j);
            if (!(new = ft_get_data(init, tmp)))
            {
                ft_strdel(&tmp);
                return (NULL);
            }
          
            tmp_2 = str;
            str = ft_join__(str, new, i, i+ j + 1);
            ft_strdel(&tmp_2);
            ft_strdel(&tmp);
        }
        else if (str[i] == '!' && str[i + 1] == '\0')
            return (NULL);
        i++;
    }
    return (str);
}
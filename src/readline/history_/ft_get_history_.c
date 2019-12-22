/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_history_.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 08:16:33 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/21 19:18:23 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_write_file(t_init *init)
{
    int fd;
    char c;

    c = -3;
    char *name;

    name = ft_join("/Users/%s/.history",ft_getusername());
    if (0 > (fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0777)))
    {
        free(name);
        return;
    }
    free(name);
    if ((init->last_history)->str && ft_strcmp((init->last_history)->str, ""))
    {
        ft_printf_fd(fd, "%f", ft_itoa(init->index, 10));
        write(fd, &c, 1);
        write(fd, (init->last_history)->str, ft_promptlen((init->last_history)->str));
        c = -1;
        write(fd, &c, 1);
    }
    close(fd);
}

void ft_new_history_(t_init *init, char *line)
{
    t_history *new;

    new = NULL;
    init->index++;
    if (!(new = (t_history *)malloc(sizeof(t_history))))
        return;
    if (ft_strchr(line, -3))
    {
        new->str = ft_strdup(ft_strchr(line, -3) + 1);
        new->index = ft_atoi(line);
    }
    else
    {
        new->str = ft_strdup(line);
        new->index = init->index;
    }
    new->next = NULL;
    new->prvet = NULL;
    if (!init->history)
    {
        init->last_history = new;
        init->history = new;
        return;
    }
    new->prvet = init->last_history;
    (init->last_history)->next = new;
    init->last_history = new;
 if (init->history_postoin)
   init->history_postoin = new;
}


static void ft_del_history(t_init *init)
{
    t_history *tmp;

    if (!(init->last_history))
        return;
    tmp = init->last_history->next;
    if (tmp)
    {
        ft_strdel(&tmp->str);
        ft_memdel((void **)&tmp);
    }
    init->last_history->next = NULL;
    init->history_postoin = NULL;
}
static void ft_update_history(t_init *init, char *line)
{
    t_history *new;

    new = NULL;
    if (!(init->last_history))
        return;
    if (!(new = (t_history *)malloc(sizeof(t_history))))
        return;
    ft_del_history(init);
    new->next = NULL;
    new->prvet = init->last_history;
    new->str = ft_strdup(line);//ft_putendl(" dhdhjd");
    init->last_history->next = new;
}
void ft_add_history_(t_init *init, char *line, int i)
{
    if (i)
    {
        if (ft_strcmp(line, ""))
        {
            ft_del_history(init);
            ft_new_history_(init, line);
            //init->history_postoin = init->last_history;
            ft_write_file(init);
        }
    }
    else
        ft_update_history(init, line);
}
void ft_read_file_(t_init *init)
{
    int fd;
    char *line;
    char *name;

    line = NULL;
    // if (0 > (fd = open("/Users/yelazrak/.history", O_RDWR)))
    //     return;
        name = ft_join("/Users/%s/.history",ft_getusername());
    if (0 > (fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0777)))
    {
        free(name);
        return;
    }
    free(name);
    while (get_next_line(fd, -1, &line))
    {

        ft_new_history_(init, line);
        ft_strdel(&line);
    }
    close(fd);
}
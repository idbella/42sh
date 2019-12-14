#include "shell.h"

static int ft_printerror()
{
    ft_printf("42sh : fc: history specification out of range\n");
    return (-1);
}

static int get_index_nm(char *key)
{
    t_history *tmp;

    tmp = get_shell_cfg(0)->init->last_history;
    while (tmp)
    {
        if (ft_strncmp(tmp->str, key, ft_strlen(key)) == 0)
            return (tmp->index);
        tmp = tmp->prvet;
    }
    return (-1);
}
int get_start_end(int *s, int *e, char **args)
{
    int a;

    if (args[0] && ft_isdigit(args[0][0]))
        *s = ft_atoi(args[0]);
    else if (args[0])
        *s = get_index_nm(args[0]);
    else
    {
        if (get_shell_cfg(0)->init->last_history->index > 16)
            *s = get_shell_cfg(0)->init->last_history->index - 15;
        else
            *s = get_shell_cfg(0)->init->history->index;
    }
    if (*s < 0)
        return (ft_printerror());
    if (args[0] && args[1] && ft_isdigit(args[1][0]))
        *e = ft_atoi(args[1]);
    else if (args[0] && args[1])
        *e = get_index_nm(args[1]);
    else
        *e = get_shell_cfg(0)->init->last_history->index;
    if (*e < 0)
        return (ft_printerror());
    if (*s > *e)
    {
        a = *s;
        *s = *e;
        *e = a;
    }
    return (0);
}

static int ft_print_r(char *options, char **args, int fd)
{
    t_history *lst;
    int s;
    int e;

    lst = get_shell_cfg(0)->init->last_history;
    if (get_start_end(&s, &e, args) < 0)
        return (1);
    while (lst)
    {
        if (lst->index == e)
            break;
        lst = lst->prvet;
    }
    while (lst && lst->next)
    {
        if (options['e'])
            ft_putendl_fd(lst->str, fd);
        else if (!options['n'])
            ft_printf("%d\t%s\n", lst->index, lst->str);
        else
            ft_printf("\t%s\n", lst->str);
        if (lst->index == s)
            return (0);
        lst = lst->prvet;
    }
    return 0;
}
int ft_print___(char *options, char **args, int fd)
{
    t_history *lst;
    int s;
    int e;
    if (options['r'])
        return (ft_print_r(options, args, fd));
    lst = get_shell_cfg(0)->init->last_history;
    if (get_start_end(&s, &e, args) < 0)
        return (1);

    while (lst)
    {
        if (lst->index == s)
            break;
        lst = lst->prvet;
    }
    while (lst && lst->next)
    {
        if (options['e'])
            ft_putendl_fd(lst->str, fd);
        else if (!options['n'])
            ft_printf("%d\t%s\n", lst->index, lst->str);
        else
            ft_printf("\t%s\n", lst->str);
        if (lst->index == e)
            return (0);
        lst = lst->next;
    }
    return (0);
}

static char *get_index(int i)
{
    t_history *tmp;

    tmp = get_shell_cfg(0)->init->last_history;
    while (tmp)
    {
        if (tmp->index == i)
            return (ft_strdup(tmp->str));
        tmp = tmp->prvet;
    }
    return (NULL);
}

char *get_arg(char *key)
{
    t_history *lst;

    lst = get_shell_cfg(0)->init->last_history;
    if (key == NULL)
        return (ft_strdup(lst->str));
    if (ft_isdigit(key[0]))
        return (get_index(ft_atoi(key)));
    while (lst)
    {
        if (ft_strncmp(lst->str, key, ft_strlen(key)) == 0)
            return (ft_strdup(lst->str));
        lst = lst->prvet;
    }
    ft_printerror();
    return (NULL);
}

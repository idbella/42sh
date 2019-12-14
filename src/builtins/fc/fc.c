#include "shell.h"

int ft_getopt(char **args, char *buffer, char *valid)
{
    int i0;
    int i1;
    int found;
    int option;
    found = 0;
    i0 = -1;
    ft_bzero(buffer, 127);
    while (args[++i0])
    {
        if (ft_strequ(args[i0], "--"))
            return (i0 + 1);
        if (args[i0][0] == '-')
        {
            i1 = 0;
            while (args[i0][++i1])
            {
                ;
                if (!ft_strchr(valid, args[i0][i1]))
                    return (-args[i0][i1]);
                if ((option = (int)args[i0][i1]) > 0)
                    buffer[option] = 1;
                found = 1;
            }
        }
        else
            return (i0);
    }
    return (i0);
}

int ft_printusage(int c)
{
    if (c)
        ft_printf("42sh: fc: -%c: invalid option\n", -c);
    ft_printf("usage :\n\
    fc [-r] [-e editor] [first [last]]\n\
    fc -l [-nr] [first [last]]\n\
    fc -s [old=new] [first]\n");
    return (1);
}
char *get_name_randm()
{
    struct timeval tv;
    char *name;
    char *tmp;

    gettimeofday(&tv, NULL);
    name = ft_itoa(tv.tv_sec, 10);
    tmp = ft_strjoin("/tmp/", name);
    ft_strdel(&name);
    return (tmp);
}

int read_file_(char *fille)
{
    int fd;
    char *line;
    t_job *tokens;

    line = NULL;
    if ((fd = open(fille, O_RDONLY)) < 0)
        return (1);
    while (get_next_line(fd, '\n', &line))
    {
        if ((tokens = parse(line)))
            exec(tokens);
        ft_strdel(&line);
    }
    close(fd);
    return (0);
}
int ft_creat_cmd(char *edit, char *options, char **args)
{
    int fd;
    char *fille;
    char *cmd;
    t_job *tokens;

    fille = get_name_randm();
    if ((fd = open(fille, O_WRONLY | O_RDONLY | O_CREAT | O_TRUNC, 0777)) < 0)
        return (1);
    if (args[0] && args[1])
        ft_print___(options, args, fd);
    else
    {
        if (get_arg(args[0]))
            ft_putendl_fd(get_arg(args[0]), fd);
        else
        {
            close(fd);
            return (1);
        }
    }
    cmd = ft_join("%s%s%s", edit, "  ", fille);
    if ((tokens = parse(cmd)))
        exec(tokens);
    close(fd);
    read_file_(fille);
    return 0;
}

static int ft_exec_(char *options, char **args)
{
    char *cmd;
    char *edit;
    int i;
    t_job *tokens;

    cmd = NULL;
    i = 0;
    if (options['e'])
    {
        if (args[i])
            edit = ft_strdup(args[i]);
        else
            return (ft_printusage(0));
        i++;
    }
    if (options['s'] || (!options['e'] && !options['l']))
    {
        if (args[i])
            cmd = ft_rep_lace(args[i], args[1] != NULL ? args[i + 1] : NULL);
        else
            cmd = get_arg(args[i]);
        if ((tokens = parse(cmd)))
        {
            exec(tokens);
            ft_free_job(tokens);
        }
        ft_strdel(&cmd);
    }
    else if (!options['e'] && options['l'])
        return (ft_print___(options, args + i, 1));
    else if (options['e'])
        return (ft_creat_cmd(edit, options, args + i));
    return (0);
}

int ft_fc(char **args)
{
    char options[127];
    int index;
    if ((index = ft_getopt(args, options, "relns")) < 0)
        return (ft_printusage(index));
    return (ft_exec_(options, args + index));
}
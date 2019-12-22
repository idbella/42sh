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
        ft_add_history_(get_shell_cfg(0)->init, line, 1);
        if ((tokens = parse(line)))
        {
            exec(tokens);
            ft_free_job(tokens);
        }
        ft_strdel(&line);
    }
    close(fd);
    return (0);
}
int ft_open_(char **str, char *options, char **args)
{
     int fd;
    char *fille;
     char *cmd;

     cmd = NULL; 
     (*str) = get_name_randm();
     fille = (*str);
    if ((fd = open(fille, O_WRONLY | O_RDONLY | O_CREAT | O_TRUNC, 0777)) < 0)
        return (-1);
    if (args[0] && args[1])
        ft_print___(options, args, fd);
    else
    {
        if ((cmd = get_arg(args[0])))
            ft_printf_fd(fd,"%f",cmd); //ft_strdel(&cmd);
        else
        {
            close(fd);
            return (-1);
        }
    }
    return (fd);
}
int ft_creat_cmd(char *edit, char *options, char **args)
{  
    char *cmd;
    char *fille;
    int fd;
    t_job *tokens;

    cmd =NULL;
    if ((fd = ft_open_(&fille, options, args)) < 0)
    return (1);
    if (!edit && (edit = ft_getvlaue_bykey("FCEDIT",INTERN)))
            edit = ft_strdup(edit);
    cmd = ft_join("%s%s%s", edit, "  ", fille);
    ft_strdel(&edit);
    if ((tokens = parse(cmd)))
    {
        exec(tokens);
        ft_free_job(tokens);
    }
    close(fd);
    read_file_(fille);
    ft_strdel(&cmd);
    ft_strdel(&fille);//
    return 0;
}
static void ft__ex(int i,char **args)
{
    char *cmd; 
    t_job *tokens;
    
    cmd = NULL;
     if (args[i])
     {
            cmd = ft_rep_lace(args[i], args[i + 1]);
     }
        else
            cmd = get_arg(args[i]);
        if ((tokens = parse(cmd)))
        {
            exec(tokens);
            ft_free_job(tokens);
        }
        ft_strdel(&cmd);
}
static int ft_exec_(char *options, char **args)
{  
    char *edit;
    int i;
   
    i = 0;
    edit = NULL;
    if (options['e'])
    {
        if (args[i])
            edit = ft_strdup(args[i]);
        else
            return (ft_printusage(0));
        i++;
    }
    if (options['s'] || (!options['e'] && !options['l']))
       ft__ex(i, args);
    else if (options['l'])
        return (ft_print___(options, args + i, 1));
    else if (options['e'])
        return (ft_creat_cmd(edit, options, args + i));
    return (0);
}

int ft_fc(char **args)
{
    char options[127];
    int index;
    ft_bzero(options, 127);
    if ((index = ft_getopt(args, options, "relns")) < 0)
        return (ft_printusage(index));
    return (ft_exec_(options, args + index));
}
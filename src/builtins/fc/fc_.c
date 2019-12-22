#include "shell.h"

static void ft_intstrstr(char *str, char *to_search, int *start, int *end)
{
    int str_index;
    int to_search_index;

    str_index = 0;
    while (str[str_index])
    {
        to_search_index = 0;
        *start = str_index;
        while (to_search[to_search_index] == str[str_index] && to_search[to_search_index] != '\0')
        {
            to_search_index++;
            str_index++;
        }
        if (to_search[to_search_index] == '\0')
        {
            *end = str_index;
            break;
        }
        str_index++;
    }
    if (to_search[to_search_index] && !str[str_index])
        *start = -1;
}
 char *sandr(char *str, char *to_search, char *to_replace)
{
    int start;
    int end;
    char *first_half;
    char *second_half;
    char *result;
    if (!str || !to_search || !to_replace || ft_strlen(str) < ft_strlen(to_search))
        return (NULL);
    ft_intstrstr(str, to_search, &start, &end);
    if (start == -1)
        return (NULL);
    first_half = ft_strsub(str, 0, start);
    second_half = ft_strsub(str, end, ft_strlen(str) - end);
    result = ft_join("%s%s%s", first_half, to_replace, second_half);
    ft_strdel(&second_half);
    ft_strdel(&first_half);
    return (result);
}

 char *ft_rep_lace(char *str, char *dst)
{
    char *t;
    char *s;
    char *split;
    char *tmp;
  
    tmp = NULL;
    t = NULL;
    split = NULL;
    s = NULL;
    if (str == NULL || !ft_strchr(str, '='))
        return (get_arg(str));
    split = ft_strchr(str, '=');
    s = ft_strsub(str, 0, ft_strchr(str, '=') - str); 
    tmp = get_arg(dst);
    if (!(t = sandr(tmp, s, &split[1])))
    {
        //ft_strdel(&tmp);
        ft_strdel(&s);
        return (tmp);
    }ft_putendl(t);
     ft_strdel(&s);
      ft_strdel(&tmp);
      
    return (t);
}

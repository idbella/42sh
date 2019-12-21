/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:38:01 by oherba            #+#    #+#             */
/*   Updated: 2019/12/20 11:24:38 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// void	ft_move_left(t_init *init)
// {
// 	int i;

// 	if (init->s_cursor > (int)ft_strlen(init->promt))
// 	{
// 		i = init->s_cursor;
// 		while (i > (int)ft_strlen(init->promt))
// 		{
// 			i--;
// 			if (init->out_put[i] == ' ' &&
// 					init->out_put[i - 1] != ' ')
// 			{
// 				ft_move(init, "-", init->s_cursor - i);
// 				break ;
// 			}
// 		}
// 	}
// }
void	ft_move_left(t_init *init)
{
	int i;

	if (init->s_cursor > (int)ft_strlen(init->promt))
	{
		i = init->s_cursor;
		while (i > (int)ft_strlen(init->promt))
		{
			i--;
			if ((init->out_put[i] == ' ' || init->out_put[i] == '\t' || init->out_put[i] == '\n') &&
					(init->out_put[i - 1] != ' ' && init->out_put[i - 1] != '\n' && init->out_put[i - 1] != '\t'))
			{
				ft_move(init, "-", init->s_cursor - i);
				break ;
			}
		}
	}
}


void	ft_move_right(t_init *init)
{
	int i;

	if (init->s_cursor < init->s_l)
	{
		i = init->s_cursor;
		if (init->out_put[i] &&
				(init->out_put[i] != ' ' || init->out_put[i] != '\t' || init->out_put[i] != '\n' ) && i < init->s_l)
			i++;
		while (init->out_put[i] &&
				(init->out_put[i] == ' ' ||  init->out_put[i] == '\t' || init->out_put[i] == '\n' ) && i < init->s_l)
			i++;
		while ((init->out_put[i] != ' ' && init->out_put[i] != '\t'  && init->out_put[i] != '\n' ) && i < init->s_l)
			i++;
		ft_move(init, "+", i - init->s_cursor);
	}
}


int		ft_take_move_2(int x, int a, char buffer[5], t_init *init)
{
	if (buffer[0] == 27 && buffer[1] == 91 &&
			buffer[2] == 72 && buffer[3] == '\0')
	{
		home_cursor_2(init);
		return (1);
	}
	else if (buffer[0] == 27 && buffer[1] == 91 &&
			buffer[2] == 70 && buffer[3] == '\0')
	{
		end_cursor_2(init);
		return (1);
	}
	else if ((buffer[0] == 27 && buffer[1] == 27
				&& buffer[2] == 91 && buffer[3] == 66))
	{
		ft_alt_down(&x, &a, init);
		return (1);
	}
	else if (buffer[0] == 27 && buffer[1] == 27 &&
			buffer[2] == 91 && buffer[3] == 68)
	{
		ft_move_left(init);
		return (1);
	}
	return (0);
}

char	*ft_take_move(t_init *init, char *buffer, int position)
{
	int x;
	int x1;
	int a;
	char	*line;

	a = 0;
	x = 0;
	line = NULL;
	if (ft_take_move_2(x, a, buffer, init) == 1)
		x1 = 0;
	else if (buffer[0] == 27 && buffer[1] == 91 &&
				buffer[2] == 53 && buffer[3] == 126)
		ft_next_completion(init);
	else if (buffer[0] == 27 && buffer[1] == 91 &&
				buffer[2] == 54 && buffer[3] == 126)
		ft_prev_completion(init);
	else if ((buffer[0] == 27 && buffer[1] == 27 &&
				buffer[2] == 91 && buffer[3] == 65))
		ft_alt_up(&x, &x1, &a, init);
	else if (buffer[0] == 27 && buffer[1] == 27 &&
			buffer[2] == 91 && buffer[3] == 67)
		ft_move_right(init);
	else if (buffer[0] == 4 && buffer[1] == '\0' &&
			init->out_put[5] == '\0' && init->heredoc_int != 1)
		exit(1);
	else
	{
		////dprintf(open("/dev/ttys016",O_RDWR),"\n5str = %s\n", buffer);	
		if ((line = ft_read(buffer, position, init)))
			return (line);
	}
	return (NULL);
}


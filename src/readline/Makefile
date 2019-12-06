# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 16:55:55 by sid-bell          #+#    #+#              #
#    Updated: 2019/12/05 16:06:24 by yelazrak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libreadline.a

OBJ= srcs/ft_put.o                 termcap/ft_herdoc_exec.o\
srcs/ft_read_cmd.o\
srcs/ft_select_copy_paste.o   termcap/ft_mul_line.o\
srcs/ft_select_copy_paste_2.o termcap/ft_qout.o\
srcs/moves_2.o                termcap/ft_treat_line.o\
srcs/moves_3.o                termcap/move_cursor_of_line.o\
srcs/read_line_.o             termcap/print_line.o\
termcap/cursor_moves.o        termcap/take_line.o\
history_/ft_get_history_.o 	   history_/search_.o

CFLAGS=-g -Wall -Wextra -Werror -I../includes

all:$(NAME)

$(NAME):$(OBJ)
	@echo "\tCompiling $(NAME)"
	ar rc $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME) $(OBJ)

re:fclean all
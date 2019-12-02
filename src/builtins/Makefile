# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 16:55:55 by sid-bell          #+#    #+#              #
#    Updated: 2019/12/02 08:48:54 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libbuiltins.a

OBJ=ft_type.o ft_is_builtin.o\
exit/ft_exit.o\
builtins.o\
hashmap/ft_addtomap.o\
hashmap/ft_empty.o\
hashmap/ft_get_hash.o\
hashmap/ft_getbykey.o\
hashmap/ft_hash.o\
hashmap/ft_init_map.o\
hashmap/ft_mapdelete_one.o\
hashmap/ft_print_hashmap.o\
env/ft_getenv.o\
env/ft_export.o\
env/ft_set.o\
interns/ft_getinters.o\
interns/ft_isintern.o\
interns/ft_cpyenv.o
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

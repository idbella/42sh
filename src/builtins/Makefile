# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 16:55:55 by sid-bell          #+#    #+#              #
#    Updated: 2019/12/06 20:31:29 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libbuiltins.a

OBJ=type/ft_type.o\
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
interns/ft_cpyenv.o\
cd/ft_cd.o\
echo/ft_echo.o\
alias/ft_alias.o         alias/ft_free_aliases.o   alias/ft_showaliases.o  alias/ft_unalias.o\
test/ft_eval.o          test/ft_numbertest.o    test/ft_test.o\
test/ft_rd_wr_ex.o      test/ft_usergroup.o\
test/ft_getoperators.o  test/ft_sizetest.o\
test/ft_isnbr.o         test/ft_strtest.o\
fc/ft_fc.o fc/ft_editor.o
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

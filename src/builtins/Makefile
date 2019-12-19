# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 16:55:55 by sid-bell          #+#    #+#              #
#    Updated: 2019/12/19 16:07:46 by mmostafa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libbuiltins.a

OBJ=ft_getopt.o prompt.o type/ft_type.o\
exit/ft_exit.o\
builtins.o\
hashtable/ft_addtomap.o\
hashtable/ft_empty.o\
hashtable/ft_get_hash.o\
hashtable/ft_getbykey.o\
hashtable/ft_hash.o\
hashtable/ft_init_map.o\
hashtable/ft_mapdelete_one.o\
hashtable/ft_printtable.o\
interns/ft_getinters.o\
interns/ft_isintern.o\
env/ft_getenv.o\
env/ft_export.o\
env/ft_set.o\
cd/ft_cd.o\
cd/chdir_and_path_handling.o\
cd/cd_tools.o\
cd/cd_wheels.o\
echo/ft_echo.o\
alias/ft_alias.o         alias/ft_free_aliases.o   alias/ft_showaliases.o  alias/ft_unalias.o\
test/ft_eval.o          test/ft_numbertest.o    test/ft_test.o\
test/ft_rd_wr_ex.o      test/ft_usergroup.o\
test/ft_getoperators.o  test/ft_sizetest.o\
test/ft_isnbr.o         test/ft_strtest.o\
fc/fc.o         fc/fc_.o        fc/fc_flg.o
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

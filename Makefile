# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 16:59:12 by sid-bell          #+#    #+#              #
#    Updated: 2019/12/06 18:53:12 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=42sh

FLAGS= -Wextra -Werror -Wall

PARSER=src/parser

READLINE=src/readline

EXEC=src/exec

FT=src/libft

BUILTINS=src/builtins

MAIN=src/main.o src/init.o

LIBPARSER= $(PARSER)/libparser.a

LIBREADLINE= $(READLINE)/libreadline.a

LIBBUILTINS= $(BUILTINS)/libbuiltins.a

LIBEXEC= $(EXEC)/libexec.a

LIBFT=$(FT)/libft.a

LIBs= $(LIBEXEC) $(LIBPARSER) $(LIBREADLINE) $(LIBFT) $(LIBBUILTINS)

CFLAGS=-g -Isrc/includes $(FLAGS)

all: $(NAME)

$(NAME): $(MAIN) 
	gcc $(MAIN) $(LIBs) $(FLAGS) -o $(NAME) -Isrc/includes -ltermcap

$(MAIN): $(LIBs)

$(LIBFT):
	@echo "\tCompiling LIB-FT"
	@make -C $(FT)

$(LIBPARSER):
	@echo "\tCompiling LIB-PARSER"
	@make -C $(PARSER)

$(LIBREADLINE):
	@echo "\tCompiling LIB-READLINE"
	@make -C $(READLINE)

$(LIBEXEC):
	@echo "\tCompiling LIB-EXEC"
	@make -C $(EXEC)

$(LIBBUILTINS):
	@echo "\tCompiling LIB-BUILTINS"
	@make -C $(BUILTINS)

clean:
	rm -rf $(MAIN)
	make -C $(FT) clean
	make -C $(PARSER) clean
	make -C $(READLINE) clean
	make -C $(EXEC) clean
	make -C $(BUILTINS) clean

fclean:
	rm -rf $(NAME)
	rm -rf $(MAIN)
	make -C $(FT) fclean
	make -C $(PARSER) fclean
	make -C $(READLINE) fclean
	make -C $(EXEC) fclean
	make -C $(BUILTINS) fclean

.PHONY: $(LIBFT) $(LIBEXEC) $(LIBREADLINE) $(LIBPARSER) $(LIBBUILTINS)

re:fclean all
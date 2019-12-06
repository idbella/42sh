# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 16:55:55 by sid-bell          #+#    #+#              #
#    Updated: 2019/12/06 09:51:47 by yoyassin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libparser.a
SRC = src
BUILD = .build
INC = ../includes
HDRS = ../includes/shell.h ../includes/parser.h
LIB = libft
CC = gcc
FLAGS = -g -Wall -Wextra -Werror
INCLUDE = -I$(INC) -I$(LIB)/includes
# LIBFT = $(LIB)/libft.a
SRC_SUBDIRS = expansions parsing

SRC_PARAM_EXPAN = $(addprefix param-expan/ , params_expan.c rm_mpattern.c params_expan_operaters.c split_param_word.c)
SRC_EXPANSION = $(addprefix expansions/, alias_expansion.c tild_expansion.c escape.c exp_helper_funcs.c exp_helper_funcs2.c expansions.c)
SRC_PARSING = $(addprefix parsing/, build_job_list.c build_parse_list.c parse.c parse_heredoc.c parse_redir.c parse_redir2.c pre_parsing.c special_chars.c syntax_checking.c utility_funcs.c)
SRCS = $(SRC_EXPANSION) $(SRC_PARSING) 
OBJECT = $(addprefix $(BUILD)/, $(SRCS:.c=.o))
OBJ_DIRS = $(addprefix $(BUILD)/, $(SRC_SUBDIRS))

# all:
# 	$(info $$OBJ_DIRS is [${OBJ_DIRS}])

all: $(NAME)

$(NAME): $(OBJECT)
	ar rc $(NAME) $(OBJECT)

$(OBJECT): $(BUILD)/%.o : $(SRC)/%.c $(HDRS) | $(BUILD)
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(BUILD):
	mkdir $(BUILD)
	mkdir $(OBJ_DIRS)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -rf $(NAME)

re : fclean all

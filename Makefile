# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 11:29:27 by llacaze           #+#    #+#              #
#    Updated: 2018/02/05 17:35:26 by llacaze          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang

OPTIONS = -c

CFLAGS = -Wall -Wextra -Werror

RM = rm -Rfv

SRC = 		main.c \
			get_next_line.c \
			init.c\
			builtin.c\
			builtin_env.c\
			bi_echo.c\
			bi_setenv.c\
			bi_unsetenv.c

OBJ = $(SRC:.c=.o)

HEAD_DIR = ./libft/

all: $(NAME)

$(NAME): $(OBJ) Makefile minishell.h
	@$(CC) $(CFLAGS) $(OPTIONS) $(SRC)
	@cd $(HEAD_DIR) && $(MAKE)
	@$(CC) $(OBJ) ./libft/libft.a -o $(NAME)

clean:
	@$(RM) $(OBJ)
	@cd $(HEAD_DIR) && $(MAKE) $@

fclean: clean
	@$(RM) $(OBJ)
	@$(RM) $(NAME)
	@make -C $(HEAD_DIR) fclean

re: fclean all

.PHONY : all clean fclean re

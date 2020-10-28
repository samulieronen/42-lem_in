# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/03 22:23:49 by seronen           #+#    #+#              #
#    Updated: 2020/10/28 16:32:43 by seronen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRCS =	srcs/lem_in.c srcs/input/*.c srcs/pathfinding.c \
		srcs/hash/*.c srcs/flow.c srcs/path.c srcs/super_algo.c \
		srcs/calc.c

FLAGS = -Wall -Wextra -Werror

INCL = -I ./includes/ -I ./libft/includes/

LIB = -L libft -lft

RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): libftmake
	@echo "Compiling executable "lem-in"."
	@gcc -o $(NAME) $(SRCS) $(INCL) $(LIB) -O3
	@echo "$(GREEN)Executable "lem-in" compiled successfully.$(RESET)"

libftmake:
	@make -C libft

lemin:
	@echo "Compiling executable "lem-in"."
	@gcc -o $(NAME) $(SRCS) $(INCL) $(LIB)
	@echo "$(GREEN)Executable "lem-in" compiled successfully.$(RESET)"

clean:
	@make clean -C libft

fclean:
	@make fclean -C libft
	@echo "$(RED)Removing executable "lem-in".$(RESET)"
	@rm -rf $(NAME)

re: fclean all
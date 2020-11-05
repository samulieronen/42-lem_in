# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/03 22:23:49 by seronen           #+#    #+#              #
#    Updated: 2020/11/05 13:03:16 by seronen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRCS =	srcs/lem_in.c srcs/input/input.c srcs/input/lines.c srcs/input/pipes.c srcs/input/rooms.c \
		srcs/input/validate.c srcs/hash/hash.c srcs/hash/hash_utils.c \
		srcs/algo/calc.c srcs/algo/flow.c srcs/algo/flow_utils.c srcs/algo/parent.c \
		srcs/algo/path.c srcs/algo/print.c srcs/algo/print_utils.c srcs/algo/queue.c srcs/algo/sets.c \
		srcs/algo/balance.c

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
	@gcc $(FLAGS) -o $(NAME) $(SRCS) $(INCL) $(LIB)
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
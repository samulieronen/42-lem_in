# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/21 12:12:13 by seronen           #+#    #+#              #
#    Updated: 2020/09/04 03:28:39 by seronen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCLUDES = includes/

SRC = srcs/ft_isprint.c srcs/ft_memalloc.c srcs/ft_putchar.c srcs/ft_strcat.c srcs/ft_striter.c srcs/ft_strncmp.c \
srcs/ft_strsub.c srcs/ft_itoa.c srcs/ft_memccpy.c srcs/ft_putchar_fd.c srcs/ft_strchr.c srcs/ft_striteri.c \
srcs/ft_strncpy.c srcs/ft_strtrim.c srcs/ft_atoi.c srcs/ft_lstadd.c srcs/ft_memchr.c srcs/ft_putendl.c srcs/ft_strclr.c \
srcs/ft_strjoin.c srcs/ft_strnequ.c srcs/ft_tolower.c srcs/ft_bzero.c srcs/ft_lstdel.c srcs/ft_memcmp.c srcs/ft_putendl_fd.c \
srcs/ft_strcmp.c srcs/ft_strlcat.c srcs/ft_strnew.c srcs/ft_toupper.c srcs/ft_isalnum.c srcs/ft_lstdelone.c srcs/ft_memcpy.c \
srcs/ft_putnbr.c srcs/ft_strcpy.c srcs/ft_strlen.c srcs/ft_strnstr.c srcs/ft_isalpha.c srcs/ft_lstiter.c srcs/ft_memdel.c \
srcs/ft_putnbr_fd.c srcs/ft_strdel.c srcs/ft_strmap.c srcs/ft_strrchr.c srcs/ft_isascii.c srcs/ft_lstmap.c srcs/ft_memmove.c \
srcs/ft_putstr.c srcs/ft_strdup.c srcs/ft_strmapi.c srcs/ft_strsplit.c srcs/ft_isdigit.c srcs/ft_lstnew.c srcs/ft_memset.c \
srcs/ft_putstr_fd.c srcs/ft_strequ.c srcs/ft_strncat.c srcs/ft_strstr.c srcs/ft_number_len.c srcs/ft_word_ccount.c \
srcs/ft_word_len_ic.c srcs/get_next_line.c srcs/ft_strndup.c srcs/ft_itoa_base.c srcs/ft_ftoa.c srcs/ft_strrev.c srcs/ft_2dstrdel.c \
srcs/ft_strcdup.c


PRINTFSRC = srcs/ft_printf/helpers.c srcs/ft_printf/helpers2.c srcs/ft_printf/save.c srcs/ft_printf/ft_printf.c srcs/ft_printf/print_char.c \
srcs/ft_printf/print_dec.c srcs/ft_printf/print_float.c srcs/ft_printf/print_hex.c srcs/ft_printf/print_octal.c srcs/ft_printf/print_ptr.c \
srcs/ft_printf/print_str.c srcs/ft_printf/print_unsig.c srcs/ft_printf/print_percentage.c


OBJ = ft_isprint.o ft_memalloc.o ft_putchar.o ft_strcat.o ft_striter.o ft_strncmp.o \
ft_strsub.o ft_itoa.o ft_memccpy.o ft_putchar_fd.o ft_strchr.o ft_striteri.o \
ft_strncpy.o ft_strtrim.o ft_atoi.o ft_lstadd.o ft_memchr.o ft_putendl.o ft_strclr.o \
ft_strjoin.o ft_strnequ.o ft_tolower.o ft_bzero.o ft_lstdel.o ft_memcmp.o ft_putendl_fd.o \
ft_strcmp.o ft_strlcat.o ft_strnew.o ft_toupper.o ft_isalnum.o ft_lstdelone.o ft_memcpy.o \
ft_putnbr.o ft_strcpy.o ft_strlen.o ft_strnstr.o ft_isalpha.o ft_lstiter.o ft_memdel.o \
ft_putnbr_fd.o ft_strdel.o ft_strmap.o ft_strrchr.o ft_isascii.o ft_lstmap.o ft_memmove.o \
ft_putstr.o ft_strdup.o ft_strmapi.o ft_strsplit.o ft_isdigit.o ft_lstnew.o ft_memset.o \
ft_putstr_fd.o ft_strequ.o ft_strncat.o ft_strstr.o ft_number_len.o ft_word_ccount.o \
ft_word_len_ic.o get_next_line.o ft_strndup.o ft_itoa_base.o ft_ftoa.o helpers.o \
helpers2.o save.o ft_printf.o print_char.o print_str.o print_ptr.o print_float.o \
print_hex.o print_unsig.o print_octal.o print_dec.o print_percentage.o ft_strrev.o \
ft_2dstrdel.o ft_strcdup.o

RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

$(NAME):
	@echo "Compiling libft."
	@gcc -c $(SRC) $(PRINTFSRC) -Wall -Wextra -Werror -I $(INCLUDES)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "$(GREEN)libft.a compiled successfully.$(RESET)"

clean:
	@echo "$(RED)Removing all .o files.$(RESET)"
	@/bin/rm -f $(OBJ)

fclean: clean
	@echo "$(RED)Removing libft.a.$(RESET)"
	@/bin/rm -f $(NAME)

re: fclean all

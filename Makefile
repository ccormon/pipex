# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/02 16:38:09 by ccormon           #+#    #+#              #
#    Updated: 2024/03/06 11:23:46 by ccormon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= pipex

CC 			= gcc
RM			= rm -f
CLONE 		= git clone
CFLAGS 		+= -g -Wall -Wextra -Werror
CLINKS		=

FT			= libft
LIBFT		= $(FT)/libft.a

SRC		=	main.c\
			init_pipex.c\
			init_pipex_hd.c\
			exit_pipex.c\

OBJ 		= $(SRC:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(CLINKS)

$(LIBFT):
	$(MAKE) -C $(FT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:		all bonus clear clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/02 16:38:09 by ccormon           #+#    #+#              #
#    Updated: 2024/03/04 19:43:44 by ccormon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= pipex

CC 			= gcc
RM			= rm -f
CLONE 		= git clone
CFLAGS 		+= -Wall -Wextra -Werror
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
	if [ -d "$(FT)" ]; then $(MAKE) clean -C $(FT); fi
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

clear: fclean
	$(RM) -r $(FT)

re: fclean all

.PHONY:		all bonus clear clean fclean re

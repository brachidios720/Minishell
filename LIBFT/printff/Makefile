# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spagliar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 12:59:39 by spagliar          #+#    #+#              #
#    Updated: 2023/05/18 12:59:40 by spagliar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a 

SRC = ft_*.c \

CC = gcc

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	$(CC) -Wall -Wextra -Werror -c $(SRC) 
	ar -rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re : fclean all
.PHONY: all clean fclean re

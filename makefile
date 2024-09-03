# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 18:39:18 by raphaelcarb       #+#    #+#              #
#    Updated: 2024/09/03 18:43:04 by raphaelcarb      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Werror -Wextra -g3
EXE = philo
RM = rm -rf

src = 	src/utils.c \
		src/minishell.c \

srco = $(src:.c=.o)

all: $(EXE)

$(MAKE) -C 

$(EXE): $(srco) $(LINK)
	$(CC) $(CFLAGS) $(srco) -o $(EXE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C clean
	$(RM) $(srco)

fclean: clean
	$(MAKE) -C fclean
	$(RM) $(EXE)

re: fclean all

.PHONY: all clean fclean re libft
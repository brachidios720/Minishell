# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 18:39:18 by raphaelcarb       #+#    #+#              #
#    Updated: 2024/09/11 16:12:01 by raphaelcarb      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Werror -Wextra -g3
LDFLAGS = -lreadline -ltinfo
EXE = Minishell
RM = rm -rf

LIBFT_PATH = ./LIBFT
LIBFT = $(LIBFT_PATH)/libft.a

src = 	src/utils.c \
		src/utils_env.c \
		src/minishell.c \
		src/read_line.c \
		src/builtins/builtins.c \
		src/builtins/pwd.c \
		src/builtins/env.c \
		src/builtins/cd.c \
		src/builtins/echo.c \
		src/builtins/export.c \
		src/builtins/unset.c \
		src/init.c \
		src/init_lst.c\
		src/free.c \
		src/ctrl/ctrl.c \
		src/exec/exec.c \
		src/exec/inout.c \
		src/exec/path.c \
		src/exec/pipe.c \
		src/parsing/utils_parsing.c \
		src/parsing/parsing1.c \
		src/parsing/ft_utils_cmd.c \
		src/parsing/option.c \
		src/parsing/parsing2.c \
		src/redirection/redirection.c \
		src/builtins/utils_builtins.c \


srco = $(src:.c=.o)

all: $(EXE)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(EXE): $(srco) $(LIBFT)
	$(CC) $(CFLAGS) $(src) $(LIBFT) -o $(EXE) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(srco)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(EXE)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re

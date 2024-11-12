# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almarico <almarico@student.42lehavre.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 18:39:18 by raphaelcarb       #+#    #+#              #
#    Updated: 2024/11/09 20:57:45 by almarico         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Werror -Wextra -g3 -gdwarf-4
LDFLAGS = -lreadline -ltinfo
EXE = Minishell
RM = rm -rf

LIBFT_PATH = ./LIBFT
LIBFT = $(LIBFT_PATH)/libft.a

src = 	src/builtins/builtins.c \
		src/builtins/cd.c \
		src/builtins/echo.c \
		src/builtins/env.c \
		src/builtins/export.c \
		src/builtins/pwd.c \
		src/builtins/unset.c \
		src/builtins/utils_builtins.c \
		src/exec/exec.c \
		src/exec/path.c \
		src/init/init_lst.c\
		src/init/init.c\
		src/parsing/ft_utils_cmd.c \
		src/parsing/option.c \
		src/parsing/parsing1.c \
		src/parsing/parsing2.c \
		src/parsing/utils_parsing_line.c \
		src/parsing/utils_parsing.c \
		src/pipe/pipe.c \
		src/redirection/handle_heredoc.c \
		src/redirection/heredoc_file.c \
		src/redirection/read_heredoc.c \
		src/redirection/utils_heredoc.c \
		src/redirection/utils_redir.c \
		src/signals/parse_signal.c \
		src/free.c \
		src/minishell.c \
		src/read_line.c \
		src/utils_env.c \
		src/utils.c \
		src/pipe/utils_pipe.c \


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

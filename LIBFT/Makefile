# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raphaelcarbonnel <raphaelcarbonnel@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 15:22:24 by spagliar          #+#    #+#              #
#    Updated: 2024/09/04 17:48:40 by raphaelcarb      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = libft.a

SRC = ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c

OBJ = $(SRC:.c=.o)

BONUS = ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstsize.c

BONUS_OBJS = $(BONUS:.c=.o)

SRCG = get_next_line/get_next_line_bonus.c \
		get_next_line/get_next_line_utils_bonus.c \
		get_next_line/get_next_line_utils.c \
		get_next_line/get_next_line.c

OBJG = $(SRCG:.c=.o)

SRCP = printf/ft_pprintptr.c \
		printf/ft_printf.c \
		printf/ft_printnbru.c \
		printf/ft_putchar_fd.c \
		printf/ft_putchar.c \
		printf/ft_putdeci.c \
		printf/ft_puthexa.c \
		printf/ft_putstr.c \
		printf/ft_strlen.c 

OBJP = $(SRCP:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJG) $(OBJP)
	ar -rc $(NAME) $(OBJ) $(OBJG) $(OBJP)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ) $(BONUS_OBJS) $(OBJG) $(OBJP)

fclean: clean
	/bin/rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

bonus: $(OBJ) $(BONUS_OBJS) $(OBJG) $(OBJP)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJS) $(OBJG) $(OBJP)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@

.PHONY: all clean fclean re bonus

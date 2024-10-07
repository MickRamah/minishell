# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 16:34:14 by zramahaz          #+#    #+#              #
#    Updated: 2024/09/21 16:46:20 by zramahaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -lreadline #-Wall -Wextra -Werror

SRC_DIR = src/

PARS_DIR = src/parsing/

UTLS_DIR = src/utils/

SRCS = main.c $(PARS_DIR)quote.c $(PARS_DIR)create_token.c $(PARS_DIR)dollar_replace.c $(PARS_DIR)dollar_env.c \
		$(UTLS_DIR)ms_utils.c $(UTLS_DIR)list_token.c $(UTLS_DIR)debug.c \
		$(UTLS_DIR)list_utils.c $(UTLS_DIR)ft_free.c

OBJS = $(SRCS:.c=.o)

RM = rm -f

LIBFT_A = libft/libft.a

all: $(NAME);

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_A)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIBFT_A):
	@make -C libft/ all

clean:
	$(RM) $(OBJS)
	@make -C libft/ clean
	
fclean:	clean
	$(RM) $(NAME)
	@make -C libft/ fclean

re:	fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 16:34:14 by zramahaz          #+#    #+#              #
#    Updated: 2024/10/10 16:10:33 by zramahaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -lreadline -g#-Wall -Wextra -Werror

SRC_DIR = src/

PARS_DIR = src/parsing/

UTLS_DIR = src/utils/

EXEC_DIR = src/exec/

SRCS = main.c $(PARS_DIR)quote.c $(PARS_DIR)create_token.c $(PARS_DIR)dollar_replace.c $(PARS_DIR)dollar_env.c \
		$(UTLS_DIR)ms_utils.c $(UTLS_DIR)list_token.c $(UTLS_DIR)debug.c \
		$(UTLS_DIR)list_utils.c $(UTLS_DIR)ft_free.c $(PARS_DIR)create_cmd.c \
		$(EXEC_DIR)exec.c

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

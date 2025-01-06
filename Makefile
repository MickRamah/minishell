# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 16:34:14 by zramahaz          #+#    #+#              #
#    Updated: 2024/12/23 15:11:14 by herakoto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src/

PARS_DIR = src/parsing/

UTLS_DIR = src/utils/

EXEC_DIR = src/exec/

BUILTINS_DIR = src/builtins/

SIG_DIR = src/signal/

SRCS = main.c $(PARS_DIR)quote.c $(PARS_DIR)create_token.c $(PARS_DIR)dollar_replace.c $(PARS_DIR)dollar_env.c \
		$(PARS_DIR)cmd_fd.c $(PARS_DIR)create_cmd.c $(PARS_DIR)create_cmd_utils.c \
		$(UTLS_DIR)ms_utils.c $(UTLS_DIR)main_utils.c \
		$(UTLS_DIR)list_utils.c $(UTLS_DIR)ft_free.c \
		$(EXEC_DIR)exec.c $(EXEC_DIR)exec_part_2.c $(EXEC_DIR)here_doc.c $(EXEC_DIR)build.c $(EXEC_DIR)exec_utils.c \
		$(BUILTINS_DIR)pwd.c $(BUILTINS_DIR)export.c $(BUILTINS_DIR)cd.c \
		$(BUILTINS_DIR)ft_exit.c $(BUILTINS_DIR)echo.c $(BUILTINS_DIR)env.c \
		$(BUILTINS_DIR)unset.c $(BUILTINS_DIR)utils.c $(SIG_DIR)signals.c \
		$(SIG_DIR)child.c

OBJS = $(SRCS:.c=.o)

RM = rm -f

LIBFT_A = libft/libft.a

all: $(NAME);

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_A) -lreadline

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

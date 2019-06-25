# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlagos <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/21 14:10:04 by jlagos            #+#    #+#              #
#    Updated: 2019/06/21 14:10:06 by jlagos           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fillit
CFLAGS		= -Wall -Werror -Wextra

INCLUDES = $(wildcard *.c)

.PHONY: silent show all clean fclean re

silent:
	@make all -s

debug:
	make all CFLAGS='$(CFLAGS) -g'

all: $(NAME)

$(NAME): $(INCLUDES)	
	$(MAKE) all -C libft_1
	gcc $(CFLAGS) $(INCLUDES) libft_1/libft.a -o $(NAME)

clean:
	-@$(MAKE) clean -C libft_1 -s

fclean: clean
	-@rm -f $(NAME)
	-@rm -f -r $(NAME).dSYM
	-@$(MAKE) fclean -C libft_1 -s

re: fclean all
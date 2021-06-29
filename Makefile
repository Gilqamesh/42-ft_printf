# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edavid <edavid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/25 20:47:25 by edavid            #+#    #+#              #
#    Updated: 2021/06/29 14:10:25 by edavid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
objects = ft_printf.o
NAME = libftprintf.a
libftPath = ./libft/libft.h

$(NAME) : $(objects)
	cd libft && $(MAKE) all
	cp $(libftPath:.h=.a) .
	mv libft.a $(NAME)
	ar -rs $(NAME) $^

ft_printf.o : $(libftPath) ft_printf.h

driver.o : ft_printf.h

.PHONY: all clean fclean re bonus 
all :
re :
	make clean
	make all
bonus :
test : $(objects) driver.o
	cd libft && $(MAKE) all
	cp $(libftPath:.h=.a) .
	mv libft.a $(NAME)
	ar -rs $(NAME) $(objects) driver.o
	$(CC) -o test.out $^ -Llibft -lft
clean :
	rm -f *.o libft/*.o
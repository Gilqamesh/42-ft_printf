# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edavid <edavid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/25 20:47:25 by edavid            #+#    #+#              #
#    Updated: 2021/06/25 20:54:49 by edavid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

$(NAME) : $(objects)
	ar rcs $@ $^

.PHONY: all clean fclean re bonus
all : 
re :
	make clean
	make all
bonus :
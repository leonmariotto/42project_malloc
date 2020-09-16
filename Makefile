# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/07 14:46:10 by lmariott          #+#    #+#              #
#    Updated: 2020/09/15 08:09:04 by lmariott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
    HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME            := libft_malloc_$(HOSTTYPE).so
LIBNAME         := libft_malloc.so

CC              := gcc
FLAGS           := -Wall -Wextra -Werror -fPIC

SRCS_FILES      :=  malloc.c\
					zone.c\
					show_alloc_mem.c\
					free.c\
					realloc.c\
					calloc.c\
					reallocarray.c

HEADERS_FILES   :=  ft_malloc.h

SRCS_PATH       := src/
SRCS            := $(addprefix $(SRCS_PATH), $(SRCS_FILES))

OBJS_PATH       := obj/
OBJS            := $(addprefix $(OBJS_PATH), $(SRCS_FILES:.c=.o))

INCLUDES_PATH   := inc/
INCLUDES        := -I $(INCLUDES_PATH) -I libft
HEADERS         := $(addprefix $(INCLUDES_PATH), $(HEADERS_FILES))

LIBFT := libft/libft.a

all: $(NAME)

$(LIBFT):
	make -j 8 -C libft/

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(HEADERS)
	mkdir $(OBJS_PATH) 2> /dev/null || true
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) -shared $(OBJS) $(LIBFT) -o $(NAME)
	ln -fs $@ $(LIBNAME)

clean:
	rm -fv $(OBJS)
	rmdir $(OBJS_PATH) 2> /dev/null || true

fclean: clean
	rm -fv $(NAME)
	rm -fv $(LIBNAME)

re: fclean all

.PHONY: all clean fclean re

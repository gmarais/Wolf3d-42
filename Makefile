#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/22 12:39:07 by gmarais           #+#    #+#              #
#    Updated: 2015/01/22 19:37:07 by gmarais          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc

NAME = wolf3d

SRC = main.c \
	draw/draw.c \
	draw/skybox.c \
	draw/walls.c \
	draw/floor.c \
	draw/sprite_cast.c \
	draw/sorting_sprites.c \
	draw/print_sprites.c \
	draw/door.c \
	draw/gun.c \
	draw/end.c \
	draw/victory.c \
	draw/mlx_usage.c \
	mech/basic_ia.c \
	mech/damages.c \
	mech/keyhooks.c \
	mech/move.c \
	mech/physics.c \
	mech/teleport.c \
	load/world.c \
	load/textures.c \
	load/parse.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I ./libft/includes -I /usr/X11/include -I./ -O3

LDFLAGS = -L./libft -lft -L/usr/X11/lib -lmlx -lXext -lX11 -L /usr/lib -lm

all: lib $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $@ $(OBJ) $(CFLAGS) $(LDFLAGS)

lib:
	@(cd libft && $(MAKE))

clnlib:
	@(cd libft && $(MAKE) clean)

fclnlib:
	@(cd libft && $(MAKE) fclean)

clean: clnlib
	@/bin/rm -f $(OBJ)

fclean: clean fclnlib
	@/bin/rm -f $(NAME)

re: fclean all

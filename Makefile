# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 15:54:37 by rmarzouk          #+#    #+#              #
#    Updated: 2024/11/16 16:37:29 by mskhairi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -Werror  #-fsanitize=address #-O3
MLX_FALGS=MLX42/build/libmlx42.a MLX42/build/libglfw3.a
LIBS = -framework Cocoa -framework OpenGL -framework IOKit
LIBFT_FLAGS = -L src/libft -lft

NAME = cub3D

PARSING_DIR = parsing/
S_PARSING= $(addprefix $(PARSING_DIR), ft_requirements.c\
									ft_textures.c\
									ft_colors.c\
									ft_map.c\
									ft_map_utils.c\
								)

O_PARSING = $(S_PARSING:.c=.o)

RAYCASTING_DIR = raycasting/
S_RAYCASTING= $(addprefix $(RAYCASTING_DIR), ft_init_mlx.c\
											render_map.c \
											ft_hooks.c \
											projection_3D.c \
											ft_player.c \
											mini_map.c \
								)

O_RAYCASTING = $(S_RAYCASTING:.c=.o)

all: $(NAME)

$(NAME): $(NAME).o $(O_PARSING) $(O_RAYCASTING)
	make -C src/libft
	$(CC) $(CFLAGS) $(MLX_FALGS) $(LIBS) $(LIBFT_FLAGS) $(NAME).o $(O_RAYCASTING) $(O_PARSING) -o $(NAME)

%.o:%.c cube3d.h
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	# make fclean -C src/libft
	rm -f $(NAME).o 
	rm -fr $(O_PARSING) $(O_RAYCASTING)

fclean: clean
	rm -f $(NAME)

re: fclean all

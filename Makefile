# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/20 10:43:19 by vvasiuko          #+#    #+#              #
#    Updated: 2025/04/15 10:19:15 by ykhattab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= miniRT
CC      		= cc
CFLAGS			= -Wall -Werror -Wextra -Ofast -flto -march=native $(HEADERS)
HEADERS			= -I./libft -I./vector -I./fdf_utils -I. -I./mlx -I./gnl -I./src/parsing
LIBFT			= libft/libft.a
LIBFT_FLAGS		= -Llibft
MINILIBX		= mlx/libmlx.a
MLX_FLAGS		= -Lmlx -lmlx -framework OpenGL -framework AppKit
LFLAGS			= $(MLX_FLAGS) $(LIBFT_FLAGS)
FILES			= cleanup error main parse utils key_events key_events_2 \
				vector_ops vector_ops_2 vector_ops_inplace colour \
				parsing/parse_lights parsing/parse_objects parsing/parse_scene parsing/parse_vector_color parsing/parsing_utils parsing/create_objects \
				hit_objects put_pixels sphere cylinder plane \
				change_r_h \
				translate_obj translate_camera translate_light \
				rotate_camera rotate_object
GNL				= gnl/get_next_line
SRC_PATH		= ./src/
OBJ_PATH 		= ./obj/
SRC				= $(patsubst %, $(SRC_PATH)%.c, $(FILES)) $(GNL).c
OBJS			= $(patsubst %, $(OBJ_PATH)%.o, $(FILES)) $(OBJ_PATH)get_next_line.o
RM      		= rm -rf

all: $(OBJ_PATH) $(NAME) 

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)parsing

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -O3 -c $< -o $@

$(OBJ_PATH)get_next_line.o: $(GNL).c
	$(CC) $(CFLAGS) -O3 -c $< -o $@

$(NAME): $(OBJS) $(MINILIBX) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(MINILIBX) $(LIBFT) -o $(NAME)

minilibx: $(MINILIBX)

$(MINILIBX):
	make -C mlx

libft: $(LIBFT)

$(LIBFT):
	make -C libft

clean:
	make clean -C mlx
	make clean -C libft
	rm -rf $(OBJ_PATH)

fclean: clean
	make clean -C mlx
	make fclean -C libft
	rm -rf $(NAME)
	rm -rf $(MINILIBX)

re: fclean all

.PHONY: all clean re fclean minilibx libft

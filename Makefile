NAME			= miniRT
CC      		= cc
CFLAGS			= -Wall -Werror -Wextra $(HEADERS)
HEADERS			= -I./libft -I./vector -I./fdf_utils -I. -I./mlx
LIBFT			= libft/libft.a
LIBFT_FLAGS		= -Llibft
MINILIBX		= mlx/libmlx.a
MLX_FLAGS		= -Lmlx -lmlx -framework OpenGL -framework AppKit
LFLAGS			= $(MLX_FLAGS) $(LIBFT_FLAGS)
FILES			= cleanup error main parse utils vector_ops
SRC_PATH		= ./src/
OBJ_PATH 		= ./obj/
SRC				= $(patsubst %, $(SRC_PATH)%.c, $(FILES))
OBJS			= $(patsubst %, $(OBJ_PATH)%.o, $(FILES))
RM      		= rm -rf

all: $(OBJ_PATH) $(NAME) 

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
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

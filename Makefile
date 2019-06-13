# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/29 16:28:19 by nalexand          #+#    #+#              #
#    Updated: 2019/06/13 06:30:44 by nalexand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIB = fdf.a

LIBFT = libft

CС = gcc -g

SRC_DIR = src/

OBJ_DIR = obj/

HEADER = -I includes

MLX_LIB = -L /usr/local/lib/ -lmlx
MLX_HEAD = -I /usr/local/include
FRAMEWORK = -framework OpenGL -framework AppKit

SRC =	fdf_parce.c \
		fdf_draw_line.c \
		fdf_clear_exit.c \
		fdf_info_handle.c \
		fdf_render.c \
		fdf_key_handle.c \
		fdf_gradient_handle.c \
		fdf_read_file.c \
		fdf_mlx_hooks.c

OBJ = $(patsubst %.c, %.o, $(SRC))

C_PATH = $(addprefix $(SRC_DIR), $(SRC))

O_PATH = $(addprefix $(OBJ_DIR), $(OBJ))

all: $(NAME)

$(NAME): $(LIB)
	gcc -g -o $(NAME) src/main.c $(MLX_HEAD) $(MLX_LIB) $(FRAMEWORK) $(HEADER) $(LIB)


$(LIB): $(OBJ_DIR) $(O_PATH)
	make -C libft
	cp $(LIBFT)/libft.a ./$(LIB)
	ar -rc $(LIB) $(O_PATH)
	ranlib $(LIB)

$(OBJ_DIR):
	mkdir -p obj

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	gcc -g -c $< -o $@ $(HEADER)

clean:
	@rm -f $(O_PATH)
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(LIB)
	@make -C $(LIBFT) fclean

val:
	valgrind --leak-check=full ./$(NAME)

re: fclean all

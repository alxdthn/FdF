# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/29 16:28:19 by nalexand          #+#    #+#              #
#    Updated: 2019/06/06 17:40:58 by nalexand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIB = fdf.a

CС = gcc -g

SRC_DIR = src/

OBJ_DIR = obj/

HEADER = -I includes
LIBFT = ../libft/libft.a
MLX_LIB = -L ../../../usr/local/lib/ -lmlx
MLX_HEAD = -I ../../../usr/local/include
FRAMEWORK = -framework OpenGL -framework AppKit

SRC = fdf_parce.c

OBJ = $(patsubst %.c, %.o, $(SRC))

C_PATH = $(addprefix $(SRC_DIR), $(SRC))

O_PATH = $(addprefix $(OBJ_DIR), $(OBJ))

all: $(NAME)

$(NAME): $(LIB) $(LIBFT)
	gcc -g -o $(NAME) main.c $(MLX_HEAD) $(MLX_LIB) $(FRAMEWORK) $(LIBFT) $(HEADER) $(LIB)
	##gcc -g -o $(NAME) main.c $(MLX_HEAD) $(LIBFT) $(HEADER) $(LIB)

$(LIBFT):
	make -C libft

$(LIB): $(OBJ_DIR) $(O_PATH)
	ar -rc $(LIB) $(O_PATH)
	ranlib $(LIB)

$(OBJ_DIR):
	mkdir -p obj

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	gcc -g -c $< -o $@ $(HEADER)

clean:
	@rm -f $(O_PATH)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

val:
	valgrind --leak-check=full ./$(NAME)

re: fclean all

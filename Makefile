# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/17 13:20:54 by mlavreni          #+#    #+#              #
#    Updated: 2019/01/17 13:20:57 by mlavreni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fractol

#files
SRC		= main.c \
			color.c \
			action.c \
			creation.c \
			get_fractal.c \
			render.c \
			fractals/julia.c \
			fractals/mandelbrot.c \
			fractals/tricorn.c

OBJ		= $(addprefix $(OBJDIR), $(SRC:.c=.o))

#compiler
CC		= gcc
# FLAGS	= -g
FLAGS	= -g -Wall -Wextra -Werror

#mlx library
MLX		= ../libmlx/
MLX_LIB	= $(addprefix $(MLX), mlx.a)
MLX_INC	= -I ../libmlx/
MLX_LNK	= -lmlx -framework OpenGL -framework AppKit # -L ../libmlx/ -lmlx -lXext -lX11

#ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT), libft.a)
FT_INC	= -I ./libft/
FT_LNK	= -L ./libft/ -lft

#directories
SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/

all: obj $(FT_LIB) $(NAME) #$(MLX_LIB) 

obj:
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/fractals

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(FLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $< #$(MLX_INC) 

$(FT_LIB):
	make -C $(FT)

# $(MLX_LIB):
# 	make -C $(MLX)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(FT_LNK) $(MLX_LNK) -lpthread -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean
	# make -C $(MLX) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FT) fclean

re: fclean all

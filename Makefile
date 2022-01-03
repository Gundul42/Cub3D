# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/28 18:22:38 by graja             #+#    #+#              #
#    Updated: 2021/09/17 13:52:13 by graja            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fractol 
SRCS		= main.c
COMMON		= common/colors.c common/draw.c common/ccalc.c common/init.c \
		  common/hsv2rgb.c common/rgb2hsv.c common/hooks.c \
		  common/sets.c common/cmdline.c common/fractset.c
FRACTALS	= fractals/mandel.c fractals/julia.c fractals/ship.c
CC		= gcc
FLAGS		= -Wall -Wextra -Werror
LIBFT		= libft
FLGFT		= -Llibft -lft
APLFLG		= -L/usr/X11/include -L/usr/X11/lib
FLGMLX		= -Lminilibx -lmlx -lXext -lX11 -lm
MLX		= minilibx

$(NAME)		:	$(SRCS) $(MLX) $(COMMON) $(LIBFT)
	make bonus -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(SRCS) $(COMMON) $(FRACTALS) $(FLAGS) $(FLGMLX) $(FLGFT) -o $(NAME)

apple		:	$(SRCS) $(MLX) $(COMMON) $(LIBFT)
	make bonus -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(SRCS) $(COMMON) $(FRACTALS) $(FLAGS) $(FLGMLX) $(APLFLG) $(FLGFT) -o $(NAME)

all		:	$(NAME)

clean		:	$(LIBFT) $(MLX)
	make clean -C $(LIBFT)
	make clean -C $(MLX)

bonus		:	all

fclean		:	$(LIBFT) $(MLX)
	rm -f $(NAME)
	rm -f $(MLX)/libmlx.a
	rm -f $(MLX)/libmlx_$(shell uname).a
	make fclean -C $(LIBFT)
	make clean -C $(MLX)

re		:	fclean all
	

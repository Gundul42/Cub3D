# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/28 18:22:38 by graja             #+#    #+#              #
#    Updated: 2022/01/09 09:38:03 by graja            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d
SRCS		= main.c
COMMON		= common/colors.c common/draw.c common/col_hsv2rgb.c \
			common/col_rgb2hsv.c common/hooks.c common/load_map.c \
			common/load_map_utils.c common/map2d.c common/maths.c \
			common/raycast.c common/movePlayer.c error.c \
			common/points.c
CC		= gcc
FLAGS	= -Wall -Wextra -Werror
LIBFT	= libft
FLGFT	= -Llibft -lft
APLFLG	= -L/usr/X11/include -L/usr/X11/lib
FLGMLX	= -Lminilibx -lmlx -lXext -lX11 -lm
MLX		= minilibx

$(NAME)		:	$(SRCS) $(MLX) $(COMMON) $(LIBFT)
	make bonus -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(SRCS) $(COMMON) $(FLAGS) $(FLGMLX) $(FLGFT) -o $(NAME)

apple		:	$(SRCS) $(MLX) $(COMMON) $(LIBFT)
	make bonus -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(SRCS) $(COMMON) $(FLAGS) $(FLGMLX) $(APLFLG) $(FLGFT) -o $(NAME)

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


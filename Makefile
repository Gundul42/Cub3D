# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/28 18:22:38 by graja             #+#    #+#              #
#    Updated: 2022/01/21 13:16:18 by flormich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d
SRCS		= main.c
COMMON		= common/colors.c common/draw.c common/col_hsv2rgb.c \
			common/col_rgb2hsv.c common/hooks.c common/load_map.c \
			common/player.c common/map2d.c common/maths.c \
			common/raycast.c common/movePlayer.c common/points.c \
			common/draw3D.c common/textures.c common/minimap.c \
			common/sprites.c common/checkmap.c common/errors.c \
			common/readmaphead.c common/parsemap.c common/checkmap_close.c
CC		= gcc
FLAGS	= -Wall -Wextra -Werror -g
LIBFT	= libft
FLGFT	= -Llibft -lft
FLGMLX	= -L /usr/X11/lib -lXext -lX11 -lm 
APLFLGMLX	= -L /usr/X11/lib -lXext -lX11 -lm 
MLX		= minilibx

$(NAME)		:	$(SRCS) $(MLX) $(COMMON) $(LIBFT)
	make bonus -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(SRCS) $(COMMON) $(FLAGS) $(FLGFT) ./minilibx/libmlx.a $(FLGMLX) -o $(NAME)

apple		:	$(SRCS) $(MLX) $(COMMON) $(LIBFT)
	make bonus -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(SRCS) $(COMMON) $(FLAGS) $(FLGFT) ./minilibx/libmlx.a $(APLFLGMLX) -o $(NAME)

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


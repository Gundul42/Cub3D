
NAME		= cub3d
BNAME		= bcub3d
SRCS		= main.c
COMMON		= common/colors.c common/draw.c common/col_hsv2rgb.c \
			common/col_rgb2hsv.c common/hooks.c common/hooks_2.c common/load_map.c \
			common/player.c common/map2d.c common/maths.c \
			common/raycast.c common/movePlayer.c common/points.c \
			common/draw3D.c common/textures.c common/minimap.c \
			common/sprites.c common/checkmap.c common/errors.c \
			common/readmaphead.c common/parsemap.c common/checkmap_close.c
BONUS		= bonus/main.c bonus/spritecast.c bonus/draw.c bonus/hooks.c
CC		= gcc
FLAGS	= -Wall -Wextra -Werror -g
LIBFT	= libft
FLGFT	= -Llibft -lft
APLFLG	= -L /usr/X11/lib -lXext -lX11 -lm
WINFLG	= -Lminilibx -lmlx -lXext -lX11 -lm
MLX		= minilibx

$(NAME)		:	$(SRCS) $(MLX) $(COMMON) $(LIBFT)
	make bonus -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(SRCS) $(COMMON) $(FLAGS) $(WINFLG) $(FLGFT) -o $(NAME)

$(BNAME)	:	$(BONUS) $(MLX) $(COMMON) $(LIBFT)
	make bonus -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(BONUS) $(COMMON) $(FLAGS) $(WINFLG) $(FLGFT) -o $(BNAME)

apple		:	$(SRCS) $(MLX) $(COMMON) $(LIBFT)
	make bonus -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(SRCS) $(COMMON) $(FLAGS) $(FLGFT) $(APLFLG) ./minilibx/libmlx.a -o $(NAME)

apple_bonus	:	$(BONUS) $(MLX) $(COMMON) $(LIBFT)
	make bonus -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(BONUS) $(COMMON) $(FLAGS)  $(FLGFT) $(APLFLG) ./minilibx/libmlx.a -o $(BNAME)

all		:	$(NAME)

bonus		:	$(BNAME)

clean		:	$(LIBFT) $(MLX)
	make clean -C $(LIBFT)
	make clean -C $(MLX)

fclean		:	$(LIBFT) $(MLX)
	rm -f $(NAME)
	rm -f $(BNAME)
	rm -f $(MLX)/libmlx.a
	rm -f $(MLX)/libmlx_$(shell uname).a
	make fclean -C $(LIBFT)
	make clean -C $(MLX)

re		:	fclean all


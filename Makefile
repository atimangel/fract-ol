# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/12 11:01:00 by snpark            #+#    #+#              #
#    Updated: 2021/07/16 16:50:40 by snpark           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
SRC = main.c\
	event.c\
	utils.c\
	mandelbrot.c\
	mandelbrot_utils.c\
	char_to_num.c

SRC_BONUS = main_bonus.c\
	event_bonus.c\
	utils_bonus.c\
	mandelbrot_bonus.c\
	mandelbrot_utils_bonus.c\
	sierpinski_bonus.c\
	char_to_num_bonus.c\
	parse_bonus.c\
	sierpinski_iterate_bonus.c


CFLAG = -Wall -Werror -Wextra
LINUX = -I /usr/include/lib -lXext -lX11 -lm -lbsd
MLX = -I mlx -L mlx -l mlx

all :
	gcc -O3 -o $(NAME) $(SRC) $(MLX) $(LINUX)
clean :
	rm $(NAME) $(NAME)_bonus
fclean : clean

re : fclean all

bonus :
	gcc -O3 -o $(NAME)_bonus $(SRC_BONUS) $(MLX) $(LINUX)

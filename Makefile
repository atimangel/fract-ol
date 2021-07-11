NAME = fractol
SRC = main.c\
	event.c\
	utils.c\
	mandelbrot.c\
	char_to_num.c
	
CFLAG = -Wall -Werror -Wextra
LINUX = -I /usr/include/lib -lXext -lX11 -lm -lbsd
MLX = -I mlx -L mlx -l mlx

all :
	gcc -o $(NAME) $(SRC) $(MLX) $(LINUX)
clean :

fclean :

re :

bonus :

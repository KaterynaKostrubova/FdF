NAME = fdf

SRC = main.c\
	  read_map.c\
	  bresenham.c\
	  mlx.c\
	  action.c\
	  color.c\
	  help_func.c\
	  help_actions.c

INC = -Ifdf.h 

INC2 = -I /usr/locale/include

OBJ = $(SRC:.c=.o)

LIBFT =	libft/libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror

FRMWR = -framework OpenGL -framework AppKit

MLX_LIB = -L /usr/local/lib/ -lmlx

.PHONY : all, re, clean, flcean

all: $(NAME)

$(OBJ): %.o: %.c
	$(CC) -c $(FLAGS) $< -o $@ $(INC) $(INC2)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(INC2) -o $(NAME) $(LIBFT) $(FRMWR) $(MLX_LIB)

$(LIBFT):
		make -C libft

clean:
		rm -f $(OBJ)
			make clean -C libft

fclean: clean
		rm -f $(NAME)
			make fclean -C libft

re: fclean all
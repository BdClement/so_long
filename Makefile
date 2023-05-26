# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 20:44:46 by clbernar          #+#    #+#              #
#    Updated: 2023/05/19 12:35:34 by clbernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = @cc
CFLAGS = -Wall -Werror -Wextra
RM = @rm -f

SRCS = main.c parsing.c read_map.c utils.c moves.c display.c clean.c

OBJ_DIR = ./obj

#OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

LIB = $(LIBFT_PATH)/libft.a
LIBFT_PATH = ./Libft

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(LIB) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft -L ./minilibx-linux/libmlx.a ./minilibx-linux/libmlx_Linux.a -Ilmlx -lXext -lX11


# $(OBJS): $(OBJ_DIR)/%.o: /%.c
# 		@mkdir -p $(OBJ_DIR)
# 		$(CC) -I $(CFLAGS) -c $<

%.o : %.c
	$(CC) -I $(CFLAGS) -c $<

$(LIB):
	@make -C Libft/
	@make bonus -C Libft/

git :
	git add *
	git commit -m c
	git push

clean:
##rm -rf $(OBJ_DIR)
	$(RM) $(OBJS)
	@make fclean -C Libft/

fclean: clean
	 $(RM) $(NAME)

re: fclean all

.PHONY : re all fclean bonus clean

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 20:44:46 by clbernar          #+#    #+#              #
#    Updated: 2023/05/12 19:58:16 by clbernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = @cc
CFLAGS = -Wall -Werror -Wextra
RM = @rm -f

SRCS = main.c parsing.c read_map.c utils.c

LIB = $(LIBFT_PATH)/libft.a
LIBFT_PATH = ./Libft

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(LIB) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft -L ./minilibx-linux/libmlx.a ./minilibx-linux/libmlx_Linux.a -Ilmlx -lXext -lX11

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
	$(RM) $(OBJS) $(B_OBJS) $(GNL_OBJ)
	@make fclean -C Libft/

fclean: clean
	 $(RM) $(NAME)

re: fclean all

.PHONY : re all fclean bonus clean

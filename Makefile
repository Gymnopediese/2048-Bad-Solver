# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaud <albaud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 13:07:44 by albaud            #+#    #+#              #
#    Updated: 2023/03/01 15:24:37 by albaud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS 		= draw.c get_state.c init.c max_max.c main.c move.c snake_ia.c step.c win.c cfiles/atoia.c cfiles/f_file_size.c cfiles/f_read.c cfiles/f_readlines.c libia/forward.c libia/ia_relu.c libia/ia_sigmoid.c libia/init_net.c libia/k_voisin.c libia/save.c libia/train.c libia/visualizer.c
OBJS 		= ${SRCS:.c=.o}
FLIB		= libia/mlib/mlib.a libia/mlib/vlib/vlib.a
LIBS 		= koflibc/libft.a p/p.a libia/mlib/mlib.a libia/mlib/vlib/vlib.a
LIBSS		= -Lminilibx_macos -lmlx -Lkoflibc -lft -Lp
NAME 		= 2048
CC			= gcc
FRAMEWORK	= -framework OpenGL -framework AppKit
CFLAGS		= -Wall -Wextra -Werror -g

.c.o 	:
		${CC} ${CFLAGS} -I minilibx_macos -c $< -o ${<:.c=.o}
		
all 	: $(NAME) $(DNAME)

$(NAME)	: ${OBJS} ${LIBS}
		${CC} ${CFLAGS} -o ${NAME} ${FRAMEWORK} ${OBJS} ${LIBS} ${LIBSS}

$(DNAME): ${DOBJS} ${LIBS}
		${CC} ${CFLAGS} -o ${DNAME} ${FRAMEWORK} ${DOBJS} ${LIBS} ${LIBSS}

${LIBS} :
		make -C koflibc 

clean	:
		rm -f ${OBJS}

fclean	:	clean
		rm -f ${NAME} 

re		: fclean all

c 		:
		find *.c cfiles/*.c libia/*.c | tr '\n' ' '

make	:
		make -C koflibc && make -C libia && make -C libia/mlib && make -C libia/mlib/vlib && make -C p && make

makere	:
		make re -C koflibc && make re -C libia && make re -C libia/mlib && make re -C libia/mlib/vlib && make re -C p && make re

run		: 
		make -C koflibc && make -C libia && make -C p && make && ./digit

test	: make
		${CC} ${CFLAGS} -o t ${FRAMEWORK} test.c ${LIBS} ${LIBSS}
		./t
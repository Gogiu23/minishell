# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_tester.mk                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 19:32:44 by gdominic          #+#    #+#              #
#    Updated: 2023/05/30 19:37:38 by gdominic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_TESTER = src/tester/printer.c

OBJS_TESTER = $(patsubst $(SRC_DIR_TESTER)/%, $(OBJ_DIR_TESTER)/%, $(SRCS_TESTER:.c=.o))
DEPS_TESTER = $(patsubst $(SRC_DIR_TESTER)/%, $(DEP_DIR_TESTER)/%, $(SRCS_TESTER:.c=.d))

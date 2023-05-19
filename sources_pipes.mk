# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_pipes.mk                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:41:27 by vduchi            #+#    #+#              #
#    Updated: 2023/05/19 18:21:16 by gdominic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_PIPES	=	src/pipes/pipes.c
SRCS_PIPES	+=	src/pipes/run_commands.c

OBJS_PIPES	=	$(patsubst $(SRC_DIR_PIPES)/%, $(OBJ_DIR_PIPES)/%, $(SRCS_PIPES:.c=.o))
DEPS_PIPES	=	$(patsubst $(SRC_DIR_PIPES)/%, $(DEP_DIR_PIPES)/%, $(SRCS_PIPES:.c=.d))


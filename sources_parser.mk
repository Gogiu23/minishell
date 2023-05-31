# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_parser.mk                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/29 19:06:12 by vduchi            #+#    #+#              #
#    Updated: 2023/05/30 16:02:08 by vduchi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_PARSER	=	src/parser/parser.c
SRCS_PARSER	+=	src/parser/quotes.c
SRCS_PARSER	+=	src/parser/utils.c

OBJS_PARSER	=	$(patsubst $(SRC_DIR_PARSER)/%, $(OBJ_DIR_PARSER)/%, $(SRCS_PARSER:.c=.o))
DEPS_PARSER	=	$(patsubst $(SRC_DIR_PARSER)/%, $(DEP_DIR_PARSER)/%, $(SRCS_PARSER:.c=.d))


# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 22:11:19 by vduchi            #+#    #+#              #
#    Updated: 2023/03/30 16:58:43 by vduchi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
DEL_LINE		=	\033[2K
ITALIC			=	\033[3m
BOLD			=	\033[1m
DEF_COLOR		=	\033[0;39m
GRAY			=	\033[0;90m
RED				=	\033[0;91m
GREEN			=	\033[0;92m
YELLOW			=	\033[0;93m
BLUE			=	\033[0;94m
MAGENTA			=	\033[0;95m
CYAN			=	\033[0;96m
WHITE			=	\033[0;97m
BLACK			=	\033[0;99m
ORANGE			=	\033[38;5;209m
BROWN			=	\033[38;2;184;143;29m
DARK_GRAY		=	\033[38;5;234m
MID_GRAY		=	\033[38;5;245m
DARK_GREEN		=	\033[38;2;75;179;82m
DARK_YELLOW		=	\033[38;5;143m

NAME			=	minishell

LIBS_DIR		=	libs
SRC_DIR			=	src/pipes
OBJ_DIR			=	obj
DEPS_DIR		=	dep
GNL_DIR			=	get_next_line
INC_DIR			=	inc/ ft_printf/include/ get_next_line/
RD_LIB			=	readline

LIBFT			=	libft
PRINTF			=	ft_printf
ALL_LIBS		=	libft/libft.a ft_printf/libftprintf.a

SRCS			=	src/pipes/pipes.c src/pipes/check_command.c src/pipes/run_commands.c \
					src/pipes/free.c
GNL_SRCS		=	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJS			=	$(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRCS:.c=.o))
GNL_OBJS		=	$(patsubst $(GNL_DIR)/%, $(GNL_DIR)/%, $(GNL_SRCS:.c=.o))
DEPS			=	$(patsubst $(SRC_DIR)/%, $(DEPS_DIR)/%, $(SRCS:.c=.d))
GNL_DEPS		=	$(patsubst $(GNL_DIR)/%, $(GNL_DIR)/%, $(GNL_SRCS:.c=.d))

CFLAGS			+= 	-Wall -Werror -Wextra -g -O3 $(addprefix -I , $(INC_DIR))
LDFLAGS			= 	-L ft_printf -L libft -lft -lftprintf
DEPFLAGS		=	-MMD -MP -MF $(DEPS_DIR)/$*.d
DEPFLAGS_GNL	=	-MMD -MP -MF $(GNL_DIR)/$*.d

CC				=	gcc
RM				=	rm -rf
MKDIR			=	mkdir -p

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@
	@echo "$(YELLOW)$(patsubst $(SRC_DIR)/%,%, $<) \tcompiled!$(DEF_COLOR)"

$(GNL_DIR)/%.o	:	$(GNL_DIR)/%.c
	@$(CC) $(CFLAGS) $(DEPFLAGS_GNL) -D BUFFER_SIZE=1 -c $< -o $@
	@echo "$(YELLOW)$(patsubst $(GNL_DIR)/%,%, $<) \tcompiled!$(DEF_COLOR)"

all				:
	@$(MAKE) -C $(LIBFT)
	@$(MAKE) -C $(PRINTF)
	@$(MAKE) $(NAME)

$(NAME)		::
	@echo "$(MAGENTA)\nChecking minishell...$(DEF_COLOR)"

$(NAME)		::	$(OBJ_DIR) $(DEPS_DIR) $(OBJS) $(ALL_LIBS)
	@echo "$(ORANGE)Compiling minishell exec...$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

$(NAME)		::
	@echo "$(GREEN)Minishell executable ready!$(DEF_COLOR)"

$(OBJ_DIR)	:
	@$(MKDIR) $@

$(DEPS_DIR)	:
	@$(MKDIR) $@

clean		:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(DEPS_DIR)
	@$(RM) $(GNL_OBJS)
	@$(RM) $(GNL_DEPS)

fclean		:	clean
	@$(RM) $(NAME) $(NAME_BON) $(LIBS_DIR)
	@$(MAKE) -C libft fclean
	@$(MAKE) -C ft_printf fclean
	@echo "$(BLUE)\nMinishell cleaned!$(DEF_COLOR)"

re			:	fclean all

-include $(DEPS)
-include $(GNL_DEPS)

.PHONY: all clean fclean re

#
#valgrind:
#	valgrind --leak-check=yes --show-leak-kinds=all "nombre del executable" "nombre de argumentos"
#	valgrind --leak-check=yes --track-origins=yes "nombre del executable" "nombre de argumentos"
#
#	gcc $(CFLAGS) -fsanitize=address -g -O3 -fno-omit-frame-pointer $(LDFLAGS) $(SRCS) -o $@

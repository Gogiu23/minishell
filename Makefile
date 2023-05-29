# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 22:11:19 by vduchi            #+#    #+#              #
#    Updated: 2023/05/29 19:35:05 by vduchi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-#

-include directories.mk

-include sources_pipes.mk
-include sources_parser.mk
-include sources_built_ins.mk
-include sources_minishell.mk

#=-=-=-=-=-=-=- COLORS DEFINITION =-=-=-=-=-=-=-=-=-#

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

#=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-#

NAME			=	minishell

RD_PATH			=	libs/libreadline.a
LIBFT_PATH		=	libs/libft.a

#=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-#

CFLAGS			+= 	-Wall -Werror -Wextra -DREADLINE_LIBRARY -g -O3 $(addprefix -I , $(INC_DIR))
LDFLAGS			= 	-L $(LIBS_DIR) -lft -lreadline -lncurses
DFLAGS_MS		=	-MMD -MP -MF $(DEP_DIR_MS)/$*.d
DFLAGS_BI		=	-MMD -MP -MF $(DEP_DIR_BI)/$*.d
DFLAGS_PIPES	=	-MMD -MP -MF $(DEP_DIR_PIPES)/$*.d
DFLAGS_PARSER	=	-MMD -MP -MF $(DEP_DIR_PARSER)/$*.d

#=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-#

CC				=	gcc
RM				=	rm -rf
MKDIR			=	mkdir -p

#=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-#

$(OBJ_DIR_BI)/%.o	:	$(SRC_DIR_BI)/%.c
	@$(CC) -c $< $(CFLAGS) $(DFLAGS_BI) -o $@
	@echo "$(YELLOW)$(patsubst $(SRC_DIR_BI)/%,%, $<)   \tcompiled!$(DEF_COLOR)"

$(OBJ_DIR_MS)/%.o	:	$(SRC_DIR_MS)/%.c
	@$(CC) -c $< $(CFLAGS) $(DFLAGS_MS) -o $@
	@echo "$(YELLOW)$(patsubst $(SRC_DIR_MS)/%,%, $<)   \tcompiled!$(DEF_COLOR)"

$(OBJ_DIR_PIPES)/%.o	:	$(SRC_DIR_PIPES)/%.c
	@$(CC) -c $< $(CFLAGS) $(DFLAGS_PIPES) -o $@
	@echo "$(YELLOW)$(patsubst $(SRC_DIR_PIPES)/%,%, $<)   \tcompiled!$(DEF_COLOR)"

$(OBJ_DIR_PARSER)/%.o	:	$(SRC_DIR_PARSER)/%.c
	@$(CC) -c $< $(CFLAGS) $(DFLAGS_PARSER) -o $@
	@echo "$(YELLOW)$(patsubst $(SRC_DIR_PARSER)/%,%, $<)   \tcompiled!$(DEF_COLOR)"

all				:	directories $(LIBFT_PATH) $(RD_PATH)
	@$(MAKE) $(NAME)

$(NAME)			::
	@echo "$(MAGENTA)\nChecking minishell...$(DEF_COLOR)"

$(NAME)			::	$(OBJS_MS) $(OBJS_PIPES) $(OBJS_BI) $(OBJS_PARSER)
	@$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@
	@echo "$(ORANGE)Compiling minishell exec...$(DEF_COLOR)"

$(NAME)			::
	@echo "$(GREEN)Minishell executable ready!$(DEF_COLOR)"

$(LIBFT_PATH)	:
	@$(MAKE) -C libft
	@cp libft/libft.a libs/

$(RD_PATH)		:
	@echo "$(ORANGE)\nCompiling readline library...$(DEF_COLOR)"
	@cd readline; ./configure --prefix=$(shell pwd)/readline/library; make; make install;
	@cp readline/libreadline.a libs/
	@echo "$(GREEN)Readline library ready!$(DEF_COLOR)"

directories	:
	@$(MKDIR) $(LIBS_DIR)
	@$(MKDIR) $(OBJS_DIR)
	@$(MKDIR) $(DEPS_DIR)
	@$(MKDIR) $(OBJ_DIR_MS)
	@$(MKDIR) $(DEP_DIR_MS)
	@$(MKDIR) $(OBJ_DIR_BI)
	@$(MKDIR) $(DEP_DIR_BI)
	@$(MKDIR) $(OBJ_DIR_PIPES)
	@$(MKDIR) $(DEP_DIR_PIPES)


clean			:
	@$(RM) $(OBJS_DIR)
	@$(RM) $(DEPS_DIR)
	@$(RM) $(LIBS_DIR)

fclean			:	clean
	@$(RM) $(NAME) readline/library
	@$(MAKE) -C libft fclean
	@-cd readline; make distclean -sik;
	@echo "$(BLUE)\nMinishell cleaned!$(DEF_COLOR)"

re				:	fclean all

-include $(DEPS_MS)
-include $(DEPS_PIPES)

.PHONY: all clean fclean re

#
#valgrind:
#	valgrind --leak-check=yes --show-leak-kinds=all "nombre del executable" "nombre de argumentos"
#	valgrind --leak-check=yes --track-origins=yes "nombre del executable" "nombre de argumentos"
#
#	gcc $(CFLAGS) -fsanitize=address -g -O3 -fno-omit-frame-pointer $(LDFLAGS) $(SRCS) -o $@

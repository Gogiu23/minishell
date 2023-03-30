# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 22:11:19 by vduchi            #+#    #+#              #
#    Updated: 2022/11/16 15:57:39 by vduchi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
DEL_LINE	=	\033[2K
ITALIC		=	\033[3m
BOLD		=	\033[1m
DEF_COLOR	=	\033[0;39m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[0;92m
YELLOW		=	\033[0;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m
BLACK		=	\033[0;99m
ORANGE		=	\033[38;5;209m
BROWN		=	\033[38;2;184;143;29m
DARK_GRAY	=	\033[38;5;234m
MID_GRAY	=	\033[38;5;245m
DARK_GREEN	=	\033[38;2;75;179;82m
DARK_YELLOW	=	\033[38;5;143m

NAME		=	libftprintf.a

SRCS		=	src/ft_printf.c src/ft_utils.c src/ft_funcs.c \
				src/ft_int_to_ascii.c src/ft_hex.c
OBJS		=	$(SRCS:.c=.o)
DEPS		=	$(SRCS:.c=.d)

CFLAGS		=	-Wall -Wextra -Werror
DEP_FLAGS	=	-MMD -MP

CC			=	gcc
RM			=	rm -rf
MKDIR		=	mkdir -p

%.o: 		%.c
	@echo "$(YELLOW)$(patsubst $(SRCS_DIR)/%,%, $<)  \tcompiled!$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(DEP_FLAGS) -c $< -o $@

all:		$(NAME)

$(NAME)	::
	@echo "$(MAGENTA)\nChecking printf...$(DEF_COLOR)"

$(NAME)	::	$(OBJS)
	@echo "$(ORANGE)Creating printf library...$(DEF_COLOR)"
	@ar -rcs $@ $^

$(NAME)	::
	@echo "$(GREEN)Printf archive ready!$(DEF_COLOR)"

clean	:
	@$(RM) $(OBJS)
	@$(RM) $(DEPS)

fclean	:	clean
	@$(RM) $(NAME)
	@echo "$(BLUE)\nPrintf cleaned!$(DEF_COLOR)"

re		:	fclean all

-include $(DEPS)

.PHONY	:	all clean fclean re

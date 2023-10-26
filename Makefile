# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yothmani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 20:44:56 by yothmani          #+#    #+#              #
#    Updated: 2023/10/25 21:26:33 by yothmani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 				= pipex

NAME_BONUS 			= pipex_bonus

CC 					= gcc
CFLAGS 				= -Wall -Wextra -Werror

RM					= rm -rf

SRC_DIR 			= src
INC_DIR 			= includes

INC 				= -I $(INC_DIR)

SRC = $(SRC_DIR)/file.c $(SRC_DIR)/pipex_utils.c  $(SRC_DIR)/lib_utils.c\
$(SRC_DIR)/path_utils.c  $(SRC_DIR)/main_bonus.c\



OBJ 				= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(INC)
	@printf $(CUT)$(CUT)$(CUT)$(CUT)
	@echo $(BOLD)$(L_PURPLE) PIPEX is ready to be executed ! 💪💥$(RESET)

all bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(INC)
	@printf $(CUT)$(CUT)$(CUT)$(CUT)
	@echo $(BOLD)$(L_PURPLE) PIPEX BONUS is ready to be executed ! 💪💥$(RESET)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INC) 
	@echo $(BOLD)$(GREEN) "Compiled $<"

norm :
	@echo $(BOLD)$(PINK)" Mandatory part!"$(MINT)
	@norminette $(SRC) $(INC_DIR)

run :
	@make && ./pipex infile "cat" "ls -a" outfile

run_bonus:
	@make bonus && ./pipex_bonus infile "grep a1" "wc -w" "cat" outfile

leaks:
	@make && leaks --atExit -- ./pipex  infile "cat" "popdosplls -la"   outfile
	
clean :
	@printf $(CUT)$(CUT)
	@$(RM) $(OBJ) pipex.dSYM
	@echo $(BOLD)$(L_PURPLE)"Cleaned objects and executables!" ... 🧹🗑️$(RESET)

fclean : clean
	@$(RM) $(NAME)
	@printf $(CUT)$(CUT)
	@echo $(BOLD)$(L_PURPLE) ✨pipex✨ $(PINK)All cleaned up! ....🧹🗑️$(RESET)

re: fclean all bonus

.PHONY: all clean fclean re

# ######################### Color #########################

GREEN="\033[32m"
MINT="\033[38;5;51m"
L_PURPLE="\033[38;5;55m"
MAUVE="\033[38;5;147m"
PINK="\033[38;5;175m"
RESET="\033[0m"
BOLD="\033[1m"
UP = "\033[A"
DOWN = "\033[B"
RIGHT = "\033[C"
LEFT = "\033[D"
CUT = "\033[K"
SAVE = "\033[s"
RESTORE = "\033[u"
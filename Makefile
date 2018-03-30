# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: logan  <logan@42.us.org>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/13 10:03:24 by logan             #+#    #+#              #
#    Updated: 2018/03/13 10:03:26 by logan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bomberman
LIST = main \
ShadingProgram \
Time \
VoxObject \
VoxRenderer \
VoxelChunk \
Window \
Particles.class \

SRC_DIR = src
OBJ_DIR = obj

SRC = $(addsuffix .cpp, $(addprefix src/, $(LIST)))
OBJ = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(LIST)))

CPPFLAGS = -std=c++11 -O3 -march=native -Wall -Wextra -Werror \
$(shell pkg-config --cflags glfw3 glm)

LDFLAGS = -framework OpenGl $(shell pkg-config --libs glfw3 glm)

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@echo "\033[32;1mLinking.. \033[0m"
	@clang++ $(LDFLAGS) -o $@ $^
	@echo "\033[32;1m"$(NAME)" created\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	clang++ $(CPPFLAGS) -c -o $@ $<

clean:
	@echo "\033[31;1mCleaning..\033[0m"
	@rm -f $(OBJ)

fclean:
	@echo "\033[31;1mFull Cleaning..\033[0m"
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)

re:	fclean all

.PHONY: clean fclean all re directories docs

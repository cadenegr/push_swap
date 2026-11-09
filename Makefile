# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 14:55:14 by cadenegr          #+#    #+#              #
#    Updated: 2025/09/30 12:23:02 by cadenegr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

SRCDIR = src
OBJDIR = obj
LIBFTDIR = libft

SRC_FILES = $(wildcard $(SRCDIR)/*.c)
SRC = $(addprefix $(SRCDIR)/, $(SRC_FILES))
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC_FILES))

LIBFT = $(LIBFTDIR)/libft_printf.a
INCLUDES = -I./include -I$(LIBFTDIR)/include

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L$(LIBFTDIR) -lft_printf
RM = rm -rf

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	$(RM) $(OBJDIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

# Testing and Performance Analysis Targets
test: $(NAME)
	@./benchmark.sh

quick_test: $(NAME)
	@echo "5 elements:" && ./$(NAME) 5 3 8 1 9 | wc -l
	@echo "100 elements:" && seq 1 100 | shuf | xargs ./$(NAME) | wc -l
	@echo "500 elements:" && seq 1 500 | shuf | xargs ./$(NAME) | wc -l

benchmark: $(NAME)
	@python3 tester/checker.py

stress: $(NAME)
	@python3 tester/checker.py 500 100 5500

validate: $(NAME)
	@python3 tester/checker.py 100 20 700

demo: $(NAME)
	@echo "Input: 5 3 8 1 9"
	@./$(NAME) 5 3 8 1 9
	@echo "Total moves: $$(./$(NAME) 5 3 8 1 9 | wc -l)"

visual: $(NAME)
	@./visualize.sh

help:
	@echo "Building:"
	@echo "  make            build push_swap"
	@echo "  make clean      remove object files"
	@echo "  make fclean     remove all build files"
	@echo "  make re         rebuild from scratch"
	@echo ""
	@echo "Testing:"
	@echo "  make test       input checks + sorting suite at the 42 limits"
	@echo "  make benchmark  sorting suite only (3, 4, 5, 10, 50, 100, 500 numbers)"
	@echo "  make stress     100 runs of 500 numbers, limit 5500"
	@echo "  make validate   20 runs of 100 numbers, limit 700"
	@echo "  make quick_test move counts for 5, 100 and 500 numbers"
	@echo "  make demo       moves for 5 3 8 1 9"
	@echo "  make visual     open the visualizer with 100 and 500 numbers"

.PHONY: test quick_test benchmark stress validate demo visual help



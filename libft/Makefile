# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 15:45:39 by cadenegr          #+#    #+#              #
#    Updated: 2024/02/02 11:42:53 by cadenegr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	libft_printf.a
INCLUDES 	= 	../include
SRC_DIR 	= 	src/
OBJ_DIR 	= 	obj/
OUTPUT		=	OUTPUT

CC = 			gcc
CFLAGS 		= 	-Wall -Werror -Wextra -I

RM 		= 	rm -f
AR 		= 	ar rcs

SRC_FILES = ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii \
	ft_isdigit ft_isprint ft_itoa ft_memchr ft_memcmp ft_memcpy \
	ft_memmove ft_memset ft_putchar_fd ft_putendl_fd ft_putnbr_fd \
	ft_putstr_fd ft_split ft_strchr ft_strdup ft_striteri ft_strjoin \
	ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp ft_strnstr \
	ft_strrchr ft_strtrim ft_substr ft_tolower ft_toupper ft_lstadd_back \
	ft_lstadd_front ft_lstclear ft_lstdelone ft_lstiter ft_lstlast \
	ft_lstmap ft_lstnew ft_lstsize ft_printf ft_printf_utils ft_print_ptr \
	ft_print_unsigned ft_print_hex ft_atol_index ft_atol ft_swap ft_qsort \
	ft_countword 

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))


all: 		$(NAME)


$(NAME): 	$(OBJ)
		@$(AR) $(NAME) $(OBJ)
		@ranlib $(NAME)
		@echo "Libft_printf compiled!"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
		@echo "Compiling: $< "
		@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)


clean:
		@$(RM) -rf $(OBJ_DIR)
		@$(RM) -f $(NAME)
		@$(RM) -f libft.a
		@echo "Libft_print objects files cleaned!"


fclean: 	clean
		@$(RM) -f $(NAME)
		@echo "Libft_printf executable files cleaned!"


re: 		fclean all
		@echo "Cleaned and rebuilt everything for libft!"
	
norm:
		@norminette $(SRC) $(INCLUDES) | grep -v Norme -B1 || true

.PHONY: 	all clean fclean re norm


NAME = push_swap

CC = cc

CCFLAG = -Wall -Wextra -Werror -g3

SRC = for_free.c init.c main.c  p_operation.c  r_operation.c  rr_operation.c s_operate.c  small_sort.c   split.c  utils.c  utils2.c k_sort.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CCFLAG) $(OBJ) -o $(NAME)

%.o: %.c push_swap.h
	@printf "\033[1;92mCompiled 👌🏽 %s\033[0m\n" $@
	@$(CC) $(CCFLAG) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	@printf "\033[1;31mRemoved binary: $(NAME) 💣\033[0m\n"
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
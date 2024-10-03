NAME = philo
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -pthread

SRC =	sources/main.c\
		sources/validate_args.c\
		sources/dinner.c
OBJ = $(SRC:.c=.o)

Reset = \033[0m
G = \033[32m
R = \033[31m
Y = \033[33m
blink = \033[6;7;1;3m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "-----------------------Compilation of $(NAME)----------------------------------------"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline
	@echo "-------------------------------------------------------------------------------------"
	@echo "$(blink)$(G) ✅ $(NAME) successfully compiled $(Reset)"

fsanitize: FLAGS += -fsanitize=thread
fsanitize: fclean ${NAME}

debug: FLAGS += -ggdb3
debug: fclean ${NAME}

val: re debug
	valgrind --tool=helgrind -s ./philo 5 800 200 200 7 

clean:
	$(RM) $(OBJ)
	@echo "$(Y) 😉 Objects from the $(NAME) project have been removed $(Reset)"

fclean: clean
	@echo "-------------------------------------------------------------------------------------"
	$(RM) $(NAME)
	@echo "$(blink)$(R) ❌ removed $(NAME) executable $(Reset)"
	@echo "-------------------------------------------------------------------------------------"

re: fclean all

.PHONY: all clean fclean re
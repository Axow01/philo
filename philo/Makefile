#--- DEFAULT VALUES ---#

NAME = philo

SRC = src/main.c src/parsing.c src/ft_atoi.c src/action_philo.c

OBJS = $(patsubst src/%.c, bin/%.o, $(SRC))

CC = gcc

CFLAGS = -Wall -Wextra -Werror -O2 # -g -fsanitize=thread

#---   COLORS   ---#

RED = \033[31m
BLUE = \033[36m
GREEN = \033[32m
YELLOW = \033[33m
BOLD = \033[1m
RESET = \033[0m

#---   RULES   ---#

all: $(NAME) logo

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(BOLD)$(YELLOW)Compilation done$(RESET)\n"

bin/%.o: src/%.c
	@mkdir -p bin/
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -drf bin/
	@echo "$(BOLD)$(YELLOW)clean complete$(RESET)\n"

fclean: clean
	@rm -df $(NAME)
	@echo "$(BOLD)$(YELLOW)fclean complete$(RESET)\n"

bonus: all

re: fclean all

# warning:
# 	@echo "$(BOLD)$(YELLOW)WARNING$(RESET)\n$(RED)Debug flag are actives !!! (remove before push)$(RESET)\n\n"

logo:
	@echo "\033[32;1m--- BUILD COMPLETE ---"
	@echo "███▄ ▄███▓ ███▄ ▄███▓ ▄▄▄       ██▀███   ▄████▄   ▒█████  ▄▄▄█████▓▄▄▄█████▓"
	@echo "▓██▒▀█▀ ██▒▓██▒▀█▀ ██▒▒████▄    ▓██ ▒ ██▒▒██▀ ▀█  ▒██▒  ██▒▓  ██▒ ▓▒▓  ██▒ ▓▒"
	@echo "▓██    ▓██░▓██    ▓██░▒██  ▀█▄  ▓██ ░▄█ ▒▒▓█    ▄ ▒██░  ██▒▒ ▓██░ ▒░▒ ▓██░ ▒░"
	@echo "▒██    ▒██ ▒██    ▒██ ░██▄▄▄▄██ ▒██▀▀█▄  ▒▓▓▄ ▄██▒▒██   ██░░ ▓██▓ ░ ░ ▓██▓ ░ "
	@echo "▒██▒   ░██▒▒██▒   ░██▒ ▓█   ▓██▒░██▓ ▒██▒▒ ▓███▀ ░░ ████▓▒░  ▒██▒ ░   ▒██▒ ░ "
	@echo "░ ▒░   ░  ░░ ▒░   ░  ░ ▒▒   ▓▒█░░ ▒▓ ░▒▓░░ ░▒ ▒  ░░ ▒░▒░▒░   ▒ ░░     ▒ ░░   "
	@echo "░  ░      ░░  ░      ░  ▒   ▒▒ ░  ░▒ ░ ▒░  ░  ▒     ░ ▒ ▒░     ░        ░    "
	@echo "░      ░   ░      ░     ░   ▒     ░░   ░ ░        ░ ░ ░ ▒    ░        ░      "
	@echo "       ░          ░         ░  ░   ░     ░ ░          ░ ░                    "
	@echo "                                         ░                                   \033[0m"


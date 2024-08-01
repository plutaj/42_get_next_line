NAME = get_next_line.a
SOURCES = \
		get_next_line.c \
		get_next_line_utils.c \

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -Werror
CC = cc

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f *.so

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

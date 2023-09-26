CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_isalpha.c ft_isdigit.c ft_toupper.c ft_tolower.c ft_isalnum.c ft_bzero.c ft_isascii.c ft_isprint.c ft_memset.c ft_strlen.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_strchr.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
SRCBB = ft_lstnew_bonus.c  ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
RM = rm -rf
NAME = libft.a



all : $(NAME)

$(NAME) : $(SRC:.c=.o)
	ar rc libft.a $(SRC:.c=.o)

	
bonus :	ft_lstnew_bonus.o  ft_lstadd_front_bonus.o ft_lstsize_bonus.o ft_lstlast_bonus.o ft_lstadd_back_bonus.o ft_lstdelone_bonus.o ft_lstclear_bonus.o ft_lstiter_bonus.o ft_lstmap_bonus.o

ft_lstnew_bonus.o : ft_lstnew_bonus.c
	$(CC) $(CFLAGS) -c $<
	ar rc libft.a $@


ft_lstadd_front_bonus.o : ft_lstadd_front_bonus.c
	$(CC) $(CFLAGS) -c $<
	ar rc libft.a $@

ft_lstsize_bonus.o : ft_lstsize_bonus.c
	$(CC) $(CFLAGS) -c $<
	ar rc libft.a $@

ft_lstlast_bonus.o : ft_lstlast_bonus.c
	$(CC) $(CFLAGS) -c $<
	ar rc libft.a $@

ft_lstadd_back_bonus.o : ft_lstadd_back_bonus.c
	$(CC) $(CFLAGS) -c $<
	ar rc libft.a $@

ft_lstdelone_bonus.o : ft_lstdelone_bonus.c
	$(CC) $(CFLAGS) -c $<
	ar rc libft.a $@

ft_lstclear_bonus.o : ft_lstclear_bonus.c
	$(CC) $(CFLAGS) -c $<
	ar rc libft.a $@

ft_lstiter_bonus.o : ft_lstiter_bonus.c
	$(CC) $(CFLAGS) -c $<
	ar rc libft.a $@
	
ft_lstmap_bonus.o: ft_lstmap_bonus.c
	$(CC) $(CFLAGS) -c $<
	ar rc libft.a $@

	



clean:
	$(RM) $(SRC:.c=.o) $(SRCBB:.c=.o)

fclean: clean
	$(RM) $(NAME)

re: fclean all


.PHONY : all clean fclean re bonus

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/27 14:03:00 by irozhkov          #+#    #+#              #
#    Updated: 2025/02/20 11:41:39 by irozhkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADER = libft.h

CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -f
AR = ar rcs

SRC = ft_atoi ft_isprint ft_memmove ft_strchr ft_strmapi ft_toupper \
	  ft_bzero ft_itoa ft_memset ft_strdup ft_strncmp ft_calloc \
	  ft_putchar_fd ft_striteri ft_strnstr ft_isalnum ft_putendl_fd \
	  ft_strjoin ft_strrchr ft_isalpha ft_memchr ft_putnbr_fd \
	  ft_strlcat ft_strtrim ft_isascii ft_memcmp ft_putstr_fd \
	  ft_strlcpy ft_substr ft_isdigit ft_memcpy ft_split ft_strlen \
	  ft_tolower

SRC_BONUS = ft_lstadd_back_bonus ft_lstadd_front_bonus \
			ft_lstclear_bonus ft_lstdelone_bonus ft_lstiter_bonus \
			ft_lstlast_bonus t_lstmap_bonus ft_lstnew_bonus \
			ft_lstsize_bonus


SRCS = $(addsuffix .c, $(SRC))
SRCS_BONUS = $(addsuffix _bonus.c, $(SRC_BONUS))

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

%.o:%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) Makefile
	$(AR) $(NAME) $(OBJS)

bonus: $(OBJS_BONUS)
	$(AR) $(NAME) $(OBJS_BONUS)

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:		all bonus clean fclean re

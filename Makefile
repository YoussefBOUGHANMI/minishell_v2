
TARGET		= minishell
SRCS		= minishell.c split_cmd.c clean_quotes.c outils/outils.c \
			parsing/p_add_space.c parsing/p_count.c parsing/p_lexer.c parsing/p_outils.c parsing/p_verif.c parsing/parsing.c \
			parsing/p_split.c parsing/p_manage_quote_pipe.c  parsing/p_outils_2.c  parsing/p_verif_2.c \
			find_path/find_path.c manage_dollar.c manage_redir_out.c manage_redir_in.c \
			builtins/b_builtins.c builtins/b_cd.c builtins/b_echo.c builtins/b_env.c builtins/b_outils.c builtins/b_pwd.c \
			builtins/b_export.c builtins/b_unset.c signaux.c

CC			= gcc
C_FLAGS		= 
# -Wall -Wextra -Werror
LD			= $(CC)
OBJS		= $(SRCS:%.c=%.o)
RM			= rm -rf
READLINE        = -lreadline 

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(LD) $(OBJS) $(READLINE) -o $(TARGET)
	@printf "LD $(TARGET)\n"

%.o: %.c $(HEADERS)
	@$(CC) -c $(C_FLAGS) $< -o $@ 
	@printf "CC $<\n"

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(TARGET)

re: fclean all

.PHONY: all clean fclean re
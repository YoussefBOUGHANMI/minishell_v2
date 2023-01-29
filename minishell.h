/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:43:41 by pschemit          #+#    #+#             */
/*   Updated: 2023/01/17 20:31:43 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# define CHAR " \t"


typedef struct cmd
{
    char    **list_token;
    int     nb_token;
    int     num_cmd;
    struct cmd     *next;
    struct cmd     *before;
	char			*cmd_path;
	int			fd[2];
	int			top_redir;
	char		**cmd_redir;
	int			fd_in;
	int			fd_out;
	int         redir_in;
	int			redir_out;
}   t_cmd;

typedef struct minishell{
	char		**env;
	char		*prompt;
	char		*cmd;
	char		**list_token;
	int			nb_cmd;
	int			keypipe;
	t_cmd		*list_cmd;
}t_data_mini;


int		ft_strcmp(char *s1, char *s2);
char	ft_mot_command(char *str, int i);
int		verif_quote(char *str, char c, char r);
char	*ft_strchr(const char *s, int c);
void	lexer(t_data_mini *data);
int		ft_parcing_readline(t_data_mini *data);
int		ft_strlen(const char *tab);

char	*skeep_qotes(char *str, char c);
char	**ft_split(const char *s);
void	add_space_pipe(t_data_mini *data);
void	add_space_redir(t_data_mini *data);
int		count_p(char *str);
int		v_quote(char *str, char a, char b);
int		count_redir(char *cmd);
int		verif_redir(char *cmd);
char	*ft_strjoin(char const *s1, char const *s2);

t_cmd	*init_all_cmd(int nb_cmd , char **token_cmd);
int get_nb_cmd(char **token_cmd);
void run_shell(t_data_mini *data);
int	ft_verif_all(t_data_mini *data);
void	supp_char(t_data_mini *data , char c);
int	cmd_empty(char *str);
void	manage_quote_err(t_data_mini *data);
void manage_pipe(t_data_mini *data);

void	ft_command(t_data_mini *data);
void ft_clean_quotes(t_data_mini *data);
char    *get_cmd_path(char **env, char    *cmd);
char   *ft_strjoin_3(char *s1 , char *s2, char *s3);
char	*ft_strcpy(char *dst, const char *src);
void check_leaks();
void    manage_dollar(t_data_mini *data);
char    *ft_strjoin_33(char *s1 , char *s2, char *s3);
void	ft_free_tab(char **tab);
void manage_redir_out(t_cmd *cmd);
int	is_redir(char **list_token);
char	**get_cmd_redir(char **list_token);
void	ft_open_close_pipe_red(t_cmd *cmd , int i , int nb_cmd);
int	check_if_redir(t_data_mini *data);
char	*rl_gets(char *prompt);
void close_all_pipe(t_cmd *cmd , int i);
// int main()
// {
// 	t_data_mini mini;

// 	t_cmd_part a;
// 	t_cmd_part b;
// 	a.next = &b;
// 	b.next = NULL

// }


#endif
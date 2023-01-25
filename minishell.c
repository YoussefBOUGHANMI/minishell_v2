/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:20:02 by pschemit          #+#    #+#             */
/*   Updated: 2023/01/20 19:06:04 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>



void close_all_pipe(t_cmd *cmd , int i){
	int p;
	t_cmd *current;

	p = 0;
	current = cmd;
	while(p <= i )
	{
    	close(current->fd[1]);
    	close(current->fd[0]);
		current = current->before;
		p++;
	}

}

void	ft_open_close_pipe(t_cmd *cmd , int i , int nb_cmd)
{
	if (i == 0 && nb_cmd != 1)
	{
		dup2(cmd->fd[1], 1);
		close_all_pipe(cmd , i);
	}
	else if (i == nb_cmd - 1)
	{
		dup2(cmd->before->fd[0], 0);
		close_all_pipe(cmd , i);
	}
	else
	{
		dup2(cmd->before->fd[0], 0);
		dup2(cmd->fd[1], 1);
		close_all_pipe(cmd , i);
	}
} 

void	ft_run_pipe(t_data_mini *data , int i)
{
	char *arg[] = {data->list_cmd->list_token[0] , NULL};
	ft_open_close_pipe(data->list_cmd , i , data->nb_cmd);
    execve(data->list_cmd->cmd_path, (char *const *)data->list_cmd->list_token , data->env);
}





void    ft_command(t_data_mini *data)
{
    int i = 0;
	int p = 0;
	pid_t pid;
	int fork_error;

    while(i < data->nb_cmd )
    {
		pipe(data->list_cmd->fd);
		pid = fork();
	    if(pid== 0)
		{
			ft_run_pipe(data , i);
		}
		else if (pid < 0)
			fork_error = 1;
        data->list_cmd = data->list_cmd->next;
        i++;
    }
	close_all_pipe(data->list_cmd, i -1 );
    while (waitpid(0, NULL, 0) != -1);
	if(fork_error == 1)
		printf("zsh: fork failed: resource temporarily unavailable\n");
}



char	*rl_gets(char *prompt)
{
	static char	*line_read = (char *) NULL;

	if (line_read)
	{
		free(line_read);
		line_read = (char *) NULL;
	}
	line_read = readline(prompt);

	return (line_read);
}



int		ft_find_path(t_data_mini *data)
{
	int i;

	i=0;
	while(i<data->nb_cmd)
	{
		if(get_cmd_path(data->env, data->list_cmd->list_token[0]) == NULL)
		{
			printf("command not found %s\n" , data->list_cmd->list_token[0]);
			return(0);
		}
		data->list_cmd->cmd_path = get_cmd_path(data->env, data->list_cmd->list_token[0]);
		data->list_cmd = data->list_cmd->next;
		i++;
	}
	return(1);
}



ft_clean_all(t_data_mini *data)
{
	int i = 0;
	t_cmd *current;

	while(i < data->nb_cmd - 1 )
	{
		current = data->list_cmd;
		data->list_cmd = data->list_cmd->next;
		ft_free_tab(current->list_token);
		//free(current->list_token);
		free(current);
		i++;
	}
	ft_free_tab(data->list_cmd->list_token);
	free(data->list_cmd);
	free(data->list_token);
}



void	run_shell(t_data_mini *data)
{
	int i;
	data->cmd = rl_gets(data->prompt);
	add_history(data->cmd);
	if(ft_parcing_readline(data) == 0)
		return;

	data->nb_cmd = get_nb_cmd(data->list_token);
	data->list_cmd = init_all_cmd(data->nb_cmd, data->list_token);
	/*ft_clean_quotes(data);
	
	if(ft_find_path(data) == 1)
		ft_command(data);*/
	ft_clean_all(data);
}

int	main(int ac, char **av, char **env)
{	
	t_data_mini	data;
	
	data.env = env;
	data.prompt = "MonkeyShell >> ";
	
	while (42)
	{
		run_shell(&data);
		//printf("%s", data.result);
	}
	return (0);
}


	// if (line_read && *line_read)data->list_cmd->
	// {
	// add_history(data->cmd);
	// 	ft_command(cmds);
	// }
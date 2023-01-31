/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:29:14 by pschemit          #+#    #+#             */
/*   Updated: 2023/01/29 18:29:58 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int	ft_is_builtin_1(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return(1);
	if (ft_strcmp(cmd, "export") == 0)
		return(1);
	if (ft_strcmp(cmd, "unset") == 0)
		return(1);
	return(0);
}


int	ft_is_builtin_2(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return(1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return(1);
	if (ft_strcmp(cmd, "env") == 0)
		return(1);
	return(0);
}



int	ft_run_builtin_1(t_data_mini *data)
{
	if (ft_strcmp(data->list_cmd->list_token[0], "cd") == 0)
		ft_cd(data);
	if (ft_strcmp(data->list_cmd->list_token[0], "export") == 0)
		ft_export(data);
	if (ft_strcmp(data->list_cmd->list_token[0], "unset") == 0)
		ft_unset(data);
	return (1);
}





int	ft_run_builtin_2(t_data_mini *data)
{
	if (ft_strcmp(data->list_cmd->list_token[0], "env") == 0)
	{
		if (!data->list_cmd->list_token[1])
			ft_env(data->env);
		else
			printf("env: «%s» sans aucune option ni argument \n",\
			data->list_cmd->list_token[1]);
	}
	else if (ft_strcmp(data->list_cmd->list_token[0], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(data->list_cmd->list_token[0], "cd") == 0)
		ft_cd(data);
	else if (ft_strcmp(data->list_cmd->list_token[0], "echo") == 0)
		ft_echo(data);
	else if (ft_strcmp(data->list_cmd->list_token[0], "export") == 0)
	{
		if (data->list_cmd->list_token[1])
			ft_export(data);
		else
			printf("export : probleme argument\n");
	}
	else if (ft_strcmp(data->list_cmd->list_token[0], "unset") == 0)
		ft_unset(data);
	else
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:30:38 by pschemit          #+#    #+#             */
/*   Updated: 2023/01/29 18:36:37 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	*get_var_home(t_data_mini *data)
{
	char	*var_to_check;
	char 	*home;
	int 	i;

	while(data->env[i])
    {
        var_to_check = get_var_to_add(data->env[i]);
        if(ft_strcmp("HOME" , var_to_check) == 0)
		{
			free(var_to_check);
            return(&data->env[i][5]);
		}
        i++;
        free(var_to_check);
    }
	return(NULL);
}

void ft_cd_bis(t_data_mini *data)
{
	char *home;
	int ret;
	char *new_path;
	char *pwd;

	home = get_var_home(data);
	if(home != NULL)
	{
		ret = chdir(home);
		if (ret == -1)
		{
			printf("cd: %s: No such file or directory\n" , home);
			data->dollar = 1;
			return;
		}
		data->dollar = 0;
		pwd = getcwd(NULL, 0);
		new_path = ft_strjoin("PWD=" , pwd);
		
		ft_export_var(data , new_path);
		free(pwd);
		free(new_path);
		return;
	}
	data->dollar = 1;
	printf("cd: HOME not set\n");
}


void ft_cd(t_data_mini *data) 
{
	int ret;
	char *new_path;
	char *pwd;
	char *home;
	
	if(data->list_cmd->list_token[1])
	{
		ret = chdir(data->list_cmd->list_token[1]);
		if (ret == -1)
		{
			printf("cd: %s: No such file or directory\n" , data->list_cmd->list_token[1]);
			data->dollar = 1;
			return;
		}
		data->dollar = 0;
		pwd = getcwd(NULL, 0);
		new_path = ft_strjoin("PWD=" , pwd );
		ft_export_var(data , new_path);
		free(new_path);
		free(pwd);
		return;
	}
	ft_cd_bis(data);
}

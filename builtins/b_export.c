/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:26:09 by pschemit          #+#    #+#             */
/*   Updated: 2023/01/29 17:10:22 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **new_env(t_data_mini *data, char *var)
{
    int i = 0;
    char **new_env;
    while (data->env[i])
        i++;
    new_env = malloc((sizeof(char *))*(i+2));
    i = 0;
    while(data->env[i])
    {
        new_env[i] = data->env[i];
        i++;
    }
    new_env[i] = var;
    new_env[i+1] = 0;
    free(data->env);
    return(new_env);
}


int ft_check_export(t_data_mini *data)
{
	int i;
	char c;

	i = 0;
	if (data->list_cmd->list_token[1][i] >= '0' && data->list_cmd->list_token[1][i] <= '9')
		return(0);
	while(data->list_cmd->list_token[1][i])
	{
		c = (data->list_cmd->list_token[1][i]);
		if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
			|| (c >= '0' && c <= '9') || c == '_' || c == '=')
			;
		else
			return(0);
		i++;
	}
	return(1);
}

int ft_export(t_data_mini *data)
{
    int i = 0;
    char *var;
    int a;

	if (ft_check_export(data) == 0)
	{
		printf("\"%s\": not a valid identifier\n", data->list_cmd->list_token[1]);
		return(0);
	}
    while(data->list_cmd->list_token[1][i] != '=' && data->list_cmd->list_token[1][i])
        i++;
    if(data->list_cmd->list_token[1][i] == '=')
    {
        var = malloc(sizeof(char)* i+1);
        var[i] = '\0';
        i = 0;
        while(data->list_cmd->list_token[1][i] != '=' && data->list_cmd->list_token[1][i])
        {
            var[i] = data->list_cmd->list_token[1][i];
            i++;
        }
        a = ft_search_pwd(data, var);
        if (a != -1)
        {
            free(data->env[a]);
            data->env[a] = data->list_cmd->list_token[1];
        }
        else
            data->env = new_env(data, data->list_cmd->list_token[1]);
    }
	return(1);
}

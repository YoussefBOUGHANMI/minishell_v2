/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:11:21 by pschemit          #+#    #+#             */
/*   Updated: 2023/01/29 17:11:41 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **delete_element_in_dtab(t_data_mini *data, int a)
{
    char **new_env;
    int i;
    int j;
    
    j = 0;
    i = 0;
    while(data->env[i])
        i++;
    new_env = malloc(sizeof(char *) * (i+1));
    i = 0;
    while(data->env[i])
    {
        if (i != a)
        {
            new_env[j] = data->env[i];
            j++;
        }
        i++;
    }
    free(data->env[i]);
    new_env[j] = 0;
    return (new_env);
}


void ft_unset(t_data_mini *data)
{
    char c;
    int i;

    if (data->list_cmd->list_token[1])
    {
        i = ft_search_pwd(data, data->list_cmd->list_token[1]);
        if (i != -1)
        {
            data->env = delete_element_in_dtab(data, i);
        }
    }
}

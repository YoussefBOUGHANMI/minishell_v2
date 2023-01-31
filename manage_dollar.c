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

#include"minishell.h"


int check_is_special(char c)
{
    int tab[] = {32 , 37, 39, 43, 44, 46, 47, 58, 60, 61, 63, 64, 91, 92, 93, 94, 123, 124, 125, 126 , '$'};
    int i = 0;

    while(tab[i])
    {
        if(tab[i] == c)
            return(1);
        i++;
    }
    return(0);
}


char    *get_var(char *cmd , int *i)
{
    char *var;
    int len = 0;
    int ii = 0;

    while(!check_is_special(cmd[len + 1]) && cmd[len + 1])
        len++;

    *i = *i + len;

    var=malloc((len +1) * sizeof(char));
    while(ii < len)
    {
        var[ii] = cmd[ii+1];
        ii++;
    }
    var[ii] = '\0';

    return(var);
}


char *get_new_value(char *var , char **env)
{
    char **tmp_tab;
    int i=0;
    int ii=0;

    while(env[i])
    {
        ii = 0;
        while(var[ii] == env[i][ii])
        {
            if(env[i][ii + 1] == '=' && var[ii + 1] == '\0')
            {
                ii++;
                free(var);
                return(&env[i][ii + 1]);
            }
            ii++;
        }   
        i++;
    }
    free(var);
    return(NULL);
}


char    *ft_strjoin_33(char *s1 , char *s2, char *s3)
{
    char *tmp;
    char *res;
    tmp = ft_strjoin(s1 , s2);
    res = ft_strjoin(tmp , s3);
    free(tmp);
    if(s1)
        free(s1);
    return(res);
}


void initial_vars(int *i , int *ii ,char *new_cmd)
{
    *i = 0;
    *ii = 0;
    new_cmd = NULL;
}


void    manage_dollar(t_data_mini *data)
{
    int i = 0;
    int ii = 0;
    char *new_cmd = NULL;
    char *tmp;
    char *res;

    tmp = malloc((ft_strlen(data->cmd) + 1) * sizeof(char));
    initial_vars(&i , &ii , new_cmd);
    while(data->cmd[i])
    {   
        if(data->cmd[i] == '$' )
        {
            tmp[ii] = '\0';
            ii = 0;
            new_cmd = ft_strjoin_33(new_cmd, tmp , get_new_value(get_var(&data->cmd[i] , &i) , data->env));     
        }
        else
            tmp[ii++] = data->cmd[i];
        i++;
    }
    tmp[ii] = '\0';
    res = ft_strjoin(new_cmd, tmp);
    free(tmp);
    free(new_cmd);
    free(data->cmd);
    data->cmd = res;
}


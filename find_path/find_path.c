/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:43:18 by pschemit          #+#    #+#             */
/*   Updated: 2023/01/21 14:54:03 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words_1(char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup_1(char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split_1(char *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	if (!s || !(split = malloc((count_words_1(s, c) + 1) * sizeof(char *))))
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == strlen(s)) && index >= 0)
		{
			split[j++] = word_dup_1(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

char	**ft_test_1(char **env)
{
	char	*path;
	char	**path2;
	int		i;
	int		j;
	int		a;

	a = 0;
	j = 0;
	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'\
		&& env[i][3] == 'H' && env[i][4] == '=')
		{
			j = strlen(env[i]) - 5;
			path = malloc(sizeof(char) * j +1);
			j = 5;
			while (env[i][j++])
				path[a++] = env[i][j];
			path2 = ft_split_1(path, ':');
			free(path);
			return (path2);
		}
		i++;
	}
	return (NULL);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}


char    *ft_strjoin_3(char *s1 , char *s2, char *s3)
{
    char *tmp;
    char *res;
    tmp = ft_strjoin(s1 , s2);
    res = ft_strjoin(tmp , s3);
    free(tmp);
    return(res);
}


char    *get_cmd_path(char **env, char    *cmd)
{
    char    **ev;
    char    *path;
    int     result;
    int     i;
    i = 0;
    ev = ft_test_1(env);
    while (ev[i])
    {
        path = ft_strjoin_3(ev[i] , "/", cmd);
        result = access(path, F_OK);
        if (result == 0)
        {
            ft_free_tab(ev);
            return(path);
        }
        i++;
        free(path);
    }
    ft_free_tab(ev);
    return (NULL);
}


char	*check_abs_path(char *str)
{
	char	**chemin;
	int i;

	i = 0;
	chemin = ft_split_1(str, '/');
	while(chemin[i])
		i++;
	if(ft_is_builtin_1(chemin[i-1]) == 1 || ft_is_builtin_2(chemin[i-1]))
	{
		ft_free_tab(chemin);
		return(NULL);
	}
	ft_free_tab(chemin);
	if(access(str, F_OK) == 0)
		return(str);
	return(NULL);
}
int		ft_find_path(t_data_mini *data)
{
	int	i;

	i = 0;
	while (i<data->nb_cmd)
	{
		if(ft_strchr(data->list_cmd->list_token[0] , '/'))
		{
		 	data->list_cmd->cmd_path = check_abs_path(data->list_cmd->list_token[0]);
			data->list_cmd->top_path = 0;
		}
		else 
		{
			data->list_cmd->cmd_path = get_cmd_path(data->env, data->list_cmd->list_token[0]);
			data->list_cmd->top_path = 1;
		}
		if (data->list_cmd->cmd_path == NULL && ft_is_builtin_1(data->list_cmd->list_token[0]) != 1 && ft_is_builtin_2(data->list_cmd->list_token[0]) != 1)
		{
			printf("command not found %s\n" , data->list_cmd->list_token[0]);
			data->dollar = 127;
			return (0);
		}
		data->list_cmd = data->list_cmd->next;
		i++;
	}
	return (1);
}

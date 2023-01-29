/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:49:17 by pschemit          #+#    #+#             */
/*   Updated: 2023/01/17 19:33:36 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void drop_quotes(char *str)
{
	char *str_copie;

	str_copie = malloc(ft_strlen(str) + 1);
	strcpy(str_copie , str);
	int i = 0;
	int ii = 0;
	char c;
	while(str_copie[i])
	{
		if(str_copie[i] == '\'' || str_copie[i] == '\"')
		{
			c = str_copie[i++];
			while(str_copie[i] != c && str_copie[i])
				str[ii++]=str_copie[i++];
			i++;
		}
		else 
			str[ii++]=str_copie[i++];
	}
	str[ii] = 0;
	free(str_copie);
}

void ft_clean_quotes(t_data_mini *data)
{
	int i = 0;
	int ii;

	while(i++<data->nb_cmd)
	{
		ii = 0;
		if(ft_strcmp(data->list_cmd->list_token[ii] , "\"\"") == 0 || 
				ft_strcmp(data->list_cmd->list_token[ii] , "\'\'") == 0 )
		{
			data->list_cmd->list_token[ii] = malloc(20);
			data->list_cmd->list_token[ii++] = " ";
		}
		while(data->list_cmd->list_token[ii])
			drop_quotes(data->list_cmd->list_token[ii++]);
		data->list_cmd = data->list_cmd->next;
	}
}


/*
int main(int argc , char **argv)
{
	char test[] =   '"l""''s"""';
	printf("%s \n" , test);  //argv[1];
	drop_quotes(test);
	printf("%s \n" , test);
}*/
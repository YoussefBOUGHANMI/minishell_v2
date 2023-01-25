/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_manage_quote_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:42:26 by pschemit          #+#    #+#             */
/*   Updated: 2023/01/15 16:31:15 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	manage_quote_err(t_data_mini *data)
{
	static char	*suite = (char *) NULL;
	char	*new_cmd;

	if (suite)
	{
		free(suite);
		suite = (char *) NULL;
	}
	if (data->keypipe == 1)
		suite = readline("pipe quote>");
	else
		suite = readline("quote>");
	new_cmd = ft_strjoin_3(data->cmd , "\n" , suite);
	free(data->cmd);
	data->cmd = new_cmd;
}

void manage_pipe(t_data_mini *data)
{
	static char	*suite = (char *) NULL;
	char *new_cmd;

	if (suite)
	{
		free(suite);
		suite = (char *) NULL;
	}
	suite = readline("pipe>");
	new_cmd= ft_strjoin(data->cmd, suite);
	free(data->cmd);
	data->cmd = new_cmd;
	data->keypipe = 1;
}
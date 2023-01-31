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


void ft_cd(t_data_mini *data) 
{
	int ret;
	
	if(data->list_cmd->list_token[1])
	{
		ret = chdir(data->list_cmd->list_token[1]);
		if (ret == -1)
		{
			printf("cd: %s: No such file or directory" , data->list_cmd->list_token[1]);
			data->dollar = 1;
		}
		data->dollar = 0;
		return;
	}
	ret = chdir(data->home);
	data->dollar = 0;
}

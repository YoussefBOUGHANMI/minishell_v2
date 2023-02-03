/* ************************************************************************** */
/*																								*/
/*																	  :::		 ::::::::   */
/*   b_echo.c														  :+:	 :+:	 :+:   */
/*																  +:+ +:+			+:+		*/
/*   By: pschemit <pschemit@student.42.fr>			+#+  +:+		   +#+		  */
/*															+#+#+#+#+#+   +#+			*/
/*   Created: 2023/01/29 13:18:27 by pschemit			 #+#	#+#				 */
/*   Updated: 2023/01/29 13:18:49 by pschemit			###   ########.fr	  */
/*																								*/
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(t_data_mini *data)
{
	int i;
	
	i = 1;
	if (data->list_cmd->list_token[i])
	{
		while(data->list_cmd->list_token[i])
		{
				if (i != 1 || ft_strcmp(data->list_cmd->list_token[1], "-n") != 0)
				{
						printf("%s", data->list_cmd->list_token[i]);
						if (data->list_cmd->list_token[i+1])
								printf(" ");
				}
				i++;
		}
		if (ft_strcmp(data->list_cmd->list_token[1], "-n") != 0)
				printf("\n");
	}
	else
		printf("\n");
	exit(0);
}
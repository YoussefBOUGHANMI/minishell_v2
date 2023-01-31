/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:20:29 by pschemit          #+#    #+#             */
/*   Updated: 2023/01/15 16:24:13 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	ft_parcing_readline(t_data_mini *data)
{
	int	status;
	char *cmd;

	data->keypipe = 0;
	cmd = malloc((ft_strlen(data->cmd) + 1) * sizeof(char));
	ft_strcpy(cmd , data->cmd);
	data->cmd = cmd;
	status = ft_verif_all(data);
	while (status == 1)
		status = ft_verif_all(data);
	if (status == 0)
		return (0);
	supp_char(data , '\t');
	supp_char(data , ';');
	supp_char(data , '\\');
	manage_dollar(data);
	lexer(data);
	return (1);

}

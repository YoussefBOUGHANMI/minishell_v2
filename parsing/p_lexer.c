/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:24:29 by pschemit          #+#    #+#             */
/*   Updated: 2023/01/14 16:02:44 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	lexer(t_data_mini *data)
{
	int	i;

	i = 0;
	add_space_pipe(data);
	add_space_redir(data);
	data->list_token = ft_split(data->cmd);
	free(data->cmd);
}

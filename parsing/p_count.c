/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_count.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:22:50 by pschemit          #+#    #+#             */
/*   Updated: 2023/01/14 15:58:52 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	count_p(char *str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			nb++;
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				i++;
		}
		i++;
	}
	return (nb);
}

int	count_redir(char *cmd)
{
	int		nb;
	char	q;

	nb = 0;
	while (*cmd)
	{
		if (*cmd == '\'' || *cmd == '\"')
		{
			q = *cmd;
			cmd++;
			while (*cmd != q)
				cmd++;
		}
		if (*cmd == '>' || *cmd == '<')
		{
			q = *cmd;
			while (*cmd == q)
				cmd++;
			nb++;
			cmd--;
		}
		cmd++;
	}
	return (nb);
}

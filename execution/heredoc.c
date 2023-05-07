/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:15:40 by met-tahe          #+#    #+#             */
/*   Updated: 2023/03/31 18:15:42 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
	// while(i <= pip_count)
	// {
	// 	fd[i] = malloc(sizeof(int) * 2);
	// 	i++;
	// }
	// i = 0;
	// while (i <= pip_count)
	// {
	// 	if (pipe(fd[i]) < 0)
	// 		fct_error("pipe");
	// 	i++;
	// }
char	*heredoc(char **herdoc)
{
	char	*s;
	int		i;
	char	*reading;
	//char *l;
	i = 0;
	reading= NULL; 
	while (herdoc && herdoc[i])
	{
		s = readline("> ");
		if(reading!=NULL)
		{
				free(reading);
				reading = NULL;
		}
		while (s)
		{
			
			if (ft_strcmp(s, herdoc[i]) == 0)
			{
				free(s);
				break ;
			}
		//	if (herdoc[i + 1] == NULL)
			//{
				reading = ft_strjoin(reading, s);
				
				reading = ft_strjoin(reading, "\n");
				free(s);
			//}
			s = readline("> ");
		}
		i++;
	}
	return (reading);
}
// char	**heredoc_exe(t_cmd *tmp)
// {
// 	int	i;

// 	i = 0;
// 	while (tmp->herdoc[i])
// 	{

// 	}
// }

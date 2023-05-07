#include"../minishell.h"

void	ctrlc_handler(int sig)
{
	int	i;

	i = 0;
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	while (i <= my_global->count_cmd)
	{
		if (my_global->id[i] != 0)
			kill(my_global->id[i], SIGINT);
		i++;
	}
	if (my_global->hrd_id != 0)
	{
		my_global->status = 1;
		//write(1, "heredoc> ", 9);
		kill(my_global->hrd_id, SIGINT);
	}
}

void	ctrld_handler(int sig)
{
	int	i;

	(void)sig;
	i = 0;
	if (my_global->hrd_id != 0)
		rl_on_new_line();
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (my_global->id)
	{
		while (my_global->id[i])
		{
			kill(my_global->id[i], SIGQUIT);
			i++;
		}
	}
}

void	sig_sil(int sig)
{
	(void)sig;
	rl_on_new_line();
	//rl_redisplay();
	return ;
}


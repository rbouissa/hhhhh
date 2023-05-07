



#include "minishell.h"

int	is_allpha1(char s)
{
	if ((s >= 65 && s <= 90) || (s >= 97 && s <= 122))
		return (1);
	return (0);
}

int	is_digit1(char s)
{
	if ((s >= 48 && s <= 57))
		return (1);
	return (0);
}

int	find_spliter1(char s, char *sp)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (sp[i])
	{
		if (s == sp[i]||(!is_digit1(s)&&!is_allpha1(s)))
			return (1);
		i++;
	}
	return (0);
}
char *get_it_witout_$(char *str)
{
	char	*var;
	int		i;
	int		j;

	i = 1;
	j = 0;
	var = malloc(ft_strlen(str));
	while (str[i])
	{
		var[j] = str[i];
		i++;
		j++;
	}
	var[j] = 0;
	return (var);
}

char	*finnd_valeur(t_mini *env, char *str)
{
	t_mini	*tmp_env;

	//char	*valeur;
	tmp_env = env;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->data_var, str))
		{
			return (tmp_env->data_val);
		}
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

// char	*full_string(t_mini *env, char *str)
// {
// 	char	*string;
// 	char	*var;
// 	int		i;

// 	i = 0;
// 	while (str[i] && str[i] != '$')
// 	{
// 		string[i] = str[i];
// 		i++;
// 	}
// 	if (str[i] == '$')
// 	{
// 		while (str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != ' '
// 			&& str[i] != '\t')
// 		{
// 			var[i] = str[i];
// 			i++;
// 		}
// 	}
// 	var[i] string = malloc(ft_strlen(str))
// }

char	*ft_expand(char *str, t_mini *expand, int start)
{
	char	*after;
	char	*before;
	char	*var;
	char	*valeur;
	char	*full_string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	after = NULL;
	before = NULL;
	var = NULL;
	valeur = NULL;
	before = malloc(start);
	while (i < start - 1)
	{
		before[i] = str[i];
		i++;
	}
	before[i] = '\0';
	i = 0;
	while (!find_spliter1(str[start + i], "|>< \t\n\'\""))
		i++;
	var = malloc(i + 1);
	i = 0;
	while (!find_spliter1(str[start + i], "|>< \t\n\'\""))
	{
		var[i] = str[start + i];
		i++;
	}
	var[i] = '\0';
	valeur = finnd_valeur(expand, var);
    // if(valeur==NULL)
    //     valeur=var;
	j = 0;
	// printf("%c\n",str[start+i+j]);
	while (str[start + i + j])
		j++;
	after = malloc(j + 1);
	j = 0;
	while (str[start + i])
	{
		after[j] = str[start + i];
		i++;
		j++;
	}
	after[j] = '\0';
	// printf(">%s\n",before);
	// printf(">%s\n",valeur);
	//printf(">%s\n",after);
	full_string = ft_strjoin(before, valeur);
	if (after[0] == 0)
	{
		//printf("oioioi\n");
		return (full_string);
	}
	else
	{
		//  printf("%s\n",after);
		//printf("oioioi\n");
		full_string = ft_strjoin(full_string, after);
		//printf(">>%s\n",full_string);
		//printf("")
	}
	return (full_string);
}

char	*exp_hoho(char *str, t_mini *expand)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i+1])
		{
			i++;
			str = ft_expand(str, expand, i);
		}
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*handle_quotes(char *str, t_mini *env)
{
	int quotes;
	char *buffer;
	int i;
	int k;
	quotes = no_quotes;
	buffer = NULL;
	(void)env;
	k = 0;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && quotes == no_quotes)
			quotes = isingle_quotes;
		else if (str[i] == '\"' && quotes == no_quotes)
			quotes = idouble_quotes;
		else if (str[i] == '\"' && quotes == idouble_quotes)
			quotes = no_quotes;
		else if (str[i] == '\'' && quotes == isingle_quotes)
			quotes = no_quotes;
		if (str[i] == '$' && quotes != isingle_quotes)
		{
			//printf("hhhhh\n");
			buffer = exp_hoho(str, env);
			k++;
		}
		i++;
	}
	//printf("%d\n", quotes);
	if (quotes == idouble_quotes || quotes == isingle_quotes)
	{
		ft_write("syntax error exepected quote");
		return (NULL);
	}
	else if (k)
		return (buffer);
	else
		return (str);
}
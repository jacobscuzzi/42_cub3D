/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:59:56 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/10 14:59:45 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	wordcount(char const *str, char c)
// {
// 	int	mode;
// 	int	counter;
// 	int	i;

// 	mode = 0;
// 	counter = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			mode = 0;
// 		if (str[i] != 0)
// 		{
// 			if (mode == 0)
// 				counter += 1;
// 			mode = 1;
// 		}
// 		i++;
// 	}
// 	printf("counter: %d\n", counter);
// 	return (counter);
// }

int	wordcount(char const *str, char c)
{
	char const	*tmp;
	int			counter;

	tmp = str;
	counter = 0;
	while (*tmp)
	{
		while (*tmp && *tmp == c)
			tmp++;
		if (*tmp == '\0')
			break ;
		while (*tmp && *tmp != c)
			tmp++;
		counter++;
	}
	return (counter);
}

int	len_next_word(char const *str, int i, char c)
{
	int	counter;

	counter = 0;
	while (str[i] != c && str[i] != 0)
	{
		counter++;
		i++;
	}
	return (counter);
}

char	*word_dupl(char const *str, char c, int i)
{
	int		k;
	int		size;
	char	*word;

	k = 0;
	size = len_next_word(str, i, c);
	word = (char *)malloc(sizeof(char) * (size + 1));
	if (!word)
		return (0);
	while (k < size)
	{
		word[k] = str[i + k];
		k++;
	}
	word[k] = '\0';
	return (word);
}

void	ft_free(char **table, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(table[i++]);
	free(table);
}

char	**ft_split(char const *s, char c)
{
	char	**table;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = wordcount(s, c);
	table = (char **)malloc(((size + 1) * sizeof(char *)));
	if (!table)
		return (0);
	while (j < size && s[i])
	{
		if (s[i] != c)
		{
			table[j] = word_dupl(s, c, i);
			if (!table[j])
				return (ft_free(table, j), NULL);
			i += len_next_word(s, i, c);
			j++;
		}
		i++;
	}
	table[size] = 0;
	return (table);
}
/*
int	main(int argc, char **argv)
{
	// int		i;
	// char	**table;

	// i = 0;
	// if	(argc == 3)
	// {
	// 	table = ft_split(argv[1], argv[2]);
	// 	while (table[i] != 0)
	// 	{
	// 		printf("%s\n", table[i]);
	// 		i++;
	// 	}
	// }

		(void)argc;
		(void)argv;
        char *s = "xxxxxxxxhello!";

        char **result = ft_split(s, 'x');
        while (*result)
        {
			printf("|%s|\n", *result);

            result++;
        }

	int i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);

}
*/

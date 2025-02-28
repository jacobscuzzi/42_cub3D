/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:34:22 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/09/20 18:22:28 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trim_mem(char *mem, int finder)
{
	char	*new;

	if (finder == -1 || finder == 0)
	{
		free(mem);
		mem = NULL;
		return (NULL);
	}
	if ((int)ft_strlen(mem) > finder)
		new = ft_strdup(mem + finder);
	else
		new = ft_strdup("");
	if (!new)
	{
		free(mem);
		mem = NULL;
		return (NULL);
	}
	free(mem);
	mem = NULL;
	return (new);
}

int	fill_mem(int fd, int *finder, char **mem, int cursor)
{
	char	*buf;
	char	*temp;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	while (*finder == -1 && cursor != 0)
	{
		cursor = read(fd, buf, BUFFER_SIZE);
		if (cursor == 0)
		{
			*finder = ft_strlen(*mem);
			break ;
		}
		buf[cursor] = '\0';
		temp = ft_strjoin(*mem, buf);
		if (!temp)
			return (free(buf), -1);
		if (*mem)
			free(*mem);
		*mem = temp;
		*finder = ft_strchr_pos(*mem, '\n');
	}
	free(buf);
	return (*finder);
}

char	*free_str(char **str)
{
	free (*str);
	*str = NULL;
	return (NULL);
}

char	*fill_line(int finder, char **mem)
{
	char		*line;

	line = ft_substr(*mem, 0, finder);
	if (!line)
		return (NULL);
	*mem = trim_mem(*mem, finder);
	if (!*mem)
		return (free(line), NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*mem;
	int			finder;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (mem)
			free (mem);
		return (NULL);
	}
	if (!mem)
		mem = ft_strdup("");
	if (!mem)
		return (NULL);
	finder = ft_strchr_pos(mem, '\n');
	if (fill_mem(fd, &finder, &mem, -1) == -1)
	{
		if (mem)
			free(mem);
		mem = NULL;
		return (NULL);
	}
	if (ft_strlen(mem) == 0)
		return (free_str(&mem));
	return (fill_line(finder, &mem));
}

// int	main(void)
// {
// 	int	fd;
// 	// char *line;

// 	//fd = open("./files/multiple_nl.txt", O_RDONLY);
// 	fd = open("test.txt", O_RDONLY);

// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	printf("Return: |%s|", get_next_line(fd));
// 	printf("Return: |%s|", get_next_line(fd));
// 	close(fd);
// 	fd = open("test.txt", O_RDONLY);
// 	printf("Return: |%s|", get_next_line(fd));
// 	printf("Return: |%s|", get_next_line(fd));

// 	// while ((line = get_next_line(fd)) != NULL)
// 	// {
// 	// 	printf("Return: |%s|", line);
// 	// 	free(line);
// 	//	}
// 	close(fd);
// 	return (0);
// }

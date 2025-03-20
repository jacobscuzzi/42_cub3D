/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:35:27 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/20 19:14:42 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n') 
		i++;
	return (i);
}

/*
int	main(int argc, char **argv)
{
	if (argc == 2)
		printf("%zu", ft_strlen(argv[1]));
}
*/

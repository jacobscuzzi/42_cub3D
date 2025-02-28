/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:57:26 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/09/17 22:57:27 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dup;
	size_t	size;

	i = 0;
	size = ft_strlen(s1);
	dup = (char *) malloc(size + 1);
	if (!dup)
		return (0);
	while (i < size)
	{
		dup [i] = s1[i];
		i++;
	}
	dup [i] = '\0';
	return (dup);
}

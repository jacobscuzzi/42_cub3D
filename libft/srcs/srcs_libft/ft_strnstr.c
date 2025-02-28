/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:55:14 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/06 16:50:07 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *ned, size_t len)
{
	size_t	i;
	size_t	j;
	char	*first;

	i = 0;
	j = 0;
	if (!*ned)
		return ((char *)str);
	while (i < len && str[i])
	{
		if (str[i] == ned[j])
		{
			first = (char *)str + i;
			while (str[i + j] == ned[j] && i + j < len && str[i + j])
				j++;
			if (ned[j] == '\0')
				return (first);
			j = 0;
		}
		i++;
	}
	return (NULL);
}

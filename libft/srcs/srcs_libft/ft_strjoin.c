/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:59:02 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/07 16:04:54 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*cat;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	cat = (char *)malloc(len1 + len2 + 1);
	i = 0;
	if (!cat)
		return (NULL);
	while (i < len1)
	{
		cat[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		cat[i] = s2[i - len1];
		i++;
	}
	cat[i] = '\0';
	return (cat);
}

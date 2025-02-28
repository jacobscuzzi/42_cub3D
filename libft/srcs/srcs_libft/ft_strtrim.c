/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:59:23 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/26 18:42:04 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	len = ft_strlen(s1);
	j = len;
	while (ft_strchr(set, s1[i]) != NULL)
		i++;
	while (ft_strchr(set, s1[j]) != NULL)
		j--;
	return (ft_substr(s1, i, j - (i - 1)));
}

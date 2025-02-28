/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:50:20 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/05 21:24:37 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	a;
	char	*last;

	a = (char)c;
	i = 0;
	last = NULL;
	while (s[i])
	{
		if (s[i] == a)
			last = (char *)s + i;
		i++;
	}
	if (a == 0)
		last = (char *)s + i;
	return (last);
}

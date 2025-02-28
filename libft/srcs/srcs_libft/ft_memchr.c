/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:53:45 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/06 16:51:36 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	*b;

	a = (unsigned char)c;
	i = 0;
	b = (unsigned char *)s;
	while (i < n)
	{
		if (*(b + i) == a)
			return ((void *)(b + i));
		i++;
	}
	return (NULL);
}

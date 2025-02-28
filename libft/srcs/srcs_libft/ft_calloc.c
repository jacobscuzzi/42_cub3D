/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:57:02 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/07 12:24:35 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*cache;
	size_t			i;

	i = 0;
	cache = malloc(count * size);
	if (!cache)
		return (0);
	while (i < count * size)
		cache[i++] = 0;
	return (cache);
}

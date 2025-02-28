/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:49:12 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/05 09:47:27 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*i;

	i = dest;
	if (!dest && !src)
		return (dest);
	while (n > 0)
	{
		*(unsigned char *)i++ = *(unsigned char *)src++;
		n--;
	}
	return (dest);
}

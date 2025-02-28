/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:13:56 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/05 09:42:40 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	void	*i;

	i = s;
	while (n > 0)
	{
		*(unsigned char *)s = (unsigned char)c;
		n--;
		s++;
	}
	return (i);
}

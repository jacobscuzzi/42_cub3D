/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:37:51 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/05 09:44:10 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*desti;
	char	*srci;
	size_t	counter;

	desti = (char *) dest;
	srci = (char *) src;
	counter = 0;
	if (!dest && !src)
		return (dest);
	if (dest > src)
	{
		while (n-- > 0)
			desti[n] = srci[n];
	}
	else
	{
		while (counter++ < n)
			*desti++ = *srci++;
	}
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
	char	src[] = "abcde";
	memmove(src + 2, src, 3);
	printf("neuer String: %s", src);
}
*/

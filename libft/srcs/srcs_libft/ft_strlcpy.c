/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:36:08 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/05 21:05:20 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (siz == 0)
		return (len);
	if (siz > len)
	{
		while (i < len)
		{
			dst[i] = src[i];
			i++;
		}
	}
	else
	{
		while (i < siz - 1)
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (len);
}

/*
#include <stdio.h>

int main(int argc, const char *argv[])
{
	char	*dest;
	size_t	i;

	i = 0;
	if (argc == 3)
	{
		dest = (char *)malloc(atoi(argv[2]) * sizeof(const char));
		i = ft_strlcpy(dest, argv[1], atoi(argv[2]));
		printf("Dest: %s SrcSize: %zu", dest, i);
	}
	return 0;
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:14:14 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/07/23 15:10:34 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	len_dst;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_dst >= siz)
		len_dst = siz;
	if (siz == len_dst)
		return (siz + len_src);
	if (len_src < siz - len_dst)
		ft_memcpy(dst + len_dst, src, len_src + 1);
	else
	{
		ft_memcpy(dst + len_dst, src, siz - len_dst - 1);
		dst[siz - 1] = '\0';
	}
	return (len_dst + len_src);
}
/*
int	main(int argc, char const *argv[])
{
	if argc == 4
	{

	}
	return 0;
}
*/

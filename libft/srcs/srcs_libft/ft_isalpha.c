/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:17:49 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/05 21:02:56 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (c < 'A' || c > 'z')
		return (0);
	if (c > 'Z' && c < 'a')
		return (0);
	else
		return (1);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc == 2)
		printf("%d", ft_isalpha(*argv[1]));
}
*/

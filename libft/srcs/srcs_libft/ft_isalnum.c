/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:52:16 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/04 20:29:07 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
#include <stdlib.h>
int	main(int argc, char **argv)
{
	if (argc == 2)
		printf("%d", ft_isalnum(atoi(argv[1])));
}
*/

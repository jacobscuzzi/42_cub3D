/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:18:38 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/04 20:31:36 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c < 32 || c > 126)
		return (0);
	else
		return (1);
}
/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc == 2)
		printf("%d", ft_isprint(*argv[1]));
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:45:56 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/04 20:29:05 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
/*still gotta check if int c is right (does not work with main)
*/
{
	if (c > -1 && c < 128)
		return (1);
	else
		return (0);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 2)
		printf("%d", ft_isascii(atoi(*argv[1])));
}
*/

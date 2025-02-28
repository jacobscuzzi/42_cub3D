/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:48:44 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/20 18:05:35 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdlib.h>
#include <unistd.h>

void	hex_text(unsigned int n, char *hex)
{
	write(1, &hex[n], 1);
}

int	ft_putnbr_hex(unsigned int n, int size)
{
	int		counter;

	counter = 0;
	if (n >= 16)
		counter += ft_putnbr_hex(n / 16, size);
	if (size == 0)
		hex_text(n % 16, "0123456789abcdef");
	if (size == 1)
		hex_text(n % 16, "0123456789ABCDEF");
	counter++;
	return (counter);
}
/*
#include <stdlib.h>
int	main(int argc, char **argv)
{
	if (argc == 3)
		ft_putnbr_base(atoi(argv[1]), argv[2]);
}
*/

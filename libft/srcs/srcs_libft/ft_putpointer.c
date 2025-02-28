/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:16:42 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/25 17:02:04 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putadr_hex(unsigned long long n)
{
	int		counter;

	counter = 0;
	if (n >= 16)
		counter += ft_putadr_hex(n / 16);
	hex_text(n % 16, "0123456789abcdef");
	counter++;
	return (counter);
}

int	ft_putpointer(unsigned long long pointer)
{
	unsigned long long	adress;
	int					counter;

	if (pointer == 0)
	{
		counter = ft_putstr("(nil)");
		return (counter);
	}
	counter = ft_putstr("0x");
	adress = pointer;
	counter += ft_putadr_hex(adress);
	return (counter);
}

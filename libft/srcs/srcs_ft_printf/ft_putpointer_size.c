/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:16:42 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/08/13 19:14:53 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_putadr_hex_size(unsigned long long n)
{
	int		counter;

	counter = 0;
	if (n >= 16)
		counter += ft_putadr_hex_size(n / 16);
	hex_text(n % 16, "0123456789abcdef");
	counter++;
	return (counter);
}

int	ft_putpointer_size(unsigned long long pointer)
{
	unsigned long long	adress;
	int					counter;

	if (pointer == 0)
	{
		counter = ft_putstr_size("(nil)");
		return (counter);
	}
	counter = ft_putstr_size("0x");
	adress = pointer;
	counter += ft_putadr_hex_size(adress);
	return (counter);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_uns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:05:22 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/25 17:11:04 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_uns(unsigned int n)
{
	long	nbr;
	int		counter;

	counter = 0;
	nbr = n;
	if (nbr > 9)
		counter += ft_putnbr_uns(nbr / 10);
	ft_putchar((nbr % 10) + 48);
	counter++;
	return (counter);
}

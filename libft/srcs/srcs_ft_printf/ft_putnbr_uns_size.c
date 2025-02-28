/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_uns_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:05:22 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/08/13 19:12:38 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_putnbr_uns_size(unsigned int n)
{
	long	nbr;
	int		counter;

	counter = 0;
	nbr = n;
	if (nbr > 9)
		counter += ft_putnbr_uns_size(nbr / 10);
	counter += ft_putchar_size((nbr % 10) + 48);
	return (counter);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:47:46 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/08/13 19:14:43 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_putnbr_size(int n)
{
	long	nbr;
	int		counter;

	counter = 0;
	nbr = n;
	if (nbr < 0)
	{
		counter += ft_putchar_size('-');
		nbr *= -1;
	}
	if (nbr > 9)
		counter += ft_putnbr_size(nbr / 10);
	counter += ft_putchar_size((nbr % 10) + 48);
	return (counter);
}

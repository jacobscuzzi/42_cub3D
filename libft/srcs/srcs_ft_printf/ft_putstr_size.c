/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 23:32:21 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/08/13 19:15:13 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_size(char *str)
{
	int	i;
	int	counter;

	if (str == 0)
	{
		counter = ft_putstr_size("(null)");
		return (counter);
	}
	i = 0;
	counter = 0;
	while (str[i])
		counter += ft_putchar_size(str[i++]);
	return (counter);
}
/*
int main(int argc, char *argv[])
{
	if (argc == 2)
		ft_putstr(argv[1]);
	return 0;
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:35:36 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/08/13 19:08:30 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	arg_print(char c, va_list	arguments)
{
	int	counter;

	counter = 1;
	if (c == '%')
		counter = ft_putchar_size('%');
	if (c == 'c')
		counter = ft_putchar_size(va_arg(arguments, int));
	if (c == 's')
		counter = ft_putstr_size(va_arg(arguments, char *));
	if (c == 'p')
		counter = ft_putpointer_size(va_arg(arguments, unsigned long long));
	if (c == 'd')
		counter = ft_putnbr_size(va_arg(arguments, int));
	if (c == 'i')
		counter = ft_putnbr_size(va_arg(arguments, int));
	if (c == 'u')
		counter = ft_putnbr_uns_size(va_arg(arguments, unsigned int));
	if (c == 'x')
		counter = ft_putnbr_hex_size(va_arg(arguments, unsigned int), 0);
	if (c == 'X')
		counter = ft_putnbr_hex_size(va_arg(arguments, unsigned int), 1);
	return (counter);
}

int	ft_printf(const char *text, ...)
{
	int		counter;
	int		i;
	va_list	arguments;

	if (text == NULL)
		return (-1);
	va_start(arguments, text);
	counter = 0;
	i = 0;
	while (text[i])
	{
		if (text[i] == '%')
		{
			i++;
			counter += arg_print(text[i], arguments);
		}
		else
			counter += ft_putchar_size(text[i]);
		i++;
	}
	va_end (arguments);
	return (counter);
}

// #include <stdio.h>

// int	main(void)
// {

// 	printf("My: %d Real: %d", ft_printf("hello test %"),
//printf("hello test %"));
// 	int	i = 10;
// 	int	*s = NULL;

// 	ft_printf("test, %%, %c, %s, %p, %d, %i, %u, %x, %X, \n", 'c', "hello",
// 	(void *)s, 10, 100, 1000000, 500, 500);
// 	printf("Return_Number is %d\nReal Number is %d",
// 	ft_printf("test, %%, %c, %s, %p, %d, %i, %u, %x, %X, \n", 'c', "hello",
// 	(void *)s, 10, 100, 1000000, 500, 500),
// 	printf("test, %%, %c, %s, %p, %d, %i, %u, %x, %X, \n", 'c', "hello",
// 	(void *)s, 10, 100, 1000000, 500, 500));
// 	return (0);
// }

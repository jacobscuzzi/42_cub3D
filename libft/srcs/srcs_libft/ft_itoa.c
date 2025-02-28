/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:00:32 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/06/08 14:35:08 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_fill(char *arg, long n, int size)
{
	int				i;

	i = size;
	arg[i--] = '\0';
	if (n < 0)
	{
		n = n * -1;
		while (i > 0)
		{
			arg[i--] = (n % 10) + 48;
			n = n / 10;
		}
		arg[0] = '-';
	}
	else
	{
		while (i >= 0)
		{
			arg[i--] = (n % 10) + 48;
			n = n / 10;
		}
	}
	arg[size] = '\0';
}

char	*ft_itoa(int n)
{
	int		size;
	long	dec;
	char	*arg;
	long	nbr;

	nbr = (long) n;
	dec = 10;
	size = 1;
	while (nbr / dec != 0)
	{
		dec *= 10;
		size++;
	}
	if (nbr < 0)
		size = size + 1;
	arg = (char *)malloc(size + 1);
	if (!arg)
		return (NULL);
	ft_fill(arg, nbr, size);
	return (arg);
}

/*
int	main(int argc, char **argv)
{
	if (argc == 2)
		printf("%s", ft_itoa(atoi(argv[1])));
	return (0);
}
*/

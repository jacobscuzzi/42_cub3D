/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:25:27 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/08/13 19:09:43 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int		ft_putchar_size(int a);
int		ft_putnbr_size(int n);
int		ft_putstr_size(char *str);
int		ft_putnbr_hex_size(unsigned int n, int size);
void	hex_text(unsigned int n, char *hex);
int		ft_putpointer_size(unsigned long long pointer);
int		ft_printf(const char *text, ...);
int		ft_putnbr_uns_size(unsigned int n);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:02:12 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/07/20 15:07:03 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	counter;

	counter = 1;
	if (!lst)
		return (0);
	if (lst->next != NULL)
		counter = 1 + ft_lstsize(lst->next);
	return (counter);
}

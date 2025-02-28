/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:05:40 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/07/20 17:12:35 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ls;
	t_list	*tmp;

	ls = *lst;
	while (ls)
	{
		tmp = ls->next;
		ft_lstdelone(ls, del);
		ls = tmp;
	}
	*lst = NULL;
}

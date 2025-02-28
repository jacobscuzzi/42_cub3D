/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:07:19 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/07/20 17:57:53 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*mem;

	if (!lst || !f || !del)
		return (0);
	mem = NULL;
	new = ft_lstnew((f)(lst->content));
	if (!new)
		return (0);
	mem = new;
	lst = lst->next;
	while (lst)
	{
		new->next = ft_lstnew((f)(lst->content));
		if (!new->next)
		{
			ft_lstclear(&mem, del);
			return (0);
		}
		new = new->next;
		lst = lst->next;
	}
	new->next = NULL;
	return (mem);
}

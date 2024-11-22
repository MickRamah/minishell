/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:40:41 by zramahaz          #+#    #+#             */
/*   Updated: 2024/03/07 10:49:02 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/*
l'adresse de <new->next> va etre l'adresse du 1er element;
et le 1er element va etre new car <*lst> = <new> ce qui veux 
dire que l'adresse de <new> sera affecte a l'adresse de <lst>
*/

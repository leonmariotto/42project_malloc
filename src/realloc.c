/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 09:51:16 by lmariott          #+#    #+#             */
/*   Updated: 2020/09/15 08:56:09 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** CHANGE FOR OPTI :
** if (size <= (size_t)(a_head->end - a_head->start)
** 		|| (!a_head->next && (size_t)(z_head->start
** 				+ z_head->size - a_head->end) <= size
** 			- (size_t)(a_head->end - a_head->start)))
** {
** 	a_head->end = a_head->start + size;
** 	return (a_head->start);
** }
** else
** {
*/

void					*realloc(void *ptr, size_t size)
{
	t_zone		*z_head;
	t_alloc		*a_head;

	z_head = g_zone;
	if (!ptr)
		return (malloc(size));
	while (z_head)
	{
		a_head = z_head->allocs;
		while (a_head)
		{
			if (a_head->start == ptr)
			{
				ptr = malloc(size);
				ft_memcpy(ptr, a_head->start, (size > (size_t)(a_head->end
					- a_head->start) ? (size_t)(a_head->end - a_head->start)
					: size));
				free(a_head->start);
				return (ptr);
			}
			a_head = a_head->next;
		}
		z_head = z_head->next;
	}
	return (NULL);
}

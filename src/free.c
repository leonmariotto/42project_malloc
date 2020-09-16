/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 09:02:48 by lmariott          #+#    #+#             */
/*   Updated: 2020/09/16 10:38:00 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void		browse_alloc(t_alloc *a_head, t_alloc **a_previous,
							char *z_free, void *ptr)
{
	while (a_head)
	{
		if (a_head->start == ptr)
			a_head->free = 1;
		if (a_head->free == 0)
			*z_free = 0;
		*a_previous = a_head;
		a_head = a_head->next;
	}
}

void			free(void *ptr)
{
	t_zone		*z_head;
	t_zone		*z_previous;
	t_alloc		*a_previous;
	char		z_free;

	z_head = g_zone;
	z_previous = NULL;
	if (!(a_previous = NULL) && !ptr)
		return ;
	while (z_head && (z_free = 1))
	{
		browse_alloc(z_head->allocs, &a_previous, &z_free, ptr);
		if (z_free && (z_head->type == LARGE_TYPE ||
			(void*)z_head + z_head->size - a_previous->end < z_head->size / 3))
		{
			if (z_previous)
				z_previous->next = z_head->next;
			else
				g_zone = z_head->next;
			munmap(z_head, z_head->size);
			return ;
		}
		z_previous = z_head;
		z_head = z_head->next;
	}
}

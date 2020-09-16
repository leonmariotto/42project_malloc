/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 09:57:18 by lmariott          #+#    #+#             */
/*   Updated: 2020/09/16 10:40:46 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_zone	*g_zone = NULL;

t_alloc			*newalloc(t_alloc *new, size_t size)
{
	ft_bzero((void*)new, sizeof(t_alloc));
	new->start = (char*)new + sizeof(t_alloc);
	new->end = (char*)new->start + size;
	return (new);
}

static void		*browse_alloc(t_alloc *a_head, t_zone *z_head, size_t size)
{
	while (a_head)
	{
		if (!a_head->next)
		{
			if (z_head->type != LARGE_TYPE
				&& ((void*)z_head + z_head->size)
				- a_head->end > (unsigned int)(size + sizeof(t_alloc)))
				return ((a_head->next = newalloc(a_head->end,
								size))->start);
		}
		a_head = a_head->next;
	}
	return (NULL);
}

void			*fitinzone(size_t size)
{
	t_zone		*z_head;
	void		*ptr;

	z_head = g_zone;
	while (z_head)
	{
		if (zonetype(size) != z_head->type)
		{
			z_head = z_head->next;
			continue ;
		}
		if (!z_head->allocs)
			return ((z_head->allocs = newalloc(z_head->start, size))->start);
		if ((ptr = browse_alloc(z_head->allocs, z_head, size)))
			return (ptr);
		z_head = z_head->next;
	}
	return (NULL);
}

size_t			align16(size_t size)
{
	return ((size / 16 + 1) * 16);
}

void			*malloc(size_t size)
{
	void	*ptr;

	size = align16(size);
	if (!(ptr = fitinzone(size)))
		ptr = create_zone(size);
	return (ptr);
}

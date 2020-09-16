/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 14:43:12 by lmariott          #+#    #+#             */
/*   Updated: 2020/09/16 09:54:43 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void				add_zone(void *ptr, size_t zonesize, char zonetype)
{
	t_zone		*head;
	t_zone		*new;

	new = (t_zone*)ptr;
	ptr += sizeof(t_zone);
	ft_bzero((void*)new, sizeof(t_zone));
	new->start = ptr;
	new->size = zonesize;
	new->type = zonetype;
	if (!g_zone)
		g_zone = new;
	else
	{
		head = g_zone;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

char				zonetype(size_t size)
{
	if (size < TINY_ASIZE)
		return (TINY_TYPE);
	else if (size < SMALL_ASIZE)
		return (SMALL_TYPE);
	else
		return (LARGE_TYPE);
}

size_t				zonesize(size_t size)
{
	size_t s_zone;

	if (size < TINY_ASIZE)
		s_zone = TINY_ZSIZE;
	else if (size < SMALL_ASIZE)
		s_zone = SMALL_ZSIZE;
	else
		s_zone = ((size + sizeof(t_zone) +
			sizeof(t_alloc)) / getpagesize() + 1) * getpagesize();
	return (s_zone);
}

void				*create_zone(size_t size)
{
	void		*ptr;
	size_t		zone_size;
	char		zone_type;

	zone_size = zonesize(size);
	zone_type = zonetype(size);
	if (!(ptr = mmap(NULL, zone_size,
					PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	add_zone(ptr, zone_size, zone_type);
	return (fitinzone(size));
}

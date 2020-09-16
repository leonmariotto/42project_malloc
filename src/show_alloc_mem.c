/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:52:05 by lmariott          #+#    #+#             */
/*   Updated: 2020/09/16 09:59:51 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void				print_zone(t_zone *head_z, t_zone **h)
{
	t_alloc		*head_a;

	*h = g_zone;
	if (head_z->type == 0)
		printf("TINY");
	else if (head_z->type == 1)
		printf("MEDIUM");
	else
		printf("LARGE");
	printf(" : %p - %p\n", head_z->start,
			(void*)head_z + head_z->size);
	head_a = head_z->allocs;
	while (head_a)
	{
		if (!head_a->free)
			printf("%p - %p : %ld octets\n", head_a->start, head_a->end,
				head_a->end - head_a->start);
		head_a = head_a->next;
	}
}

void				show_alloc_mem(void)
{
	t_zone				*head_z;
	t_zone				*min_zone;
	void				*min;
	void				*prec;

	head_z = g_zone;
	prec = NULL;
	min = NULL;
	min_zone = NULL;
	while (head_z)
	{
		if ((void*)head_z < min || !min)
		{
			min = (void*)head_z;
			if ((void*)head_z > prec)
				min_zone = (void*)head_z;
		}
		if (!(head_z = head_z->next) && min_zone)
		{
			print_zone((prec = (void*)min_zone), &head_z);
			min = NULL;
			min_zone = NULL;
			continue ;
		}
	}
}

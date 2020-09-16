/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 10:11:42 by lmariott          #+#    #+#             */
/*   Updated: 2020/09/08 13:17:54 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			*init_gmalloc(void *ptr)
{
	g_malloc = (t_malloc*)ptr;
	ptr += sizeof(t_malloc);
	ft_bzero(g_malloc, sizeof(t_malloc));
	return (ptr);
}

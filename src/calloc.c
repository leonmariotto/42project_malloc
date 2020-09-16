/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 07:42:49 by lmariott          #+#    #+#             */
/*   Updated: 2020/09/16 10:01:37 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			*calloc(size_t nmemb, size_t size)
{
	void *ptr;

	if (!size || !nmemb)
		return (NULL);
	if (!(ptr = malloc(size * nmemb)))
		return (NULL);
	ft_bzero(ptr, size * nmemb);
	return (ptr);
}

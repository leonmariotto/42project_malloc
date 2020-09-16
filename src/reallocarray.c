/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocarray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 08:01:16 by lmariott          #+#    #+#             */
/*   Updated: 2020/09/15 08:14:12 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			*reallocarray(void *ptr, size_t nmemb, size_t size)
{
	void	*ret;

	ret = realloc(ptr, nmemb * size);
	return (ret);
}

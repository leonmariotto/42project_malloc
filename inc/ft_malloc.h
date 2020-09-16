/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 14:50:59 by lmariott          #+#    #+#             */
/*   Updated: 2020/09/16 09:27:47 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h> // mmap
# include <sys/time.h>
# include <sys/resource.h>
# include "libft.h"

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				*calloc(size_t nmemb, size_t size);
void				*reallocarray(void *ptr, size_t nmemb, size_t size);

void				*create_zone(size_t size);
void				*fitinzone(size_t size);
void				show_alloc_mem(void);
char				zonetype(size_t size);

typedef struct				s_alloc
{
	void			*start;
	void			*end;
	char			free;
	struct s_alloc	*next;
}							t_alloc;

typedef struct				s_zone
{
	void			*start;
	t_alloc			*allocs;
	char			type;
	int				size;
	struct s_zone	*next;
}							t_zone;

typedef struct				s_malloc
{
	t_zone		*z_tiny;
	t_zone		*z_small;
	t_zone		*z_large;
}							t_malloc;

extern t_zone	 			*g_zone;

# define TINY_ASIZE 160
# define SMALL_ASIZE 700

# define TINY_ZSIZE 20480
# define SMALL_ZSIZE 81920

# define TINY_TYPE		0
# define SMALL_TYPE		1
# define LARGE_TYPE		2

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:55:03 by rjeong            #+#    #+#             */
/*   Updated: 2022/07/10 15:51:59 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (!p)
		return (NULL);
	return (memset(p, 0, count * size));
}

# define STATE_TAKE		"has taken a fork\n"
# define STATE_EAT		"is eating\n"
# define STATE_SLEEP	"is sleeping\n"
# define STATE_THINK	"is thinking\n"
# define STATE_DIED		"died\n"

typedef enum e_lock
{
	UNLOCKED = 0,
	LOCKED = 1
}	t_lock;


int		ft_atoi(const char *str);

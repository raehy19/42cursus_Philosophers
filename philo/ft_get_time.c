/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:27:22 by rjeong            #+#    #+#             */
/*   Updated: 2023/05/28 18:27:26 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/time.h>

long long int	ft_get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_usec * 1000);
}

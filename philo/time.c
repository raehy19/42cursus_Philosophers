/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:27:22 by rjeong            #+#    #+#             */
/*   Updated: 2023/05/29 05:50:22 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/time.h>

long long int	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

long long int	get_timestamp(long long int start_time)
{
	return (get_time() - start_time);
}

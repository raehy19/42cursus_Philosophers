/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 02:55:46 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/04 02:55:48 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_arg_err(void)
{
	ft_putstr_fd("Please Check Program Arguments\n", STDERR_FILENO);
	return(-1);
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		(void )argv;
		return (0);
	}
	return (ft_arg_err());
}

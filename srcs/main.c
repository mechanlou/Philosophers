/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 15:21:50 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/06/30 14:49:08 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct timeval  g_eur;

int	perror_ret(char *error)
{
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (1);
}

int	main(int argc, char **argv)
{
	int			ret;
	t_table		table;
	pthread_t	*philo_tab;
	
	ret = 0;
	if (check_args(&table, argc, argv) < 0)
		return (1);
	if (init_table(&table) < 0)
		return (perror_ret("was that a malloc error ?"));
	philo_tab = create_philosophers(&table);
	if (!philo_tab)
	{
		ret = 1;
		write(2, "uh, something went wrong when creating threads\n", 47);
	}
	else if (table.nb_philo > 0)
		ret = monitor_philos(&table);
	free_struct(&table);
	free(philo_tab);
	return (ret);
}

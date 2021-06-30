/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:13:02 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/06/30 15:06:07 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_philos(pthread_t *tab, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_detach(tab[i]);
		i++;
	}
	free(tab);
}

int	check_stuff(t_table *table)
{
	int				i;
	bool			all_done;
	int				time_stamp;
	struct timeval	eur;

	i = 0;
	all_done = true;
	while (i < table->nb_philo)
	{
		if (table->turns > -1 && table->ate_times[i] < table->turns)
			all_done = false;
		gettimeofday(&eur, NULL);
		time_stamp = ((1000 * (eur.tv_sec - g_eur.tv_sec))
				+ ((eur.tv_usec - g_eur.tv_usec) / 1000));
		if (time_stamp - table->last_meal[i] - 5 > table->die)
		{
			pthread_mutex_lock(&table->talk_mutex);
			printf("[%d] %d died\n", time_stamp, i + 1);
			return (-1);
		}
		i++;
	}
	return (!(table->turns != -1 && all_done));
}

int	monitor_philos(t_table *table)
{
	int	ret;

	while (1 == true)
	{
		ret = check_stuff(table);
		if (ret < 1)
		{
			if (ret == 0)
			{
				pthread_mutex_lock(&table->talk_mutex);
				printf("miam, bien mangé\n");
			}
			return (0);
		}
	}
	return (0);
}

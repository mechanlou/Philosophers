/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 18:58:04 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/06/30 14:52:13 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_tabs(t_table *table)
{
	table->ate_times = malloc(sizeof(int) * table->nb_philo);
	if (!table->ate_times)
		return (-1);
	table->last_meal = malloc(sizeof(int) * table->nb_philo);
	if (!table->last_meal)
	{
		free(table->ate_times);
		return (-1);
	}
	table->fork_mutex = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->fork_mutex)
	{
		free(table->last_meal);
		free(table->ate_times);
		return (-1);
	}
	return (0);
}

int	init_tabs(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->last_meal[i] = 0;
		table->ate_times[i] = 0;
		if (pthread_mutex_init(table->fork_mutex + i, NULL))
			return (-1);
		i++;
	}
	return (0);
}

int	init_table(t_table *table)
{
	if (alloc_tabs(table) < 0)
		return (-1);
	if (init_tabs(table))
	{
		free_struct(table);
		return (-1);
	}
	if (pthread_mutex_init(&table->talk_mutex, NULL))
	{
		free_struct(table);
		return (-1);
	}
	table->stop = false;
	table->philo_inc = 0;
	return (0);
}

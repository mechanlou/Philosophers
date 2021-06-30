/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 20:50:01 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/06/30 14:50:09 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(int number, t_table *table)
{
	struct timeval	eur;

	gettimeofday(&eur, NULL);
	pthread_mutex_lock(&table->talk_mutex);
	printf("[%ld] %d is thinking\n", (1000 * (eur.tv_sec - g_eur.tv_sec))
		+ ((eur.tv_usec - g_eur.tv_usec) / 1000), number + 1);
	pthread_mutex_unlock(&table->talk_mutex);
}

void	philo_sleep(int number, t_table *table)
{
	struct timeval	eur;

	gettimeofday(&eur, NULL);
	pthread_mutex_lock(&table->talk_mutex);
	printf("[%ld] %d is sleeping\n", (1000 * (eur.tv_sec - g_eur.tv_sec))
		+ ((eur.tv_usec - g_eur.tv_usec) / 1000), number + 1);
	pthread_mutex_unlock(&table->talk_mutex);
	usleep(table->sleep * 1000);
}

void	*philo_thread(void *table)
{
	int				my_number;

	my_number = ((t_table *)table)->philo_inc++;
	while (1)
	{
		philo_eat(my_number, ((t_table *)table));
		philo_sleep(my_number, ((t_table *)table));
		philo_think(my_number, ((t_table *)table));
	}
	return (NULL);
}

pthread_t	*create_philosophers(t_table *table)
{
	pthread_t		*philo_tab;
	int				i;

	philo_tab = (pthread_t *)malloc(sizeof(pthread_t) * table->nb_philo);
	if (!philo_tab)
		return (NULL);
	i = 0;
	gettimeofday(&g_eur, NULL);
	while (i < table->nb_philo)
	{
		if (pthread_create(philo_tab + i, NULL, philo_thread, table)
			|| pthread_detach(philo_tab[i]))
		{
			free(philo_tab);
			return (NULL);
		}
		usleep(50);
		i++;
	}
	return (philo_tab);
}

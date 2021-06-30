/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 14:18:12 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/06/30 14:49:23 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_as_taken(t_table *table, int left, int right, int number)
{
	struct timeval	eur;
	int				time_stamp;

	pthread_mutex_lock(table->fork_mutex + left);
	gettimeofday(&eur, NULL);
	time_stamp = (1000 * (eur.tv_sec - g_eur.tv_sec))
		+ ((eur.tv_usec - g_eur.tv_usec) / 1000);
	pthread_mutex_lock(&table->talk_mutex);
	printf("[%d] %d has taken a fork\n", time_stamp, number + 1);
	pthread_mutex_unlock(&table->talk_mutex);
	pthread_mutex_lock(table->fork_mutex + right);
	gettimeofday(&eur, NULL);
	time_stamp = (1000 * (eur.tv_sec - g_eur.tv_sec))
		+ ((eur.tv_usec - g_eur.tv_usec) / 1000);
	pthread_mutex_lock(&table->talk_mutex);
	printf("[%d] %d has taken a fork\n", time_stamp, number + 1);
	pthread_mutex_unlock(&table->talk_mutex);
	return (0);
}

int	take_forks(int number, t_table *table)
{
	if (number == 0)
		return (set_as_taken(table, table->nb_philo - 1, 0, number));
	else
		return (set_as_taken(table, number - 1, number, number));
}

void	put_forks_down(t_table *table, int number)
{
	if (number == 0)
	{
		pthread_mutex_unlock(table->fork_mutex + table->nb_philo - 1);
		pthread_mutex_unlock(table->fork_mutex + 0);
	}
	else
	{
		pthread_mutex_unlock(table->fork_mutex + number - 1);
		pthread_mutex_unlock(table->fork_mutex + number);
	}
}

void	eat(int number, t_table *table)
{
	struct timeval	eur;
	int				time_stamp;

	gettimeofday(&eur, NULL);
	time_stamp = (1000 * (eur.tv_sec - g_eur.tv_sec))
		+ ((eur.tv_usec - g_eur.tv_usec) / 1000);
	table->last_meal[number] = time_stamp;
	pthread_mutex_lock(&table->talk_mutex);
	printf("[%d] %d is eating\n", time_stamp, number + 1);
	pthread_mutex_unlock(&table->talk_mutex);
	usleep(table->eat * 1000);
	table->ate_times[number] += 1;
	put_forks_down(table, number);
}

void	philo_eat(int number, t_table *table)
{
	take_forks(number, table);
	eat(number, table);
}

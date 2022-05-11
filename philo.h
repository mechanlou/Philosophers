/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 15:22:20 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/06/30 14:51:50 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

extern struct timeval  g_eur;

typedef struct s_table
{
	int				die;
	int				eat;
	int				sleep;
	int				turns;
	int				nb_philo;
	int				philo_inc;
	bool			stop;
	pthread_mutex_t	talk_mutex;
	pthread_mutex_t	*fork_mutex;
	int				*ate_times;
	int				*last_meal;
}				t_table;

int			ft_atoi(const char *str);
int			ft_strlen(char *str);
int			ft_isdigit(int c);
int			check_args(t_table *table, int argc, char **argv);
int			init_table(t_table *table);
void		free_struct(t_table *table);
void		*philo_thread(void *table);
void		close_mutex_tab(pthread_mutex_t *tab, int length);
void		print_struct(t_table table);
void		free_pthread_tab(pthread_t *tab, int size);
int			monitor_philos(t_table *table);
pthread_t	*create_philosophers(t_table *table);
void		philo_eat(int number, t_table *table);
bool		check_stop_call(t_table *table);

#endif	

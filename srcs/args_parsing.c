/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:40:34 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/06/23 14:34:32 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pars_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (-1);
		i++;
	}
	i = ft_atoi(arg);
	if (i < 0)
		return (-1);
	return (i);
}

int	check_args(t_table *table, int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong arg number\n", ft_strlen("Wrong arg number\n"));
		return (-1);
	}
	table->nb_philo = pars_arg(argv[1]);
	table->die = pars_arg(argv[2]);
	table->eat = pars_arg(argv[3]);
	table->sleep = pars_arg(argv[4]);
	if (argc == 6)
		table->turns = pars_arg(argv[5]);
	else
		table->turns = -1;
	if (table->nb_philo < 0 || table->die < 0 || table->eat < 0
		|| table->sleep < 0 || (argc == 6 && table->turns < 0))
	{
		write(2, "Arg error\n", ft_strlen("Arg error\n"));
		return (-1);
	}
	return (0);
}

#include "philosophers.h"

t_error	start_dinner(t_rules *rules, t_philosopher **philo)
{
	if (init_mutexes(rules) == ERROR)
		return (ERROR);
	if (init_philosophers(philo, rules) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

t_error	init_philosophers(t_philosopher **philo, t_rules *rules)
{
	int	i;
	int	err_check;

	*philo = malloc(sizeof(t_philosopher) * rules->num_of_philo);
	if (*philo == NULL)
		return (ERROR);
	rules->synchro = FALSE;
	gettimeofday(&rules->start, NULL);
	i = -1;
	while (++i < rules->num_of_philo)
	{
		(*philo)[i].index = i + 1;
		gettimeofday(&(*philo)[i].time_start_last_meal, NULL);
		(*philo)[i].rules = rules;
		(*philo)[i].num_of_eats = 0;
		err_check = pthread_mutex_init(&(*philo)[i].eating, NULL);
		if (pthread_create(&(*philo)[i].thread_id, NULL, dinner, &(*philo)[i])
				!= 0 || err_check != 0 )
			return (ERROR);
	}
	rules->synchro = TRUE;
	return (SUCCESS);
}

t_error	init_mutexes(t_rules *rules)
{
	int	i;
	int	err_check;

	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->num_of_philo);
	if (!rules->forks)
		return (ERROR);
	i = -1;
	while (++i < rules->num_of_philo)
	{
		err_check = pthread_mutex_init(&rules->forks[i], NULL);
		if (err_check != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&rules->forks[i]);
			return (ERROR);
		}
	}
	err_check = pthread_mutex_init(&rules->speak, NULL);
	if (err_check != 0)
		return (ERROR);
	return (SUCCESS);
}

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef int	t_bool;
# define TRUE (1)
# define FALSE (0)

# define INVALID_NUMBER (-1)

typedef int	t_error;

enum e_errors
{
	SUCCESS,
	WRONG_NUM_OF_ARGS,
	INVALID_ARGUMENTS,
	ERROR,
};

typedef struct s_rules
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	
	struct timeval	start;
	t_bool			valid;
}				t_rules;

typedef struct s_philospher
{
	int			index;
	pthread_t	thread_id;
	int			time_start_last_meal;
	t_rules		*rules;
}				t_philosopher;

/* parsing */

t_rules	parse_arguments(int argc, char **argv);
int		get_number(char *str);
void	check_validity(t_rules *rules, int argc);

/* parsing utils */

int		ft_atoi(const char *nptr);
t_bool	ft_isdigit(int c);

/* debug */

void	print_rules(t_rules rules);
void	print_philos(t_philosopher *philos, int num_of_philos);

/* philosophers */

t_error	start_dinner(t_rules *rules, t_philosopher **philo, pthread_mutex_t **forks);
t_error	init_philosophers(t_philosopher **philo, t_rules *rules);
t_error	init_forks(pthread_mutex_t **forks, int num_of_philo);
void	free_forks(pthread_mutex_t *forks, int num_of_philo);

void	*dinner(void *philosopher);
void	threads_join(t_philosopher *philosopher, int number_of_philosophers);

#endif

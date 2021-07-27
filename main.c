#include "philosophers.h"

int main(int argc, char **argv)
{
	t_rules			rules;
	t_philosopher	*philosophers;
//	t_fork			*forks;

	if (argc < 5 || argc > 6)
		return (WRONG_NUM_OF_ARGS);
	rules = parse_arguments(argc, argv);	
	print_rules(rules); // debug
	if (!rules.valid)
		return (INVALID_ARGUMENTS);	
	if (init_philosophers(&philosophers, rules.number_of_philosophers) == ERROR)
		return (EXIT_FAILURE);
	print_philos(philosophers, rules.number_of_philosophers);
	return (EXIT_SUCCESS);
}

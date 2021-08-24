#include "philosophers.h"

int main(int argc, char **argv)
{
	t_rules			rules;
	t_philosopher	*philosophers;

	rules = parse_arguments(argc, argv);
	print_rules(rules); // debug
	if (!rules.valid)
		return (INVALID_ARGUMENTS);	

	start_dinner(&rules, &philosophers);
	print_philos(philosophers, rules.number_of_philosophers); // debug

	threads_join(philosophers, rules.number_of_philosophers);
	free_forks(rules.forks, rules.number_of_philosophers);
	free(philosophers);
	return (EXIT_SUCCESS);
}

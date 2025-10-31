#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdbool.h>

typedef struct	s_table t_table;

typedef struct	s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	meal_mutex;
	long			last_meal;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}   t_philo;

typedef struct s_table
{
	int				philo_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_required;
	long			start_time;
	bool			stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		monitor;
	t_philo			*philos;
}   t_table;

int		parse_arguments(t_table *table, int argc, char **argv);
int		init_table(t_table *table);
void	destroy_table(t_table *table);

long	current_time_ms(void);
long	elapsed_since(long start);
void	precise_sleep(long duration_ms, t_table *table);

void	*philo_routine(void *arg);
int		launch_threads(t_table *table);

void	print_action(t_philo *philo, const char *message);
bool	simulation_stopped(t_table *table);
void	stop_simulation(t_table *table);

void	*monitor_routine(void *arg);

#endif

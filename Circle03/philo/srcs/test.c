typedef struct s_data
{
    int             num_philos;
    int             time_to_die;    // in milliseconds
    int             time_to_eat;    // in milliseconds  
    int             time_to_sleep;  // in milliseconds
    int             must_eat_count;
    int             simulation_end;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    pthread_mutex_t death_lock;
    long long       start_time;     // in milliseconds
}   t_data;

int init_mutexes(t_data *data)
{
    int i;
    
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (!data->forks)
        return (0);
    
    i = 0;
    while (i < data->num_philos)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
            return (0);
        i++;
    }
    
    if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
        return (0);
    if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
        return (0);
    
    return (1);
}

int init_philos(t_philo **philos, t_data *data)
{
    int i;
    
    *philos = malloc(sizeof(t_philo) * data->num_philos);
    if (!*philos)
        return (0);
    
    i = 0;
    while (i < data->num_philos)
    {
        (*philos)[i].id = i + 1;
        (*philos)[i].meals_eaten = 0;
        (*philos)[i].last_meal_time = 0;
        (*philos)[i].data = data;
        (*philos)[i].left_fork = &data->forks[i];
        (*philos)[i].right_fork = &data->forks[(i + 1) % data->num_philos];
        i++;
    }
    return (1);
}

void print_status(t_philo *philo, char *status)
{
    long timestamp;
    
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->simulation_ended)
    {
        timestamp = get_current_time() - philo->data->start_time;
        printf("[%ld] Philosopher %d %s\n", timestamp, philo->id, status);
    }
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void smart_sleep(long milliseconds)
{
    long start;
    
    start = get_current_time();
    while (get_current_time() - start < milliseconds)
        usleep(100);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    while (!philo->data->simulation_ended)
    {
        print_status(philo, "is thinking");
        smart_sleep(philo->data->time_to_sleep);
    }
    return (NULL);
}

int main(int argc, char **argv)
{
    t_data data;
    t_philo *philos;
    int i;
    
    // Parse arguments into data struct
    // Initialize mutexes
    // Initialize philosophers
    data.start_time = get_current_time();
    
    // Create threads with basic routine
    i = 0;
    while (i < data.num_philos)
    {
        pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
        i++;
    }
    
    // Let them run for a bit
    sleep(3);
    data.simulation_ended = 1;
    
    // Join threads and cleanup
    // ...
}

think → acquire forks → eat → release forks → sleep
forks → [MUTEX][MUTEX][MUTEX][MUTEX][MUTEX]
          ↑      ↑      ↑      ↑      ↑
         fork0  fork1  fork2  fork3  fork4
         [0]    [1]    [2]    [3]    [4]

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine) (void *), void *arg);

pthread_t thread1;
pthread_t thread2;
pthread_t thread3;
int	ids[3] = {0, 1, 2};

void	*act(void *arg)
{
	int	id;
		
	id = *(int*)arg;
	printf("Philo %d is thinking\n", id);
	sleep(1);
	printf("Philo %d is eating\n", id);
	sleep(1);
	printf("Philo %d is sleeping\n", id);
	sleep(1);
	return (NULL);
}

pthread_create(&thread1, NULL, act, &ids[0]);
pthread_create(&thread2, NULL, act, &ids[1]);
pthread_create(&thread3, NULL, act, &ids[2]);
pthread_join(thread1, NULL);
pthread_join(thread2, NULL);
pthread_join(thread3, NULL);

[prefix] + [action] + [target]
parse_arguments(extraction) → validate_input(check extracted value) → initialize_simulation(set up)
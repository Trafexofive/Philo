

#include "philo.h"

void  *routine(void)
{
  int i = 0;

  while (i < 10)
  {
    i++;
    puts("hello\n");
    usleep(10000);
  }
  return NULL;
}


void  default_philo(t_philo *philo, pthread_mutex_t *fork, t_parse *parse)
{
  unsigned int i;

  i = 0;
  while (i < parse->max)
  {
    philo[i].id = i + 1;
    philo[i].left_fork = fork[i];
    philo[i].times_eaten = 0;
    if (i == 0)
      philo[parse->max].right_fork = &fork[i];
    else
      philo[i].right_fork = &fork[i + 1];

    i++;
  }

}

void  exit_status(char *str)
{
  printf("%s", str);
  exit(1);
}

pthread_mutex_t  *init_forks(t_parse *parse)
{
  unsigned int i;
  pthread_mutex_t fork[parse->max];

  i = 0;

  while (i < parse->max)
  {
    if (pthread_mutex_init(&fork[i], NULL) != 0)
      exit_status("Mutex Init Error\n");
    i++;
  }

}

void  init_philos(t_philo *philo, t_parse *data)
{
  unsigned int i;

  i = 0;
  
  while (i < data->max)
  {
    if (pthread_create(&philo[i], NULL, routine, (void *) i) != 0)
      exit_status("Thread Creating Error\n");
    i++;
  }
}

int main(int ac, char *av[])
{
    t_philo philo[200];
    t_parse *data;

    data = parse(ac,av);
    init_philos(philo, data);
    init_forks(data);
    default_philo(philo, );

    return 0;
}

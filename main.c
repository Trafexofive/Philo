
#include "philo.h"

void print_status(t_philo *philo, char *str) {
  pthread_mutex_lock(philo->global->watchdogs);
  printf("%lld %d %s\n", get_time(philo->global),philo->id, str);
  pthread_mutex_unlock(philo->global->watchdogs);
}
long long get_time(t_global *global) {
  struct timeval tv;

  if (gettimeofday(&tv, NULL) < 0)
    return 0;
  if (global->starting_time == 0)
    global->starting_time = ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));

  return (((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000)) - global->starting_time);
}

void  init_mutex(t_global *global)
{
      int i = -1;

      while (++i < global->parse->max)
      {
        pthread_mutex_init(&global->fork[i], NULL);
        pthread_mutex_init(&global->watchdogs[i], NULL);
      }
      pthread_mutex_init(&global->allow_print, NULL);
}

void  usleep_prime(t_philo *philo, long long time)
{
  long long start;

  start = get_time(philo->global);
  while (get_time(philo->global) - start < time)
    usleep(100);
}

void  sleeping(t_philo *philo)
{
  usleep_prime(philo, philo->global->parse->tts);
  print_status(philo, SLEEP);
}

void eat(t_philo *philo)
{
  usleep_prime(philo, philo->global->parse->tte);
  print_status(philo, EAT);
  // philo->times_eaten++;
}


void  init_philo(t_global *global)
{
  int i;

  i = 0;

  while (i < global->parse->max)
  {
    global->philo[i].id = i + 1;
    global->philo[i].times_eaten = 0;
    global->philo[i].last_meal = 0;
    global->philo[i].right_fork = &global->fork[(i + 1) % global->parse->max];
    global->philo[i].left_fork = &global->fork[i];
    global->philo[i].watchdog = &global->watchdogs[i];

    global->philo[i].global = global;
    i++;
  }
}

void  init_global(t_global *global, t_parse *data)
{
    global->philo = malloc(sizeof(t_philo) * data->max);
    global->watchdogs = malloc(sizeof(pthread_mutex_t) * data->max);
    global->thrds = malloc(sizeof(pthread_t) * data->max);
    global->fork = malloc(sizeof(pthread_mutex_t) * data->max);
    global->parse = data;
    global->starting_time = 0;

    init_mutex(global);
    init_philo(global);
}


void  *routine(void *ptr)
{
  t_philo *philo;

  philo = (t_philo *)ptr;

  if (philo->id % 2)
    usleep(200);
  while (TRUE)
  {
      pthread_mutex_lock(philo->left_fork);
      print_status(philo, PICK);
      pthread_mutex_lock(philo->right_fork);
      print_status(philo, PICK);
      eat(philo);
      pthread_mutex_unlock(philo->left_fork);
      pthread_mutex_unlock(philo->right_fork);
      sleeping(philo);
      print_status(philo, THINKING);
  }
}

int main(int ac, char *av[]) {

  t_parse data;
  t_global  global;
  int i = 0;

  if (valid_args(ac, av))
    init_args(av, &data);

    init_global(&global, &data);
    while (i < global.parse->max)
    {
      pthread_create(&global.thrds[i], NULL, &routine, &global.philo[i]);
      pthread_detach(global.thrds[i]);
      i++;
    }
  return 0;
}

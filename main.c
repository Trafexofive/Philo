
#include "philo.h"

void print_status(t_philo *philo, char *str) {
  pthread_mutex_lock(&philo->global->allow_print);
  printf("%lld %d %s\n", get_time(philo->global),philo->id, str);
  if (strncmp(str, "died",5) == 0)
    return ;
  pthread_mutex_unlock(&philo->global->allow_print);
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
        global->philo[i].is_dead = FALSE;
      }
      pthread_mutex_init(&global->allow_print, NULL);
}

void  usleep_prime(t_philo *philo, long long time)
{
  long long start;

  start = get_time(philo->global);
  while (get_time(philo->global) - start < time)
    usleep(200);
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
  pthread_mutex_lock(philo->watchdog);
  if (philo->global->parse->ntte != -1)
    philo->times_eaten++;
  philo->last_meal = get_time(philo->global);
  pthread_mutex_unlock(philo->watchdog);
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

bool death_checker(t_philo *philo)
{
	bool flag = true;
    pthread_mutex_lock(philo->watchdog);
    if ((philo->global->parse->ntte != -1 && philo->times_eaten < philo->global->parse->ntte) || philo->is_dead == TRUE)
       flag = false;
    if (philo->last_meal && get_time(philo->global) - philo->last_meal >= philo->global->parse->ttd)
	flag = false;
    pthread_mutex_unlock(philo->watchdog);
    return flag;
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
      if (!death_checker(philo))
      {
        pthread_mutex_unlock(philo->watchdog);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        return NULL;
      }
      eat(philo);
      if (!death_checker(philo))
      {
		pthread_mutex_unlock(philo->watchdog);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        return NULL;
      }
      pthread_mutex_unlock(philo->left_fork);
      // if (!death_checker(philo))
      //   return NULL;
      pthread_mutex_unlock(philo->right_fork);
      sleeping(philo);
      if (!death_checker(philo))
        return (pthread_mutex_unlock(philo->watchdog),NULL);
      print_status(philo, THINKING);
      if (!death_checker(philo))
        return (pthread_mutex_unlock(philo->watchdog),NULL);
      usleep(200);
  }
  return NULL;
}

void  set_death(t_global *global)
{
  int i;

  i = 0;
  while (i < global->parse->max)
  {
    pthread_mutex_lock(global->philo[i].watchdog);
    global->philo[i].is_dead = TRUE;
    pthread_mutex_unlock(global->philo[i].watchdog);
    i++;
  }
}

bool    is_death(t_global *global)
{
  int i;

  i = 0;
  while (i < global->parse->max)
  {
    pthread_mutex_lock(global->philo[i].watchdog);
    if (global->parse->ntte != -1 && global->philo[i].times_eaten < global->parse->ntte){
    pthread_mutex_unlock(global->philo[i].watchdog);
      usleep_prime(&global->philo[i], global->parse->tte);
      return (TRUE);
    }
    if (global->philo[i].last_meal && get_time(global) - global->philo[i].last_meal >= global->parse->ttd)
    {
      print_status(&global->philo[i], "died");
     pthread_mutex_unlock(global->philo[i].watchdog);
      set_death(global);
      return (TRUE);
    }
    pthread_mutex_unlock(global->philo[i].watchdog);
    i++;
  }
  return (FALSE);
}

void  destroy_mutex(t_global *global) // protect the case when a pholosopher dies and keeps the mutex locked;
{
  int i;

  i = 0;
  while (i < global->parse->max)
  {
    pthread_mutex_destroy(&global->fork[i]);
    pthread_mutex_destroy(&global->watchdogs[i]);
    i++;
  }
  pthread_mutex_destroy(&global->allow_print);
}

int main(int ac, char *av[]) { // fix relink

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
  while (!is_death(&global))
    usleep(200);
  pthread_mutex_unlock(&global.allow_print);
  free(global.philo);
  free(global.watchdogs);
  free(global.thrds);
  free(global.fork);
  // destroy_mutex(&global);
  return 0;
}


#include "philo.h"

void print_status(t_philo *philo, char *str) {
  // pthread_mutex_lock(&philo->parse->allow_print);
  printf("%u %s\n", philo->id, str);
  // pthread_mutex_unlock(&philo->parse->allow_print);
}
long long get_time(void) {
  struct timeval tv;

  if (gettimeofday(&tv, NULL))
    return 0;
  return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void eating(t_philo *philo) {
  pthread_mutex_lock(philo->left_fork);
  pthread_mutex_lock(philo->right_fork);

  long long start = get_time();

  while (get_time() - start < philo->parse->ttd)
    print_status(philo, EAT);
  usleep(philo->parse->tte);
}

void sleeping(t_philo *philo) { usleep(philo->parse->tts); }

void routine(void *data) {
  t_philo *philo;

  philo = (t_philo *)data;
  if (philo->id % 2 == 0)
    usleep(100);
  while (TRUE) {
    eating(philo);
    sleeping(philo);
    print_status(philo, SLEEP);
    print_status(philo, THINKING);
  }
}

void default_philo(t_philo *philo, pthread_mutex_t *fork, t_parse *parse,
                   pthread_mutex_t *watchdog) {
  unsigned int i;

  i = 0;
  while (i < parse->max) {
    philo[i].id = i + 1;
    philo[i].left_fork = &fork[i];
    philo[i].times_eaten = 0;
    philo[i].parse = parse;
    philo[i].right_fork = &fork[(i + 1) % parse->max];
    philo[i].watchdog = &watchdog[i];
    i++;
  }
}

void exit_status(char *str) {
  printf("%s", str);
  exit(1);
}

void init_forks(t_parse *parse, pthread_mutex_t *fork,
                pthread_mutex_t *watchdog) {
  unsigned int i;

  i = 0;

  while (i < parse->max) {
    if (pthread_mutex_init(&fork[i], NULL) != 0)
      exit_status("Mutex Init Error\n");
    i++;
  }
  i = 0;
  while (i < parse->max) {
    if (pthread_mutex_init(&watchdog[i], NULL) != 0)
      exit_status("Mutex Init Error\n");
    i++;
  }
}

void init_philos(t_philo *philo, t_parse *data) {
  unsigned int i;

  i = 0;

  while (i < data->max) {
    if (pthread_create(&philo[i].philo, NULL, (void *)routine,
                       (void *)&philo[i]) != 0)
      exit_status("Thread Creating Error\n");
    i++;
  }
  i = 0;
  while (i < data->max) {
    if (pthread_detach(philo[i].philo) != 0)
      exit_status("Thread Creating Error\n");
    i++;
  }
}

int main(int ac, char *av[]) {
  t_parse *data;

  data = parse(ac, av);
  t_philo philo[data->max];
  pthread_mutex_t fork[data->max];
  pthread_mutex_t watchdog[data->max];

  init_forks(data, fork, watchdog);
  default_philo(philo, fork, data);
  init_philos(philo, data);

  return 0;
}

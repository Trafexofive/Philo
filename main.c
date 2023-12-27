
#include "philo.h"

void lock_forks(t_philo *philo) {
  pthread_mutex_lock(&philo->left_fork);
  printf("%u %s\n", philo->id, PICK);
  pthread_mutex_lock(philo->right_fork);
  printf("%u %s\n", philo->id, PICK);
}

void unlock_forks(t_philo *philo) {
  pthread_mutex_unlock(&philo->left_fork);
  pthread_mutex_unlock(philo->right_fork);
}

void eating(t_philo *philo) {
  lock_forks(philo);
  philo->times_eaten += 1;
  printf("%u %s\n", philo->id, EAT);
  usleep(philo->parse->tte);
  unlock_forks(philo);
}

void sleeping(t_philo *philo) { usleep(philo->parse->tts); }

void routine(void *data) {
  t_philo *philo;

  philo = (t_philo *)data;
  while (TRUE) {
    eating(philo);
    sleeping(philo);
    printf("%u\n %s", philo->id, SLEEP);
  }
}

void default_philo(t_philo *philo, pthread_mutex_t *fork, t_parse *parse) {
  unsigned int i;

  i = 0;
  while (i < parse->max) {
    philo[i].id = i + 1;
    philo[i].left_fork = fork[i];
    philo[i].times_eaten = 0;
    philo[i].dead = 0;
    if (i == 0)
      philo[parse->max].right_fork = &fork[i];
    else
      philo[i].right_fork = &fork[i + 1];
    i++;
  }
}

void exit_status(char *str) {
  printf("%s", str);
  exit(1);
}

void init_forks(t_parse *parse, pthread_mutex_t *fork) {
  unsigned int i;

  i = 0;

  while (i < parse->max) {
    if (pthread_mutex_init(&fork[i], NULL) != 0)
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
}

int main(int ac, char *av[]) {
  t_philo philo[20];
  pthread_mutex_t fork[20];
  t_parse *data;

  data = parse(ac, av);
  init_forks(data, fork);
  default_philo(philo, fork, data);
  init_philos(philo, data);

  return 0;
}

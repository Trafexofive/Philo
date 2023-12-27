#include "philo.h"

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
    printf("%u\n %s", philo->id, THINKING);
  }
}

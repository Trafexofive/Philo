
#include "philo.h"

void print_status(t_philo *philo, char *str) {
  pthread_mutex_lock(&philo->parse->allow_print);
  printf("%u %s\n", philo->id, str);
  pthread_mutex_unlock(&philo->parse->allow_print);
}


void lock_forks(t_philo *philo) {
  if(philo->left_fork)
    pthread_mutex_lock(philo->left_fork);
 // print_status(philo, PICK);
  if(philo->right_fork)
	pthread_mutex_lock(philo->right_fork);
  //print_status(philo, PICK);
}

void unlock_forks(t_philo *philo) {
  if(philo->left_fork)
  	pthread_mutex_unlock(philo->left_fork);
  if(philo->right_fork)
  	pthread_mutex_unlock(philo->right_fork);
}

void eating(t_philo *philo) {
  lock_forks(philo);
  //philo->times_eaten += 1;
  print_status(philo, EAT);
  //usleep(philo->parse->tte);
  unlock_forks(philo);
}

void sleeping(t_philo *philo) { 

	usleep(philo->parse->tts); 
}

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

void default_philo(t_philo *philo, pthread_mutex_t *fork, t_parse *parse) {
  unsigned int i;

  i = 0;
  while (i < parse->max) {
    philo[i].id = i + 1;
    philo[i].left_fork = &fork[i];
    philo[i].times_eaten = 0;
	philo[i].parse = parse;
    philo[parse->max].right_fork = &fork[i + 1];
    if (i == parse->max)
      philo[parse->max].right_fork = &fork[0];
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
  i =0;
    while (i < data->max) {
    if (pthread_detach(philo[i].philo) != 0)
      exit_status("Thread Creating Error\n");
    i++;
  }
}

int main(int ac, char *av[]) {
  t_philo philo[20];
  pthread_mutex_t fork[20];
  t_parse *data;

  data = parse(ac, av);
  unsigned int  i = 0;
   while (i < data->max+1) {
    if (pthread_mutex_init(&fork[i], NULL) != 0)
      exit_status("Mutex Init Error\n");
    i++;
  }
 // init_forks(data, fork);
  default_philo(philo, fork, data);
  init_philos(philo, data);

  return 0;
}

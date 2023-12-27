

#ifndef PHILO_H
#define PHILO_H

#include "libft/libft.h"
#include <pthread.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

/* =========> Macros <=============*/

#define TRUE 1
#define FALSE 0
#define MAX_PHILO 200

/* =========> structs <===========*/

typedef struct s_parse {

  unsigned int max;
  unsigned int ttd;
  unsigned int tts;
  unsigned int tte;
  int ntte;
  pthread_mutex_t allow_print;
  bool            dead;

} t_parse;

typedef struct s_philo {
  pthread_t   philo;

  unsigned int id;
  pthread_mutex_t left_fork;
  pthread_mutex_t *right_fork;
  unsigned int    times_eaten;








} t_philo;

//detach no longger use?
//
typedef struct s_watchdog {
  int c;

} t_watchdog;

/* =========> Defines <===========*/

t_parse *parse(int ac, char **av);

#endif

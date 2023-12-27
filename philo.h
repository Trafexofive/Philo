

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
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINKING "is thinking"
#define PICK "has taken a fork"

/* =========> structs <===========*/

typedef struct s_parse {

  long  max;
  long  ttd;
  long  tts;
  long   tte;
  long    ntte;

  pthread_mutex_t allow_print;
  

} t_parse;

typedef struct s_philo {
  pthread_t   philo;

  unsigned int id;
  pthread_mutex_t left_fork;
  pthread_mutex_t *right_fork;
  bool            *dead;
  unsigned int    times_eaten;
  struct s_parse *parse;


} t_philo;

//detach no longger use?
//
typedef struct s_watchdog {

} t_watchdog;

/* =========> Defines <===========*/

t_parse *parse(int ac, char **av);

#endif

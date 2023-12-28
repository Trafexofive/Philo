/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 03:53:02 by mlamkadm          #+#    #+#             */
/*   Updated: 2023/12/28 21:34:43 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PHILO_H
#define PHILO_H

#include "libft/libft.h"
#include <pthread.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>

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

  int             max;
  int             ttd;
  int             tts;
  int             tte;
  int             ntte;

} t_parse;

typedef struct s_philo {

  unsigned int id;
  int times_eaten;
  long long last_meal;

  pthread_mutex_t *watchdog;
  pthread_mutex_t *left_fork;
  pthread_mutex_t *right_fork;

  struct s_global *global;
  bool              is_dead;

} t_philo;

typedef struct s_global
{
  pthread_mutex_t   *fork;
  pthread_mutex_t   *watchdogs;
  pthread_t         *thrds;

  struct s_parse    *parse;
  struct s_philo    *philo;
  long long         starting_time;
  pthread_mutex_t   allow_print;

}t_global;

/* =========> Defines <===========*/


/* =========> Utils <===========*/
long long get_time(t_global *global);

/* =========> Initilization <===========*/

void  init_mutex(t_global *global);
void  init_philo(t_global *global);
void  init_global(t_global *global, t_parse *data);
void  sleeping(t_philo *philo);
void print_status(t_philo *philo, char *str);
void  eat(t_philo *philo);
void  *routine(void *arg);
void  *watchdog(void *arg);
void  *death(void *arg);
void  destroy_mutex(t_global *global);
void  ft_usleep(long long time);
void  ft_usleep_prime(long long time);

/* =========> Parse <===========*/

void init_args(char **av, t_parse *data);
bool is_digit(int c);
bool valid_args(int ac, char **av);



#endif

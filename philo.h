

#ifndef PHILO_H
# define PHILO_H


# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdio.h>
# include "libft/libft.h"

/* =========> Macros <=============*/

# define TRUE 1
# define FALSE 0
# define MAX_PHILO 300

/* =========> structs <===========*/

typedef struct    s_parse
{
    unsigned int    num;
    unsigned int    ttd;
    unsigned int    tts;
    unsigned int    tte;
    int    ntte;
}t_parse;

typedef struct    s_philo
{
    unsigned int    num;
    unsigned int    ttd;
    unsigned int    tts;
    unsigned int    tte;

}t_philo;

typedef struct    s_watchdog
{
  int c;
  
}t_watchdog;

/* =========> Defines <===========*/

t_parse *parse(int ac, char **av);


#endif

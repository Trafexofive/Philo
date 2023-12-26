

#ifndef PHILO_H
# define PHILO_H


# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>
# include <pthread.h>
# include "libft/libft.h"

/* =========> Macros <=============*/

# define TRUE 1
# define FALSE 0



/* =========> structs <===========*/

typedef struct    s_philo
{
    unsigned int    num;
    unsigned int    ttd;
    unsigned int    tts;
    unsigned int    tte;

}t_philo;

typedef struct    s_watchdog
{
  struct s_philo  *fork;
  
}

/* =========> Defines <===========*/

t_philo *parse(int ac, char **av);


#endif

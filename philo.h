

#ifndef PHILO_H
# define PHILO_H


# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>
# include "libft/libft.h"

/* =========> Macros <=============*/

# define TRUE 1
# define FALSE 0



/* =========> structs <===========*/

typedef struct
{
    unsigned int    number;
    unsigned int    to_die;
    unsigned int    to_sleep;
    unsigned int    to_eat;
}philo;

/* =========> Defines <===========*/

bool  parse(int ac, char **av);


#endif

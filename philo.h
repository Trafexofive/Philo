

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
    unsigned int    num;
    unsigned int    ttd;
    unsigned int    tts;
    unsigned int    tte;

}t_philo;

/* =========> Defines <===========*/

t_philo *parse(int ac, char **av);


#endif

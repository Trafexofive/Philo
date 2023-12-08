

#include "libft/libft.h"
#include "philo.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void    matrix_free(char **ptr)
{
    int i;

    i = -1;
    while (ptr[++i])
        free(ptr[i]);
    free (ptr);
    ptr = NULL;
}


char    **tokenize(char **av, char delim)
{
    int i;
    int j;
    char    **args;
    char    *appended_str;

    j = 0;
    i = 0;
    while (av[++i])
        appended_str = ft_strjoin(appended_str, av[i]);
    printf("%s", appended_str);
    free(appended_str);
    while (av[++i])
    {
        args = ft_split(av[i], delim);
    
    }
    matrix_free(args);
    
    return (NULL);
}


// bool  valid_args(int ac, char **av)
// {
//
//     int i;
//
//     i = 0;
//     
//
// }


bool  parse(int ac, char **av)
{
  int i;

  i = 0;
    (void) ac;
  // if (valid_args(ac, av))
    if (tokenize(av, ' '))
  	    return (TRUE);

    return (TRUE);
}


int main(int ac, char *av[])
{
    parse(ac, av);

    return EXIT_SUCCESS;
}

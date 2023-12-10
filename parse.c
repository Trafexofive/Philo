

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



static bool is_whitespace(const char c)
{
	if (c == '\n' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (TRUE);
	else
		return (FALSE);
}

t_philo *init_struct(char **av)
{
    t_philo *data;

    data = malloc(sizeof(t_philo));

    data->num = ft_atoi(av[1]);
    data->ttd = ft_atoi(av[2]);
    data->tte = ft_atoi(av[3]);
    data->tts = ft_atoi(av[4]);

    return (data);
}

bool    is_digit(int c)
{
    if (c >= 48 && c <= 57)
        return (TRUE);
     return (FALSE);
}
bool    check_ac(int ac)
{
    if (ac == 5)
        return (TRUE);
    if (ac > 5)
    {
        ft_putstr_fd("Too many arguments\n", 1);
        exit(1);
    }
    else if (ac < 5)
    {
        ft_putstr_fd("Too few arguments\n", 1);
        exit(1);
    }

    return (TRUE);
}

bool    valid_args(int ac, char **av)
{
    int i;
    int j;

    i = 1;
    if (!check_ac(ac))
        return (FALSE);
    while (av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (is_digit(av[i][j]) == FALSE|| is_whitespace(av[i][j]) == TRUE)
            {
                ft_putstr_fd("Invalid arguments", 1);
                exit(1);
            }
            j++;
        }
        i++;
    }
    return (TRUE);
}

t_philo *parse(int ac, char **av)
{
    t_philo *data;

    if (valid_args(ac, av))
        data = init_struct(av);
    printf("%d\n", data->num);
    return (data);
}


// int main(int ac, char *av[])
// {
//     parse(ac, av);
//
//     return EXIT_SUCCESS;
// }

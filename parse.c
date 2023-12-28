

#include "libft/libft.h"
#include "philo.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_whitespace(const char c) {
  if (c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
    return (TRUE);
  else
    return (FALSE);
}

void init_args(char **av, t_parse *data)
{

  data->max = ft_atoi(av[1]);
  data->ttd = ft_atoi(av[2]);
  data->tte = ft_atoi(av[3]);
  data->tts = ft_atoi(av[4]);
  if (av[5])
    data->ntte = ft_atoi(av[5]);
  else
    data->ntte = -1;
  if (data->max < 0 || data->ttd < 0 || data->tte < 0 || data->tts < 0)
      {
        ft_putstr_fd("Invalid arguments", 1);
        return ;
      }
}

bool is_digit(int c) {
  if (c >= 48 && c <= 57)
    return (TRUE);
  return (FALSE);
}
bool check_ac(int ac) {
  if (ac == 5 || ac == 6)
    return (TRUE);
  if (ac > 6) {
    ft_putstr_fd("Too many arguments\n", 1);
    exit(1);
  } else if (ac < 5) {
    ft_putstr_fd("Too few arguments\n", 1);
    exit(1);
  }
  return (TRUE);
}

// check for max values in args

bool valid_args(int ac, char **av) {
  int i;
  int j;

  i = 1;

  if (!check_ac(ac))
    return (FALSE);
  while (av[i]) {
    j = 0;
    if (!av[i] && av[i][j])
      ft_putstr_fd("Invalid arguments", 1);      
    while (av[i][j]) {
      if (is_digit(av[i][j]) == FALSE || is_whitespace(av[i][j]) == TRUE) {
        ft_putstr_fd("Invalid arguments", 1);
        exit(1);
      }
      j++;
    }
    i++;
  }
  return (TRUE);
}

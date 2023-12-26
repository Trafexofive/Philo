

#include "philo.h"

int main(int ac, char *av[])
{
  t_parse *data;

  data = parse(ac, av);

  printf("%du\n", data->ttd);

  return 0;
}

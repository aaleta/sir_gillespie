#include "head.h"

gsl_rng *random_gsl;

void seedRNG(int seed)
{
    const gsl_rng_type *T;

    gsl_rng_env_setup();
    T = gsl_rng_default;
    random_gsl = gsl_rng_alloc(T);
    gsl_rng_set(random_gsl, seed);
}

void addElementToList(List *list, int element)
{
    list->n++;
    list->v = realloc(list->v, list->n * sizeof *list->v);
    list->v[list->n - 1] = element;
}

int randomElementFromList(List list)
{
    return list.v[gsl_rng_uniform_int(random_gsl, list.n)];
}

int removeRandomElementFromList(List *list)
{
    int element, index;
    index = gsl_rng_uniform_int(random_gsl, list->n);
    element = list->v[index];
    list->n--;
    list->v[index] = list->v[list->n];
    
    return element;
}

int countFileLines(char *filename)
{
  FILE *file;
  char buffer[1024], lastchar = '\n';
  size_t bytes;
  int lines = 0;

  file = fopen(filename, "r");
  while((bytes = fread(buffer, 1, sizeof(buffer) - 1, file)))
    {
      lastchar = buffer[bytes - 1];
      for(char *c = buffer; (c = memchr(c, '\n', bytes - (c - buffer))); c++)
        lines++;
    }

  if(lastchar != '\n')
    lines++; // Count the last line if it does not end in a newline

  fclose(file);

  return lines;
}

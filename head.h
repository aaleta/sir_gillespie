#define  _GNU_SOURCE

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

/* Data structures */
typedef enum {S, I, R, V} State;

typedef struct Parameters {
    // Network parameters;
    int n_nodes;
    int max_degree;
    int n_groups;
    // Model parameters
    double lambda;
    double delta;
    int initial_infected;
    char *vaccination_type;
    double vaccination_fraction;
    // Simulation parameters
    int n_runs;
    int seed;
} Parameters;

typedef struct Rate {
    double infection;
    double recovery;
    double total;
} Rate;

typedef struct List {
    int n;
    int *v;
} List;

typedef struct Node {
    int group;
    State state;
    bool vaccinated;
    List links;
} Node;

typedef struct RunInfo {
    double t;
    int id;
    int n_infected_links;
    List infected_nodes;
    int n_recovered_nodes;
    char f_verbose[256];
    char f_prevalence[256];
    int print_counter;
} RunInfo;

/* Global variables */
extern Node *node;
extern Parameters parameters;
extern gsl_rng *random_gsl;
extern RunInfo run_info;
extern Rate rate;

/* Functions main */
extern void setParameters(char**);
extern int getMaximumDegree();
extern void cleanUp();
/* Functions read */
extern void readData();
extern void readNodes();
extern void readLinks();
extern void readVaccination();
/* Functions spread */
extern void init();
extern void resetState();
extern void Gillespie();
extern void infection();
extern void recovery();
/* Functions output */
extern void resetFiles();
extern void printVerbose();
extern void printResults();
/* Functions utils */
extern void seedRNG(int);
extern void addElementToList(List*, int);
extern int randomElementFromList(List);
extern int removeRandomElementFromList(List*);
extern int countFileLines(char*);


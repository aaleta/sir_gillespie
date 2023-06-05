#include "head.h"

Parameters parameters;
RunInfo run_info;

int main(int argc, char *argv[])
{
    /* Initial configuration */
    setParameters(argv);
    seedRNG(parameters.seed);

    /* Load Data */
    readData();
    resetFiles();
    parameters.max_degree = getMaximumDegree();
    
    /* Run simulation */
    for(run_info.id = 0; run_info.id < parameters.n_runs; run_info.id++) {
        init();
        while(run_info.infected_nodes.n > 0)
          Gillespie();
        
        printResults();
    }

    cleanUp();

    return 0;
}

void setParameters(char *argv[])
{
    // Variable parameters
    parameters.lambda = atof(argv[1]);
    parameters.n_runs = atoi(argv[2]);
    parameters.vaccination_type = argv[3];
    parameters.vaccination_fraction = atof(argv[4]);

    // Fixed parameters
    parameters.delta = 1;
    parameters.initial_infected = 10;
    parameters.seed = time(NULL);
}

int getMaximumDegree() {
    int maximum = 0;
    
    for(int i = 0; i < parameters.n_nodes; i++)
        if(node[i].links.n > maximum)
            maximum = node[i].links.n;

    return maximum;
}

void cleanUp()
{
    for(int i = 0; i < parameters.n_nodes; i++)
      free(node[i].links.v);
    free(node);
}

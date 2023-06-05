#include "head.h"

Rate rate;
RunInfo run_info;

void init()
{
    int selected_node;

    run_info.t = 0;
    run_info.n_recovered_nodes = 0;

    for(int i = 0; i < parameters.n_nodes; i++) {
        node[i].state = node[i].vaccinated?V:S;
    }

    for(int i = 0; i < parameters.initial_infected; i++) {
        do
            selected_node = gsl_rng_uniform_int(random_gsl, parameters.n_nodes);
        while(node[selected_node].state != S);

        node[selected_node].state = I;
    }

    resetState();

#ifdef VERBOSE
    run_info.print_counter = 0;
#endif
}

void resetState()
{
    run_info.infected_nodes.n = 0;
    run_info.n_infected_links = 0;
    for(int i = 0; i < parameters.n_nodes; i++) {
        if(node[i].state == I) {
            addElementToList(&run_info.infected_nodes, i);
            run_info.n_infected_links += node[i].links.n;
        }
    }

    rate.infection = parameters.lambda * run_info.n_infected_links;
    rate.recovery = parameters.delta * run_info.infected_nodes.n;
    rate.total = rate.infection + rate.recovery;
}

void Gillespie()
{
    run_info.t += 1.0/rate.total;

    if(gsl_rng_uniform(random_gsl) < rate.infection / rate.total) {
        infection();
    } else {
        recovery();
    }

#ifdef VERBOSE    
    printVerbose();
#endif
}

void infection()
{
    int source, target;

    do
        source = randomElementFromList(run_info.infected_nodes);
    while(gsl_rng_uniform(random_gsl) > node[source].links.n / (double) parameters.max_degree);

    if(node[source].links.n > 0) {
        target = randomElementFromList(node[source].links);

        if(node[target].state == S) {
            node[target].state = I;
            addElementToList(&run_info.infected_nodes, target);

            run_info.n_infected_links += node[target].links.n;

            rate.infection = parameters.lambda * run_info.n_infected_links;
            rate.recovery += parameters.delta;
            rate.total = rate.infection + rate.recovery;
        }
    }
}

void recovery()
{
    int selected;

    selected = removeRandomElementFromList(&run_info.infected_nodes);
    run_info.n_infected_links -= node[selected].links.n;
    run_info.n_recovered_nodes++;

    node[selected].state = R;

    rate.infection = parameters.lambda * run_info.n_infected_links;
    rate.recovery -= parameters.delta;
    rate.total = rate.infection + rate.recovery;
}

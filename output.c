#include "head.h"

void resetFiles()
{
    FILE *f;
    
    sprintf(run_info.f_prevalence, "results/prevalence_l%.2lf_%s_v%.2lf.txt", parameters.lambda, parameters.vaccination_type, parameters.vaccination_fraction);
    f = fopen(run_info.f_prevalence, "w");
    for(int i = 0; i < parameters.n_groups; i++)
      fprintf(f,"\"P%d\" ", i);
    fprintf(f,"\"run_id\"\n");
    fclose(f);
    
#ifdef VERBOSE
    sprintf(run_info.f_verbose, "results/results_l%.2lf_%s_v%.2lf_verbose.txt", parameters.lambda, parameters.vaccination_type, parameters.vaccination_fraction);
    f = fopen(run_info.f_verbose, "w");
    fprintf(f, "\"t\" \"n_infected\" \"n_recovered\" \"run_id\"\n");
    fclose(f);
#endif
}

void printVerbose()
{
    FILE *f;

    if(run_info.print_counter == 100) {
        f = fopen(run_info.f_verbose, "a");
        fprintf(f, "%lf %d %d %d\n", run_info.t, run_info.infected_nodes.n, run_info.n_recovered_nodes, run_info.id);
        fclose(f);
    } else {
        run_info.print_counter++;
    }
}

void printResults()
{
    FILE *f;
    int *prevalence;
    
    prevalence = calloc(parameters.n_groups, sizeof *prevalence);
    for(int i = 0; i < parameters.n_nodes; i++)
      if(node[i].state == R)
         prevalence[node[i].group]++;

    f = fopen(run_info.f_prevalence, "a");
    for(int i = 0; i < parameters.n_groups; i++)
      fprintf(f,"%d ", prevalence[i]);
    fprintf(f,"%d\n", run_info.id);
    fclose(f);
    
    free(prevalence);
}

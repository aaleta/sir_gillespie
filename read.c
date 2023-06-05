#include "head.h"

Node *node;

void readData()
{
    readNodes();
    readLinks();
    readVaccination();
}

void readNodes()
{
    FILE *f;
    int id, group, max_group;
    char filename[256];

    sprintf(filename, "data/nodes.txt");
    parameters.n_nodes = countFileLines(filename);
    node = malloc(parameters.n_nodes * sizeof *node);
    max_group = 0;
    
    f = fopen(filename, "r");
    for(int i = 0; i < parameters.n_nodes; i++)
    {
        fscanf(f, "%d %d\n", &id, &group);
        node[id].group = group;
        if(group > max_group)
          max_group = group;
    }
    fclose(f);
    
    // Assuming that groups start at 0
    parameters.n_groups = max_group + 1;
}

void readLinks()
{
    FILE *f;
    size_t len = 0;
    char *line = NULL;
    int s, t;

    for(int i = 0; i < parameters.n_nodes; i++) {
        node[i].links.n = 0;
        node[i].links.v = malloc(sizeof *node[i].links.v);
    }

    f = fopen("data/links.txt", "r");
    while(getline(&line, &len, f) != -1)
    {
        s = atoi(strtok(line, " "));
        t = atoi(strtok(NULL, " "));

        addElementToList(&node[s].links, t);
        addElementToList(&node[t].links, s);
    }
    fclose(f);
}

void readVaccination()
{
    FILE *f;
    char filename[256];
    int id;
    double n_vaccinated;

    n_vaccinated = parameters.n_nodes * parameters.vaccination_fraction;
    sprintf(filename, "data/nodes_%s.txt", parameters.vaccination_type);
    f = fopen(filename, "r");
    for(int i = 0; i < parameters.n_nodes; i++) {
        if(i >= n_vaccinated)
            break;
        
        fscanf(f,"%d\n",&id); 
        node[id].state = V;
        node[id].vaccinated = true;
    }
    fclose(f);
}

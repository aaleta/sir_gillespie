# Description

This repository contains a C code that implements simulations of the SIR (Susceptible-Infectious-Recovered) model on networks using the Gillespie algorithm. For more detailed information about the algorithm, please refer to the following papers and references therein:

[1] [Fundamentals of spreading processes in single and multilayer complex networks](https://doi.org/10.1016/j.physrep.2018.06.007)

[2] [Optimized Gillespie algorithms for the simulation of Markovian epidemic processes on large and heterogeneous networks](https://doi.org/10.1016/j.cpc.2017.06.007)

[3] [Solving the Dynamic Correlation Problem of the Susceptible-Infected-Susceptible Model on Networks](https://doi.org/10.1103/PhysRevLett.116.258301)

The code can be used to study the effect of different vaccination strategies. It requires three data files:

1. `data/nodes.txt`: a two column file with the `ID` and `group` of each node. Groups do not have any effect on the simulation and thus it can be set to 0 if desired.
2. `data/links.txt`: a two column file with the `Source ID` and `Target ID`of each link. It is assumed that the network is undirected.
3. `data/nodes_vaccination_strategy.txt`: where *vaccination_strategy* is a string representing the strategy. Two example strategies are provided: degree-based and random strategies.

# Prerequisites

Before compiling the code, ensure that you have the following prerequisites installed on your system:

1. GCC (GNU Compiler Collection): The code is written in C and requires the GCC compiler to be installed to compile it. It has been tested with GCC version 9.4.0. You can check if GCC is installed and verify its version by running the following command in your terminal:

```
gcc --version
```

2. GSL (GNU Scientific Library): The code uses the GSL library for certain computations. Make sure you have the GSL library installed on your system. It has been tested with GSL version 2.6. You can check if GSL is installed and verify its version by running the following command in your terminal:

```
gsl-config --version
```

If you have different versions installed, the code may still work, but it is recommended to use the tested versions for optimal results.

# Compilation instructions

To compile the code, follow these steps:

1. Clone the repository to your local machine:

```
git clone https://github.com/aaleta/sir_gillespie
```

2. Change to the repository directory

```
cd sir_gillespie
```

3. Run the following command to compile the code with basic settings:

```
make basic
```

This command will use the Makefile to compile the code using the `basic` target. Alternatively, if you want to compile the code with additional verbosity enabled, run the following command instead:

```
make verbose
```

4. After sucessful compilation, the executable file `sir` or `sir_verbose` will be generated, depending on the compilation target you chose.

# Running the Program

Once the code is sucessfully compiled, execute the following command in your terminal:

```
./sir lambda n_runs vaccination_type vaccination_fraction
```

Replace `sir` with `sir_verbose` if you compiled the code with the `verbose` target.

The program requires the following input parameters:

- *lambda*: a floating-point value representing the transmission rate.
- *n_runs*: an integer value indicating the number of runs.
- *vaccination_type*: name of the strategy that should be followed. The code assumes that there will be a file named data/nodes_*vaccination_type*.txt with the ID of the nodes to be vaccinated ordered from most important to least important.
- vaccination_fraction: a floating-point value between 0 and 1 representing the fraction of those nodes that should be vaccinated.

# Output

The program generates output files that store the simulation results. The output files are created in a directory called "results" within the repository directory.

- *Prevalence File*: The prevalence file (prevalence_l\<lambda>_<vaccination_type>_v<vaccination_fraction>.txt) stores the prevalence of the infection across different groups. Each line of the file represents a simulation run, and the columns represent the prevalence in each group. The last column represents the run ID. The file is in a tabular format, with values separated by spaces.

```
"P0" "P1" "P2" "P3" "run_id"
10  5  8  3  0
12  7  6  2  1
...
```

- Verbose File (if VERBOSE flag is enabled): The verbose file (results_l\<lambda>_<vaccination_type>_v<vaccination_fraction>_verbose.txt) provides additional detailed information about the simulation. It stores the time (t), the number of infected individuals (n_infected), the number of recovered individuals (n_recovered), and the run ID. The file is in a tabular format, with values separated by spaces.

```
"t" "n_infected" "n_recovered" "run_id"
0.0  0  0   0
0.5  3  1   1
1.0  5  3   2
...
```

# Additional Notes

- The compilation process assumes that the necessary libraries and header files are available in the default system paths. If you have installed the libraries in a non-standard location, you may need to adjust the compilation flags or include paths in the Makefile.

- This README was created with the assistance of ChatGPT, an AI language model developed by OpenAI.


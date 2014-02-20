

#include <fstream>
#include <time.h>
#include <string>
#include <sstream>
#include "CRandomGenerator.h"
#include "CPopulation.h"
#include "COptionParser.h"
#include "CStoppingCriterion.h"
#include "CEvolutionaryAlgorithm.h"
#include "global.h"
#include "CIndividual.h"

using namespace std;

#include "regressionIndividual.hpp"
bool INSTEAD_EVAL_STEP = false;

CRandomGenerator* globalRandomGenerator;
extern CEvolutionaryAlgorithm* EA;
#define STD_TPL

// User declarations
#line 12 "regression.ez"


// these 3 defines are mandatory here. Adjust as you like.
#define NO_FITNESS_CASES 5900
#define VAR_LEN 11
#define OBJECTIVE_FUNCTION 0
#define GROW_FULL_RATIO 0.5
#define FILENAME1 "swing1.csv"
#define FILENAME2 "swing2.csv"

#define NUMTHREAD 1024
#define MAX_STACK 15

// Some options
//#define NORMALIZE
//#define DIVISION      // You have to comment or uncomment the OP_DIV.
                      //Look for //DIVISION
#define DIVPENALTY 4  // 1)INCREMENT, 2)MULTIPLY, 3)GEN_PROGRESSIVE,
                      //4)INVALID_PROGRESSIVE, 5) REPLACE, 6)KILL(default)
//#define SINCOS      // You have to comment or uncomment
                      // the OP_SIN OP_COS. Look for //SINCOS
//#define PMUTVAR 1     // 1)EXP, 2)INVERSE(default)
                      // You have to set mutation probability for the initial value.
//#define FILES2
#define FITNESS 6    // 1) sum sqrt(abs(ERROR)) 2) sum abs(ERROR), 3) sum ERROR*ERROR,
                     // 4) sqrt of 1, 5) sqrt of 2, 6) sqrt of 3 (default)
#define MUTATOR 5    // 1) ch opCode or ERC, select height 
                     // 2) ch ERC value, select an erc node
                     // 3) ch opCode or ERC, select heights (mutation per gene)
                     // 4) ch opCode or ERC, select nodes (mutation per gene)
                     // 5) replace a node by a globalRandomGenerator->random tree, select height
#define CROSSOVER
#define INITIALIZER  // creates 0.5 full, 1/(init_max_depth-init_min_depth) depth.
                     // non-necessary-terminal nodes are 0.5 operator, 0.5 terminal.
#define PRINT
#define FILEOUT


// Options dependancy

// If the division is not used create a false OP_CODE to avoid
// problems in tests.
#ifndef DIVISION
#define OP_DIV 100
#endif

// Cannot normalize sine and cosine.
#ifdef NORMALIZE
#undef SINCOS
#endif

// Cannot perform division test if not normalized
// Perform division test is useless if there is no division.
#if !defined DIVISION || !defined NORMALIZE
#undef DIVPENALTY
#endif

// Normalization does not handle several files.
#ifdef NORMALIZE
#undef FILES2
#endif

// If there is only one file, th second filename is useless.
#ifndef FILES2
#undef FILENAME2
#endif

// There is an output file only if there are things to print.
#ifndef PRINT
#undef FILEOUT
#endif

// If new mutation or crossover operator are used, they will
// need to perform some action on GPNode.
#if defined MUTATOR || defined CROSSOVER || defined FILEOUT
#define GPNODEOP
#endif

// If the mutation creates a part of the tree it will need
// the function which initialize trees.
#if defined MUTATOR && !defined INITIALIZER
#if MUTATOR==5 || MUTATOR==6
#define INITIALIZER
#endif
#endif




// User classes


// User functions

#line 101 "regression.ez"

// include
#include "add/globalDeclarations.add"
#include "add/generateAndFreeData.add"
//#include "add/GPNodeCompare.add"
#include "add/SNode.add"
#include "add/best.add"

#ifdef INITIALIZER
#include "add/initializer.add"
#endif

#ifdef NORMALIZE
#include "add/normalize.add"
#endif

#ifdef GPNODEOP
#include "add/GPNodeOp.add"
#endif

#ifdef MUTATOR
#include "add/mutator.add"
#endif

#ifdef DIVISION
#include "add/divisionTest.add"
#endif

#ifdef PMUTVAR
#include "add/mutation.add"
#endif

#ifdef PRINT
#include "add/print.add"
#endif

#ifdef CROSSOVER
#include "add/crossover.add"
#endif



// Initialisation function
void EASEAInitFunction(int argc, char *argv[]){
#line 144 "regression.ez"

{
    // ///////////////// TEST
    // GPNode* b = best();
    // SNode* s = createSNode(b, opArity);
    // std::cout << sNodeToMatlab(s) << endl;
    // exit(0);

    ///////////// Set parameters.
    setParam(); // See globalDeclaration.add

    ///////////// Generate data.
#ifdef FILES2
    generateData(&inputs1, &output1, FILENAME1, &inputs2, &output2, FILENAME2, VAR_LEN, OBJECTIVE_FUNCTION);
    inputs = new float*[NO_FITNESS_CASES];
    for (int i = 0; i < NO_FITNESS_CASES; i++) {
	inputs[i] = new float[VAR_LEN];
    }
    outputs = new float[NO_FITNESS_CASES];
    inputs = inputs2;
    outputs = output2;
#else
    generateData(&inputs, &outputs, FILENAME1, VAR_LEN, OBJECTIVE_FUNCTION);
#endif    
    
    ////////////// Normalize.
#ifdef NORMALIZE
    // see normalize.add
    normalizeData(&inputs, &normalizationCoeff, NO_FITNESS_CASES, VAR_LEN);
#endif

    ///////////// Print parameters.
#ifdef PRINT
    // see print.add
    setDescriptions();
    print_prm();
#endif

}
}

// Finalization function
void EASEAFinalization(CPopulation* population){
#line 185 "regression.ez"

{
#ifdef PRINT
    printSolution();
#endif    

    free_data();
}
}



void evale_pop_chunk(CIndividual** population, int popSize){
  
// No Instead evaluation step function.

}

void regressionInit(int argc, char** argv){
	
  EASEAInitFunction(argc, argv);

}

void regressionFinal(CPopulation* pop){
	
  EASEAFinalization(pop);
;
}

void EASEABeginningGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	#line 426 "regression.ez"
{
#line 195 "regression.ez"

{
    /////////// Test the diversity (take a LONG time)
    /*
    printf("mut: %d, cross: %d, mutClone: %d, crossClone: %d\n",
	   mut, cross, mutClone, crossClone);
    mut = cross = mutClone = crossClone = 0;
    
    // Initialisation du tableau d'index.
    int length = EA->population->parentPopulationSize;
    IndividualImpl** pop = (IndividualImpl**)EA->population->parents;
    int index[length];
    for (int i = 0; i < length; i++) {
	index[i] = i;
    }
    long nbTest = 0;
    int fit = 0, tree = 0;
    // Crible de la population pour n'avoir que des individus différents.
    for (int i = 0; i < length; i++) {
	for (int j = i+1; j < length; j++) {
	    nbTest++;
	    if (pop[index[i]]->fitness != pop[index[j]]->fitness) continue;
	    fit++;
	    if (GPNodeCompare(pop[index[i]]->root, pop[index[j]]->root))
		{index[j] = index[--length];tree++;}
	}
    }
    printf("test: %ld, fitness: %d, tree: %d\n", nbTest, fit, tree);
    printf("different individuals: %d\n", length);
    */
    /////////////// Change mutation probability
#ifdef PMUTVAR
    // see mutation.add
    updatePMut();
#endif

    /////////////// Change data
#ifdef FILES2
    if (EA->getCurrentGeneration()%2) {
	outputs = output1;
	inputs = inputs1;
    } else {
	outputs = output2;
	inputs = inputs2;
    }
    /*    for (int i = 0; i < VAR_LEN-1; i++) {
	std::cout << inputs[2][i] << ", ";
    }
    std::cout << inputs[2][VAR_LEN-1] << endl;*/
#endif

}
}
}

void EASEAEndGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	{

{    
}
}
}

void EASEAGenerationFunctionBeforeReplacement(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	{

{

    /////////////// Test population for division
#ifdef DIVPENALTY
    // see divisionTest.add
    populationDivisionValidity();
#endif

}
}
}


IndividualImpl::IndividualImpl() : CIndividual() {
      root=NULL;
 
  // Genome Initialiser
#line 278 "regression.ez"

{
#ifdef INITIALIZER
    (*this).root = initializer();
#else
    (*this).root = ramped_hh();
    //(*this).root = best();
#endif
}

  valid = false;
  isImmigrant = false;
}

CIndividual* IndividualImpl::clone(){
	return new IndividualImpl(*this);
}

IndividualImpl::~IndividualImpl(){
  // Destructing pointers
  if (root) delete root;
  root=NULL;

}


float IndividualImpl::evaluate(){
  if(valid)
    return fitness;
  else{
    valid = true;
    
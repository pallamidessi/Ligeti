

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

#include "listsortIndividual.hpp"
bool INSTEAD_EVAL_STEP = false;

CRandomGenerator* globalRandomGenerator;
extern CEvolutionaryAlgorithm* EA;
#define STD_TPL

// User declarations
#line 12 "listsort.ez"

  int SIZE=10;
  double pMutPerGene=0.4;

  inline void swap(int& a,int& b) {int c=a; a=b; b=c;}



// User classes

class Element {
public:
// Default methods for class Element
  Element(){  // Constructor
    pNext=NULL;
  }
  Element(const Element &EASEA_Var) {  // Copy constructor
    pNext=(EASEA_Var.pNext ? new Element(*(EASEA_Var.pNext)) : NULL);
    Value=EASEA_Var.Value;
  }
  virtual ~Element() {  // Destructor
    if (pNext) delete pNext;
    pNext=NULL;
  }
  string serializer() {  // serialize
  	ostringstream EASEA_Line(ios_base::app);
	if(this->pNext != NULL){
		EASEA_Line << "\a ";
		EASEA_Line << this->pNext->serializer() << " ";
}
	else
		EASEA_Line << "NULL" << " ";
	EASEA_Line << this->Value << " ";
  	return EASEA_Line.str();
  }
  void deserializer(istringstream* EASEA_Line) {  // deserialize
  	string line;
	(*EASEA_Line) >> line;
	if(strcmp(line.c_str(),"NULL")==0)
		this->pNext = NULL;
	else{
		this->pNext = new Element;
		this->pNext->deserializer(EASEA_Line);
	}	(*EASEA_Line) >> this->Value;
  }
  Element& operator=(const Element &EASEA_Var) {  // Operator=
    if (&EASEA_Var == this) return *this;
    if (pNext) delete pNext;
    pNext = (EASEA_Var.pNext? new Element(*(EASEA_Var.pNext)) : NULL);
    Value = EASEA_Var.Value;
  return *this;
  }

  bool operator==(Element &EASEA_Var) const {  // Operator==
    if (((pNext) && (!EASEA_Var.pNext)) || ((!pNext) && (EASEA_Var.pNext))) return false;
    if ((pNext)&&(pNext!=EASEA_Var.pNext)) return false;
    if (Value!=EASEA_Var.Value) return false;
  return true;
  }

  bool operator!=(Element &EASEA_Var) const {return !(*this==EASEA_Var);} // operator!=

  friend ostream& operator<< (ostream& os, const Element& EASEA_Var) { // Output stream insertion operator
    if (EASEA_Var.pNext) os << "pNext:" << *(EASEA_Var.pNext) << "\n";
    os <<  "Value:" << EASEA_Var.Value << "\n";
    return os;
  }

// Class members 
  Element *pNext;
  int Value;
};


// User functions

#line 20 "listsort.ez"

void cross(IndividualImpl *pChild, IndividualImpl *pParent, int locus){
  Element *p, *pChildList, *pParentList;
  pChildList=pChild->pList; pParentList=pParent->pList;
  for (int i=0;i<SIZE;i++){
    if (i>=locus){
      for(p=pChild->pList;pParentList->Value!=p->Value;p=p->pNext);
      swap(p->Value, pChildList->Value);
    }
    pChildList=pChildList->pNext;
    pParentList=pParentList->pNext;
  }
}


// Initialisation function
void EASEAInitFunction(int argc, char *argv[]){
#line 34 "listsort.ez"

  if ((argc>1)&&(!strcmp(argv[1],"size"))) SIZE=atoi(argv[2]);
}

// Finalization function
void EASEAFinalization(CPopulation* population){
#line 45 "listsort.ez"

  std::cout << (*population) ;
}



void evale_pop_chunk(CIndividual** population, int popSize){
  
// No Instead evaluation step function.

}

void listsortInit(int argc, char** argv){
	
  EASEAInitFunction(argc, argv);

}

void listsortFinal(CPopulation* pop){
	
  EASEAFinalization(pop);
;
}

void EASEABeginningGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	#line 132 "listsort.ez"
{
#line 100 "listsort.ez"

  if ((*EZ_NB_GEN)-(*EZ_current_generation)==10) pMutPerGene=0.1; 
}
}

void EASEAEndGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	{

  if ((*EZ_NB_GEN)-(*EZ_current_generation)==10) pMutPerGene=0.1; 
}
}

void EASEAGenerationFunctionBeforeReplacement(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	
// No generation function.

}


IndividualImpl::IndividualImpl() : CIndividual() {
      pList=NULL;
 
  // Genome Initialiser
#line 49 "listsort.ez"

  Element *pElt;
  (*this).Size=0;                       
  (*this).pList=NULL;
  for (int i=0;i<SIZE;i++){  // creation of a linked list of SIZE elements
    pElt=new Element;        // with the decreasing values:
    pElt->Value=i+1;         //       (SIZE, SIZE-1, ... , 3, 2, 1)
    pElt->pNext=(*this).pList;
    (*this).pList=pElt;
    (*this).Size++;
  }

  valid = false;
  isImmigrant = false;
}

CIndividual* IndividualImpl::clone(){
	return new IndividualImpl(*this);
}

IndividualImpl::~IndividualImpl(){
  // Destructing pointers
  if (pList) delete pList;
  pList=NULL;

}


float IndividualImpl::evaluate(){
  if(valid)
    return fitness;
  else{
    valid = true;
    #line 80 "listsort.ez"

  int i=0,eval=0;
  Element *p=(*this).pList;
  while(p->pNext){
    if (p->Value==++i) eval+=10;
    if (p->Value<p->pNext->Value) eval+=4;
    else eval-=2;
    p=p->pNext;
  }
  if (p->Value==SIZE) eval+=10;

  return fitness =  (eval<0 ? 0 : eval);

  }
}

void IndividualImpl::boundChecking(){
	
// No Bound checking function.
}

string IndividualImpl::serialize(){
    ostringstream EASEA_Line(ios_base::app);
    // Memberwise serialization
	EASEA_Line << this->Size << " ";
	if(this->pList != NULL){
		EASEA_Line << "\a ";
		EASEA_Line << this->pList->serializer() << " ";
	}
	else
		EASEA_Line << "NULL" << " ";

    EASEA_Line << this->fitness;
    return EASEA_Line.str();
}

void IndividualImpl::deserialize(string Line){
    istringstream EASEA_Line(Line);
    string line;
    // Memberwise deserialization
	EASEA_Line >> this->Size;
	EASEA_Line >> line;
	if(strcmp(line.c_str(),"NULL")==0)
		this->pList = NULL;
	else{
		this->pList = new Element;
		this->pList->deserializer(&EASEA_Line);
	}
    EASEA_Line >> this->fitness;
    this->valid=true;
    this->isImmigrant = false;
}

IndividualImpl::IndividualImpl(const IndividualImpl& genome){

  // ********************
  // Problem specific part
  // Memberwise copy
    Size=genome.Size;
    pList=(genome.pList ? new Element(*(genome.pList)) : NULL);



  // ********************
  // Generic part
  this->valid = genome.valid;
  this->fitness = genome.fitness;
  this->isImmigrant = false;
}


CIndividual* IndividualImpl::crossover(CIndividual** ps){
	// ********************
	// Generic part
	IndividualImpl** tmp = (IndividualImpl**)ps;
	IndividualImpl parent1(*this);
	IndividualImpl parent2(*tmp[0]);
	IndividualImpl child(*this);

	//DEBUG_PRT("Xover");
	/*   cout << "p1 : " << parent1 << endl; */
	/*   cout << "p2 : " << parent2 << endl; */

	// ********************
	// Problem specific part
  	#line 62 "listsort.ez"

  int locus=globalRandomGenerator->random(0,SIZE-1);
  cross(&child, &parent2, locus);



	child.valid = false;
	/*   cout << "child : " << child << endl; */
	return new IndividualImpl(child);
}


void IndividualImpl::printOn(std::ostream& os) const{
	
  os << "Size:" << (*this).Size << "\n";
  os << "pList:" << *((*this).pList) << "\n";
  os << "This was MY display function !\n";

}

std::ostream& operator << (std::ostream& O, const IndividualImpl& B)
{
  // ********************
  // Problem specific part
  O << "\nIndividualImpl : "<< std::endl;
  O << "\t\t\t";
  B.printOn(O);

  if( B.valid ) O << "\t\t\tfitness : " << B.fitness;
  else O << "fitness is not yet computed" << std::endl;
  return O;
}


unsigned IndividualImpl::mutate( float pMutationPerGene ){
  this->valid=false;


  // ********************
  // Problem specific part
  #line 67 "listsort.ez"

  int NbMut=0;
  Element *p=(*this).pList;
  while (p->pNext){
    if (globalRandomGenerator->tossCoin(pMutPerGene)){  //We swap the current value with the next
      swap(p->Value,p->pNext->Value);
      NbMut++;
    }
    p=p->pNext;
  }
  return  NbMut>0?true:false;

}

void ParametersImpl::setDefaultParameters(int argc, char** argv){

	this->minimizing = false;
	this->nbGen = setVariable("nbGen",(int)5);

	seed = setVariable("seed",(int)time(0));
	globalRandomGenerator = new CRandomGenerator(seed);
	this->randomGenerator = globalRandomGenerator;


	selectionOperator = getSelectionOperator(setVariable("selectionOperator","Tournament"), this->minimizing, globalRandomGenerator);
	replacementOperator = getSelectionOperator(setVariable("reduceFinalOperator","Tournament"),this->minimizing, globalRandomGenerator);
	parentReductionOperator = getSelectionOperator(setVariable("reduceParentsOperator","Tournament"),this->minimizing, globalRandomGenerator);
	offspringReductionOperator = getSelectionOperator(setVariable("reduceOffspringOperator","Roulette"),this->minimizing, globalRandomGenerator);
	selectionPressure = setVariable("selectionPressure",(float)2.000000);
	replacementPressure = setVariable("reduceFinalPressure",(float)2.000000);
	parentReductionPressure = setVariable("reduceParentsPressure",(float)2.000000);
	offspringReductionPressure = setVariable("reduceOffspringPressure",(float)0.000000);
	pCrossover = 0.900000;
	pMutation = 1.000000;
	pMutationPerGene = 0.05;

	parentPopulationSize = setVariable("popSize",(int)5);
	offspringPopulationSize = setVariable("nbOffspring",(int)5);


	parentReductionSize = setReductionSizes(parentPopulationSize, setVariable("survivingParents",(float)5.000000));
	offspringReductionSize = setReductionSizes(offspringPopulationSize, setVariable("survivingOffspring",(float)5.000000));

	this->elitSize = setVariable("elite",(int)5);
	this->strongElitism = setVariable("eliteType",(int)0);

	if((this->parentReductionSize + this->offspringReductionSize) < this->parentPopulationSize){
		printf("*WARNING* parentReductionSize + offspringReductionSize < parentPopulationSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	if((this->parentPopulationSize-this->parentReductionSize)>this->parentPopulationSize-this->elitSize){
		printf("*WARNING* parentPopulationSize - parentReductionSize > parentPopulationSize - elitSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	if(!this->strongElitism && ((this->offspringPopulationSize - this->offspringReductionSize)>this->offspringPopulationSize-this->elitSize)){
		printf("*WARNING* offspringPopulationSize - offspringReductionSize > offspringPopulationSize - elitSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	

	/*
	 * The reduction is set to true if reductionSize (parent or offspring) is set to a size less than the
	 * populationSize. The reduction size is set to populationSize by default
	 */
	if(offspringReductionSize<offspringPopulationSize) offspringReduction = true;
	else offspringReduction = false;

	if(parentReductionSize<parentPopulationSize) parentReduction = true;
	else parentReduction = false;

	generationalCriterion = new CGenerationalCriterion(setVariable("nbGen",(int)5));
	controlCStopingCriterion = new CControlCStopingCriterion();
	timeCriterion = new CTimeCriterion(setVariable("timeLimit",0));

	this->optimise = 0;

	this->printStats = setVariable("printStats",1);
	this->generateCSVFile = setVariable("generateCSVFile",0);
	this->generatePlotScript = setVariable("generatePlotScript",0);
	this->generateRScript = setVariable("generateRScript",0);
	this->plotStats = setVariable("plotStats",0);
	this->printInitialPopulation = setVariable("printInitialPopulation",0);
	this->printFinalPopulation = setVariable("printFinalPopulation",0);
	this->savePopulation = setVariable("savePopulation",0);
	this->startFromFile = setVariable("startFromFile",0);

	this->outputFilename = (char*)"listsort";
	this->plotOutputFilename = (char*)"listsort.png";

	this->remoteIslandModel = setVariable("remoteIslandModel",0);
	this->ipFile = (char*)setVariable("ipFile","NULL").c_str();
	this->migrationProbability = setVariable("migrationProbability",(float)0.000000);
    this->serverPort = setVariable("serverPort",0);
}

CEvolutionaryAlgorithm* ParametersImpl::newEvolutionaryAlgorithm(){

	pEZ_MUT_PROB = &pMutationPerGene;
	pEZ_XOVER_PROB = &pCrossover;
	EZ_NB_GEN = (unsigned*)setVariable("nbGen",5);
	EZ_current_generation=0;

	CEvolutionaryAlgorithm* ea = new EvolutionaryAlgorithmImpl(this);
	generationalCriterion->setCounterEa(ea->getCurrentGenerationPtr());
	ea->addStoppingCriterion(generationalCriterion);
	ea->addStoppingCriterion(controlCStopingCriterion);
	ea->addStoppingCriterion(timeCriterion);	

	EZ_NB_GEN=((CGenerationalCriterion*)ea->stoppingCriteria[0])->getGenerationalLimit();
	EZ_current_generation=&(ea->currentGeneration);

	 return ea;
}

void EvolutionaryAlgorithmImpl::initializeParentPopulation(){
	if(this->params->startFromFile){
	  ifstream EASEA_File("listsort.pop");
	  string EASEA_Line;
  	  for( unsigned int i=0 ; i< this->params->parentPopulationSize ; i++){
	  	  getline(EASEA_File, EASEA_Line);
		  this->population->addIndividualParentPopulation(new IndividualImpl(),i);
		  ((IndividualImpl*)this->population->parents[i])->deserialize(EASEA_Line);
	  }
	  
	}
	else{
  	  for( unsigned int i=0 ; i< this->params->parentPopulationSize ; i++){
		  this->population->addIndividualParentPopulation(new IndividualImpl(),i);
	  }
	}
        this->population->actualParentPopulationSize = this->params->parentPopulationSize;
}


EvolutionaryAlgorithmImpl::EvolutionaryAlgorithmImpl(Parameters* params) : CEvolutionaryAlgorithm(params){
	;
}

EvolutionaryAlgorithmImpl::~EvolutionaryAlgorithmImpl(){

}


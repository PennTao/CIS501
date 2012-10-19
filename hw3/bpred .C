#define __STDC_FORMAT_MACROS
#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "BimodalPredictor.h"
#include "GSharePredictor.h"
#include "TournamentPredictor.h"
using namespace std;
void simulate(uint16_t predictorType,int32_t predictor_size, uint16_t htSize, uint16_t bmSize, uint16_t gsSize,FILE* inputFile, FILE* outputFile, FILE* debugOutputFile, FILE* debugInputFile)
{
  // See the documentation to understand what these variables mean.
  int32_t microOpCount;
  uint64_t instructionAddress;
  int32_t sourceRegister1;
  int32_t sourceRegister2;
  int32_t destinationRegister;
  char conditionRegister;
  char TNnotBranch;
  char loadStore;
  int64_t immediate;
  uint64_t addressForMemoryOp;
  uint64_t fallthroughPC;
  uint64_t targetAddressTakenBranch;
  char macroOperation[12];
  char microOperation[23];

  int64_t totalMicroops = 0;
  int64_t totalCondBranches = 0;

  int correct = 0;
  int incorrect = 0;
  Predictor* predictor;

  uint16_t bimodalSize = bmSize;
  uint16_t gShareSize = gsSize;
  uint16_t gShareHistorySize = htSize;
  
  switch (predictorType)
  {
  case 0:
	  predictor = new Predictor();
	  printf("naive predictor created\r\n");

	  break;
  case 1:
	  predictor = new BimodalPredictor(predictor_size);
	  printf("Bimodal predictor created\r\n");
	  fprintf(outputFile,"predictor size: %d\r\n",predictor_size);

	  break;
  case 2:
	  predictor = new GSharePredictor(predictor_size, gShareHistorySize);
	  printf("GShare predictor created\r\n");
	  fprintf(outputFile,"predictor size: %d	history table size:%d\r\n",predictor_size,gShareHistorySize);
	  break;
  case 3:
	  predictor = new TournamentPredictor(predictor_size, new BimodalPredictor(bimodalSize), new GSharePredictor(gShareSize, gShareHistorySize));
	  printf("Tournament predictor created\r\n");
	  fprintf(outputFile,"choose table size: %d	bimodal size:%d	gShare size:%d	gShare History size:%d\r\n",predictor_size,bimodalSize,gShareSize,gShareHistorySize);


	  break;
  default:
	  predictor = new Predictor();
	  printf("naive predictor created\r\n");
	  fprintf(outputFile,"predictor size: %d\r\n",predictor_size);

	  break;
  }
  //Predictor* predictor = new Predictor();
 // Predictor* predictor = new BimodalPredictor(predictor_size);
  // Predictor* predictor = new GSharePredictor(4, 3);
   //Predictor* predictor = new TournamentPredictor(3, new BimodalPredictor(3), new GSharePredictor(4, 4));

  
  while (true) {
    int result = fscanf(inputFile, 
                        "%" SCNi32
                        "%" SCNx64 
                        "%" SCNi32
                        "%" SCNi32
                        "%" SCNi32
                        " %c"
                        " %c"
                        " %c"
                        "%" SCNi64
                        "%" SCNx64
                        "%" SCNx64
                        "%" SCNx64
                        "%11s"
                        "%22s",
                        &microOpCount,
                        &instructionAddress,
                        &sourceRegister1,
                        &sourceRegister2,
                        &destinationRegister,
                        &conditionRegister,
                        &TNnotBranch,
                        &loadStore,
                        &immediate,
                        &addressForMemoryOp,
                        &fallthroughPC,
                        &targetAddressTakenBranch,
                        macroOperation,
                        microOperation);
                        
    if (result == EOF) {
      break;
    }

    if (result != 14) {
      fprintf(stderr, "Error parsing trace at line %" PRIi64 "\n", totalMicroops);
      abort();
    }

    // For each micro-op
    totalMicroops++;

    if (TNnotBranch == '-') {
      continue;  // Not a branch
    }

    if (conditionRegister != 'R') {
      continue;  // Not a conditional branch
    }

    totalCondBranches++;

    if (debugOutputFile) { // debug output trace
      predictor->print(debugOutputFile);
    }
    
    char pred = predictor->makePrediction(instructionAddress, TNnotBranch);

    if (pred == TNnotBranch) {
      correct++;
    } else {
      incorrect++;
    }
    
    if (debugOutputFile) { // debug output trace
      fprintf(debugOutputFile, "| %" PRIx64 "  %c | %c  %s%d\n", 
              instructionAddress, 
              TNnotBranch, 
              pred,
              (pred == TNnotBranch) ? "correct    " : "incorrect  ",
              incorrect);
    }
    


  }
    
      if (debugInputFile) {
      int expected_incorrect;
      fscanf(debugInputFile, "%*[^|] %*s %*s %*s %*s %*s %*s %d",  // Read many fields, throwing away all but the last
             &expected_incorrect);
      
      if (incorrect != expected_incorrect) {
        fprintf(stderr, "Mismatched mis-prediction count: %d vs %d\n", incorrect, expected_incorrect);
        abort();
      }
    }
  std::string s = predictor->getConfig();
  fprintf(outputFile, " %11i %11i %8.2f%%\n", 
           correct, incorrect, 100.0*correct/(correct+incorrect));
  
 /*   fprintf(outputFile, "%11i %11i %8.2f%%\n", 
          correct, incorrect, 100.0*correct/(correct+incorrect));*/
}

int main(int argc, char *argv[]) 
{
  int32_t predictor_size = 1;
  FILE *inputFile = stdin;
  FILE *outputFile = stdout;
  FILE *debugInputFile = NULL;
  FILE *debugOutputFile = NULL;
  uint16_t predictorType = 0;
  uint16_t htSize = 8;
  uint16_t bimodalSize =4;
  uint16_t gShareSize = 4;
  if(argc >=2)
  {
	  predictorType = atoi(argv[1]);
  }
  if(argc>=3)
  {
	  predictor_size = atoi(argv[2]);

  }
  if(argc>=4)
  {
	  htSize = atoi(argv[3]);
  }
  if (argc >= 5) {

	  bimodalSize = atoi(argv[4]);
  }
  if (argc >= 6) {

	  gShareSize = atoi(argv[5]);
  }
  
  if (argc >= 7) {
    debugOutputFile = fopen(argv[6], "w");
    assert(debugOutputFile != NULL);
  }

  if (argc >= 8) {
    debugInputFile = fopen(argv[7], "r");
    assert(debugInputFile != NULL);
  }

  simulate(predictorType,predictor_size, htSize,bimodalSize,gShareSize, inputFile, outputFile, debugOutputFile, debugInputFile);
  return 0;
}

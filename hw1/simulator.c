#define __STDC_FORMAT_MACROS

#define LOADS	0
#define STORES	1
#define UBRANCH	3
#define CBRANCH	4
#define OTHER	5
#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <map>
#include <math.h>
void simulate(FILE* inputFile, FILE* outputFile)
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
  int32_t micorPerMacro[5] = {0,0,0,0,0};
  int32_t isnCnt = 0;

  int64_t totalMicroops = 0;
  int64_t totalMacroops = 0;
 
  std::map<uint32_t, uint64_t> m_mapBitCnt;
  std::map<uint32_t, uint64_t>::iterator ItrBitCnt;

  uint64_t instructionClassifier[5] = {0,0,0,0,0};
  float instructionPercent = 0.0f;
  int64_t branchDist = 0;
  int32_t bitForBranchDist = 0;
  fprintf(outputFile, "Processing trace...\n");
  
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
	isnCnt++;
    // For each macro-op:
    if (microOpCount == 1) {
      totalMacroops++;
	  micorPerMacro[isnCnt-1]++;
	  isnCnt = 0;
    }

	//branch distances:
	if(targetAddressTakenBranch != 0)
	{
		branchDist = abs(targetAddressTakenBranch - instructionAddress);
		bitForBranchDist = 2 + floor(log(branchDist)/log(2));
		if(m_mapBitCnt.find(bitForBranchDist) == m_mapBitCnt.end())
		{
			m_mapBitCnt.insert(std::pair<uint32_t, uint64_t>(bitForBranchDist, 0));
		}
		else
			(*m_mapBitCnt.find(bitForBranchDist)).second++;
	}
	//Instruction classifier:
	if(loadStore == 'L')
	{
		instructionClassifier[LOADS]++;
	}
	else if(loadStore == 'S')
	{
		instructionClassifier[STORES]++;
	}
	
	else if((targetAddressTakenBranch != 0) && (conditionRegister ='-'))
	{
		instructionClassifier[UBRANCH]++;
	}
	else if((targetAddressTakenBranch != 0) && (conditionRegister ='R'))
	{
		instructionClassifier[CBRANCH]++;
	}
	else
	{
		instructionClassifier[OTHER]++;
	}
  }
  
  fprintf(outputFile, "Processed %" PRIi64 " trace records.\n", totalMicroops);

  fprintf(outputFile, "Micro-ops: %" PRIi64 "\n", totalMicroops);
  fprintf(outputFile, "Macro-ops: %" PRIi64 "\n", totalMacroops);
  totalMacroops = 0;
  for(uint32_t i = 0; i < sizeof(micorPerMacro)/sizeof(uint32_t); i++)
  {
	  fprintf(outputFile, "Micro/Macro count: %" PRIi32 "\n", micorPerMacro[i]);
	  totalMacroops += micorPerMacro[i];
  }
  fprintf(outputFile, "sum of Macro: %ld\r\n", totalMacroops);

  for(ItrBitCnt = m_mapBitCnt.begin(); ItrBitCnt != m_mapBitCnt.end(); ++ItrBitCnt)
  {
	  fprintf(outputFile,"Bit Length: %d	Cnt: %ld\r\n",ItrBitCnt->first, ItrBitCnt->second);
  }
  for(int i = 0; i < sizeof(instructionClassifier)/sizeof(uint64_t); i++)
  {
	  instructionPercent = instructionClassifier[i]\totalMicroops;
	  fprintf(outputFile, "instruction type%d: %ld, %f", i, instructionClassifier[i], instructionPercent);
  }

}

int main(int argc, char *argv[]) 
{
  FILE *inputFile = stdin;
  FILE *outputFile = stdout;
  
  if (argc >= 2) {
    inputFile = fopen(argv[1], "r");
    assert(inputFile != NULL);
  }
  if (argc >= 3) {
    outputFile = fopen(argv[2], "w");
    assert(outputFile != NULL);
  }
  
  simulate(inputFile, outputFile);
  return 0;
}

#define __STDC_FORMAT_MACROS

#define LOADS	0
#define STORES	1
#define UBRANCH	2
#define CBRANCH	3
#define OTHER	4
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
  char  lastConditionRegister;
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

  uint64_t extraInstruction = 0;

  uint64_t fusionPair = 0;
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
			m_mapBitCnt.insert(std::pair<uint32_t, uint64_t>(bitForBranchDist, 1));
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
	
	else if((targetAddressTakenBranch != 0) && (conditionRegister == '-'))
	{
		instructionClassifier[UBRANCH]++;
	}
	else if((targetAddressTakenBranch != 0) && (conditionRegister =='R'))
	{
		instructionClassifier[CBRANCH]++;
		if (lastConditionRegister == 'W')
			fusionPair++;
	}
	else
	{
		instructionClassifier[OTHER]++;
	}

	lastConditionRegister = conditionRegister;
  }
  
  fprintf(outputFile, "Processed %" PRIi64 " trace records.\n", totalMicroops);

  fprintf(outputFile, "Micro-ops: %" PRIi64 "\n", totalMicroops);
  fprintf(outputFile, "Macro-ops: %" PRIi64 "\n", totalMacroops);
  totalMacroops = 0;
  for(uint32_t i = 0; i < sizeof(micorPerMacro)/sizeof(uint32_t); i++)
  {
	  fprintf(outputFile, "Micro/Macro = %d count: %" PRIi32 "\n",i+1, micorPerMacro[i]);
	  totalMacroops += micorPerMacro[i];
  }
  fprintf(outputFile, "sum of Macro: %ld\r\n", totalMacroops);

  for(ItrBitCnt = m_mapBitCnt.begin(); ItrBitCnt != m_mapBitCnt.end(); ++ItrBitCnt)
  {
	  fprintf(outputFile,"Bit Length: %d	Cnt: %ld\r\n",ItrBitCnt->first, ItrBitCnt->second);
	  //extraInstruction = extraInstruction + ((floor(ItrBitCnt->first /8) - 1) > 0?(floor(ItrBitCnt->first /8) - 1):0) * ItrBitCnt->second;
	  if(ItrBitCnt->first >= 9 && ItrBitCnt->first <= 16)
		  extraInstruction += ItrBitCnt->second;
	  else if(ItrBitCnt->first >= 17)
		  extraInstruction += ItrBitCnt->second * 2;
  }
  fprintf(outputFile,"extra instructions: %ld\r\n", extraInstruction);
  for(int i = 0; i < sizeof(instructionClassifier)/sizeof(uint64_t); i++)
  {
	  instructionPercent = 100 * (float)instructionClassifier[i] / (float)totalMicroops;
	  fprintf(outputFile, "instruction type%d: %ld,	%f%%\r\n", i, instructionClassifier[i], instructionPercent);
  }
  fprintf(outputFile, "Operation Fusion Pairs: %ld	%f%%\r\n", fusionPair, 200 * (float)fusionPair / (float)totalMicroops);
  fprintf(outputFile, "fusion performance improvement: %f%%\r\n",100 * (1 - (float)(totalMicroops - fusionPair) / (float)totalMicroops));
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

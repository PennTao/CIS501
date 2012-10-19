#include "BimodalPredictor.h"

BimodalPredictor::BimodalPredictor()
{}

BimodalPredictor::BimodalPredictor(uint16_t size)
{
	pred_size = pow(2,size);
	saturatingCounters = new char[pred_size];
	memset(saturatingCounters, 'N', pred_size);
}
char BimodalPredictor::makePrediction(uint64_t isnAdd, char actualBranch)
{
	
	uint32_t index;
	index = isnAdd % pred_size;
	char predValue = toupper(saturatingCounters[index]);
//	printf("%s | %ld  %c | %c  \r\n", saturatingCounters,isnAdd, actualBranch,predValue);
	if(actualBranch == toupper(saturatingCounters[index]))
	{
		saturatingCounters[index] = toupper(saturatingCounters[index]);
		return predValue;
	}
	if(actualBranch == 'N' && saturatingCounters[index] == 't')
		saturatingCounters[index] = 'n';
	else if (actualBranch == 'N' && saturatingCounters[index] == 'T')
		saturatingCounters[index] = 't';
	else if(actualBranch == 'T' && saturatingCounters[index] == 'n')
		saturatingCounters[index] = 't';
	else if(actualBranch == 'T' && saturatingCounters[index] == 'N')
		saturatingCounters[index] = 'n';
	return predValue;
	
}

void BimodalPredictor::print(FILE * debugOutputFile)
{
	
}

std::string BimodalPredictor::getConfig()
{
	return std::string(saturatingCounters);
}
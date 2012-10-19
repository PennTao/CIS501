#include "GSharePredictor.h"

GSharePredictor::GSharePredictor()
{}

GSharePredictor::GSharePredictor(uint16_t logPredSize, uint16_t htSize)
{
	pred_size = pow(2,logPredSize);
	saturatingCounters = new char[pred_size];
	history = 0;
	historySize = pow(2,htSize);
	memset(saturatingCounters, 'N', pred_size);
}

char GSharePredictor::makePrediction(uint64_t isnAdd, char actualBranch)
{
	uint32_t index;
	char predValue;
	index = (isnAdd^history) % pred_size;
	predValue = toupper(saturatingCounters[index]);
//	printf("%s %d | %ld  %c | %c  \r\n", saturatingCounters,history,isnAdd, actualBranch,predValue);
	history = (history << 1) % historySize + (actualBranch == 'T'?1:0);
	
	if(actualBranch == predValue)
	{
		saturatingCounters[index] = toupper(saturatingCounters[index]);
		return predValue;
	}
	if(actualBranch == 'N' && saturatingCounters[index] == 't')
		saturatingCounters[index]= 'n';
	else if(actualBranch == 'N' && saturatingCounters[index] == 'T')
		saturatingCounters[index] ='t';
	else if(actualBranch == 'T' && saturatingCounters[index] == 'n')
		saturatingCounters[index] = 't';
	else if(actualBranch == 'T' && saturatingCounters[index] == 'N')
		saturatingCounters[index] = 'n';

	return predValue;
} 

std::string GSharePredictor::getConfig()
{
	return std::string(saturatingCounters);
}
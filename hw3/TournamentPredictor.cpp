#include "TournamentPredictor.h"

TournamentPredictor::TournamentPredictor()
{};

TournamentPredictor::TournamentPredictor(uint16_t chooseTableBit, BimodalPredictor* bimodal, GSharePredictor* gShare)
{
	chooseTableSize = pow(2,chooseTableBit);
	chooseTalbe = new char[chooseTableSize];
	memset(chooseTalbe, 'B', chooseTableSize);
	tour_Bimodal = bimodal;
	tour_GShare = gShare;
}

char TournamentPredictor::makePrediction(uint64_t isnAdd, char actualBranch)
{
	uint32_t index;
	char chooserDecision;
	char bimodalPredValue;
	char gSharePredValue;
	char predValue;

	index = isnAdd % chooseTableSize;
	chooserDecision = chooseTalbe[index];
	bimodalPredValue = tour_Bimodal->makePrediction(isnAdd,actualBranch);
	gSharePredValue = tour_GShare->makePrediction(isnAdd,actualBranch);
//	printf("%s \r\n",chooseTalbe);
//	printf("----------------------------------------------------\r\n");
	
 
	switch (toupper(chooserDecision))
	{
	case 'B':
		predValue = bimodalPredValue;
		break;
	case 'G':
		predValue = gSharePredValue;
		break;
	default:
		break;
	}
	if(bimodalPredValue == gSharePredValue)
		return predValue;
	if(bimodalPredValue == actualBranch)
	{
		switch (chooseTalbe[index])
		{
		case 'B':
			break;
		case 'b':
			chooseTalbe[index] = 'B';
			break;
		case 'g':
			chooseTalbe[index] ='b';
			break;
		case 'G':
			chooseTalbe[index] = 'g';
			break;
		default:
			break;
		}
	}
	else if(gSharePredValue == actualBranch)
	{
		switch (chooseTalbe[index])
		{
		case 'B':
			chooseTalbe[index] = 'b';
			break;
		case 'b':
			chooseTalbe[index] = 'g';
			break;
		case 'g':
			chooseTalbe[index] = 'G';
			break;
		case 'G':
			break;
		default:
			break;
		}
	}
	return predValue;

	
}

std::string TournamentPredictor::getConfig()
{
	return std::string(chooseTalbe);
}
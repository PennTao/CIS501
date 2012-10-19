#ifndef _GSHAREPRED
#define _GSHAREPRED

#include "Predictor.h"

class GSharePredictor :public Predictor
{
private:
	uint32_t pred_size;
	char* saturatingCounters;
	uint32_t history;
	uint32_t historySize;
public:
	GSharePredictor();
	GSharePredictor(uint16_t,uint16_t);

	char makePrediction(uint64_t,char);
	void print();
	std::string getConfig();

};


#endif // !_GSHAREPRED


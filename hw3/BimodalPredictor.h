#ifndef  _BIMODALPRED
#define _BIMODALPRED

#include "Predictor.h"

class BimodalPredictor : public Predictor
{
private:
	uint32_t pred_size;
	char* saturatingCounters;
public:
	BimodalPredictor();
	BimodalPredictor(uint16_t);
	char makePrediction(uint64_t,char);
	void print(FILE*);
	std::string getConfig();

};

#endif // ! _BIMODALPRED

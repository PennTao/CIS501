#ifndef _PRED
#define _PRED

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <cctype>
#include <string>
#include <math.h>
using namespace std;
class Predictor
{
public:
	Predictor();
	virtual char makePrediction(uint64_t,char);
	virtual void print(FILE *);
	virtual std::string getConfig();

};

#endif
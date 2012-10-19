#include "Predictor.h"

Predictor::Predictor()
{}
char Predictor::makePrediction(uint64_t, char)
{
	return 'T';
}

void Predictor::print(FILE * debugOutputFile)
{
}

std::string Predictor::getConfig()
{
	return "N/A";
}
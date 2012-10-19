#ifndef _TOURNAMENTPRED
#define _TOURNAMENTPRED

#include "Predictor.h"
#include "BimodalPredictor.h"
#include "GSharePredictor.h"
class TournamentPredictor: public Predictor
{
private:
	char* chooseTalbe;
	uint32_t chooseTableSize;
	BimodalPredictor* tour_Bimodal;
	GSharePredictor* tour_GShare;
public:
	TournamentPredictor();
	TournamentPredictor(uint16_t, BimodalPredictor*, GSharePredictor*);

	char makePrediction(uint64_t, char);
	std::string getConfig();


};


#endif // !_TOURNAMENTPRED



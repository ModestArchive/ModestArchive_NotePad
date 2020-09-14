//CoordinateCalculator.h
#ifndef _COORDINATECALCULATOR_H
#define _COORDINATECALCULATOR_H

#include"NotePadForm.h"
typedef signed long int Long;

class CoordinateCalculator {
public:
	CoordinateCalculator(NotePadForm* notePadForm);
	~CoordinateCalculator();
	CPoint CalculateCoordinateWithAbsoluteInformation(Long totalLengthToCurrent, Long rowCount);

private:
	NotePadForm* notePadForm;
};
#endif // !_COORDINATECALCULATOR_H

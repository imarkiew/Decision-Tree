/**
@Igor Markiewicz
*/
#ifndef INPUTDATAALGORITHMS_CPP
#define INPUTDATAALGORITHMS_CPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

typedef vector<string> IdAttributesAndClassification;
//Podstawowy typ danych w programie. Wektor zawierający trzyelementowe wektor : klasyfikacja, przykład, id przykładu
typedef vector<IdAttributesAndClassification> Data;

Data parseInputData(string const &, bool const &);
void randomiseData(Data &);
Data parseTestData(double const &, string const &, string const &, Data &);
Data parseValidationData(double const &, string const &, string const &, Data &);
#endif
/**
@Igor Markiewicz
*/
#ifndef DECISIONTREEALGORITHM_CPP
#define DECISIONTREEALGORITHM_CPP

#include <math.h>
#include <float.h>
#include <algorithm>
#include "InputDataAlgorithms.hpp"

//Klasa węzła lub liścia
class Node
{
	public:
	//Klasyfikacja przykładów jeśli Node jeset liściem
    int classification;
	//Wybrany test dla węzła (nr pozycji litery w ciągu) 
	int test;
	//Wartość wybranego testu
	char atributte_value;
	//Potomkowie węzła
	Node *node_A, *node_C, *node_G, *node_T, *node_N;
	//Czy Node jeset liściem
	bool isLeaf;
	//Wektor id przykładów w węźle/liściu
	vector<string> id;
	//Czy węzeł został sprawdzony(przy przycinaniu drzewa)
	bool isChecked;
	
	//Rekurencyjna destrukcja drzewa począwszy od węzła node
	void destroyRecursive(Node *&node);
	
	//Konstruktor domyślny
	Node();
	//Konstruktor
	Node(int &classification, int &test, char &atributte_value, Node *node_A, Node *node_C, Node *node_G, Node *node_T, Node *node_N, vector<string> &id, bool &isChecked);
	//Destruktor
	~Node();
	
};

bool stop(vector<string> const &, Data const &, vector<string> &);
int countCategory(vector<string> const &, Data const &);
int category(vector<string> const &, Data const &, int &);
int chooseTest(vector<string> const &, Data const &, vector<string> const &);
vector<string> eraseAttribute(vector<string> const &, int const &);
vector<string> splitId(vector<string> const &id, Data &data, char const &choosed_letter, int const &choosed_test, vector<string> const);
Node * buildDecisionTree(vector<string> &, int &, vector<string> &, Data const &, Node *, const char &);
#endif

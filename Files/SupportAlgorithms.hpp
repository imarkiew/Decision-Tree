/**
@Igor Markiewicz
*/
#ifndef SUPPORTALGORITHMS_CPP
#define SUPPORTALGORITHMS_CPP

#include "DecisionTreeAlgorithm.hpp"
#include<map>

vector<string> rewriteId(Data const &);
vector<string> rewriteAttributes(Data const &);
void preOrder(Node const *);
void deleteId(Node *);
void addTestData(Data const &, Node *);
map<string, int> predictedClassification(map<string, int> id_and_value, Node const *);
vector<double> confusionMatrix(map<string, int> const &, Data const &);
double error_for_prunning(map<string, int> const &, Data const &);
double error(vector<double> const &, Data const &);
void pruneEngine(Node *&root, Data const &data);
void pruneDecisionTree(Node *&, Data const &);
vector<double> meanConfusionMatrix(vector<vector<double>> const &);
double meanError(vector<double> const &);
#endif

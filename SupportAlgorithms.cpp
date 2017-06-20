/**
@Igor Markiewicz
*/
#include "SupportAlgorithms.hpp"

//Funkcja przepisująca id przykładów
vector<string> rewriteId(Data const &data)
{
	vector<string> id;
	for(int i = 0; i < data.size(); i++)
	{
		id.push_back(data[i][2]);
	}
	
	return id;
}

//Funkcja przepisująca atrybuty przykładów
vector<string> rewriteAttributes(Data const &data)
{
	vector<string> attributes;
	for(int i = 0; i < data[0][1].size(); i++)
	{
		attributes.push_back(to_string(i + 1));
	}
	
	return attributes;
}

//przechodzenie po drzewie w porządku preOrder począwszy od węzła node
void preOrder(Node const *node)
{
	if(node != nullptr)
	{
		cout << "Wartosc atrybutu " << node->atributte_value << endl;
		if(node->isLeaf == true)
		{
			cout << "Klasyfikator " << node->classification << endl;
		}
		else
		{
			cout << "Test " << node->test << endl;
		}
		
		for(int i = 0; i < node->id.size(); i++)
		{
			cout << "Id " << node->id[i] << endl;
		}

		cout << " " << endl;

		vector<Node *> nodes_vector;
		nodes_vector.push_back(node->node_A);
		nodes_vector.push_back(node->node_C);
		nodes_vector.push_back(node->node_G);
		nodes_vector.push_back(node->node_T);
		nodes_vector.push_back(node->node_N);
		
		for(int i = 0; i < nodes_vector.size(); i++)
		{
			if(nodes_vector[i] != nullptr)
			{
				preOrder(nodes_vector[i]);
			}
		}
	}
}

//Usuwanie przykładów z drzewa począwszy od węzła node
void deleteId(Node *node)
{
	node->id.clear();
	
	vector<Node *> nodes_vector;
	nodes_vector.push_back(node->node_A);
	nodes_vector.push_back(node->node_C);
	nodes_vector.push_back(node->node_G);
	nodes_vector.push_back(node->node_T);
	nodes_vector.push_back(node->node_N);
	
	for(int i = 0; i < nodes_vector.size(); i++)
	{
		if(nodes_vector[i] != nullptr)
		{
			deleteId(nodes_vector[i]);
		}
	}
}

//Dodawanie przykładów do drzewa 
void addTestData(Data const &data, Node *node)
{
	for(int i = 0; i < data.size(); i++)
	{
		string tmp_id = data[i][2];
		Node *tmp_node = node;
		while(tmp_node != nullptr)
		{
			tmp_node->id.push_back(tmp_id);
			if(tmp_node->isLeaf == false)
			{
				char atributte_value = data[stoi(tmp_id, nullptr, 10) - 1][1][tmp_node->test - 1];
				if(atributte_value == 'A')
				{
					tmp_node = tmp_node->node_A;
				}
				else if(atributte_value == 'C')
				{
					tmp_node = tmp_node->node_C;
				}
				else if(atributte_value == 'G')
				{
					tmp_node = tmp_node->node_G;
				}
				else if(atributte_value == 'T')
				{
					tmp_node = tmp_node->node_T;
				}
				else if(atributte_value == 'N')
				{
					tmp_node = tmp_node->node_N;
				}
			}
			else
			{
				tmp_node = node;
				break;
			}
		}
	}
}

//Przewidywana klasyfikacja zwracana w postaci <przykład, klasyfikacja>
map<string, int> predictedClassification(map<string, int> id_and_value, Node const *node)
{
	if(node->isLeaf == true)
	{
		for(int i = 0; i < node->id.size(); i++)
		{
			id_and_value[node->id[i]] = node->classification;
		}
	}
	else
	{
		vector<Node *> nodes_vector;
		nodes_vector.push_back(node->node_A);
		nodes_vector.push_back(node->node_C);
		nodes_vector.push_back(node->node_G);
		nodes_vector.push_back(node->node_T);
		nodes_vector.push_back(node->node_N);
		
		for(int i = 0; i < nodes_vector.size(); i++)
		{
				id_and_value = predictedClassification(id_and_value, nodes_vector[i]);
		}
	}
	
	return id_and_value;
}

//Macierz pomyłek
vector<double> confusionMatrix(map<string, int> const &id_and_value, Data const &data)
{
	double count_TP = 0;
	double count_TN = 0;
	double count_FP = 0;
	double count_FN = 0;
	vector<double> result;
	
	for(map<string, int>::const_iterator it = id_and_value.begin(); it != id_and_value.end(); ++it)
	{
		if(it->second == 1 && stoi(data[stoi(it->first, nullptr, 10) - 1][0], nullptr, 10) == 1)
		{
			count_TP++;
		}
		else if(it->second == 0 && stoi(data[stoi(it->first, nullptr, 10) - 1][0], nullptr, 10) == 0)
		{
			count_TN++;
		}
		else if (it->second == 1 && stoi(data[stoi(it->first, nullptr, 10) - 1][0], nullptr, 10) == 0)
		{
			 count_FP++;
		}
		else
		{
			count_FN++;
		}
	}
	
	result.push_back(count_TP);
	result.push_back(count_TN);
	result.push_back(count_FP);
	result.push_back(count_FN);
	
	return result;
}

//Obliczanie błędu z macierzy pomyłek
double error(vector<double> const &confusion_matrices, Data const &data)
{
	double result;

	double sum = confusion_matrices[0] + confusion_matrices[1] + confusion_matrices[2] + confusion_matrices[3];
	double number_of_false_values = confusion_matrices[2] + confusion_matrices[3];
	result = number_of_false_values/sum;
	
	return result;
}

//Obliczanie błędu na potrzeby przycinania
double error_for_prunning(map<string, int> const &id_and_value, Data const &data)
{
	double count_mistake = 0;
	double count_good_value = 0;
	double result = 0;
	
	for(map<string, int>::const_iterator it = id_and_value.begin(); it != id_and_value.end(); ++it)
	{
		if(it->second == stoi(data[stoi(it->first, nullptr, 10) - 1][0], nullptr, 10))
		{
			count_good_value++;
		}
		else
		{
			count_mistake++;
		}
	}

	result = (count_mistake)/(count_mistake + count_good_value) * 100;
	
	return result;
}

//Algorytm przycinania (patrz dokumentacja)
void pruneEngine(Node *&node, Data const &data)
{
	if(!((node->node_A->isChecked || node->node_A->isLeaf) && (node->node_C->isChecked || node->node_C->isLeaf) && 
	(node->node_G->isChecked || node->node_G->isLeaf) && (node->node_T->isChecked || node->node_T->isLeaf) &&  (node->node_N->isChecked || node->node_N->isLeaf)))
	{
		if(!node->node_A->isLeaf && !node->node_A->isChecked)
		{
			pruneEngine(node->node_A, data);
		}
		
		if(!node->node_C->isLeaf && !node->node_C->isChecked)
		{
			pruneEngine(node->node_C, data);
		}
		
		if(!node->node_G->isLeaf && !node->node_G->isChecked)
		{
			pruneEngine(node->node_G, data);
		}
		
		if(!node->node_T->isLeaf && !node->node_T->isChecked)
		{
			pruneEngine(node->node_T, data);
		}
		
		if(!node->node_N->isLeaf && !node->node_N->isChecked)
		{
			pruneEngine(node->node_N, data);
		}
	}
	else
	{
		node->isChecked = true;
		map<string, int> empty_id_and_value;
		map<string, int> id_and_value = predictedClassification(empty_id_and_value, node);
		map<string, int> id_and_predicted_value;
		int count_0 = 0;
		int count_1 = 0;
		
		for(map<string, int>::iterator it = id_and_value.begin(); it != id_and_value.end(); ++it)
		{
			if(it->second == 0)
			{
				count_0++;
			}
			else
			{
				count_1++;
			}
		}
		
		map<string, int>::iterator it;
		if(count_1 > count_0)
		{
			for(it = id_and_value.begin(); it != id_and_value.end(); ++it)
			{
				id_and_predicted_value[it->first] = 1;
			}
		}
		else
		{
			for(it = id_and_value.begin(); it != id_and_value.end(); ++it)
			{
				id_and_predicted_value[it->first] = 0;
			}
		}
	
		double node_error = error_for_prunning(id_and_value, data);
		double leaf_error = error_for_prunning(id_and_predicted_value, data);
		
		if(leaf_error <= node_error)
		{
			node->isLeaf = true;
			if(count_1 > count_0)
			{
				node->classification = 1;
			}
			else
			{
				node->classification = 0;
			}

			node->destroyRecursive(node->node_A);
			node->destroyRecursive(node->node_C);
			node->destroyRecursive(node->node_G);
			node->destroyRecursive(node->node_T);
			node->destroyRecursive(node->node_N);
			node->node_A = nullptr;
			node->node_C = nullptr;
			node->node_G = nullptr;
			node->node_T = nullptr;
			node->node_N = nullptr;
		}
	}
}

//*Wywołanie algorytmu przycinania (patrz dokumentacja)
void pruneDecisionTree(Node *&root, Data const &data)
{
	while(!root->isChecked)
	{
		pruneEngine(root, data);
	}
}

//Uśrednianie macierzy pomyłek 
vector<double>  meanConfusionMatrix(vector<vector<double>> const &confusion_matrices)
{
		double sum_TP = 0;
		double sum_TN = 0;
		double sum_FP = 0;
		double sum_FN = 0;
		double len = confusion_matrices.size();
		vector<double> result;
		
		for(int i = 0; i < confusion_matrices.size(); i++)
		{
			sum_TP += confusion_matrices[i][0];
			sum_TN += confusion_matrices[i][1];
			sum_FP += confusion_matrices[i][2];
			sum_FN += confusion_matrices[i][3];
		}
		
		int mean_TP =(int)(sum_TP/len);
		int mean_TN =(int)(sum_TN/len);
		int mean_FP =(int)(sum_FP/len);
		int mean_FN =(int)(sum_FN/len);
		result.push_back(mean_TP);
		result.push_back(mean_TN);
		result.push_back(mean_FP);
		result.push_back(mean_FN);
		
		return result;
}

//Uśrednianie błędów
double meanError(vector<double> const  &errors)
{
	double sum = 0;
	double result = 100;
	int len = errors.size();
	
	for(int i = 0; i < len; i++)
	{
		sum +=errors[i];
	}
	
	result = (sum/(double)len)*100;
}
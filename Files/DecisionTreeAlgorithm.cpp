/**
@Igor Markiewicz
*/
#include "DecisionTreeAlgorithm.hpp"

Node::Node()
{
	classification = 0;
	test = 0;
    atributte_value = 'H';
	node_A = nullptr;
	node_C = nullptr;
	node_G = nullptr;
	node_T = nullptr;
	node_N = nullptr;
	isLeaf = false;
	isChecked= false;
}

Node::Node(int &classification, int &test, char &atributte_value, Node *node_A, Node *node_C, Node *node_G, Node *node_T, Node *node_N, vector<string> &id, bool &isChecked)
{	
	this->classification = classification;
	this->test = test;
	this->atributte_value = atributte_value;
	this->node_A = node_A;
	this->node_C = node_C;
	this->node_G = node_G;
	this->node_T = node_T;
	this->node_N = node_N;
	this->isLeaf = isLeaf;
	this->id = id;
	this->isChecked = isChecked;
}

Node::~Node()
{
	//cout << "Destruktor " << endl;
	this->node_A = nullptr;
	this->node_C = nullptr;
	this->node_G = nullptr;
	this->node_T = nullptr;
	this->node_N = nullptr;
}

void Node::destroyRecursive(Node *&node)
{
	if(node != nullptr)
	{
		if(node->node_A != nullptr)
		{
			destroyRecursive(node->node_A);
		}
		
		if(node->node_C != nullptr)
		{
			destroyRecursive(node->node_C);
		}
		
		if(node->node_G != nullptr)
		{
			destroyRecursive(node->node_G);
		}
		
		if(node->node_T != nullptr)
		{
			destroyRecursive(node->node_T);
		}
		
		if(node->node_N != nullptr)
		{
			destroyRecursive(node->node_N);
		}
		
		delete node;
		node = nullptr;
	}
}

//Funkcja informująca czy następuje warunek stopu czy konstrukcji
bool stop(vector<string> &id, Data const &data, vector<string> &attributes)
{
	bool result = false;
	
	if(id.size() > 0 && attributes.size() > 0)
	{
		string category = data[stoi(id[0], nullptr, 10) - 1][0];
		int i = 0;
		
		while(i < id.size())
		{
			if(data[stoi(id[i], nullptr, 10) - 1][0].compare(category) == 0)
			{
				result = true;
			}
			else
			{
				result = false;
				break;
			}
			i++;
		}
	}
	else
	{
		result = true;
	}
	return result;
}

//Funkcja zliczająca kategorie i zwracająca większą z nich 
int countCategory(vector<string> const &id, Data const &data)
{
	int i = 0;
	int count_positive = 0;
	int count_negative = 0;
	int result = 0;
	
	while(i < id.size())
		{
			if(data[stoi(id[i], nullptr, 10) - 1][0].compare("1") == 0)
			{
				count_positive ++;
			}
			else
			{
				count_negative ++;
			}
			
			i++;
		}

		if(count_positive > count_negative)
		{
			result = 1;
		}
		
		return result;
}

//Funkcja zliczająca kategorie i zwracająca większą z nich przeznaczona do budowy drzewa (w przeciwieństwie do countCategory musi zawierać kategorię domyślną)
int category(vector<string> const &id, Data const &data, int &current_category)
{
	int result = 0;
	
	if(id.size() == 0)
	{
		result = current_category;
	}
	else
	{
		result = countCategory(id, data);
	}
	
	return result;
	
}

//Funkcja wybierająca test
int chooseTest(vector<string> const &id, Data const &data, vector<string> const &attributes)
{
	int number_of_atributes = attributes.size();
	vector<double> weight_entropy;
	int choosed_test = 0;
	
	//Dla każdego przykładu w węźle i każdego dostępnego atrybutu obliczamy entropię
	for(int i = 0; i < number_of_atributes; i++)
	{
		double entropy_A = 0;	
		int j = 0;
		double count_positive_A = 0;
		double count_negative_A = 0;
		
		while(j < id.size())
		{
			if(data[stoi(id[j], nullptr, 10) - 1][1][stoi(attributes[i], nullptr, 10) - 1] == 'A')
			{
				if(data[stoi(id[j], nullptr, 10) - 1][0].compare("1") == 0)
				{
					count_positive_A ++;
				}
				else
				{
					count_negative_A ++;
				}						
			}
				j++;
		}
			
		double positive_entropy_A = 0;
		double negative_entropy_A = 0;
		
		if(count_positive_A != 0)
		{
			positive_entropy_A = -(count_positive_A)/(count_positive_A + count_negative_A)*log2(count_positive_A/(count_positive_A + count_negative_A));
		}	
		else
		{
			positive_entropy_A = 0;
		}
		
		if(count_negative_A != 0)
		{
			negative_entropy_A = -(count_negative_A)/(count_positive_A + count_negative_A)*log2(count_negative_A/(count_positive_A + count_negative_A));
		}	
		else
		{
			negative_entropy_A = 0;
		}
		
		entropy_A = positive_entropy_A + negative_entropy_A;
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		double entropy_C = 0;	
		double count_positive_C = 0;
		double count_negative_C = 0;
		j = 0;
	
		while(j < id.size())
		{
			if(data[stoi(id[j], nullptr, 10) - 1][1][stoi(attributes[i], nullptr, 10) - 1] == 'C')
			{
				if(data[stoi(id[j], nullptr, 10) - 1][0].compare("1") == 0)
				{
					count_positive_C ++;
				}
				else
				{
					count_negative_C ++;
				}
					
			}
				j++;
		}
		
		double positive_entropy_C = 0;
		double negative_entropy_C = 0;
		
		if(count_positive_C != 0)
		{
			positive_entropy_C = -(count_positive_C)/(count_positive_C + count_negative_C)*log2(count_positive_C/(count_positive_C + count_negative_C));
		}	
		else
		{
			positive_entropy_C = 0;
		}
		
		if(count_negative_C != 0)
		{
			negative_entropy_C = -(count_negative_C)/(count_positive_C + count_negative_C)*log2(count_negative_C/(count_positive_C + count_negative_C));
		}	
		else
		{
			negative_entropy_C = 0;
		}
		
		entropy_C = positive_entropy_C + negative_entropy_C;
		 
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		double entropy_G = 0;	
		double count_positive_G = 0;
		double count_negative_G = 0;
		j = 0;
	
		while(j < id.size())
		{	
			if(data[stoi(id[j], nullptr, 10) - 1][1][stoi(attributes[i], nullptr, 10) - 1] == 'G')
			{
				if(data[stoi(id[j], nullptr, 10) - 1][0].compare("1") == 0)
				{
					count_positive_G ++;
				}
				else
				{
					count_negative_G ++;
				}
					
			}
				j++;
		}
		
		double positive_entropy_G = 0;
		double negative_entropy_G = 0;
		
		if(count_positive_G != 0)
		{
			positive_entropy_G = -(count_positive_G)/(count_positive_G + count_negative_G)*log2(count_positive_G/(count_positive_G + count_negative_G));
		}	
		else
		{
			positive_entropy_G = 0;
		}
		
		if(count_negative_G != 0)
		{
			negative_entropy_G = -(count_negative_G)/(count_positive_G + count_negative_G)*log2(count_negative_G/(count_positive_G + count_negative_G));
		}	
		else
		{
			negative_entropy_G = 0;
		}
		
		 entropy_G = positive_entropy_G + negative_entropy_G;
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
		double entropy_T = 0;	
		double count_positive_T = 0;
		double count_negative_T = 0;
		j = 0;
	
		while(j < id.size())
		{
			if(data[stoi(id[j], nullptr, 10) - 1][1][stoi(attributes[i], nullptr, 10) - 1] == 'T')
			{
				if(data[stoi(id[j], nullptr, 10) - 1][0].compare("1") == 0)
				{
					count_positive_T ++;
				}
				else
				{
					count_negative_T ++;
				}
					
			}
				j++;
		}
		
		double positive_entropy_T = 0;
		double negative_entropy_T = 0;
		
		if(count_positive_T != 0)
		{
			positive_entropy_T = -(count_positive_T)/(count_positive_T + count_negative_T)*log2(count_positive_T/(count_positive_T + count_negative_T));
		}	
		else
		{
			positive_entropy_T = 0;
		}
		
		if(count_negative_T != 0)
		{
			negative_entropy_T = -(count_negative_T)/(count_positive_T + count_negative_T)*log2(count_negative_T/(count_positive_T + count_negative_T));
		}	
		else
		{
			negative_entropy_T = 0;
		}
		
		entropy_T = positive_entropy_T + negative_entropy_T;
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		double entropy_N = 0;	
		double count_positive_N = 0;
		double count_negative_N = 0;
		j = 0;
	
		while(j < id.size())
		{
			if(data[stoi(id[j], nullptr, 10) - 1][1][stoi(attributes[i], nullptr, 10) - 1] == 'N')
			{
				if(data[stoi(id[j], nullptr, 10) - 1][0].compare("1") == 0)
				{
					count_positive_N++;
				}
				else
				{
					count_negative_N++;
				}
					
			}
				j++;
		}
		
		double positive_entropy_N = 0;
		double negative_entropy_N = 0;
		
		if(count_positive_N != 0)
		{
			positive_entropy_N = -(count_positive_N)/(count_positive_N + count_negative_N)*log2(count_positive_N/(count_positive_N + count_negative_N));
		}	
		else
		{
			positive_entropy_N = 0;
		}
		
		if(count_negative_N != 0)
		{
			negative_entropy_N = -(count_negative_N)/(count_positive_N + count_negative_N)*log2(count_negative_N/(count_positive_N + count_negative_N));
		}	
		else
		{
			negative_entropy_N = 0;
		}
		
		entropy_N = positive_entropy_N + negative_entropy_N;
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//Obliczanie entropi ważonych
		double weight_entropy_A = entropy_A*(count_positive_A + count_negative_A)/(data.size());
		double weight_entropy_C = entropy_C*(count_positive_C + count_negative_C)/(data.size());
		double weight_entropy_G = entropy_G*(count_positive_G + count_negative_G)/(data.size());
		double weight_entropy_T = entropy_T*(count_positive_T + count_negative_T)/(data.size());
		double weight_entropy_N = entropy_N*(count_positive_N + count_negative_N)/(data.size());
		
		weight_entropy.push_back(weight_entropy_A + weight_entropy_C + weight_entropy_G + weight_entropy_T + weight_entropy_N);
	}
	
	//Wybór testu o najmniejszej entropi
	vector<double>::iterator result = min_element(weight_entropy.begin(), weight_entropy.end());
	choosed_test = distance(weight_entropy.begin(), result);
	
	return choosed_test;
	 
}

//Usuwanie atrybutu 
vector<string> eraseAttribute(vector<string> const &attributes, int const &position)
{
	vector<string> new_attributes = attributes;
	new_attributes.erase(new_attributes.begin() + position);
	
	return new_attributes;
}

//Podział id pod względem porównywania litery na konkretnej pozycji
vector<string> splitId(vector<string> const &id, Data const &data, char const &choosed_letter, int const &choosed_test, vector<string> const &attributes)
{
	vector<string> splitted_id;
	
	for(int i = 0; i < id.size(); i++)
	{
		if(data[stoi(id[i], nullptr, 10) - 1][1][stoi(attributes[choosed_test], nullptr, 10) - 1] == choosed_letter)
		{
			splitted_id.push_back(id[i]);
		}
		
	}
	
	return splitted_id;
	
}

//Budowanie drzewa 
Node * buildDecisionTree(vector<string> &id, int &current_category, vector<string> &attributes, Data const &data, Node *node_or_leaf, const char &atributte_value)
{
	bool stop_info = stop(id, data, attributes);
	
	if(stop_info)
	{
		int leaf_category = category(id, data, current_category);
		node_or_leaf->isLeaf = true;
		node_or_leaf->classification = leaf_category;
		node_or_leaf->id = id;
		node_or_leaf->atributte_value = atributte_value;
	}
	else
	{
		int choosed_test = chooseTest(id, data, attributes);
		int choosed_category = category(id, data, current_category);
		vector<string> new_attributes = eraseAttribute(attributes, choosed_test);
		node_or_leaf->id = id;
		node_or_leaf->test = stoi(attributes[choosed_test], nullptr, 10);
		node_or_leaf->atributte_value = atributte_value;
		
		vector<char> chars;
		chars.push_back('A');
		chars.push_back('C');
		chars.push_back('G');
		chars.push_back('T');
		chars.push_back('N');
		
		Node *new_node_A = new Node();
		Node *new_node_C = new Node();
		Node *new_node_G = new Node();
		Node *new_node_T = new Node();
		Node *new_node_N = new Node();
		
		char choosed_letter = 'A';
		vector<string> splitted_id = splitId(id, data, choosed_letter, choosed_test, attributes);
		node_or_leaf->node_A = buildDecisionTree(splitted_id, choosed_category, new_attributes, data, new_node_A, choosed_letter);
		
		choosed_letter = 'C';
		splitted_id = splitId(id, data, choosed_letter, choosed_test, attributes);
		node_or_leaf->node_C = buildDecisionTree(splitted_id, choosed_category, new_attributes, data, new_node_C, choosed_letter);
		
	    choosed_letter = 'G';
		splitted_id = splitId(id, data, choosed_letter, choosed_test, attributes);
		node_or_leaf->node_G = buildDecisionTree(splitted_id, choosed_category, new_attributes, data, new_node_G, choosed_letter);
		
	    choosed_letter = 'T';
		splitted_id = splitId(id, data, choosed_letter, choosed_test, attributes);
		node_or_leaf->node_T = buildDecisionTree(splitted_id, choosed_category, new_attributes, data, new_node_T, choosed_letter);
		
		choosed_letter = 'N';
		splitted_id = splitId(id, data, choosed_letter, choosed_test, attributes);
		node_or_leaf->node_N = buildDecisionTree(splitted_id, choosed_category, new_attributes, data, new_node_N, choosed_letter);
	
	}
	
	return node_or_leaf;
	
}







/**
@author Igor Markiewicz
*/
#include "InputDataAlgorithms.hpp"
#include "DecisionTreeAlgorithm.hpp"
#include "SupportAlgorithms.hpp"


int main()
{
	//Ścieżka do pliku źródłowego
    string const path = "./Data/spliceDTrainKIS.dat";
	//Nazwy plików tekstowych do których zostają zapisane zbiór uczący, walidacyjny i testowy.
	//W przypadku pustej nazwy zbiór nie zostaje zapisany
	string const name_of_learning_file = "";
	string const name_of_test_file = "";
	string const name_of_validation_file = "";
	//Liczba obrotów pętli przeznaczonej do zbierania danych przeznaczonych do uśrednienia
	int counter = 10;
	//Procent przykładów ze zbior pierwotnego przeznaczonych do uczenia i walidacji
	double r1 = 70;
	//Procent przykładów przeznaczonych do uczenia
	double r2 = 50;
	//macierze pomyłek
	vector<vector<double>> learning_confusion_matrices, validation_confusion_matrices, test_confusion_matrices;
	//wektory błędów
	vector<double> learning_errors, validation_errors, test_errors;
	Data data = parseInputData(path, true);

	for(int i = 0; i < counter; i++)
	{
		//Budowanie drzewa
		Data data_tmp = data;
		randomiseData(data_tmp);
		Data test_data  = parseTestData(r1, name_of_learning_file, name_of_test_file, data_tmp);
		Data validation_data = parseValidationData(r2, name_of_learning_file, name_of_validation_file, data_tmp);
		Node *head = new Node();
		vector<string> id = rewriteId(data_tmp);
		vector<string> attributes = rewriteAttributes(data_tmp);
		int current_category = countCategory(id, data_tmp);
		//Wybór pierwszej litery do korzenia - nie ma znaczenia
		char choosed_letter = 'H';
		buildDecisionTree(id, current_category, attributes, data_tmp, head, choosed_letter);

		//Macierze pomyłek i błędy dla zbioru uczącego
		map<string, int> p1;
		map<string, int> m1 = predictedClassification(p1, head);
		vector<double> c1 = confusionMatrix(m1, data_tmp);
		learning_confusion_matrices.push_back(c1);
		double e1 = error(c1, data_tmp);
		learning_errors.push_back(e1);
		deleteId(head);

		//Macierze pomyłek i błędy dla zbioru walidacyjnego oraz przycinanie drzewa
		addTestData(validation_data, head);
		map<string, int> p2;
		map<string, int> m2 = predictedClassification(p2, head);
		vector<double> c2 = confusionMatrix(m2, validation_data);
		validation_confusion_matrices.push_back(c2);
		double e2 = error(c2, validation_data);
		validation_errors.push_back(e2);
		pruneDecisionTree(head, validation_data);
		deleteId(head);

		//Macierze pomyłek i błędy dla zbioru testowego oraz usuwanie drzewa
		addTestData(test_data, head);
		map<string, int> p3;
		map<string, int> m3 = predictedClassification(p3, head);
		vector<double> c3 = confusionMatrix(m3, test_data);
		test_confusion_matrices.push_back(c3);
		double e3 = error(c3, test_data);
		test_errors.push_back(e3);
		head->destroyRecursive(head);
	}

	//Uśrednione macierze pomyłek
	vector<double> learning_confusion_matrix =  meanConfusionMatrix(learning_confusion_matrices);
	vector<double> validation_confusion_matrix =  meanConfusionMatrix(validation_confusion_matrices);
	vector<double> test_confusion_matrix =  meanConfusionMatrix(test_confusion_matrices);

	cout << "Dla walidacji : TP = " << validation_confusion_matrix[0] << " TN = " << validation_confusion_matrix[1] << " FP = "  <<  validation_confusion_matrix[2]  << " FN = "  <<  validation_confusion_matrix[3] << endl;
	cout << "Dla testow : TP = " <<test_confusion_matrix[0] << " TN = " << test_confusion_matrix[1] << " FP = "  << test_confusion_matrix[2]  << " FN = "  <<  test_confusion_matrix[3] << endl;

	//Uśrednione błędy
	double learning_error = meanError(learning_errors);
	double validation_error = meanError(validation_errors);
	double test_error = meanError(test_errors);

	cout << "Sredni blad dla uczenia = "  <<  learning_error << endl;
	cout << "Sredni blad dla walidacji = " << validation_error << endl;
	cout << "Sredni blad dla testow = " << test_error << endl;

    return 0;
}

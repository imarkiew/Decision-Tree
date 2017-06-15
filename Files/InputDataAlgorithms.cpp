/**
@Igor Markiewicz
*/
#include "InputDataAlgorithms.hpp"

//Funkcja przeznaczona do parsowania danych z pliku wejściowego
//Parametr is_first_line_missed umozliwia pominięcie pierwszej linijki
Data parseInputData(string const &name_of_file, bool const &is_first_line_missed)
{
	Data data;
    ifstream file;
    file.open(name_of_file);

    if(file.fail())
    {
        cout << "Blad przy otwarciu pliku " << name_of_file << endl;
    }
    else
    {
        int miss_first_line = 1;
        string line;
        vector<string> line_even;
        vector<string> line_odd;
        vector<string> id;
		int count = 1;

        while(getline(file, line))
        {
            if(is_first_line_missed && miss_first_line != 1)
            {
				if(miss_first_line % 2)
				{
					line_even.push_back(line);
					id.push_back(to_string(count));
					count++;
				}
				else
				{
					line_odd.push_back(line);
				}
			}
			else if(!is_first_line_missed)
			{	
				if(miss_first_line % 2)
				{
					line_odd.push_back(line);
					id.push_back(to_string(count));
					count++;
				}
				else
				{
					line_even.push_back(line);
				}
			}
		
				miss_first_line++;
        }

        file.close();
		
        for(int i = 0; i < id.size(); i++)
        {
			vector<string> example;
            example.push_back(line_odd[i]);
            example.push_back(line_even[i]);
            example.push_back(id[i]);
            data.push_back(example);
        }
    }
	
	return data;
}

//Funkcja przeznaczona do randomizacji danych
void randomiseData(Data &data)
{
		srand((unsigned int)time(NULL));
		auto engine = default_random_engine(rand());
		shuffle(begin(data), end(data), engine);
	
		for(int i = 0; i < data.size(); i++)
		{
			data[i][2] = to_string(i + 1);
		}
}

//Funkcja przeznaczona do podziału zbioru wejściowego na zbiór uczący + walidacyjny oraz na zbiór testowy
Data parseTestData(double const &percent, string const &name_of_learning_file, string const &name_of_test_file, Data &data)
{
	Data data_tmp; 
	int counter = data.size() - int(data.size() * (percent/100));
	
	for(int i = 0; i < counter; i++)
	{	
		auto it = data.begin();
		data_tmp.push_back(data[0]);
		data.erase(it);
	}
	
	for(int i = 0; i < data.size(); i++)
	{
		data[i][2] = to_string(i + 1);
	}
	
	for(int i = 0; i < data_tmp.size(); i++)
	{
		data_tmp[i][2] = to_string(i + 1);
	}
	
	if(!name_of_learning_file.compare("") == 0)
	{
		fstream file_learning;
		file_learning.open(name_of_learning_file, fstream::out | fstream::trunc);
		for(int i = 0; i < data.size(); i++)
		{
			file_learning << data[i][0] << "\n";
			file_learning << data[i][1] << "\n";
		}
		file_learning.close();
	}
	
	if(!name_of_test_file.compare("") == 0)
	{
		fstream file_test;
		file_test.open(name_of_test_file, fstream::out | fstream::trunc);
		for(int i = 0; i < data_tmp.size(); i++)
		{
			file_test << data_tmp[i][0] << "\n";
			file_test << data_tmp[i][1] << "\n";
		}
		file_test.close();
	}
	
	return data_tmp;
}

//Funkcja przeznaczona do podziału zbioru wejściowego na zbiór uczący i walidacyjny
Data parseValidationData(double const &percent, string const &name_of_learning_file, string const &name_of_validation_file, Data &data)
{
	Data data_tmp; 
	int counter = data.size() - int(data.size() * (percent/100));
	
	for(int i = 0; i < counter; i++)
	{	
		auto it = data.begin();
		data_tmp.push_back(data[0]);
		data.erase(it);
	}
	
	for(int i = 0; i < data.size(); i++)
	{
		data[i][2] = to_string(i + 1);
	}
	
	for(int i = 0; i < data_tmp.size(); i++)
	{
		data_tmp[i][2] = to_string(i + 1);
	}
	
	if(!name_of_learning_file.compare("") == 0)
	{
		fstream file_learning;
		file_learning.open(name_of_learning_file, fstream::out | fstream::trunc);
		for(int i = 0; i < data.size(); i++)
		{
			file_learning << data[i][0] << "\n";
			file_learning << data[i][1] << "\n";
		}
		file_learning.close();
	}
	
	if(!name_of_validation_file.compare("") == 0)
	{
		fstream file_validation;
		file_validation.open(name_of_validation_file, fstream::out | fstream::trunc);
		for(int i = 0; i < data_tmp.size(); i++)
		{
			file_validation << data_tmp[i][0] << "\n";
			file_validation << data_tmp[i][1] << "\n";
		}
		file_validation.close();
	}
	
	return data_tmp;
}




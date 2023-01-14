#include <iostream>
#include "LogisticRegression.h"
#include<vector>
#include <sstream>
#include <string>
#include<fstream>

using namespace std;

//function to read csv data from the file ,skip first line and skip rows with na values
vector<vector<double>> read_csv(string filename)
{
	ifstream file(filename);
	vector<vector<double>> data;
	string line;
	getline(file, line);
	while (getline(file, line))
	{
		stringstream ss(line);
		string value;
		vector<double> row;
		while (getline(ss, value, ','))
		{
			if (value == "NA")
			{
				row.push_back(0);
			}
			else
			{
				row.push_back(stod(value));
			}
		}
		data.push_back(row);
	}
	return data;
}

int main()
{
    // Read the data from the file
    vector<vector<double>> data = read_csv("framingham.csv");

    // Split the data into training and testing sets
    int n_samples = data.size();
    
    
    //creating vectors to store training and testing data
    vector<vector<double>> X_train(n_samples);
    vector<double> y_train(n_samples);

    for (int i = 0; i < n_samples; i++)
    {
		//except last column all other columns are features
        vector<double> row(data[i].begin(), data[i].end() - 1);
		//last column is the target
        double label = data[i][data[i].size() - 1];
            X_train[i] = row;
            y_train[i] = label;
    }
    //columns in training data
    cout << "Features in Training data: " << X_train[0].size() << endl;
	cout << "Training data size: " << X_train.size() << endl;
    // Fit the logistic regression model to the training data
    LogisticRegression model(1000, 0.01);
    cout << "Starting the training" << endl;
	model.fit(X_train, y_train, 1e-3);
    cout << "Training completed" << endl;
	// take a row from user seperated by comma and predict the output
	string input;
	cout << "Enter the row to predict: ";
	getline(cin, input);
	stringstream ss(input);
	string value;
	vector<double> row;
	while (getline(ss, value, ','))
	{
		row.push_back(stod(value));
	}
	vector<double> y_pred = model.predict({ row });
    if (y_pred[0] < 0.5)
    {
		cout << "The person is not likely to have a heart attack" << endl;
	}
	else
	{
		cout << "The person is likely to have a heart attack" << endl;
    }
	return 0;
}
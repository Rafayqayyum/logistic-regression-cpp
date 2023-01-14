
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
    int n_train = n_samples * 0.8;
    int n_test = n_samples - n_train;

    vector<vector<double>> X_train(n_train);
    vector<double> y_train(n_train);
    vector<vector<double>> X_test(n_test);
    vector<double> y_test(n_test);

    for (int i = 0; i < n_samples; i++)
    {
        vector<double> row(data[i].begin(), data[i].end() - 1);
        double label = data[i][data[i].size() - 1];
        if (i < n_train)
        {
            X_train[i] = row;
            y_train[i] = label;
        }
        else
        {
            X_test[i - n_train] = row;
            y_test[i - n_train] = label;
        }
    }

	// print no of samples in training and testing data
	cout << "No of samples in training data: " << n_train << endl;
	cout << "No of samples in testing data: " << n_test << endl;
    // Fit the logistic regression model to the training data
    LogisticRegression model(100, 0.1);
    model.fit(X_train, y_train,1e-3);

    // Make predictions on the testing data
    vector<double> y_pred = model.predict(X_test);
	//set threshold to 0.5
    for (int i = 0; i < y_pred.size(); i++)
    {
		if (y_pred[i] >= 0.5)
		{
			y_pred[i] = 1;
		}
		else
		{
			y_pred[i] = 0;
		}
    }
	//calculating accuracy
	int correct = 0;
	for (int i = 0; i < y_pred.size(); i++)
	{
		if (y_pred[i] == y_test[i])
		{
			correct++;
		}
	}
	double accuracy = (double)correct / y_pred.size();
	cout << "Accuracy: " << accuracy << endl;
    

    return 0;
}
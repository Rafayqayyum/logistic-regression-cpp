#pragma once

#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

class LogisticRegression
{
private:
    int n_iter;
    double alpha;
    vector<double> weights;

public:
    // Constructor
    LogisticRegression(int n_iter, double alpha)
    {
        //Max iterations
        this->n_iter = n_iter;
        //Learning rate
        this->alpha = alpha;
    }

    // Method to fit the model to the training data
    void fit(const vector<vector<double>>& X, const vector<double>& y, double threshold)
    {
        int n_samples = X.size();
        int n_features = X[0].size();

        weights = vector<double>(n_features, 0);

        double prev_norm = 0;
        for (int iter = 0; iter < n_iter; iter++)
        {
            vector<double> y_pred = predict(X);
            // Calculating the error
            vector<double> error(n_samples);
            for (int i = 0; i < n_samples; i++)
            {
                error[i] = y_pred[i] - y[i];
            }


            // Calculating the gradient
            vector<double> gradient(n_features, 0);

            for (int j = 0; j < n_features; j++)
            {
                for (int i = 0; i < n_samples; i++)
                {
                    gradient[j] += error[i] * X[i][j];
                }
                gradient[j] /= n_samples;
            }

            // Compute the norm of the gradient
            // computing the norm helps us to check if the algorithm has converged
            double norm = 0;
            for (double val : gradient)
            {
                norm += val * val;
            }
            norm = sqrt(norm);

            // Check for convergence : if the norm of the gradient is less than the threshold, we stop the algorithm
            // no need to train the model further if the norm of the gradient is less than the threshold
            // otherwise we assign prev_norm = norm and continue the training
            if (fabs(norm - prev_norm) < threshold)
            {
                break;
            }
            prev_norm = norm;

            // Updating the weights
            for (int j = 0; j < n_features; j++)
            {
                weights[j] -= alpha * gradient[j];
            }
        }

    }

    // Method to predict the output for a given input
    vector<double> predict(const vector<vector<double>>& X)
    {
        int n_samples = X.size();
        vector<double> y_pred(n_samples);
        for (int i = 0; i < n_samples; i++)
        {
            double z = 0;
            for (int j = 0; j < weights.size(); j++)
            {
                z += weights[j] * X[i][j];
            }
            y_pred[i] = sigmoid(z);
        }
        return y_pred;
    }

    // Method to compute the sigmoid function
    double sigmoid(double z)
    {
        return 1.0 / (1.0 + exp(-z));
    }
};


#ifndef KNNCLASSIFIER_H
#define KNNCLASSIFIER_H

#include <queue>
#include <vector>
#include <utility>
#include <iostream>
#include <cmath>

using namespace std;

class KNNClassifier {
public:
    // Constructor: Initializes the KNN classifier with a given number of neighbors (k).
    explicit KNNClassifier(int k);

    // Trains the classifier using the provided features and labels.
    void train(const vector<vector<double>>& features, const vector<bool>& labels);

    // Predicts the class (true/false) of a new instance based on its features.
    bool predict(const vector<double>& emailFeatures) const;

    // Same as the predict function but also prints the nearest neighbor information.
    bool predictAnalyze(const vector<double>& emailFeatures) const;

private:
    // Number of nearest neighbors to consider in the KNN algorithm.
    int k;

    // Stores training feature vectors.
    vector<vector<double>> trainingFeatures;

    // Stores corresponding labels for the training feature vectors.
    vector<bool> trainingLabels;

    // Computes Euclidean distance between two feature vectors.
    double computeDistance(const vector<double>& email1, const vector<double>& email2) const;
};

#endif // KNNCLASSIFIER_H

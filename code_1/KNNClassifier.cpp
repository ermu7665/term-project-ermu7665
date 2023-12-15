#include "KNNClassifier.h"

// Constructor: Initializes the KNN classifier with a given number of neighbors (k).
KNNClassifier::KNNClassifier(int k) : k(k) {}

// Train the classifier by storing the training features and corresponding labels.
void KNNClassifier::train(const vector<vector<double>>& features, const vector<bool>& labels) {
    trainingFeatures = features;
    trainingLabels = labels;
}

// Predict the class (spam or not spam) of a new email instance using KNN algorithm.
bool KNNClassifier::predict(const vector<double>& emailFeatures) const {
    // Max heap to store the k nearest neighbors based on their distance
    priority_queue<pair<double, int>> neighbors;

    for (int i = 0; i < trainingFeatures.size(); ++i) {
        double distance = computeDistance(emailFeatures, trainingFeatures[i]);

        // If the heap has less than k elements, just add the new element
        if (neighbors.size() < k) {
            neighbors.push(make_pair(distance, i));
        } else {
            // If the new element's distance is smaller than the largest in the heap, replace it
            if (distance < neighbors.top().first) {
                neighbors.pop();
                neighbors.push(make_pair(distance, i));
            }
        }
    }

    // Count the number of spam emails among the k nearest neighbors
    int spamCount = 0;
    while (!neighbors.empty()) {
        int index = neighbors.top().second;
        bool isSpam = trainingLabels[index];
        spamCount += isSpam;
        neighbors.pop();
    }

    return spamCount > k / 2;
}


// Compute Euclidean distance between two feature vectors.
double KNNClassifier::computeDistance(const vector<double>& email1, const vector<double>& email2) const {
    double sum = 0.0;
    for (int i = 0; i < email1.size(); ++i) {
        sum += pow(email1[i] - email2[i], 2);
    }
    return sqrt(sum);
}


// Same as the predict function but also prints the nearest neighbor information.
bool KNNClassifier::predictAnalyze(const vector<double>& emailFeatures) const {
    // Max heap to store the k nearest neighbors based on their distance
    priority_queue<pair<double, int>> neighbors;

    for (int i = 0; i < trainingFeatures.size(); ++i) {
        double distance = computeDistance(emailFeatures, trainingFeatures[i]);

        // If the heap has less than k elements, just add the new element
        if (neighbors.size() < k) {
            neighbors.push(make_pair(distance, i));
        } else {
            // If the new element's distance is smaller than the largest in the heap, replace it
            if (distance < neighbors.top().first) {
                neighbors.pop();
                neighbors.push(make_pair(distance, i));
            }
        }
    }

    // Count the number of spam emails among the k nearest neighbors
    int spamCount = 0;
    while (!neighbors.empty()) {
        int index = neighbors.top().second;
        bool isSpam = trainingLabels[index];
        spamCount += isSpam;

        // Print statement
        cout << "Neighbor index: " << index << ", Distance: " << computeDistance(emailFeatures, trainingFeatures[index]) << ", Label (Spam=1/Ham=0): " << isSpam << endl;

        neighbors.pop();
    }

    return spamCount > k / 2;
}

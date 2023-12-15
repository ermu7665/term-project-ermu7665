#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H

#include <string>
#include <vector>
#include <map>
#include <utility> 
#include <algorithm>
#include <sstream>
#include <set>
#include <cctype>
#include <iostream>

using namespace std;

class FeatureExtractor {
public:
    // Extracts features from an email subject and message.
    vector<double> extractFeatures(const string& emailSubject, const string& emailMessage, const vector<string>& topFeatures);

    // Extracts a balanced set of top features from training data for spam and ham emails.
    vector<string> extractBalancedTopFeatures(const vector<pair<pair<string, string>, bool>>& trainingData, int N);

    // Analyzes features of nearest neighbors and returns a summary.
    string analyzeFeaturesOfNeighbors(const vector<int>& neighborIndices, const vector<vector<double>>& trainingFeatures, const vector<string>& topFeatures);

private:
    // Converts a string to lowercase.
    string toLower(const string& str);

    // Tokenizes an email into a list of words, cleaning it in the process.
    vector<string> tokenizeEmail(const string& email);

    // Builds a frequency map (word count) from a list of tokens.
    map<string, int> buildFrequencyMap(const vector<string>& tokens);

    // Selects the top N words from a frequency map based on their occurrence.
    vector<string> selectTopFeatures(const map<string, int>& freqMap, int N);

    // Converts a list of email tokens into a feature vector based on the top features.
    vector<double> emailToFeatureVector(const vector<string>& emailTokens, const vector<string>& topFeatures);
};

#endif // FEATUREEXTRACTOR_H

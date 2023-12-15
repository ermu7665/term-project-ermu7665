#include "FeatureExtractor.h"

// Converts a string to lowercase for case-insensitive processing.
string FeatureExtractor::toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Tokenizes an email string into individual words, removing non-alphabetic characters.
vector<string> FeatureExtractor::tokenizeEmail(const string& email) {
    vector<string> tokens;
    string token;
    istringstream emailStream(email);

    while (emailStream >> token) {
        // Remove non-alphabetic characters and convert to lowercase.
        token.erase(remove_if(token.begin(), token.end(), [](char c) { return !isalpha(c); }), token.end());
        if (!token.empty()) {
            tokens.push_back(toLower(token));
        }
    }
    return tokens;
}

// Builds a frequency map of words from the given list of tokens.
map<string, int> FeatureExtractor::buildFrequencyMap(const vector<string>& tokens) {
    map<string, int> freqMap;
    // Increment the count for each occurrence of a token.
    for (const auto& token : tokens) {
        freqMap[token]++;
    }
    return freqMap;
}

// Selects the top N frequent words from the frequency map.
vector<string> FeatureExtractor::selectTopFeatures(const map<string, int>& freqMap, int N) {
    vector<pair<string, int>> pairs;
    for (const auto& it : freqMap) {
        pairs.push_back(it);
    }

    // Sort pairs based on frequency, in descending order.
    sort(pairs.begin(), pairs.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });

    vector<string> topFeatures;
    // Select the top N features.
    for (int i = 0; i < static_cast<int>(N) && i < pairs.size(); ++i) {
        topFeatures.push_back(pairs[i].first);
    }

    return topFeatures;
}

// Converts email tokens into a feature vector based on the presence of top features.
vector<double> FeatureExtractor::emailToFeatureVector(const vector<string>& emailTokens, const vector<string>& topFeatures) {
    vector<double> featureVector(topFeatures.size(), 0.0);
    set<string> uniqueTokens(emailTokens.begin(), emailTokens.end());

    // Create a binary feature vector indicating the presence of top features in the email.
    for (int i = 0; i < topFeatures.size(); ++i) {
        if (uniqueTokens.find(topFeatures[i]) != uniqueTokens.end()) {
            featureVector[i] = 1.0; // Set to 1 if the top feature is present in the email.
        }
    }

    return featureVector;
}


// Extracts feature vector from an email based on the top features.
vector<double> FeatureExtractor::extractFeatures(const string& emailSubject, const string& emailMessage, const vector<string>& topFeatures) {
    // Combining subject and message into one string.
    string fullEmail = emailSubject + " " + emailMessage;
    // Tokenizing the email into words.
    auto tokens = tokenizeEmail(fullEmail);
    // Converting the tokens into a feature vector based on the top features.
    return emailToFeatureVector(tokens, topFeatures);
}

// Extracts a balanced set of top features from the training data.
vector<string> FeatureExtractor::extractBalancedTopFeatures(const vector<pair<pair<string, string>, bool>>& trainingData, int N) {
    // List of common words to be excluded from feature selection.
    set<string> excludedWords = {"if", "is", "these", "in", "this", "on", "of", "with", "our", "the", "you", "for", "a", "and", "your", "to", "out", "at", "be", "here", "just", "im", "or", "youre", "are", "have", "dont", "can", "any", "me", "some", "we", "about", "around", "as", "before", "during", "from", "how", "into", "off", "over", "so", "up", "without", "been", "being", "could", "do", "get", "has", "know", "make", "may", "see", "take", "want", "will", "all", "each", "every", "few", "many", "most", "other", "such", "they", "this", "those", "which", "i", "ive", "let", "lets", "were", "", " "};

    // Maps to track word frequency separately for spam and ham emails.
    map<string, int> frequencyMapSpam, frequencyMapHam;

    // Iterating over training data to build frequency maps.
    for (const auto& data : trainingData) {
        string fullEmail = data.first.first + " " + data.first.second;
        auto tokens = tokenizeEmail(fullEmail);

        // Increment frequency count, excluding common words.
        for (const auto& token : tokens) {
            if (excludedWords.find(token) == excludedWords.end()) {
                if (data.second) {
                    frequencyMapSpam[token]++;
                } else {
                    frequencyMapHam[token]++;
                }
            }
        }
    }

    // Lambda function to extract top N features from a frequency map.
    auto extractTop = [&](const map<string, int>& freqMap, int halfN) {
        // Sorting the frequency map to find top features.
        vector<pair<string, int>> freqVec(freqMap.begin(), freqMap.end());
        sort(freqVec.begin(), freqVec.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });

        // Collecting the top features.
        vector<string> top;
        for (int i = 0; i < static_cast<int>(halfN) && i < freqVec.size(); i++) {
            top.push_back(freqVec[i].first);
        }
        return top;
    };

    // Extracting top features for both spam and ham emails.
    vector<string> topSpamFeatures = extractTop(frequencyMapSpam, N / 2);
    vector<string> topHamFeatures = extractTop(frequencyMapHam, N / 2);

    // Combining and deduplicating top features from both categories.
    set<string> combinedTopFeatures(topSpamFeatures.begin(), topSpamFeatures.end());
    combinedTopFeatures.insert(topHamFeatures.begin(), topHamFeatures.end());

    // Adding additional features if the combined set is less than N.
    int additionalNeeded = N - combinedTopFeatures.size();
    auto addAdditionalFeatures = [&](const map<string, int>& freqMap) {
        vector<pair<string, int>> freqVec(freqMap.begin(), freqMap.end());
        sort(freqVec.begin(), freqVec.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });

        // Inserting additional features while ensuring uniqueness.
        for (const auto& pair : freqVec) {
            if (combinedTopFeatures.size() >= N) break;
            if (combinedTopFeatures.find(pair.first) == combinedTopFeatures.end()) {
                combinedTopFeatures.insert(pair.first);
            }
        }
    };

    if (additionalNeeded > 0) {
        addAdditionalFeatures(frequencyMapSpam);
        addAdditionalFeatures(frequencyMapHam);
    }

    // Returning the final list of top features.
    return vector<string>(combinedTopFeatures.begin(), combinedTopFeatures.end());
}


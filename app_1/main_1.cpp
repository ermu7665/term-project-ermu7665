#include "../code_1/KNNClassifier.h"
#include "../code_1/FeatureExtractor.h"
#include "../code_1/EmailReader.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;


int main() {
    // File paths for training and test data.
    string spamFilePath = "../training/spam.csv";
    string hamFilePath = "../training/ham.csv";
    string testFilePath = "../tests/messages.csv";
    int k; // Variables for KNN parameter and number of features.
    int N;

    cout << "Welcome to the Email Classifier System\n";

    // Initializing reader and classifier objects.
    EmailReader reader(spamFilePath, hamFilePath, testFilePath);
    KNNClassifier classifier(0);
    vector<string> topFeatures; // To store top features.
    vector<pair<string, string>> testData; // To store test data.
    vector<vector<double>> testDataFeatures; // To store feature vectors for each test email.
    vector<pair<pair<string, string>, bool>> trainingData; // To store training data.
    
    // Create an instance of FeatureExtractor
    FeatureExtractor featureExtractor;

    // Initialize or reinitialize the classifier.
    auto initializeClassifier = [&]() {
        do {
            cout << "Please enter an odd value of k for KNN classification (e.g., 1, 3, 5, ...): ";

            // Read input
            cin >> k;

            // Check if the input is numeric and valid
            if (cin.fail() || k <= 0 || k % 2 == 0) {
                cout << "The value of k must be a positive, odd number. Please try again.\n";

                // Clear the error flag
                cin.clear();

                // Ignore the rest of the line to prevent infinite loop
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (cin.fail() || k <= 0 || k % 2 == 0);
        
        classifier = KNNClassifier(k);
        
        do {
            cout << "Please enter the number of top features for feature extraction: ";
            
            // Read input
            cin >> N;

            // Check if the input is numeric and valid
            if (cin.fail() || N <= 0) {
                cout << "The value of N must be a positive number. Please try again.\n";

                // Clear the error flag
                cin.clear();

                // Ignore the rest of the line to prevent infinite loop
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (cin.fail() || N <= 0);            

        // Clearing previous test data and features.
        topFeatures.clear();
        testData.clear();
        testDataFeatures.clear();
        reader.readTrainingEmails();
        trainingData = reader.getTrainingData();

        vector<vector<double>> features;
        vector<bool> labels;

        // Extracting top features and preparing training data for the classifier.
        topFeatures = featureExtractor.extractBalancedTopFeatures(trainingData, N);
        for (const auto& data : trainingData) {
            features.push_back(featureExtractor.extractFeatures(data.first.first, data.first.second, topFeatures));
            labels.push_back(data.second);
        }
          
        classifier.train(features, labels);
        reader.readTestEmails();
        testData = reader.getTestData();
    };

    // Initialize the classifier with user inputs.
    initializeClassifier();

    // Extracting features from each test email.
    for (const auto& email : testData) {
        testDataFeatures.push_back(featureExtractor.extractFeatures(email.first, email.second, topFeatures));
    }

    int choice = 0;
    // Interactive menu to use the classifier.
    do {
        cout << "\nMenu:\n";
        cout << "1. Classify test emails\n";
        cout << "2. Summarize classifications\n";
        cout << "3. List top features\n";
        cout << "4. Change initial parameters\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";

            // Clear the error flag
            cin.clear();

            // Ignore the rest of the line
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Continue to the next iteration
            continue;
        }
        
        cout << "\n";

        switch (choice) {
            case 1: { // Classify each test email and output results.
                cout << "Classifying...\n";
                for (int i = 0; i < testDataFeatures.size(); ++i) {
                    bool isSpam = classifier.predict(testDataFeatures[i]);
                    cout << "Subject: " << testData[i].first << "\n";
                    cout << "Classification: " << (isSpam ? "Spam" : "Ham") << endl;
                    
                    // Prints the nearest neighbors with their calculated distance.
                    cout << "Neighbors: " << "\n";
                    classifier.predictAnalyze(testDataFeatures[i]);

                    // Outputting words that led to the classification.
                    cout << "Words that lead to its classification:\n";
                    const vector<double>& emailFeatures = testDataFeatures[i];
                    for (int j = 0; j < emailFeatures.size(); ++j) {
                        if (emailFeatures[j] > 0) {
                            cout << topFeatures[j] << ", ";
                        }
                    }
                    cout << "\n" << endl;
                }
                break;
            }
            case 2: { // Summarize the overall classification results.
                cout << "Summarizing classifications...\n";
                int spamCount = 0, hamCount = 0;
                for (const auto& emailFeatures : testDataFeatures) {
                    if (classifier.predict(emailFeatures)) {
                        ++spamCount;
                    } else {
                        ++hamCount;
                    }
                }
                cout << "Total emails classified: " << testDataFeatures.size() << endl;
                cout << "Spam: " << spamCount << endl;
                cout << "Ham: " << hamCount << endl;
                break;
            }
            case 3: { // List the top features used for classification.
                cout << "Top " << N << " Features:\n";
                for (const auto& feature : topFeatures) {
                    cout << feature << endl;
                }
                break;
            }
            case 4: { // Allow the user to change initial parameters.
                initializeClassifier();
                for (const auto& email : testData) {
                    testDataFeatures.push_back(featureExtractor.extractFeatures(email.first, email.second, topFeatures));
                }
                break;
            }
            case 5: // Exit the program.
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

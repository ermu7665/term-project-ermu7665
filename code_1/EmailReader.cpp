#include "EmailReader.h"

// Constructor: Sets file paths for spam, ham, and test email datasets.
EmailReader::EmailReader(const string& spamFilePath, const string& hamFilePath, const string& testFilePath)
    : spamFilePath_(spamFilePath), hamFilePath_(hamFilePath), testFilePath_(testFilePath) {
}

// Reads and processes training emails from spam and ham datasets.
void EmailReader::readTrainingEmails() {
    trainingData_.clear(); // Clear existing training data.

    ifstream spamFile(spamFilePath_), hamFile(hamFilePath_);
    string line;
    int spamCount = 0, hamCount = 0;

    // Reading and labeling spam emails.
    if (spamFile.is_open()) {
        getline(spamFile, line); // Skip header line.
        while (getline(spamFile, line)) {
            if (!line.empty()) {
                spamCount++;
                auto parsedEmail = parseLine(line);
                trainingData_.push_back(make_pair(parsedEmail, true)); // Label as true for spam.
            }
        }
        spamFile.close();
    } else {
        throw runtime_error("Failed to open spam file: " + spamFilePath_);
    }

    // Reading and labeling ham emails.
    if (hamFile.is_open()) {
        getline(hamFile, line); // Skip header line.
        while (getline(hamFile, line)) {
            if (!line.empty()) {
                hamCount++;
                auto parsedEmail = parseLine(line);
                trainingData_.push_back(make_pair(parsedEmail, false)); // Label as false for ham.
            }
        }
        hamFile.close();
    } else {
        throw runtime_error("Failed to open ham file: " + hamFilePath_);
    }
    cout << "Total spam emails loaded: " << spamCount << endl;
    cout << "Total ham emails loaded: " << hamCount << endl;

    cout << "Total training emails loaded: " << trainingData_.size() << endl;


}

// Reads and stores test emails for later prediction.
void EmailReader::readTestEmails() {
    testData_.clear(); // Clear existing test data.
    
    ifstream testFile(testFilePath_);
    string line;

    if (testFile.is_open()) {
        getline(testFile, line); // Skip header line.
        while (getline(testFile, line)) {
            if (!line.empty()) {
                testData_.push_back(parseLine(line)); // Add parsed email to test data.
            }
        }
        testFile.close();
    } else {
        throw runtime_error("Failed to open test file: " + testFilePath_);
    }
}

// Returns the parsed training data (emails and their labels).
vector<pair<pair<string, string>, bool>> EmailReader::getTrainingData() const {
    return trainingData_;
}

// Returns the parsed test data (emails without labels).
vector<pair<string, string>> EmailReader::getTestData() const {
    return testData_;
}

// Parses a line from the dataset and returns a pair of subject and message.
pair<string, string> EmailReader::parseLine(const string& line) const {
    int commaPos = line.find(','); // Find the delimiter position.

    if (commaPos == string::npos) {
        throw runtime_error("Invalid email format: " + line); // Error handling for incorrect format.
    }

    // Split the line into subject and message.
    string subject = line.substr(0, commaPos);
    string message = line.substr(commaPos + 1);

    return make_pair(subject, message); // Return the parsed email.
}

#ifndef EMAILREADER_H
#define EMAILREADER_H

#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

class EmailReader {
public:
    // Constructor: Initializes an EmailReader with paths to spam, ham, and test email datasets.
    EmailReader(const string& spamFilePath, const string& hamFilePath, const string& testFilePath);

    // Reads and parses training emails from the specified spam and ham files.
    void readTrainingEmails();

    // Reads and parses test emails from the specified test file.
    void readTestEmails();

    // Retrieves the training data consisting of email subject, message, and label (spam/ham).
    vector<pair<pair<string, string>, bool>> getTrainingData() const;

    // Retrieves the test data consisting of email subjects and messages.
    vector<pair<string, string>> getTestData() const;

private:
    // File paths for spam, ham, and test email datasets.
    string spamFilePath_;
    string hamFilePath_;
    string testFilePath_;

    // Stores parsed training data: pairs of (subject, message) and spam/ham label.
    vector<pair<pair<string, string>, bool>> trainingData_;

    // Stores parsed test data: list of email subjects and messages.
    vector<pair<string, string>> testData_;

    // Parses a single line from the email dataset and returns subject and message.
    pair<string, string> parseLine(const string& line) const;
};

#endif // EMAILREADER_H

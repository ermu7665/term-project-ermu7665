# CSPB 2270 – Data Structures - Term Project

### Author Information
- **Author**: Eric Munoz Hernandez
- **CU ID**: ermu7665
- **GitHub Username**: ermu7665

## Project Data Structure

This project implements a K-Nearest Neighbors (KNN) based email classification system, designed to identify spam and ham (non-spam) emails. The core components of this system include:

- **KNNClassifier**: Implements the KNN algorithm for classification.
- **FeatureExtractor**: Processes emails and extracts relevant features for classification.
- **EmailReader**: Reads and preprocesses email data from provided datasets.

### Data Structures Used:

- **Vectors and Pairs**: Utilized to handle and manipulate email data and features.
- **Priority Queue**: Employed in KNNClassifier for maintaining the k nearest neighbors.
- **Maps and Sets**: Used to store and manage the frequency of words in emails.

### Why These Data Structures?

- **Vectors**: Known for their efficiency in accessing elements and dynamic nature, making them ideal for storing email features and training data.
- **Priority Queue**: Crucial for efficiently finding the k nearest neighbors in the KNN algorithm.
- **Maps and Sets**: Effective for frequency counting and ensuring the uniqueness of features, which is crucial for feature extraction.

## Objective

The objective of this project is to design and implement an effective email classifier. This system aims to differentiate between spam and ham emails using machine learning algorithms, particularly KNN, thereby improving the accuracy of email filtering.

## Benefits of Using This Data Structure

- **Efficiency**: The chosen data structures optimize the email classification process, ensuring efficient handling of large datasets.
- **Scalability**: Thanks to the dynamic nature of vectors, the system can easily handle varying sizes of data, ensuring scalability.
- **Accuracy**: Leveraging KNN and feature extraction techniques significantly aids in enhancing the accuracy of spam detection.


## How to Run the Program

### 1) Compile the Code and Run the Executables

- **Open up the Terminal**:
  - Navigate to `Terminal > New Terminal`.

- **Navigate to `build` Directory**:
  - Enter the command:
    ```console
    jovyan@jupyter-yourcuid:~$ cd build/
    ```

- **Run CMake to Setup Build Environment**:
  - This creates files in the _build_ subdirectory needed to build the application.
    ```console
    jovyan@jupyter-yourcuid:~$ cmake ..
    ```

- **Compile and Build the Executables**:
  - Use the following command:
    ```console
    jovyan@jupyter-yourcuid:~$ make
    ```

- **Executable Ready to Run - `run_app_1`**:
  - `run_app_1` is built using the `/app` and `/code` source code files.
  - Located within the build directory. Run it with:
    ```console
    jovyan@jupyter-yourcuid:~$ ./run_app_1
    ```

### 2) Folder Structure

- **`app_1`**: 
  - **Description**: Contains the main application code.
  - **Contents**: Holds source file driving the application.

- **`build`**: 
  - **Description**: Stores compiled executables.
  - **Purpose**: Post-build destination for executable files created using CMake and Make.

- **`code_1`**: 
  - **Description**: Houses all header and C++ source files.
  - **Functionality**: Includes core logic, classes, and functions, organized into header (`*.h`) and implementation (`*.cpp`) files.

- **`test`**: 
  - **Description**: Contains test email dataset.
  - **Details**: Features a CSV file with test emails, each with a subject and message, for classification.
  - **Test Emails**: There are a total of 20 emails. The first 10 are spam and the last 10 are ham (not spam).

- **`training`**: 
  - **Description**: Includes training data for the algorithm.
  - **Data Structure**: Organized into two CSV files, `spam` and `ham`, essential for training the algorithm to differentiate between these email types.
  - **Training Emails**: There are 100 spam emails and 100 ham (not spam emails). This is the data that is teaching the program the key features that would clasify the "test" emails as spam or ham.


### 3) Main Menu Interface

#### Initial Configuration

- **Input K for KNN**:
  - Enter a value for 'K', the number of nearest neighbors in the KNN algorithm.

- **Enter Feature Count (N)**:
  - Specify 'N', the number of top features for classification.

#### Navigating the Main Menu

- **Access the Main Menu**:
  - With initial parameters set, the main menu offers these options:

    - **Option 1 - Classify Test Emails**:
      - Activates classification on test emails using the KNN model.

    - **Option 2 - Summarize Classifications**:
      - Provides a summary report of classifications.

    - **Option 3 - Display Top Features**:
      - Shows the top N features used in classification.

    - **Option 4 - Modify Parameters**:
      - Allows reconfiguration of K and N parameters.

    - **Option 5 - Exit Program**:
      - Closes the application safely.


## Class Summaries

### KNNClassifier Class

- **Constructor (KNNClassifier)**: Initializes the classifier with a specified number of neighbors (k).
- **train**: Stores the training features and corresponding labels.
- **predict**: Predicts if an email instance is spam or not using the KNN algorithm.
- **computeDistance**: Calculates the Euclidean distance between two feature vectors.
- **predictAnalyze**: Similar to `predict`, but also prints neighbor information.

### FeatureExtractor Class

- **toLower**: Converts a string to lowercase for case-insensitive processing.
- **tokenizeEmail**: Tokenizes an email into words, removing non-alphabetic characters.
- **buildFrequencyMap**: Creates a frequency map of words from tokens.
- **selectTopFeatures**: Selects the top N frequent words from a frequency map.
- **emailToFeatureVector**: Converts email tokens into a binary feature vector.
- **extractFeatures**: Generates a feature vector from an email based on top features.
- **extractBalancedTopFeatures**: Extracts balanced top features from training data.

### EmailReader Class

- **Constructor (EmailReader)**: Sets file paths for spam, ham, and test email datasets.
- **readTrainingEmails**: Processes training emails from spam and ham datasets.
- **readTestEmails**: Reads and stores test emails for prediction.
- **getTrainingData**: Returns parsed training data with labels.
- **getTestData**: Provides parsed test data without labels.
- **parseLine**: Parses a dataset line into a subject and message pair.


## Testing the program

**Run the program.**

**Recomended variables:**
- k = 5
- Number of features = 150

1) **Classify test emails**:
    - Shows the classification of the emails, it will also show the training email index that most closely reflect the test email, along with its distance.
        - Verify based on its true classification.     
            - **Fist 10 emails**: Are spam.
            - **Last 10 emails**: Are ham (not spam).
    - It will also show the "word features" that lead to its classification.
        - Verify word features appear on the respective email on the test CVS.
    
2) **Summarize classifications**:
    - This will show the count of the email classification. 
    - The count should match the classifications on the "Classify test emails" screen.
        - Verify count.
    - This will change depending on the K and N values that are initially selected. 
    - This should ideally match the 10 spam and 10 ham emails from the test file. 
    
3) **List top features**:
    - This will print out the number of "word features" that was initially created.
        - Verify count.
        
4) **Change initial parameters**:
    - This selection will allow you to change the initial parameters.
        - After setting the new parameters, verify the changes with the other selections (ie. changes to the classifications, feature counts, etc.).
        
  
    


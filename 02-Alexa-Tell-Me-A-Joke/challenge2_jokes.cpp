#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Structure to hold the separated joke components
struct Joke {
    string setup;
    string punchline;
};

// Function to load jokes from the text file into a vector
vector<Joke> loadJokes(const string& filename) {
    vector<Joke> jokes;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return jokes;
    }

    string line;
    while (getline(file, line)) {
        size_t qPos = line.find('?');
        if (qPos != string::npos) {
            Joke j;
            j.setup = line.substr(0, qPos + 1);
            j.punchline = line.substr(qPos + 1);
            jokes.push_back(j);
        }
    }
    file.close();
    return jokes;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    vector<Joke> jokes = loadJokes("randomJokes.txt");

    if (jokes.empty()) {
        return 1; // Exit if file couldn't be loaded or is empty
    }

    cout << "=== Voice Assistant Joke Program ===\n";
    cout << "Say 'Alexa, tell me a joke' (or type 'quit' to exit).\n\n";

    string input;
    while (true) {
        cout << "> ";
        getline(cin, input);

        // Normalize string to lowercase to handle case variations gracefully
        string lowerInput = input;
        transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

        if (lowerInput == "quit" || lowerInput == "exit") {
            cout << "Goodbye!\n";
            break;
        } else if (lowerInput == "alexa, tell me a joke" || lowerInput == "alexa tell me a joke") {
            int randomIndex = rand() % jokes.size();
            cout << "\n" << jokes[randomIndex].setup << "\n";
            cout << "[Press Enter to hear the punchline...]";
            
            string dummy;
            getline(cin, dummy); // Wait for user to press Enter
            
            cout << jokes[randomIndex].punchline << "\n\n";
        } else {
            cout << "Command not recognised. Try typing 'Alexa, tell me a joke' or 'quit'.\n\n";
        }
    }

    return 0;
}
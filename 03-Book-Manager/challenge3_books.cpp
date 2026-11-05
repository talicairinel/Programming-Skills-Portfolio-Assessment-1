#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Book {
private:
    string title;
    string author;
    int pages;
    string id;
    bool isBorrowed;

public:
    // Constructor to initialize the Book object
    Book(string t, string a, int p, string i, bool b)
        : title(t), author(a), pages(p), id(i), isBorrowed(b) {}

    // Getters 
    string getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getPages() const { return pages; }
    bool getBorrowedStatus() const { return isBorrowed; }

    // Setters for borrowing/returning
    void setBorrowedStatus(bool status) { isBorrowed = status; }

    // Display summary for list view
    void displaySummary() const {
        cout << "[" << id << "] " << title << " by " << author 
             << " (" << (isBorrowed ? "Borrowed" : "Available") << ")\n";
    }

    // Display full details for single book view
    void displayDetails() const {
        cout << "\n--- Book Details ---\n";
        cout << "ID     : " << id << "\n";
        cout << "Title  : " << title << "\n";
        cout << "Author : " << author << "\n";
        cout << "Pages  : " << pages << "\n";
        cout << "Status : " << (isBorrowed ? "Currently Borrowed" : "Available") << "\n";
    }
};

// Load books from CSV-formatted text file 
vector<Book> loadBooks(const string& filename) {
    vector<Book> library;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << "\n";
        return library;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string title, author, pagesStr, id, borrowedStr;

        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, pagesStr, ',');
        getline(ss, id, ',');
        getline(ss, borrowedStr, ',');

        // Remove potential carriage return characters (\r) from end of line
        if (!borrowedStr.empty() && borrowedStr.back() == '\r') {
            borrowedStr.pop_back();
        }

        int pages = 0;
        try {
            pages = stoi(pagesStr);
        } catch (const exception&) {
            cerr << "Warning: skipping malformed line: " << line << "\n";
            continue;
        }
        bool borrowed = (borrowedStr == "true");
        library.emplace_back(title, author, pages, id, borrowed);
    }
    file.close();
    return library;
}

// Save updated book statuses back to the file
void saveBooks(const string& filename, const vector<Book>& library) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not write to " << filename << "\n";
        return;
    }
    for (const auto& b : library) {
        file << b.getTitle() << "," << b.getAuthor() << "," << b.getPages() << ","
             << b.getId() << "," << (b.getBorrowedStatus() ? "true" : "false") << "\n";
    }
    file.close();
}

// Helper function to find a book pointer by ID
Book* findBookById(vector<Book>& library, const string& searchId) {
    for (auto& book : library) {
        if (book.getId() == searchId) {
            return &book;
        }
    }
    return nullptr;
}

int main() {
    const string filename = "bookData.txt";
    vector<Book> library = loadBooks(filename);

    if (library.empty()) return 1;

    int choice = 0;
    while (choice != 5) {
        cout << "\n=== Library Management System ===\n";
        cout << "1. View All Books\n";
        cout << "2. View Individual Book Details\n";
        cout << "3. Borrow a Book\n";
        cout << "4. Return a Book\n";
        cout << "5. Exit\n";
        cout << "Select an option (1-5): ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            cout << "\n--- All Library Books ---\n";
            for (const auto& book : library) {
                book.displaySummary();
            }
        } else if (choice >= 2 && choice <= 4) {
            string id;
            cout << "Enter Book ID (e.g., 001): ";
            cin >> id;
            Book* book = findBookById(library, id);

            if (!book) {
                cout << "Book with ID '" << id << "' not found.\n";
            } else if (choice == 2) {
                book->displayDetails();
            } else if (choice == 3) {
                if (book->getBorrowedStatus()) {
                    cout << "Sorry, '" << book->getTitle() << "' is already borrowed.\n";
                } else {
                    book->setBorrowedStatus(true);
                    saveBooks(filename, library);
                    cout << "You have successfully borrowed. '" << book->getTitle() << "'.\n";
                }
            } else if (choice == 4) {
                if (!book->getBorrowedStatus()) {
                    cout << "'" << book->getTitle() << "' is already in the library.\n";
                } else {
                    book->setBorrowedStatus(false);
                    saveBooks(filename, library);
                    cout << "You have successfully returned '" << book->getTitle() << "'.\n";
                }
            }
        } else if (choice != 5) {
            cout << "Invalid choice. Please select between 1 and 5.\n";
        }
    }

    cout << "Exiting Book Manager. Goodbye!\n";
    return 0;
}

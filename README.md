# Programming Skills Portfolio – Assessment 1

Three C++ console programs written for the Programming Skills Portfolio.


## Repository structure

```
Programming Skills Portfolio Assessment 1/
├── 01-CO2-Calculator/
│   └── challenge1_co2.cpp
├── 02-Alexa-Tell-Me-A-Joke/
│   ├── challenge2_jokes.cpp
│   └── randomJokes.txt
├── 03-Book-Manager/
│   ├── challenge3_books.cpp
│   └── bookData.txt
└── 
```

## Requirements

- A C++11 (or newer) compiler, e.g. `g++` or MSVC
- No external libraries (standard library only)

## How to build and run

Compile and run each program **from inside its own folder**. Challenges 2 and 3 read their data files from the current directory.

```bash
# Challenge 1
cd 01-CO2-Calculator
g++ -std=c++17 challenge1_co2.cpp -o challenge1_co2
./challenge1_co2

# Challenge 2
cd 02-Alexa-Tell-Me-A-Joke
g++ -std=c++17 challenge2_jokes.cpp -o challenge2_jokes
./challenge2_jokes

# Challenge 3
cd 03-Book-Manager
g++ -std=c++17 challenge3_books.cpp -o challenge3_books
./challenge3_books
```

On Windows, run the compiled `.exe` instead (e.g. `challenge1_co2.exe`).

---

## Challenge 1 – CO₂ Calculator

Estimates the CO₂ emissions of a car journey.

**How it works**
- Asks for the distance travelled (miles) and the fuel type (Petrol or Diesel).
- Assumes consumption of 9.66 litres per 100 miles.
- Emission factors: petrol 2.31 kg CO₂ per litre, diesel 2.68 kg CO₂ per litre.
- Prints a journey summary with the estimated emissions in kg, to two decimal places.

**Features**
- Three functions: `getDistance()`, `getFuelType()`, `calculateCO2()`.
- Input validation: rejects non-numeric, zero and negative distances, and unknown fuel types.
- Fuel type is case-insensitive (`Petrol`, `PETROL`, `petrol`).

**Example**
```
Enter the distance travelled (in miles): 100
Enter fuel type (Petrol / Diesel): diesel

--- Journey Summary ---
Distance Travelled : 100.00 miles
Fuel Type          : diesel
Estimated CO2      : 25.89 kg
```

---

## Challenge 2 – "Alexa, Tell Me a Joke"

A console voice-assistant emulator that tells jokes from a text file.

**How it works**
- Loads every joke from `randomJokes.txt` at start-up. Each line is a question followed immediately by its answer; the program splits each line at the first `?`.
- Type `Alexa, tell me a joke` to hear a random joke's setup.
- Press **Enter** to hear the punchline.
- Type `quit` or `exit` to leave.

**Features**
- `Joke` struct stored in a `std::vector<Joke>`.
- Commands are case-insensitive, and the comma is optional (`alexa tell me a joke`).
- Unrecognised commands show a help message.
- Exits with an error message if the joke file cannot be opened.

**Known limitation:** jokes are chosen with `rand()`, so the same joke can appear twice in a row.

**Example**
```
> Alexa, tell me a joke

What do you call a bear with no teeth?
[Press Enter to hear the punchline...]
A gummy bear!
```

---

## Challenge 3 – Book Manager

A simple library management system using an object-oriented design.

**How it works**
- Loads books from `bookData.txt` (comma-separated: `title,author,pages,id,borrowed`).
- Shows a five-option menu:
  1. View all books
  2. View details of one book (by ID)
  3. Borrow a book
  4. Return a book
  5. Exit

**Features**
- `Book` class with private data members, getters, a setter and display methods (encapsulation).
- Book IDs are stored as strings so values such as `001` keep their leading zeros.
- Malformed lines in the data file are skipped with a warning.
- Prevents borrowing a book that is already borrowed, and returning one that is already in the library.
- **Persistence:** every borrow or return is saved back to `bookData.txt`, so changes survive between runs.

**Data file format**
```
The Great Gatsby,F. Scott Fitzgerald,180,001,true
Pride and Prejudice,Jane Austen,279,004,false
```


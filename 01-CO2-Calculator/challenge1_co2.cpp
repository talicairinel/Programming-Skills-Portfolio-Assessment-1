#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <cctype>

using namespace std;

// Function to get and validate the distance travelled from the user
double getDistance() {
    double distance = 0.0;
    while (true) {
        cout << "Enter the distance travelled (in miles): ";
        if (cin >> distance && distance > 0) {
            cin.ignore(10000, '\n'); // Discard any leftover characters (e.g. "10abc")
            return distance;
        }
        if (cin.eof()) exit(1); // Input closed (e.g. Ctrl+D): stop instead of looping forever
        cout << "Invalid input. Please enter a positive numeric value.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

// Function to get and validate the fuel type from the user
string getFuelType() {
    string fuel;
    while (true) {
        cout << "Enter fuel type (Petrol / Diesel): ";
        if (!getline(cin, fuel)) exit(1); // Whole line read; stop if input closed
        // Convert input to lowercase for case-insensitive comparison
       transform(fuel.begin(), fuel.end(), fuel.begin(),
          [](unsigned char c) {
              return static_cast<char>(std::tolower(c));
          });
        if (fuel == "petrol" || fuel == "diesel") {
            return fuel;
        }
        cout << "Invalid fuel type. Please enter either 'Petrol' or 'Diesel'.\n";
    }
}

// Function to calculate CO2 emissions in kilograms
double calculateCO2(double distance, const string& fuelType) {
    const double LITRES_PER_100_MILES = 9.66;
    const double DIESEL_CO2_PER_LITRE = 2.68;
    const double PETROL_CO2_PER_LITRE = 2.31;

    double totalLitres = (distance / 100.0) * LITRES_PER_100_MILES;
    
    // fuelType is already validated, so anything other than diesel is petrol
    if (fuelType == "diesel") {
        return totalLitres * DIESEL_CO2_PER_LITRE;
    } else {
        return totalLitres * PETROL_CO2_PER_LITRE;
    }
}

int main() {
    cout << "=== Car Journey CO2 Emissions Calculator ===\n\n";
    
    double distance = getDistance();
    string fuelType = getFuelType();
    double emissions = calculateCO2(distance, fuelType);

    cout << fixed << setprecision(2);
    cout << "\n--- Journey Summary ---\n";
    cout << "Distance Travelled : " << distance << " miles\n";
    cout << "Fuel Type          : " << fuelType << "\n";
    cout << "Estimated CO2      : " << emissions << " kg\n";

    return 0;
}

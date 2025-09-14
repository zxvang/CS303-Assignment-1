#include "Header.h"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

int readIntOrThrow(const string& prompt) {
    cout << prompt;
    int v;
    if (!(cin >> v)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Invalid integer input.");
    }
    return v;
}

void menu() {
    cout << "\nMenu:\n"
        << " 1) Find a value\n"
        << " 2) Modify at index\n"
        << " 3) Add new value to end\n"
        << " 4) Remove at index\n"
        << " 5) Print 10x10 grid\n"
        << " 0) Quit\n";
}

int main() {
    cout << "10x10 Grid\n\n";

    IntArray arr;
    arr.initializeGrid();   // fill with 1–100
    arr.printAsGrid();

    int choice = -1;
    do {
        menu();
        cout << "Choose: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Please enter a number from the menu.\n";
            continue;
        }

        switch (choice) {
        case 1: { // Find value
            try {
                int value = readIntOrThrow("Value to find: ");
                int idx = arr.find(value);
                if (idx >= 0) cout << "Found at index " << idx << ".\n";
                else cout << "Not found.\n";
            }
            catch (const exception& ex) {
                cerr << "Error: " << ex.what() << "\n";
            }
            break;
        }
		case 2: { // Modify at index
            try {
                int index = readIntOrThrow("Index to modify (0-99): ");
                int newVal = readIntOrThrow("New value: ");
                if (index < 0) throw out_of_range("Index cannot be negative.");
                int oldVal = 0;
                int returned = arr.modifyAt(static_cast<size_t>(index), newVal, oldVal);
                cout << "Modified index " << index << ": old=" << oldVal
                    << ", new=" << returned << "\n";
            }
            catch (const exception& ex) {
                cerr << "Error: " << ex.what() << "\n";
            }
            break;
        }
		case 3: { // Append new value
            try {
                int newVal = readIntOrThrow("Value to append: ");
                arr.pushBack(newVal);
                cout << "Appended " << newVal << " to end.\n";
            }
            catch (const exception& ex) {
                cerr << "Error: " << ex.what() << "\n";
            }
            break;
        }
		case 4: { // Remove at index
            try {
                int index = readIntOrThrow("Index to remove: ");
                if (index < 0) throw out_of_range("Index cannot be negative.");
                arr.removeAt(static_cast<size_t>(index));
                cout << "Removed value at index " << index << ".\n";
            }
            catch (const exception& ex) {
                cerr << "Error: " << ex.what() << "\n";
            }
            break;
        }
        case 5: // Print grid
            arr.printAsGrid();
            break;
        case 0: // Exit
            cout << "Goodbye!\n";
            break;
        default:
            cerr << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}

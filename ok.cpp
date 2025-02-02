#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

struct Item {
    string dish;
    int qty;
    double price;
};

int main() {
    vector<Item> order = {
        {"Nom banhjok", 1, 2.5},
        {"Fried rice ", 2, 2.0},
        {"Fried Noodle ", 3, 3.0},
        {"White rice ", 4, 0.50},
        {"Ice latte  ", 5, 2.0},
        {"Green tea  ", 6, 1.80},
        {"Spaghetti  ", 7, 3.0}
    };

    vector<Item> selectedItems;
    int no, qty;
    string invoice;
    const double dollarToRielRate = 4000.0; // Exchange rate: 1 Dollar = 4000 Riel
    double total = 0.0;

    // Display menu
    cout << "==================================" << endl;
    cout << "........Cha Cha Restaurant........" << setw(8) << endl;
    cout << "==================================" << endl;
    cout << "-------------- Menu --------------" << endl;
    cout << " No.  Dish            Price" << endl;
    cout << "==================================" << endl;
    for (const auto& item : order) {
        cout << setw(3) << item.qty << ". " << setw(13) << left << item.dish 
             << right << setw(8) << fixed << setprecision(2) << item.price << "$" << endl;
    }
    cout << "==================================" << endl;
    cout << "Thank you for ordering!!!" << setw(8) << endl;
    cout << "==================================" << endl;

    // Take user input
    do {
        cout << "Please enter your selection from 1-7 and input 0 to indicate the end of your selection!" << endl;
        cout << "Enter the Dish number: ";
        cin >> no;

        if (cin.fail()) {  // Handle invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 7." << endl;
            continue;
        }

        if (no >= 1 && no <= 7) {
            cout << "Enter the quantity: ";
            cin >> qty;
            if (cin.fail() || qty <= 0) {  // Handle invalid or non-positive quantity
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid quantity. Please enter a positive number." << endl;
                continue;
            }

            // Find the selected item
            for (const auto& item : order) {
                if (item.qty == no) {
                    selectedItems.push_back({item.dish, qty, item.price});
                    break;
                }
            }
        } else if (no != 0) {
            cout << "Invalid choice. Please try filling in from 1-7." << endl;
        }

    } while (no != 0);

    // Final receipt
    cout << "====================================================" << endl;
    cout << "               Cha Cha Restaurant" << endl;
    cout << "====================================================" << endl;
    cout << endl;
    cout << "   Address : Paragon International University " << endl;
    cout << setw(35) << "Phnom Penh, Cambodia" << endl;
    cout << endl;

    // Input invoice number
    do {
        cout << "Invoice number: ";
        cin >> invoice;
        if (invoice.empty()) {
            cout << "Invoice number cannot be empty. Please enter a valid invoice number." << endl;
        }
    } while (invoice.empty());

    cout << "Cashier: Cheziel " << endl;
    cout << "Customer: General" << endl;
    cout << "....................................................." << endl;
    cout << "Dish           Unit Price     Quantity     Subtotal" << endl;
    cout << "....................................................." << endl;

    for (const auto& item : selectedItems) {
        double subtotal = item.qty * item.price;
        total += subtotal;
        cout << left << setw(14) << item.dish
             << right << setw(10) << fixed << setprecision(2) << item.price << "$"
             << setw(12) << item.qty
             << setw(14) << fixed << setprecision(2) << subtotal << "$" << endl;
    }

    cout << "....................................................." << endl;
    cout << "Total: "<< fixed << setprecision(2) << total << "$" << endl;

    // Handle payment and money exchange
    cout << "....................................................." << endl;
    char currencyChoice;
    double userCash, totalInRiel, change;

    cout << "(D)ollars or (R)iels " << endl;
    cout << "Enter D for Dollar and R for riel : ";
    cin >> currencyChoice;

    if (currencyChoice == 'D' || currencyChoice == 'd') {
        cout << "Enter the cash amount in Dollars: ";
        cin >> userCash;
        if (userCash >= total) {
            change = userCash - total;
            cout << "Change: $" << fixed << setprecision(2) << change << endl;
        } else {
            cout << "Insufficient cash. The customer needs $" << fixed << setprecision(2) << (total - userCash) << " more." << endl;
        }
    } else if (currencyChoice == 'R' || currencyChoice == 'r') {
        totalInRiel = total * dollarToRielRate;  // Convert total to Riel
        cout << "Total in Riel: " << fixed << setprecision(2) << totalInRiel << " Riel" << endl;
        cout << "Enter the cash amount in Riel: ";
        cin >> userCash;
        if (userCash >= totalInRiel) {
            change = userCash - totalInRiel;
            cout << "Change: " << fixed << setprecision(2) << change << " Riel" << endl;
        } else {
            cout << "Insufficient cash. The customer needs " << fixed << setprecision(2) << (totalInRiel - userCash) << " Riel more." << endl;
        }
    } else {
        cout << "Invalid currency choice. Please restart the program." << endl;
    }

    cout << "....................................................." << endl;
    cout << "...........THANK YOU FOR DINING WITH US!............." << endl;
    cout << "....................................................." << endl;

    return 0;
}

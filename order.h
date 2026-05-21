#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct Product {
    string name;
    double price;
    int quantity;
};
struct DiscountCard {
    string cardNumber;
    double totalSpent;

    pair<double, string> getDiscountInfo() const {
        if (totalSpent >= 500.0) return { 0.10, "!vip!" };
        if (totalSpent >= 200.0) return { 0.05, "not-a-begginer" };
        return { 0.03, "First-come" };
    }

    void displayCard() const {
        pair<double, string> info = getDiscountInfo();
        double rate = info.first;
        string rank = info.second;

        cout << "\n=======================================" << endl;
        cout << " Personal Discount Card" << endl;
        cout << "=======================================" << endl;
        cout << " Number: " << cardNumber << endl;
        cout << " Status: " << rank << endl;
        cout << " Accumulated: " << totalSpent << " USD" << endl;
        cout << " Your discount: " << (rate * 100) << "% on everything!" << endl;
        cout << "=======================================\n" << endl;
    }
}; 

class OnlineOrder {
private:
    vector<Product> cart;
    string orderDate;
    string status;
    DiscountCard clientCard; 
    bool hasCard = false;

public:
    void registerClientCard(string number, double spent) {
        clientCard = { number, spent };
        hasCard = true;
        clientCard.displayCard();
    }

    OnlineOrder() : status("Pending"), orderDate("20.04.2026") {}

    void setStatus(string newStatus) { status = newStatus; }

    void addProduct(string name, double price, int qty) {
        cart.push_back({ name, price, qty });
    }

    void removeProduct(string name) {
        cart.erase(remove_if(cart.begin(), cart.end(),
            [&](const Product& p) { return p.name == name; }), cart.end());
    }

    void updateQuantity(string name, int newQty) {
        for (auto& p : cart) {
            if (p.name == name) {
                p.quantity = newQty;
                return;
            }
        }
    }

    void displayCatalog(string filename) const {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open " << filename <<  endl;
            return;
        }
        cout << "\n--- AVAILABLE PRODUCTS ---" << endl;
        string name; double price;
        while (file >> name >> price) {
            cout << left << name << " | Price: " << price << " USD" << endl;
        }
        file.close();
    }

    void showCart() const {
        double total = 0;
        cout << "\n--- CURRENT CART ---" << endl;
        for (const auto& p : cart) {
            double sum = p.price * p.quantity;
            cout << p.name << " | " << p.quantity << " pcs x " << p.price << " = " << sum << " USD" << endl;
            total += sum;
        }
        cout << "--------------------" << endl;
        cout << "\033[32mTOTAL AMOUNT: " << total << " USD\033[0m" << endl;
    }

    void saveOrderToFile(string filename) const {
        ofstream file(filename);
        double total = 0;
        file << "ORDER REPORT\nStatus: " << status << "\n\n";
        for (const auto& p : cart) {
            file << p.name << " | " << p.quantity << " x " << p.price << " = " << p.price * p.quantity << "\n";
            total += p.price * p.quantity;
        }
        file << "\nTOTAL: " << total << " USD";
        file.close();
    }
};

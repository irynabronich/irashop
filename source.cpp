#include "order.h"

double getPriceFromCatalog(string productName) {
    ifstream file("shop.txt");
    string name; double price;
    while (file >> name >> price) {
        if (name == productName) {
            file.close();
            return price;
        }
    }
    file.close();
    return -1;
}

int main() {
    OnlineOrder myOrder;
    int choice;

    while (true) {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Show Cart (Calculate Total)" << endl;
        cout << "2. Remove Product" << endl;
        cout << "3. Update Quantity" << endl;
        cout << "4. Change Status" << endl;
        cout << "5. Save to File & Exit" << endl;
        cout << "6. Add Product (Search from shop.txt)" << endl;
        cout << "7. Show All Catalog" << endl;
        cout << "8.CARD!!!" << endl;
        cout << "0. Exit without Saving" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1:
            myOrder.showCart();
            break;
        case 2: {
            string name;
            cout << "Name to remove: "; cin >> name;
            myOrder.removeProduct(name);
            cout <<"Success!" <<  endl;
            break;
        }
        case 3: {
            string name; int qty;
            cout << "Product name: "; cin >> name;
            cout << "New quantity: "; cin >> qty;
            myOrder.updateQuantity(name, qty);
            break;
        }
        case 4: {
            string s;
            cout << "New status: "; cin >> s;
            myOrder.setStatus(s);
            break;
        }
        case 5:
            myOrder.saveOrderToFile("myreceipt.txt");
            cout <<  "Saved. Goodbye!" <<  endl;
            return 0;
        case 6: {
            string name; int qty;
            cout << "Enter product name: "; cin >> name;
            double price = getPriceFromCatalog(name);
            if (price != -1) {
                cout <<  "Price: " << price  << ". Quantity: ";
                cin >> qty;
                myOrder.addProduct(name, price, qty);
                cout << "Added!"  << endl;
            }
            else {
                cout << "\033[31mProduct not found.\033[0m" << endl;
            }
            break;
        }
        case 7:
            myOrder.displayCatalog("shop.txt");
            break;
        case 8: {
            string cardNum;
            double spent;
            cout << "\n--- SCANNING DISCOUNT CARD ---" << endl;
            cout << "Enter Card Number: "; cin >> cardNum;
            cout << "Enter Accumulated Amount (USD): "; cin >> spent;
            myOrder.registerClientCard(cardNum, spent);
            break;
        }

        default:
            cout << "Invalid choice." << endl;
        }       
    }
    return 0;
}

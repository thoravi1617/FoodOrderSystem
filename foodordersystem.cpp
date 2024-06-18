#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class MenuItem {
public:
    string name;
    double price;

    MenuItem(string n, double p) : name(n), price(p) {}
};

class Order {
public:
    vector<MenuItem> items;

    void addItem(const MenuItem& item) {
        items.push_back(item);
    }

    double calculateTotal() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.price;
        }
        return total;
    }

    void displayOrder() const {
        cout << "Order Details:\n";
        for (const auto& item : items) {
            cout << item.name << "\tRs." << item.price << endl;
        }
        cout<<"------------------------\n";
        cout << "Total: Rs." << calculateTotal() << endl;
    }
};

class RoomService {
public:
    void placeOrder(Order& order) {
        orders.push_back(order);
        cout << "Order placed Successfully!\n";
    }

    void viewOrders() const {
        if (orders.empty()) {
            cout << "No orders yet.\n";
        } else {
            cout << "Current Orders:\n";
            for (const auto& order : orders) {
                order.displayOrder();
                cout << "-----------------------\n";
            }
        }
    }

private:
    vector<Order> orders;
};

class Hotel {
public:
    void displayMenu() const {
        cout << "Menu:\n";
        for (const auto& item : menu) {
            cout << item.name << "\tRs." << item.price << endl;
        }
    }

    MenuItem getItemByName(const string& itemName) const {
        string lowercaseItemName = itemName;
        transform(lowercaseItemName.begin(), lowercaseItemName.end(), lowercaseItemName.begin(), ::tolower);

        for (const auto& item : menu) {
            string lowercaseItem = item.name;
            transform(lowercaseItem.begin(), lowercaseItem.end(), lowercaseItem.begin(), ::tolower);

            if (lowercaseItem == lowercaseItemName) {
                return item;
            }
        }
        return MenuItem("", 0.0);
    }

private:
    vector<MenuItem> menu = {
        {"Burger", 49},
        {"Pizza", 139},
        {"Pasta", 69},
        {"Maggi", 49},
        {"French Fries", 60},
        {"Potato Chilli", 80},
        {"Paneer Chilli", 99},
        {"Fried Rice", 70},
        {"Spring Roll", 50},
        {"Soft Drink", 50},
        {"Mineral Water", 25},
    };
};

int main() {
    Hotel hotel;
    RoomService roomService;

    while (true) {
        cout << "\n1. Display Menu\n";
        cout << "2. Place Order\n";
        cout << "3. View Orders\n";
        cout << "4. Exit\n";
        cout << "Enter your Choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                hotel.displayMenu();
                break;

            case 2: {
                Order order;
                cout << "Enter item name to add to the order (or 'done' to finish): ";
                cin.ignore(); // Ignore newline character left in the buffer
                string itemName;
                while (getline(cin,itemName) && itemName != "done") {
                MenuItem item = hotel.getItemByName(itemName);
                    if (item.name.empty()) {
                        cout << "Invalid item. Please enter a valid item name.\n";
                    } else {
                        order.addItem(item);
                    }
                }
                roomService.placeOrder(order);
                break;
            }

            case 3:
                roomService.viewOrders();
                break;

            case 4:
                cout << "Been a pleasure serving you. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid item. Please enter a valid item(s). \n";
        }
    }
    return 0;
}

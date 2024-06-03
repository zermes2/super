#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Abstract Base Class for products
class Product {
protected:
    int id;            // Product ID
    string name;       // Product name
    float price;       // Product price
    int quantity;      // Product quantity

public:
    // Default constructor
    Product() : id(0), name(""), price(0.0), quantity(0) {}

    // Parameterized constructor
    Product(int id, string name, float price, int quantity) : id(id), name(name), price(price), quantity(quantity) {}

    // Copy constructor
    Product(const Product& other) : id(other.id), name(other.name), price(other.price), quantity(other.quantity) {}

    // Pure virtual function for displaying product information
    virtual void display() const = 0;

    // Getter functions for id and quantity
    int getId() const { return id; }
    int getQuantity() const { return quantity; }

    // Overload insertion operator for output
    friend ostream& operator<<(ostream& os, const Product& p);

    // Overload extraction operator for input
    friend istream& operator>>(istream& is, Product& p);

    // Virtual destructor
    virtual ~Product() {}
};

// Overload insertion operator for output
ostream& operator<<(ostream& os, const Product& p) {
    os << "ID: " << p.id << ", Name: " << p.name << ", Price: " << p.price << ", Quantity: " << p.quantity;
    return os;
}

// Overload extraction operator for input
istream& operator>>(istream& is, Product& p) {
    cout << "Enter product ID: ";
    is >> p.id;
    cout << "Enter product name: ";
    is >> p.name;
    cout << "Enter product price: ";
    is >> p.price;
    cout << "Enter product quantity: ";
    is >> p.quantity;
    return is;
}

// Derived class for grocery products
class Grocery : public Product {
public:
    // Default constructor
    Grocery() : Product() {}

    // Parameterized constructor
    Grocery(int id, string name, float price, int quantity) : Product(id, name, price, quantity) {}

    // Override display function
    void display() const override {
        cout << "Grocery Product - " << *this << endl;
    }
};

// Derived class for electronics products
class Electronics : public Product {
public:
    // Default constructor
    Electronics() : Product() {}

    // Parameterized constructor
    Electronics(int id, string name, float price, int quantity) : Product(id, name, price, quantity) {}

    // Override display function
    void display() const override {
        cout << "Electronics Product - " << *this << endl;
    }
};

// Class to represent a customer order


// Class to represent a customer order
class CustomerOrder {
private:
    int productId;  // Product ID
    int quantity;   // Quantity ordered

public:
    // Default constructor
    CustomerOrder() : productId(0), quantity(0) {}

    // Constructor
    CustomerOrder(int id, int qty) : productId(id), quantity(qty) {}

    // Getter functions for product ID and quantity
    int getProductId() const { return productId; }
    int getQuantity() const { return quantity; }
};



// Class to manage supermarket
class Supermarket {
private:
    Product* products[100];       // Array to store products
    int productCount;             // Number of products
    CustomerOrder orders[100];    // Array to store customer orders
    int orderCount;              // Number of orders

public:
    // Constructor
    Supermarket() : productCount(0), orderCount(0) {}

    // Function to add a product
    void addProduct(Product* p) {
        products[productCount++] = p;
        cout << "Product added successfully!" << endl;
    }

    // Function to display all products
    void displayProducts() const {
        for (int i = 0; i < productCount; i++) {
            products[i]->display();
        }
    }
    // Function to save products to a file
    void saveToFile() const {
        ofstream file("products_oop.txt");
        for (int i = 0; i < productCount; i++) {
            file << *products[i] << endl;
        }
        file.close();
        cout << "Products saved to file!" << endl;
    }

    // Function to load products from a file
    void loadFromFile() {
        ifstream file("products_oop.txt");
        Product* p;
        while (file >> *p) {
            addProduct(p);
        }
        file.close();
        cout << "Products loaded from file!" << endl;
    }

    // Function to add an order
    void addOrder(const CustomerOrder& order) {
        orders[orderCount++] = order;
        cout << "Order added successfully!" << endl;
    }

    // Function to display all orders
    void displayOrders() const {
        for (int i = 0; i < orderCount; i++) {
            cout << "Product ID: " << orders[i].getProductId() << ", Quantity: " << orders[i].getQuantity() << endl;
        }
    }

    // Destructor to clean up dynamic memory
    ~Supermarket() {
        for (int i = 0; i < productCount; i++) {
            delete products[i];
        }
    }
};

int main() {
     cout << "\t\t\t_________________________________________________________________________________\n";
    cout << "\t\t\t|                                                                                |\n";
    cout << "\t\t\t|                              Supermarket Main Menu                             |\n";
    cout << "\t\t\t|                                                                                |\n";
    cout << "\t\t\t|________________________________________________________________________________|\n";
    cout << endl;
    Supermarket supermarket;
    int choice;
    do {
        // Display menu and get user's choice
        cout << "1. Add Grocery Product\n2. Add Electronics Product\n3. Display Products\n4. Save to File\n5. Load from File\n6. Add Order\n7. Display Orders\n8. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                Grocery* g = new Grocery();
                cin >> *g;
                supermarket.addProduct(g);
                break;
            }
            case 2: {
                Electronics* e = new Electronics();
                cin >> *e;
                supermarket.addProduct(e);
                break;
            }
            case 3: supermarket.displayProducts(); break;
            case 4: supermarket.saveToFile(); break;
            case 5: supermarket.loadFromFile(); break;
            case 6: {
                int productId, quantity;
                cout << "Enter product ID: ";
                cin >> productId;
                cout << "Enter quantity: ";
                cin >> quantity;
                CustomerOrder order(productId, quantity);
                supermarket.addOrder(order);
                break;
            }
            case 7: supermarket.displayOrders(); break;
            case 8: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    } while (choice!= 8);  // Loop until the user chooses to exit
    return 0;
}

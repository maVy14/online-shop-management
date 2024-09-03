#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Shopping {
private:
    int pcode;
    float price;
    float discount;
    int quantity;
    string pname;

public:
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
    void viewPurchases();
};

void Shopping::administrator() {
    int choice;
    cout << "\n\n\n\t Administrator Menu";
    cout << "\n\t1) Add the product";
    cout << "\n\t2) Modify the product";
    cout << "\n\t3) Delete the product";
    cout << "\n\t4) Back to main menu";
    cout << "\n\n\t Please enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            add();
            break;
        case 2:
            edit();
            break;
        case 3:
            rem();
            break;
        case 4:
            return;
        default:
            cout << "\n\n Invalid choice. Please try again.";
    }
}

void Shopping::buyer() {
    int choice;
    cout << "\n\n\n\t Buyer";
    cout << "\n\t1) Buy product";
    cout << "\n\t2) Back to main menu";
    cout << "\n\n\t Please enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            receipt();
            break;
        case 2:
            return;
        default:
            cout << "\n\n Invalid choice. Please try again.";
    }
}

void Shopping::add() {
    fstream data;
    int token = 0;
    int c;
    float p, d;
    int q;
    string n;

    cout << "\n\n\t Add new product";
    cout << "\n\n\t Product code: ";
    cin >> pcode;
    cout << "\n\n\t Name of the product: ";
    cin >> pname;
    cout << "\n\n\t Price of the product: ";
    cin >> price;
    cout << "\n\n\t Discount on product: ";
    cin >> discount;
    cout << "\n\n\t Quantity of the product: ";
    cin >> quantity;

    data.open("database.txt", ios::in);
    if (!data) {
        data.open("database.txt", ios::app | ios::out);
        data << pcode << " " << pname << " " << price << " " << discount << " " << quantity << "\n";
        data.close();
    } else {
        data >> c >> n >> p >> d >> q;
        while (!data.eof()) {
            if (c == pcode) {
                token++;
            }
            data >> c >> n >> p >> d >> q;
        }
        data.close();

        if (token == 1) {
            cout << "\n\n\t Product code already exists.";
            return;
        } else {
            data.open("database.txt", ios::app | ios::out);
            data << pcode << " " << pname << " " << price << " " << discount << " " << quantity << "\n";
            data.close();
        }
    }

    cout << "\n\n\t Record inserted!";
}

void Shopping::edit() {
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p, d;
    int q;
    string n;

    cout << "\n\n\t Modify the record";
    cout << "\n\n\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n\t File doesn't exist!";
    } else {
        data1.open("database1.txt", ios::app | ios::out);

        data >> pcode >> pname >> price >> discount >> quantity;
        while (!data.eof()) {
            if (pkey == pcode) {
                cout << "\n\n\t Product new code: ";
                cin >> c;
                cout << "\n\n\t Name of the product: ";
                cin >> n;
                cout << "\n\n\t Price: ";
                cin >> p;
                cout << "\n\n\t Discount: ";
                cin >> d;
                cout << "\n\n\t Quantity: ";
                cin >> q;

                data1 << c << " " << n << " " << p << " " << d << " " << q << "\n";
                cout << "\n\n\t Record edited!";
                token++;
            } else {
                data1 << pcode << " " << pname << " " << price << " " << discount << " " << quantity << "\n";
            }
            data >> pcode >> pname >> price >> discount >> quantity;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\n\t Record not found!";
        }
    }
}

void Shopping::rem() {
    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "\n\n\t Delete product";
    cout << "\n\n\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n\t File doesn't exist!";
    } else {
        data1.open("database1.txt", ios::app | ios::out);

        data >> pcode >> pname >> price >> discount >> quantity;
        while (!data.eof()) {
            if (pcode == pkey) {
                cout << "\n\n\t Product deleted!";
                token++;
            } else {
                data1 << pcode << " " << pname << " " << price << " " << discount << " " << quantity << "\n";
            }
            data >> pcode >> pname >> price >> discount >> quantity;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\n\t Record not found!";
        }
    }
}

void Shopping::list() {
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n---------------------------------------------------\n";
    cout << "ProNo\tName\tPrice\tDiscount\tQuantity\n";
    cout << "---------------------------------------------------\n";
    data >> pcode >> pname >> price >> discount >> quantity;
    while (!data.eof()) {
        cout << pcode << "\t" << pname << "\t" << price << "\t" << discount << "%\t\t" << quantity << "\n";
        data >> pcode >> pname >> price >> discount >> quantity;
    }
    data.close();
}

void Shopping::receipt() {
    fstream data;
    int arrc[100], arrq[100];
    char choice;
    int c = 0;
    float amount = 0, discountAmount = 0, total = 0;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n\t Database is empty!";
        return;
    }

    data.close();
    list();
    cout << "\n-----------------------------------------";
    cout << "\n             Place your order";
    cout << "\n-----------------------------------------\n";
    do {
        cout << "\n\nEnter Product Code: ";
        cin >> arrc[c];
        cout << "\n\nEnter Quantity: ";
        cin >> arrq[c];
        c++;
        cout << "\n\nDo you want to buy another product? (y/n): ";
        cin >> choice;
    } while (choice == 'y');

    cout << "\n\n-----------------------------------------\n";
    cout << "Receipt\n";
    cout << "-----------------------------------------\n";
    cout << "ProNo\tName\tQuantity\tPrice\tAmount\tDiscounted Amount\n";
    
    for (int i = 0; i < c; i++) {
        data.open("database.txt", ios::in);
        data >> pcode >> pname >> price >> discount >> quantity;
        while (!data.eof()) {
            if (pcode == arrc[i]) {
                if (quantity >= arrq[i]) {
                    amount = price * arrq[i];
                    discountAmount = amount - (amount * discount / 100);
                    total += discountAmount;
                    cout << pcode << "\t" << pname << "\t" << arrq[i] << "\t\t" << price << "\t" << amount << "\t" << discountAmount << "\n";
                    
                    quantity -= arrq[i];  // Reduce the quantity in stock
                    fstream temp;
                    temp.open("database1.txt", ios::app | ios::out);
                    fstream original;
                    original.open("database.txt", ios::in);

                    int tempCode;
                    string tempName;
                    float tempPrice, tempDiscount;
                    int tempQuantity;

                    while (original >> tempCode >> tempName >> tempPrice >> tempDiscount >> tempQuantity) {
                        if (tempCode == pcode) {
                            temp << tempCode << " " << tempName << " " << tempPrice << " " << tempDiscount << " " << quantity << "\n";
                        } else {
                            temp << tempCode << " " << tempName << " " << tempPrice << " " << tempDiscount << " " << tempQuantity << "\n";
                        }
                    }

                    original.close();
                    temp.close();
                    remove("database.txt");
                    rename("database1.txt", "database.txt");
                } else {
                    cout << "\n\nNot enough quantity in stock for product code: " << pcode;
                }
            }
            data >> pcode >> pname >> price >> discount >> quantity;
        }
        data.close();
    }
    cout << "\n-----------------------------------------\n";
    cout << "Total Amount: " << total << "\n";
}

int main() {
    Shopping s;
    int choice;
    string email, password;

    cout << "\n\n\t\t Supermarket Main Menu";
    cout << "\n\t1) Administrator";
    cout << "\n\t2) Buyer";
    cout << "\n\t3) Exit";
    cout << "\n\n\t Please select: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "\n\n\t Please login ";
            cout << "\n\t Enter email: ";
            cin >> email;
            cout << "\n\t Enter password: ";
            cin >> password;

            if (email == "admin" && password == "admin123") {
                s.administrator();
            } else {
                cout << "\n\n\t Invalid email/password!";
            }
            break;
        case 2:
            s.buyer();
            break;
        case 3:
            return 0;
        default:
            cout << "\n\n Invalid choice!";
    }

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

class Shopping {
private:
    int pcode;
    float price;
    float dis;
    int quantity;
    string pname;
    int cart[100];
    int cartQuantity[100];
    int cartSize = 0;
    string mainAdminEmail = "phonemyatmaw@email.com";
    string mainAdminPassword = "pmm2004";
    string subAdminEmails[2];
    string subAdminPasswords[2];
    int subAdminCount = 0;

public:
    void menu();
    void administrator();
    void subAdministrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
    void viewPurchases();
    void showCart();
    void addSubAdmin();
    bool login(string &role);
    string generateRandomReceiptNumber();
};

void Shopping::menu() {
    int choice;
    string role;

    while (true) {
        cout << "\n\t\t\t\t __________________________\n";
        cout << "\t\t\t\t   Supermarket Main Menu   \n";
        cout << "\t\t\t\t __________________________\n";
        cout << "\t\t\t\t| 1) Administrator         |\n";
        cout << "\t\t\t\t| 2) Buyer                 |\n";
        cout << "\t\t\t\t| 3) Exit                  |\n";
        cout << "\n\t\t\t  Please Select: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (login(role)) {
                    if (role == "main_admin") {
                        administrator();
                    } else if (role == "sub_admin") {
                        subAdministrator();
                    }
                } else {
                    cout << "Invalid email/password" << endl;
                }
                break;
            case 2:
                buyer();
                break;
            case 3:
                exit(0);
            default:
                cout << "Please select from the given options" << endl;
        }
    }
}

bool Shopping::login(string &role) {
    string email, password;
    cout << "\t\t\t Please Login \n";
    cout << "\t\t\t Enter Email: ";
    cin >> email;
    cout << "\t\t\t Password: ";
    cin >> password;

    if (email == mainAdminEmail && password == mainAdminPassword) {
        role = "main_admin";
        return true;
    }

    for (int i = 0; i < subAdminCount; i++) {
        if (email == subAdminEmails[i] && password == subAdminPasswords[i]) {
            role = "sub_admin";
            return true;
        }
    }
    return false;
}

void Shopping::administrator() {
    int choice;

    while (true) {
        cout << "\n\n\n\t\t\t Administrator Menu";
        cout << "\n\t\t\t|______1) Add the Product_________|";
        cout << "\n\t\t\t|______2) Modify the Product______|";
        cout << "\n\t\t\t|______3) Delete the Product______|";
        cout << "\n\t\t\t|______4) View All Purchases______|";
        cout << "\n\t\t\t|______5) View Product Lists______|";
        cout << "\n\t\t\t|______6) Add Co-Admin___________|";
        cout << "\n\t\t\t|______7) Back to Main Menu_______|";

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
                viewPurchases();
                break;
            case 5:
                list();
                break;
            case 6:
                addSubAdmin();
                break;
            case 7:
                return;
            default:
                cout << "Invalid choice" << endl;
        }
    }
}

void Shopping::subAdministrator() {
    int choice;

    while (true) {
        cout << "\n\n\n\t\t\t Co-Administrator Menu";
        cout << "\n\t\t\t|______1) Add the Product_________|";
        cout << "\n\t\t\t|______2) Modify the Product______|";
        cout << "\n\t\t\t|______3) Delete the Product______|";
        cout << "\n\t\t\t|______4) View All Purchases______|";
        cout << "\n\t\t\t|______5) View Product Lists______|";
        cout << "\n\t\t\t|______6) Back to Main Menu_______|";

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
                viewPurchases();
                break;
            case 5:
                list();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice" << endl;
        }
    }
}

void Shopping::addSubAdmin() {
    if (subAdminCount >= 2) {
        cout << "\n\n Cannot add more than 2 Co-admins!" << endl;
        return;
    }

    cout << "\n\n\t\t\t Add new Co-Admin";
    cout << "\n\n\t Enter Co-Admin Email: ";
    cin >> subAdminEmails[subAdminCount];
    cout << "\n\n\t Enter Co-Admin Password: ";
    cin >> subAdminPasswords[subAdminCount];

    subAdminCount++;
    cout << "\n\n\t\t Co-Admin added successfully!" << endl;
}

void Shopping::buyer() {
    int choice;

    while (true) {
        cout << "\n\t\t\t     Buyer \n";
        cout << "\t\t\t 1) Buy Product  \n";
        cout << "\t\t\t 2) Show Cart    \n";
        cout << "\t\t\t 3) Go Back      \n";
        cout << "\t\t\t Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                receipt();
                break;
            case 2:
                showCart();
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice" << endl;
        }
    }
}

void Shopping::add() {
    fstream data;
    int c;
    float p;
    float d;
    int q;
    string n;
    bool found = false;

    cout << "\n\n\t\t\t Add New Product";
    cout << "\n\n\t Product Code of the Product: ";
    cin >> pcode;
    cout << "\n\n Name of the Product: ";
    cin >> pname;
    cout << "\n\n\t Price of the Product: ";
    cin >> price;
    cout << "\n\n\t Discount on Product(%): ";
    cin >> dis;
    cout << "\n\n\t Quantity of the Product: ";
    cin >> quantity;

    data.open("database.txt", ios::in);
    if (data) {
        data >> c >> n >> p >> d >> q; //>>: This is the extraction operator used to pull data from the file stream and store it in                             the variables.
        while (!data.eof()) {
            if (c == pcode) {
                found = true;
                break;
            }
            data >> c >> n >> p >> d >> q;
        }
        data.close();
    }

    if (found) {
        cout << "Product code already exists!" << endl;
    } else {
        data.open("database.txt", ios::app | ios::out);  // | bitwise OR operator
        data << pcode << " " << pname << " " << price << " " << dis << " " << quantity << "\n"; // writing into the file
        data.close();
        cout << "\n\n\t\t Record inserted!" << endl;
    }
}

void Shopping::edit() {
    fstream data, data1;
    int pkey;
    int c;  // new product code, price, discount, quantity, and name of the product, respectively.// Stores the new product code (after modification)
    float p;
    float d;
    int q;
    string n;
    bool found = false; // to check if the product is found in the file.

    cout << "\n\t\t\t\t Modify the Record";   // will get the Product Code to Modify:
    cout << "\n\t\t\t\t Product Code: ";   // lets say want to modify the product which product code is 3;
    cin >> pkey;   // pkey = 3;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n File doesn't exist!" << endl;
        return;
    }

    data1.open("database1.txt", ios::app | ios::out);
    data >> pcode >> pname >> price >> dis >> quantity; // Reading the Records from the File: there is no way to find the product you want to modify.
    while (!data.eof()) {
        if (pkey == pcode) {  //... logic to check if the product code matches and edit the record
            cout << "\n\t\t Product New Code: ";
            cin >> c;
            cout << "\n\t\t Name of the Product: ";
            cin >> n;
            cout << "\n\t\t Price: ";
            cin >> p;
            cout << "\n\t\t Discount(%): ";
            cin >> d;
            cout << "\n\t\t Quantity: ";
            cin >> q;
            data1 << c << " " << n << " " << p << " " << d << " " << q << "\n";
            cout << "\n\n\t\t Record Edited";
            found = true;
        } else {
            data1 << pcode << " " << pname << " " << price << " " << dis << " " << quantity << "\n"; //If the current product in the file does not match the pkey, the program copies the original record from database.txt to database1.txt unchanged:
        }
        data >> pcode >> pname >> price >> dis >> quantity;
    }
    data.close();
    data1.close();

    remove("database.txt");
    rename("database1.txt", "database.txt");

    if (!found) {
        cout << "\n\n Record not found, sorry!" << endl;
    }
}

void Shopping::rem() {
    fstream data, data1;
    int pkey;
    bool found = false;

    cout << "\n\n\t Delete Product";
    cout << "\n\n\t Product Code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "File doesn't exist" << endl;
        return;
    }

    data1.open("database1.txt", ios::app | ios::out);

    data >> pcode >> pname >> price >> dis >> quantity;
    while (!data.eof()) {
        if (pcode == pkey) {
            found = true;
            cout << "\n\n\t Product Deleted Successfully" << endl;
        } else {
            data1 << pcode << " " << pname << " " << price << " " << dis << " " << quantity << "\n";
        }
        data >> pcode >> pname >> price >> dis >> quantity;
    }
    data.close();
    data1.close();

    remove("database.txt");
    rename("database1.txt", "database.txt");

    if (!found) {
        cout << "\n\n Record Not Found" << endl;
    }
}

void Shopping::list() {
    fstream data;
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n No Products Available." << endl;
        return;
    }

    cout << "\n\n|_______________________________________________________\n";
    cout << "|  ProNo  |          Name          |  Price  | Quantity | Discount |\n";
    cout << "|_______________________________________________________\n";

    data >> pcode >> pname >> price >> dis >> quantity;
    while (!data.eof()) {
        // Print each product with consistent spacing
        cout << "| " << setw(7) << pcode << " | " << setw(20) << pname
             << " | " << setw(7) << fixed << setprecision(2) << price
             << " | " << setw(8) << quantity << " | " << setw(8) << dis << "% |\n";
        data >> pcode >> pname >> price >> dis >> quantity;
    }

    cout << "|_______________________________________________________\n";

    data.close();
}

void Shopping::showCart() {
    // cart[]: This array holds the product codes of the items currently in the cart.
    // cartQuantity[]:  holds the quantity of each item in the cart.
    // cartSize: The number of items in the cart.

    fstream data;
    float amount = 0;
    float disc = 0;
    float total = 0;

    if (cartSize == 0) {
        cout << "\n\nYour cart is empty!\n";
        return;
    }

    cout << "\n\n\t\t\t Current Cart\n";
    cout << "\n Product No\t Product Name\t Quantity\t Price\t Amount\t Amount with Discount(%)\n";

    for (int i = 0; i < cartSize; ++i) {
        data.open("database.txt", ios::in);
        data >> pcode >> pname >> price >> dis >> quantity;
        while (!data.eof()) {
            if (pcode == cart[i]) {  // databse file's product code and user defined product code
                amount = price * cartQuantity[i];    // 1600mmk * 5
                disc = amount - (amount * dis / 100);  // if discount is 10%, disc is 10
                total += disc;
                cout << "\n" << pcode << "\t\t" << pname << "\t\t" << cartQuantity[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << disc;
                break;
            }
            data >> pcode >> pname >> price >> dis >> quantity;
        }
        data.close();
    }
    cout << "\n\n Total Amount in Cart: " << total << endl;
}

string Shopping::generateRandomReceiptNumber() {
    srand(time(0)); // make sure random number generator would not produce the same sequence of numbers each time the program runs.
    int randomNumber = rand() % 100000; // rand() generates a random integer, % 100000 restricts the random number to a range between 0 and 99,999.
    return "RN" + to_string(randomNumber); // RN ka reciept number ko pyww dr
}


void Shopping::receipt() {
    fstream data, receiptFile, tempFile;
    float amount = 0, disc = 0, total = 0;
    string receiptNumber = generateRandomReceiptNumber();

    cout << "\n\n\t\t\t\t Product Available";

    // Check if the database exists
    ifstream databaseCheck("database.txt");
    if (!databaseCheck) {
        cout << "\n\n Empty database" << endl;
        return;
    }
    databaseCheck.close();

    // Show the list of products before the user places an order
    list();

    cout << "\n____________________________________\n";
    cout << "\n     Please Place the Order         \n";
    cout << "\n____________________________________\n";

    cartSize = 0; // Clear the cart before adding new items

    // Start order placement loop
    while (true) {
        int productCode, qty;
        cout << "\n\n Enter Product Code: ";
        cin >> productCode;
        cout << "\n\n Enter the Product Quantity: ";
        cin >> qty;

        // Check if product is available in the database
        bool productAvailable = false;
        int availableQuantity = 0;

        data.open("database.txt", ios::in);
        data >> pcode >> pname >> price >> dis >> quantity;
        while (!data.eof()) {
            if (pcode == productCode) {
                availableQuantity = quantity;
                productAvailable = true;
                break;
            }
            data >> pcode >> pname >> price >> dis >> quantity;
        }
        data.close();

        if (!productAvailable) {
            cout << "\n\n Product Code Not Found!" << endl;
            continue;
        }

        if (qty > availableQuantity) {
            cout << "\n\n Not enough stock available for " << pname << ". Available quantity: " << availableQuantity << ". Please enter a smaller quantity." << endl;
            continue;
        }

        // Add product code and quantity to the cart
        cart[cartSize] = productCode;
        cartQuantity[cartSize] = qty;
        cartSize++;

        cout << "\n\n Do you want another product? If yes then press 'y' else 'n': ";
        char continueChoice;
        cin >> continueChoice;
        if (continueChoice != 'y') break;
    }

    // Display the receipt details
    cout << "\n\n\t\t\t________________RECEIPT________________\n";
    cout << "\n Receipt Number: " << receiptNumber;
    cout << "\n-----------------------------------------------\n";
    cout << left << setw(10) << "Code"
         << setw(20) << "Product"
         << setw(8) << "Qty"
         << setw(10) << "Price"
         << setw(12) << "Amount"
         << setw(18) << "Discounted" << endl;
    cout << "-----------------------------------------------\n";

    // Save receipt information to the receipt file
    receiptFile.open("receipt.txt", ios::app | ios::out);
    receiptFile << "-----------------------------------------------" << endl;
    receiptFile << "Receipt Number: " << receiptNumber << endl;
    receiptFile << "-----------------------------------------------" << endl;
    receiptFile << left << setw(10) << "Code"
                << setw(20) << "Product"
                << setw(8) << "Qty"
                << setw(10) << "Price"
                << setw(12) << "Amount"
                << setw(18) << "Discounted" << endl;
    receiptFile << "-----------------------------------------------" << endl;

    // Create a temporary file to store the updated database
    tempFile.open("database_temp.txt", ios::out);
    if (!tempFile) {
        cout << "Error opening temporary file" << endl;
        return;
    }

    // Open the original database file
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "Error opening database file" << endl;
        return;
    }

    // Loop through the database and update quantities
    data >> pcode >> pname >> price >> dis >> quantity;
    while (!data.eof()) {
        bool productFound = false;
        for (int i = 0; i < cartSize; ++i) {
            if (pcode == cart[i]) {
                amount = price * cartQuantity[i];
                disc = amount - (amount * dis / 100);
                total += disc;
                cout << left << setw(10) << pcode
                     << setw(20) << pname
                     << setw(8) << cartQuantity[i]
                     << setw(10) << fixed << setprecision(2) << price
                     << setw(12) << fixed << setprecision(2) << amount
                     << setw(18) << fixed << setprecision(2) << disc << endl;

                receiptFile << left << setw(10) << pcode
                            << setw(20) << pname
                            << setw(8) << cartQuantity[i]
                            << setw(10) << fixed << setprecision(2) << price
                            << setw(12) << fixed << setprecision(2) << amount
                            << setw(18) << fixed << setprecision(2) << disc << endl;

                // Update the quantity in the database
                quantity -= cartQuantity[i];
                productFound = true;
                break;
            }
        }

        // Write to the temporary file based on the updated quantity
        if (productFound) {
            if (quantity > 0) {
                tempFile << pcode << " " << pname << " " << price << " " << dis << " " << quantity << "\n";
            } else {
                cout << "\nProduct Code " << pcode << " is out of stock and will be removed from the database." << endl;
            }
        } else {
            tempFile << pcode << " " << pname << " " << price << " " << dis << " " << quantity << "\n";
        }

        data >> pcode >> pname >> price >> dis >> quantity;
    }

    data.close();
    tempFile.close();

    // Replace the original database with the updated one
    remove("database.txt");
    rename("database_temp.txt", "database.txt");

    // Display the total amount and end the transaction
    cout << "-----------------------------------------------\n";
    cout << "Total Amount: " << total << endl;
    cout << "-----------------------------------------------\n";
    cout << "\t\tThank you for shopping!" << endl;
    cout << "-----------------------------------------------\n";

    receiptFile << "-----------------------------------------------" << endl;
    receiptFile << "Total Amount: " << total << endl;
    receiptFile << "-----------------------------------------------" << endl;
    receiptFile.close();
}

void Shopping::viewPurchases() {
    fstream receiptFile;
    string line;

    receiptFile.open("receipt.txt", ios::in);
    if (!receiptFile) {
        cout << "No purchases found!" << endl;
        return;
    }

    cout << "\n\n\t\t\t\t Purchases";
    cout << "\n\n_______________________________________\n";
    while (getline(receiptFile, line)) {
        cout << line << endl;
    }
    cout << "_______________________________________\n";
    receiptFile.close();
}

int main() {
    Shopping s;
    s.menu();
    return 0;
}

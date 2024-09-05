#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <regex>

using namespace std;

class shopping {
private:
    int pcode;
    float price;
    float dis;
    int quantity; // Quantity of the product
    string pname;
    int cart[100]; // Array to store product codes
    int cartQuantity[100]; // Array to store quantities of products in the cart
    int cartSize = 0; // Number of items in the cart
    string mainAdminEmail = "phonemyatmaw@email.com"; // Main admin email
    string mainAdminPassword = "pmm2004"; // Main admin password
    string subAdminEmails[4]; // Array to store sub-admin emails (updated size)
    string subAdminPasswords[4]; // Array to store sub-admin passwords (updated size)
    int subAdminCount = 0; // Counter to keep track of the number of sub-admins

public:
    void menu();
    void administrator();
    void subAdministrator(); // New method for sub-admin
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
    void viewPurchases();
    void showCart(); // Function to show the cart
    void addSubAdmin(); // Function to add a sub-admin
    bool login(string &role); // Function to handle login and return the role
    void modifyCart();
    void displayReceipt(const string&, float);
    bool validatePassword(const string&); // New function for password validation
    void loadSubAdmins(); // Function to load sub-admins from file
    void saveSubAdmins(); // Function to save sub-admins to file
};


// Display the main menu and handle user input
// ----------------------------MPST-----------------------------------
void shopping::menu() {
    int choice;
    string role;

    while (true) {
        cout << "\t\t\t\t __________________________\n";
        cout << "\t\t\t\t                           \n";
        cout << "\t\t\t\t   Supermarket Main Menu   \n";
        cout << "\t\t\t\t                           \n";
        cout << "\t\t\t\t __________________________\n";
        cout << "\t\t\t\t                           \n";
        cout << "\t\t\t\t| 1) Administrator |\n";
        cout << "\t\t\t\t|                  |\n";
        cout << "\t\t\t\t| 2) Buyer         |\n";
        cout << "\t\t\t\t|                  |\n";
        cout << "\t\t\t\t| 3) Exit          |\n";
        cout << "\t\t\t\t|                  |\n";
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

// Function to handle login and determine the role
bool shopping::login(string &role) {
    string email, password;
    cout << "\t\t\t Please Login \n";
    cout << "\t\t\t Enter Email: ";
    cin >> email;
    cout << "\t\t\t Password: ";
    cin >> password;

    // Check if the login is for the main admin
    if (email == mainAdminEmail && password == mainAdminPassword) {
        role = "main_admin";
        return true;
    }

    // Check if the login is for a sub-admin
    ifstream coadminFile("coadmin.txt");
    if (!coadminFile) {
        cout << "Error opening coadmin.txt" << endl;
        return false;
    }

    string fileEmail, filePassword;
    while (coadminFile >> fileEmail >> filePassword) {
        if (email == fileEmail && password == filePassword) {
            role = "sub_admin";
            coadminFile.close();
            return true;
        }
    }

    coadminFile.close();
    return false;
}


// Administrator menu to manage products and view purchases
void shopping::administrator() {
    int choice;

    while (true) {
        cout << "\n\n\n\t\t\t    ***** Administrator menu ***** ";
        cout << endl;
        cout << "\n\t\t\t|______1) Add the product_________|";
        cout << "\n\t\t\t|                                 |";
        cout << "\n\t\t\t|______2) Modify the product______|";
        cout << "\n\t\t\t|                                 |";
        cout << "\n\t\t\t|______3) Delete the product______|";
        cout << "\n\t\t\t|                                 |";
        cout << "\n\t\t\t|______4) View all purchases______|";
        cout << "\n\t\t\t|                                 |";
        cout << "\n\t\t\t|______5) View Product Lists______|";
        cout << "\n\t\t\t|                                 |";
        cout << "\n\t\t\t|______6) Add Co-Admin____________|"; // New option
        cout << "\n\t\t\t|                                 |";
        cout << "\n\t\t\t|______7) Back to main menu_______|";
        cout << "\n\t\t\t|                                 |";

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
                addSubAdmin(); // Call the new function
                break;

            case 7:
                menu();
                return;

            default:
                cout << "Invalid choice" << endl;
        }
    }
}

// Sub-Administrator menu with limited options
void shopping::subAdministrator() {
    int choice;

    while (true) {
        cout << "\n\n\n\t\t\t Co-Administrator menu";
        cout << "\n\t\t\t|______1) Add the product_________|";
        cout << "\n\t\t\t|                                 |";
        cout << "\n\t\t\t|______2) Modify the product______|";
        cout << "\n\t\t\t|                                 |";
        cout << "\n\t\t\t|______3) Delete the product______|";
        cout << "\n\t\t\t|                                 |";
        cout << "\n\t\t\t|______4) View all purchases______|";
        cout << "\n\t\t\t|                                 |";
        cout << "\n\t\t\t|______5) View Product Lists______|";
        cout << "\n\t\t\t|                                 |";
        cout << "\n\t\t\t|______6) Back to main menu_______|";
        cout << "\n\t\t\t|                                 |";

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
                menu();
                return;

            default:
                cout << "Invalid choice" << endl;
        }
    }
}

// Function to add a sub-admin (only available to the main admin)
void shopping::addSubAdmin() {
    if (subAdminCount >= 4) {
        cout << "\n\n Cannot add more than 4 co-admins!" << endl;
        return;
    }

    string email, password;

    cout << "\n\n\t\t\t Add new Co-Admin";
    cout << "\n\n\t Enter Co-Admin Email: ";
    cin >> email;
    
    cout << "\n\n\t Enter Co-Admin Password: ";
    cin >> password;

    // Validate password
    if (!validatePassword(password)) {
        cout << "Password must be at least 6 characters long and contain both letters and numbers." << endl;
        return;
    }

    // Open the file to store sub-admins' data
    ofstream coadminFile("coadmin.txt", ios::app);
    if (!coadminFile) {
        cout << "Error opening coadmin.txt" << endl;
        return;
    }

    // Save the new sub-admin's credentials to the file
    coadminFile << email << " " << password << endl;
    coadminFile.close();

    // Update the in-memory sub-admin data
    subAdminEmails[subAdminCount] = email;
    subAdminPasswords[subAdminCount] = password;
    subAdminCount++;

    cout << "\n\n\t\t Co-Admin added successfully!" << endl;
}


// Other methods remain unchanged

void shopping::buyer() {
    int choice;

    while (true) {
        cout << "\t\t\t     Buyer \n";
        cout << "\t\t\t_______________  \n";
        cout << "\t\t\t 1) Buy product  \n";
        cout << "\t\t\t 2) Go back      \n";
        cout << "\t\t\t Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                receipt(); // Proceed with buying a product
                break;

            case 2:
                menu(); // Go back to the main menu
                return;

            default:
                cout << "Invalid choice" << endl;
        }
    }
}



// ----------------------------HSTT-----------------------------------
// Add new product to the database
void shopping::add() {
    fstream data;
    int c;
    float p;
    float d;
    int q; // New quantity variable
    string n;
    bool found = false;

    cout << "\n\n\t\t\t Add new product";
    cout << "\n\n\t Product code of the product: ";
    cin >> pcode;
    cout << "\n\n\t Name of the product: ";
    cin >> pname;
    cout << "\n\n\t Price of the product: ";
    cin >> price;
    cout << "\n\n\t Discount on product: ";
    cin >> dis;
    cout << "\n\n\t Quantity of the product: "; // Prompt for quantity
    cin >> quantity;

        data.open("database.txt", ios::in);
    if (data) {
        data >> c >> n >> p >> d >> q; // Read quantity along with other data
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
        data.open("database.txt", ios::app | ios::out);
        data << pcode << " " << pname << " " << price << " " << dis << " " << quantity << "\n"; // Append quantity to the record
        data.close();
        cout << "\n\n\t\t Record inserted!" << endl;
    }
}

// Edit an existing product record
void shopping::edit() {
    fstream data, data1;
    int pkey;
    int c;
    float p;
    float d;
    int q; // New quantity variable
    string n;
    bool found = false;

    cout << "\n\t\t\t\t Modify the record";
    cout << "\n\t\t\t\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n File doesn't exist!" << endl;
        return;
    }

    data1.open("database1.txt", ios::app | ios::out);

    data >> pcode >> pname >> price >> dis >> quantity;
    while (!data.eof()) {
        if (pkey == pcode) {
            cout << "\n\t\t Product new code: ";
            cin >> c;
            cout << "\n\t\t Name of the product: ";
            cin >> n;
            cout << "\n\t\t Price: ";
            cin >> p;
            cout << "\n\t\t Discount(%): ";
            cin >> d;
            cout << "\n\t\t Quantity: "; // Prompt for new quantity
            cin >> q;
            data1 << c << " " << n << " " << p << " " << d << " " << q << "\n"; // Write updated quantity
            cout << "\n\n\t\t Record edited ";
            found = true;
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
        cout << "\n\n Record not found, sorry!" << endl;
    }
}

// Remove a product from the database
void shopping::rem() {
    fstream data, data1;
    int pkey;
    bool found = false;

    cout << "\n\n\t Delete product";
    cout << "\n\n\t Product code: ";
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
            cout << "\n\n\t Product deleted successfully" << endl;
            found = true;
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
        cout << "\n\n Record not found" << endl;
    }
}

// ----------------------------MKH-----------------------------------
// List all products in the database
void shopping::list() {
    fstream data;
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n No products available." << endl;
        return;
    }

    cout << "\n\n|_________________________________\n";
    cout << "ProNo\t\tName\t\tPrice\tQuantity\tDiscount\n";
    cout << "\n\n|_________________________________\n";
    data >> pcode >> pname >> price >> dis >> quantity;
    while (!data.eof()) {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\t" << quantity << "\t\t" << dis << "\n";
        data >> pcode >> pname >> price >> dis >> quantity;
    }
    data.close();
}

// Function to show the current cart contents
void shopping::showCart() {
    fstream data;
    float amount = 0;
    float disc = 0;
    float total = 0;

    if (cartSize == 0) {
        cout << "\n\nYour cart is empty!\n";
        return;
    }

    cout << "\n\n\t\t\t *** Current Cart ***\n";
    cout << "\n Product No\t Product Name\t Quantity\t Price\t Amount\t Amount with Discount\n";

    for (int i = 0; i < cartSize; ++i) {
        data.open("database.txt", ios::in);
        data >> pcode >> pname >> price >> dis >> quantity;
        while (!data.eof()) {
            if (pcode == cart[i]) {
                amount = price * cartQuantity[i];
                disc = amount - (amount * dis / 100);
                total += disc;
                cout << "\n" << pcode << "\t\t" << pname << "\t\t" << cartQuantity[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << disc;
                break; // Exit the inner loop since we found the product
            }
            data >> pcode >> pname >> price >> dis >> quantity;
        }
        data.close();
    }
    cout << "\n\n Total Amount in Cart: " << total << endl;
}

// Function to generate a random receipt number
string generateRandomReceiptNumber() {
    srand(time(0)); // Seed the random number generator
    int randomNumber = rand() % 100000; // Generate a random number
    return "RN" + to_string(randomNumber); // Format as RN followed by the random number
}

void shopping::receipt() {
    fstream data, tempFile;
    int c = 0;
    float amount = 0;
    float disc = 0;
    float total = 0;
    string receiptNumber = generateRandomReceiptNumber();

    cout << "\n\n\t\t\t\t Receipt";
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n Empty database" << endl;
        return;
    }
    data.close();
    list();

    cout << "\n____________________________________\n";
    cout << "\n                                    \n";
    cout << "\n     Please place the order         \n";
    cout << "\n                                    \n";
    cout << "\n____________________________________\n";

    cartSize = 0; // Clear the cart before adding new items

    while (true) {
        int productCode, qty;
        cout << "\n\n Enter Product code: ";
        cin >> productCode;
        cout << "\n\n Enter the product quantity: ";
        cin >> qty;

        // Check if the product code exists and has enough quantity
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
            cout << "\n\n Product code not found!" << endl;
            continue;
        }

        if (qty > availableQuantity) {
            cout << "\n\n Not enough stock available. Available quantity: " << availableQuantity << endl;
            continue;
        }

        // Check if the product is already in the cart
        bool productInCart = false;
        for (int i = 0; i < cartSize; ++i) {
            if (cart[i] == productCode) {
                cartQuantity[i] += qty; // Add to existing quantity
                productInCart = true;
                break;
            }
        }

        if (!productInCart) {
            // Add product code and quantity to the cart
            cart[cartSize] = productCode;
            cartQuantity[cartSize] = qty;
            cartSize++;
        }

        cout << "\n\n Do you want another product? If yes then press y else no: ";
        char continueChoice;
        cin >> continueChoice;
        if (continueChoice != 'y') break;
    }

    // Create temporary file to update database
    tempFile.open("database_temp.txt", ios::out);
    if (!tempFile) {
        cout << "Error opening temp file" << endl;
        return;
    }

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "Error opening database file" << endl;
        return;
    }

    // Temporary store the data in a new file while updating quantities
    data >> pcode >> pname >> price >> dis >> quantity;
    while (!data.eof()) {
        bool productFound = false;
        for (int i = 0; i < cartSize; ++i) {
            if (pcode == cart[i]) {
                amount = price * cartQuantity[i];
                disc = amount - (amount * dis / 100);
                total += disc;

                // Update quantity in memory
                quantity -= cartQuantity[i];
                productFound = true;
                break;
            }
        }
        if (productFound) {
            if (quantity > 0) {
                tempFile << pcode << " " << pname << " " << price << " " << dis << " " << quantity << "\n";
            } else {
                cout << "\nProduct code " << pcode << " is out of stock and will be removed from the database." << endl;
            }
        } else {
            tempFile << pcode << " " << pname << " " << price << " " << dis << " " << quantity << "\n";
        }
        data >> pcode >> pname >> price >> dis >> quantity;
    }

    data.close();
    tempFile.close();
    remove("database.txt");
    rename("database_temp.txt", "database.txt");

    // Post-purchase options
    while (true) {
        int postPurchaseChoice;
        cout << "\n\n\t\t\t ***** Post-Purchase Menu *****";
        cout << "\n\t\t\t|______1) Show Cart_________________|";
        cout << "\n\t\t\t|                                   |";
        cout << "\n\t\t\t|______2) Add Another Product_______|";
        cout << "\n\t\t\t|                                   |";
        cout << "\n\t\t\t|______3) Modify Cart List__________|";
        cout << "\n\t\t\t|                                   |";
        cout << "\n\t\t\t|______4) Get Receipt_______________|"; // New option for displaying receipt
        cout << "\n\t\t\t|                                   |";
        cout << "\n\t\t\t|______5) Go Back to Menu___________|";
        cout << "\n\t\t\t|                                   |";

        cout << "\n\n\t Please enter your choice: ";
        cin >> postPurchaseChoice;

        switch (postPurchaseChoice) {
            case 1:
                showCart(); // Show the current cart
                break;

            case 2:
                receipt(); // Allow adding another product
                break;

            case 3:
                modifyCart(); // Modify cart list
                break;

            case 4:
                displayReceipt(receiptNumber, total); // Display the receipt
                break;

            case 5:
                menu(); // Return to the main menu
                return;

            default:
                cout << "Invalid choice" << endl;
        }
    }
}




// View all purchases made
void shopping::viewPurchases() {
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


void shopping::modifyCart() {
    int productCode, newQuantity;
    bool productFound = false;

    cout << "\n\n\t\t\t Modify Cart List";
    cout << "\n Enter the Product Code to modify: ";
    cin >> productCode;

    for (int i = 0; i < cartSize; ++i) {
        if (cart[i] == productCode) {
            cout << "\n Enter new quantity for product " << productCode << ": ";
            cin >> newQuantity;
            cartQuantity[i] = newQuantity;
            productFound = true;
            cout << "\n Cart updated successfully!" << endl;
            break;
        }
    }

    if (!productFound) {
        cout << "\n Product code not found in the cart!" << endl;
    }
}

void shopping::displayReceipt(const string &receiptNumber, float total) {
    fstream receiptFile;
    receiptFile.open("receipt.txt", ios::app | ios::out);
    if (!receiptFile) {
        cout << "Error opening receipt file" << endl;
        return;
    }
    receiptFile << "Receipt Number: " << receiptNumber << endl;

    // Display the receipt in the console
    cout << "\n\n\t\t\t________________RECEIPT________________\n";
    cout << "\n Receipt Number: " << receiptNumber;
    cout << "\n Product No\t Product Name\t Quantity\t Price\t Amount\t Discounted Amount\n";
    cout << "_______________________________________________________________\n";

    // Display receipt details
    float amount = 0;
    float disc = 0;

    fstream data;
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "Error opening database file" << endl;
        return;
    }

    for (int i = 0; i < cartSize; ++i) {
        data.clear();
        data.seekg(0);
        data >> pcode >> pname >> price >> dis >> quantity;
        while (!data.eof()) {
            if (pcode == cart[i]) {
                amount = price * cartQuantity[i];
                disc = amount - (amount * dis / 100);
                cout << pcode << "\t\t" << pname << "\t\t" << cartQuantity[i] << "\t\t" << price << "\t" << amount << "\t" << disc << endl;
                receiptFile << pcode << "\t\t" << pname << "\t\t" << cartQuantity[i] << "\t\t" << price << "\t" << amount << "\t" << disc << endl;
                break; // Exit the inner loop since we found the product
            }
            data >> pcode >> pname >> price >> dis >> quantity;
        }
    }
    
    data.close();
    
    
    cout << "_______________________________________________________________\n";
    cout << "Total Amount: " << total << endl;
    receiptFile << "_______________________________________________________________\n";
    receiptFile << "Total Amount: " << total << endl;
    receiptFile << "------------------------------------------------------------------------------" << endl;
    receiptFile.close();
}

bool shopping::validatePassword(const string &password) {
    if (password.length() < 6) return false;

    bool hasLetter = false, hasDigit = false;
    for (char c : password) {
        if (isalpha(c)) hasLetter = true;
        if (isdigit(c)) hasDigit = true;
    }
    return hasLetter && hasDigit;
}

void shopping::loadSubAdmins() {
    ifstream file("coadmin.txt");
    if (!file) {
        cerr << "Error opening coadmin.txt" << endl;
        return;
    }
    
    subAdminCount = 0;
    while (file >> subAdminEmails[subAdminCount] >> subAdminPasswords[subAdminCount]) {
        subAdminCount++;
        if (subAdminCount >= 4) break;
    }
    file.close();
}

void shopping::saveSubAdmins() {
    ofstream file("coadmin.txt");
    if (!file) {
        cerr << "Error opening coadmin.txt" << endl;
        return;
    }

    for (int i = 0; i < subAdminCount; ++i) {
        file << subAdminEmails[i] << " " << subAdminPasswords[i] << endl;
    }
    file.close();
}

bool validatePassword(const string& password) {
    // Password should be at least 6 characters long and contain both letters and numbers
    regex pattern("^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{6,}$");
    return regex_match(password, pattern);
}


int main() {
    shopping s;
    s.menu();
    return 0;
}




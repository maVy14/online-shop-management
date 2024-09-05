# Self-service Billing System (SBS)

Welcome to the Self-service Billing System (SBS)! This group project was developed as part of my school assignment in OOP in C++ at University of Information Technology(UIT),Yangon,Myanmar. The primary goal of this project is to develop a Supermarket Management System using C++ that allows users to manage product inventory, generate customer bills, and streamline supermarket operations efficiently. The system will enable users to add, update, delete, and view product details, as well as automate billing processes for better customer service.

## Project Overview

This **Supermarket Management System** is a C++ application that simulates the operations of a supermarket, allowing users to manage inventory, process customer transactions, and generate sales reports. It aims to provide a simple and efficient way to handle day-to-day supermarket tasks through a command-line interface.

## Features

- **Product Management**: Add, update, and delete products from the inventory.
- **Stock Management**: Check available stock and update inventory levels.
- **Billing System**: Generate bills for customers based on selected products and quantities.
- **Discount System**: Apply discounts to specific products.
- **Sales Reports**: View total sales and generate reports for a specific time period.
- **User-friendly Interface**: Command-line interface to interact with the system.

## Technologies Used

- **C++**: Core programming language for the system.
- **File Handling**: Data is stored and retrieved from text files for persistent storage.
- **OOP (Object-Oriented Programming)**: The project makes use of classes, inheritance, and encapsulation for structuring the code.
  
## How to Run

1. **Clone the repository**:
    ```bash
    git clone https://github.com/maVy14/self-service-billing-system.git
    ```

2. **Navigate to the project directory**:
    ```bash
    cd self-service-billing-system
    ```

3. **Compile the code**:
    Use the following command to compile the C++ files (assuming you have a C++ compiler installed):
    ```bash
    g++ -o main main.cpp
    ```

4. **Run the application**:

    **On Windows**:
    ```bash
    main.exe
    ```

    **On Linux/Mac**
    ```bash
    ./main
    ```

## How to Use

- **Main Menu**: Upon launching the program, you'll see a menu that lets you choose between managing inventory, billing, or viewing reports.
- **Product Management**:
  - Add new products by entering details like name, price, and stock.
  - Update product prices and quantities.
  - Remove products no longer available for sale.
- **Billing**:
  - Select products for the customer's purchase and enter quantities.
  - The program will calculate the total price, including any applicable discounts.
  - Print or display the final bill.
- **Sales Reports**:
  - Generate reports of total sales over a specified period.

## License

© [2024] Min Khant Hein. All rights reserved.
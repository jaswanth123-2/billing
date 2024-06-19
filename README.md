# Supermarket Inventory Management System

## Objective
The objective of this C program is to develop a supermarket inventory management system that allows customers to shop and employees to manage the inventory.

## Features
- Customer Management:
  - Register new customers
  - Track customer visits and assign membership tiers (Gold, Silver, Platinum)
  - Allow customers to browse and add products to the cart

- Inventory Management:
  - Create new products
  - Increase/decrease stock of existing products
  - Delete products from the inventory

- Shopping Cart and Billing:
  - Add products to the cart with desired quantities
  - Display the cart with product details, quantities, and total cost

## Implementation Details
The program uses structures to store customer and product information. It employs file handling techniques to read and write data to text files, simulating a database.

1. **Customer Management**:
   - The program maintains a `Customer.txt` file to store customer information, including name, mobile number, and visit count.
   - New customers are added to the file during their first visit.
   - Existing customers are identified by their mobile number, and their visit count is updated.
   - Membership tiers are assigned based on the visit count (Gold: <5, Silver: 5-9, Platinum: ≥10).

2. **Inventory Management**:
   - The `product.txt` file stores product information, including name, cost, quantity, RFID code, and stock.
   - Employees can create new products, increment stock for existing products, or delete products from the inventory.
   - Temporary files are used during updating operations to ensure data integrity.

3. **Shopping Cart and Billing**:
   - Customers can browse the product list and add products to their cart by entering the RFID code and desired quantity.
   - The program checks the available stock and prevents adding more items than the current stock.
   - The cart displays the product name, quantity, and cost for each item, along with the total cost.
   - Upon checkout, the program updates the product stock in the `product.txt` file.

## Usage
1. Compile the C program using a C compiler.
2. Run the compiled executable.
3. Choose the desired mode: Customer or Employee.
4. For customers:
   - Enter your mobile number (new customers will be registered).
   - Browse the product list and add items to the cart.
   - Review the cart and total cost.
5. For employees:
   - View the product list with stock details.
   - Increment stock for existing products.
   - Create new products.
   - Delete products from the inventory.

## Note
The program uses text files (`Customer.txt`, `product.txt`, and temporary files) to store data. Ensure that these files are present in the same directory as the executable or modify the file paths in the code accordingly.

/*
1. Manage Customer
    1.1 Add New Customer // done
    1.2 Remove Customer // done
    1.3 View/Edit Customer // done
    1.4 View Customers by Province // done

2. Manage Prices
    2.1 Display All Prices // done
    2.2 Edit Oil Price // done
    2.3 Edit Solar Price // done
    2.4 Edit Nuclear Price // done

// maybe use SQL query for using the values of oil, solar, etc.

3. Manage Orders
    3.1 Create Order // done // make orderID random, check for uniqueness with SQL
    3.2 Edit Order // done
    3.3 Check-out Order // Bill is created here // make billID random, check for uniqueness with SQL

4. Manage Bills
    4.1 View Bills // done
    4.2 Pay Bills // done
    4.3 Check Unpaid Bills // SQL
    4.4 Check Overdue Bills // SQL
    4.5 View Customers with Unpaid Bills // can be done entirely in SQL
    4.6 View Customers with Overdue Bills // can be done entirely in SQL

*/

# // 1.1 Add New Customer

-- Add a new customer
INSERT INTO CUSTOMERS (C_name, C_phone, C_R_id)
VALUES ('John Doe', '1234567890', 1);
-- Retrieve the auto-generated ID
SELECT LAST_INSERT_ID() AS New_Customer_ID;
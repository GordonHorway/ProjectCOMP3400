-- 45 - View Customers with Unpaid Bills --
SELECT 
    CUSTOMERS.C_id AS Customer_ID,
    CUSTOMERS.C_name AS Customer_Name,
    CUSTOMERS.C_phone AS Customer_Phone,
    CUSTOMERS.C_R_id AS Region_ID,
    COUNT(BILLS.B_id) AS Unpaid_Bill_Count,
    GROUP_CONCAT(BILLS.B_id) AS Unpaid_Bill_List
FROM CUSTOMERS
JOIN BILLS ON CUSTOMERS.C_id = BILLS.B_C_id
WHERE BILLS.B_pd = FALSE
GROUP BY CUSTOMERS.C_id, CUSTOMERS.C_name, CUSTOMERS.C_phone, CUSTOMERS.C_R_id;
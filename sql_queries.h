#ifndef SQL_QUERIES
#define SQL_QUERIES

    const char* sql = "SELECT * FROM REGIONS;";
    const char *overdueQuery = "SELECT "
    "B_id, "
    "B_C_id, "
    "B_due, "
    "B_amt_paid, "
    "B_oil_ct, "
    "B_sol_ct, "
    "B_nuc_ct, "
    "B_oil_pr, "
    "B_sol_pr, "
    "B_nuc_pr "
    "FROM BILLS "
    "WHERE B_overdue = TRUE;";
    const char *unpaidBillView = "SELECT " 
    "CUSTOMERS.C_id AS Customer_ID, "
    "CUSTOMERS.C_name AS Customer_Name, "
    "CUSTOMERS.C_phone AS Customer_Phone, "
    "CUSTOMERS.C_R_id AS Region_ID, "
    "COUNT(BILLS.B_id) AS Unpaid_Bill_Count, "
    "GROUP_CONCAT(BILLS.B_id) AS Unpaid_Bill_List "
    "FROM CUSTOMERS "
    "JOIN BILLS ON CUSTOMERS.C_id = BILLS.B_C_id "
    "WHERE BILLS.B_pd = FALSE "
    "GROUP BY CUSTOMERS.C_id, CUSTOMERS.C_name, CUSTOMERS.C_phone, CUSTOMERS.C_R_id;";
    const char *unpaidBillCheck = "SELECT " 
    "B_id, "
    "B_C_id, "
    "B_due, "
    "(B_oil_ct * B_oil_pr + B_sol_ct * B_sol_pr + B_nuc_ct * B_nuc_pr) AS Total, "
    "B_amt_paid, "
    "((B_oil_ct * B_oil_pr + B_sol_ct * B_sol_pr + B_nuc_ct * B_nuc_pr) - B_amt_paid) AS Remaining_due, "
    "B_overdue "
    "FROM BILLS "
    "WHERE B_pd = FALSE;";

#endif
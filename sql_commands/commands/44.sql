SELECT 
    B_id,
    B_C_id,
    B_due,
    B_amt_paid,
    B_oil_ct,
    B_sol_ct,
    B_nuc_ct,
    B_oil_pr,
    B_sol_pr,
    B_nuc_pr
FROM BILLS
WHERE B_overdue = TRUE;
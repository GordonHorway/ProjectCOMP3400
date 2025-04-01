-- 43 - Check unpaid bills -- 
SELECT 
    B_id,
    B_C_id,
    B_due,
    (B_oil_ct * B_oil_pr + B_sol_ct * B_sol_pr + B_nuc_ct * B_nuc_pr) AS Total,
    B_amt_paid,
    ((B_oil_ct * B_oil_pr + B_sol_ct * B_sol_pr + B_nuc_ct * B_nuc_pr) - B_amt_paid) AS Remaining_due,
    B_overdue
FROM BILLS
WHERE B_pd = FALSE;
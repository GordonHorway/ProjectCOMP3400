CREATE TABLE REGIONS (
    R_id INT PRIMARY KEY,
    R_name VARCHAR(30)
);

CREATE TABLE CUSTOMERS (
    C_id INT PRIMARY KEY,
    C_name VARCHAR(30),
    C_address VARCHAR(50),
    C_phone VARCHAR(10),
    C_R_id INT,
    FOREIGN KEY (C_R_id) REFERENCES REGIONS(R_id)
);

CREATE TABLE BILLS (
    B_id INT PRIMARY KEY,
    B_C_id INT,
    B_due DATE,
    B_amt_paid DOUBLE,
    B_pd BOOLEAN,
    B_overdue BOOLEAN,
    B_oil_ct INT,
    B_sol_ct INT,
    B_nuc_ct INT,
    B_oil_pr DOUBLE,
    B_sol_pr DOUBLE,
    B_nuc_pr DOUBLE,
    FOREIGN KEY (B_C_id) REFERENCES CUSTOMERS(C_id)
);

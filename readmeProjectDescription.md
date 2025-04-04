1. ./run.sh shell script compiles and runs our program with all of the necessary compilation flags along
with passing energy_prices.txt onto the command line.
2. energy_prices.txt consists of prices for solar, oil and nuclear. This information is loaded into our program at runtime to be used for calculating the balance due by the customer when they make an order.
3. Their is a local copy of our database that we used called comp3400database.db. It has already been built using sqlite3 and the sql files in sql_commands.
4. There is menu in the terminal that will greet you with various options. Simply enter the number and press enter. (Except for 33 that is a sub-menu option for option 3)
5. The menu will continue to loop until you exit.
6. There is a customers.output file that is produced by our program containing all the customer entries
that were loaded into our program from the database at runtime. It would also reflect additions/deletions of customers that happened during runtime.
7. Currently our bill system only accepts one bill per customer. So if you make an order it will overwrite the
current customers bill from the database.
# C-Bank
Bank Management Console Application

This project was my first attempt at a Console Application in C. It is a mock bank management software which includes account creation with a unique username and password, deposits, withdrawls, and balance history. Accounts are password protected, although stored userpasswords are literal strings and are not hashed. Currently there is no functionality to save the created accounts after closing the application as all entered information is stored in the temporary "bank" struct.

Future updates could include storing created accounts in a seperate database file or using cloud services and accessing an online database via SQL. Stored user information could be hashed as well to add more security.

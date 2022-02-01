#include <iostream>
#include <string>
#include <stdlib.h>
#include <mysql.h>
#include "customer.h"
#include "dbresponse.h"
#include <iomanip>
#include "MD5.h"
#include <conio.h>

using namespace std;

string sessionc;
string cusname = " ";

void customerInitial()
{
	int choice;
	string ch;
	
	cout << "Welcome to Food Ordering System dear customer :D" << endl;
	cout << "\nOptions:" << endl;
	cout << "	1. Register new customer" << endl;
	cout << "	2. Login" << endl;
	cout << "	3. Quit" << endl;
	cout << "\nChoose: ";
	cin >> ch;

	// int validation
	if (ch == "1" || ch == "2" || ch == "3")
	{
		choice = stoi(ch);
	}
	else
	{
		customerInitial();
	}

	switch (choice)
	{
		case 1:
			system("cls");
			customerReg();

			break;
		case 2:
			system("cls");
			customerLogin();

			break;
		case 3:
			cout << "See you next time :)" << endl;
			mysql_close(conn);
			exit(0);

			break;
		default:
			cout << "Invalid option!" << endl;
			cout << "Press ENTER to go back..";
			cin.get();
			customerInitial();
	}
}

void customerReg()
{
	string email, name, address, phone, age, password, repassword, pass;
	int err = 0;

	cout << "Please enter your details, make sure to fill all form" << endl;
	cout << "\nEmail        : ";
	cin >> email;
	cin.ignore();
	cout << "username     : ";
	getline(cin, name);
	cout << "Age          : ";
	cin >> age;
	cin.ignore();
	cout << "Address      : ";
	getline(cin, address);
	cout << "Phone number : 60";
	cin >> phone;

	cout << "Password     : ";
	cin >> password;
	cout << "Re-type password : ";
	cin >> repassword;

	while (password != repassword)
	{
		cout << "Re-type password do note match!" << endl;
		cout << "Re-type password : ";
		cin >> repassword;
	}

	pass = MD5(password).toStr();

	// check if email or phone number already exist

	string emailexist = "SELECT * FROM customer WHERE customeremail ='" + email + "';";
	const char* eec = emailexist.c_str();
	qstate = mysql_query(conn, eec);

	result = mysql_store_result(conn);
	row = mysql_fetch_row(result);
	if (row != NULL)
	{
		err = err + 1;
	}

	string phoneexist = "SELECT * FROM customer WHERE customerphone ='60" + phone + "';";
	const char* pec = phoneexist.c_str();
	qstate = mysql_query(conn, pec);
	result = mysql_store_result(conn);
	row = mysql_fetch_row(result);
	if (row != NULL)
	{
		err = err + 2;
	}
	
	cout << "checking your email and phone.." << endl;

	if (err > 0)
	{
		if (err == 1)
		{
			cout << "Email already exist!" << endl;
			cin.ignore();
			cin.get();
			system("cls");
			customerReg();
		}
		else if (err == 2)
		{
			cout << "Phone already exist!" << endl;
			cin.ignore();
			cin.get();
			system("cls");
			customerReg();
		}
		else
		{
			cout << "Email and phone already exist!" << endl;
			cin.ignore();
			cin.get();
			system("cls");
			customerReg();
		}
	}
	
	// add data to db
	string query = "INSERT INTO customer (customername, customerpassword, customeremail, customerphone, customeraddress, customerage) VALUES ('" + name + "', '" + pass + "', '" + email + "', '60" + phone + "', '" + address + "', " + age + ");";
	const char* rq = query.c_str();

	qstate = mysql_query(conn, rq);

	if (!qstate)
	{
		cout << "You are successfully registered!" << endl;
		cout << "press ENTER to redirect to login..";
		cin.ignore();
		cin.get();
		system("cls");
		customerLogin();
	}
	else
	{
		cout << "error in " << mysql_errno(conn);
		cout << "press ENTER to register..";
		cin.ignore();
		cin.get();
		system("cls");
		customerReg();
	}
}

void customerLogin()
{
	string email, password, pass;
	char ps;
	
	cout << "Please login" << endl;
	cout << endl;
	cout << "Email    : ";
	cin >> email;
	cout << "Password : ";
	while ((ps = _getch()) != 13)
	{
		password += ps;
		cout << '*';
	}

	pass = MD5(password).toStr();

	string query = "SELECT * FROM customer WHERE customeremail='"+email+"' AND customerpassword='"+pass+"';";
	const char* lq = query.c_str();

	qstate = mysql_query(conn, lq);

	if (!qstate)
	{
		mysql_free_result(result);
		result = mysql_store_result(conn);
		row = mysql_fetch_row(result);
		if (row == NULL)
		{
			cout << "Invalid credential!" << endl;
			cin.ignore();
			cout << "Press ENTER to back to login..";
			cin.get();
			system("cls");
			customerLogin();
		}
		else
		{
			sessionc = string(row[0]);
			cusname = row[1];
		}
		system("cls");
		customerPanel();
	}
	else
	{
		cout << "error in " << mysql_errno(conn) << ", Make sure your credential is correct!\n";
		cout << "press ENTER to login again";
		cin.ignore();
		cin.get();
		system("cls");
		customerLogin();
	}
}

void customerPanel()
{
	system("cls");
	int choice;
	string ch;
	cout << "    dMMMMMP dMMMMMP        .aMMMb  dMMMMb  dMMMMb  dMMMMMP dMMMMb " << endl;
	cout << "   dMP       .dMP\"        dMP\"dMP dMP.dMP dMP VMP dMP     dMP.dMP" << endl;
	cout << "  dMMMP    .dMP\"         dMP dMP dMMMMK\" dMP dMP dMMMP   dMMMMK\" " << endl;
	cout << " dMP     .dMP\"          dMP.aMP dMP\"AMF dMP.aMP dMP     dMP\"AMF   " << endl;
	cout << "dMMMMMP dMMMMMP         VMMMP\" dMP dMP dMMMMP\" dMMMMMP dMP dMP    " << endl << endl; 
	cout << "Welcome back customer " << cusname << "!" << endl;

	cout << "\nChoose action :" << endl;
	cout << endl;
	cout << "	1. Profile" << endl;
	cout << "	2. Place order" << endl;
	cout << "	3. View orders" << endl;
	cout << "	4. Logout" << endl;
	cout << "\nChoose: ";
	cin >> ch;

	// Choice validation
	if (ch == "1" || ch == "2" || ch == "3" || ch == "4")
	{
		choice = stoi(ch);
	}
	else
	{
		customerPanel();
	}

	switch (choice)
	{
	case 1:
		//profile
		customerProfile();

		break;
	case 2:
		//create order
		itemorder();

		break;
	case 3:
		//view order
		customerOrder();

		break;
	case 4:
		mysql_close(conn);
		exit(0);

		break;
	default:
		cout << "Invalid option!" << endl;
		cin.ignore();
		cout << "Press ENTER to back to panel..";
		cin.get();
		customerPanel();
	}
}

void customerProfile()
{
	system("cls");
	cout << "Customer Profile" << endl;
	cout << endl;

	int option;
	int er;
	string op;
	string name = "";
	string email = "";
	string phone = "";
	string address = "";
	string oldpassword = "";
	string password = "";
	string repassword = "";
	string age = "";
	string oldpass = "";
	string pass = "";

	//validation query
	string emailexist = "SELECT * FROM customer WHERE customeremail ='" + email + "';";
	const char* eec = emailexist.c_str();
	string phoneexist = "SELECT * FROM customer WHERE customerphone =" + phone + ";";
	const char* pec = phoneexist.c_str();

	//mysql_free_result(result);
	string query = "select * from customer where customerid=" + sessionc + ";";
	const char* cp = query.c_str();

	qstate = mysql_query(conn, cp);

	if (!qstate)
	{
		mysql_free_result(result);
		result = mysql_store_result(conn);
		row = mysql_fetch_row(result);

		cout << "Username : " << row[1] << endl;
		cout << "Email : " << row[3] << endl;
		cout << "Phone : " << row[4] << endl;
		cout << "Address : " << row[5] << endl;
		cout << "Age : " << row[6] << endl;
	}
	else
	{
		cout << "Could not load profile " << mysql_errno(conn);
	}
	cout << endl;
	cout << "Change profile :" << endl;
	cout << "1.Username 2.Email 3.Phone 4.Address 5.Password 6.Age 7.Back to menu" << endl;
	cout << endl << "Option:";
	cin >> op;

	// int validation
	if (op == "1" || op == "2" || op == "3" || op == "4" || op == "5" || op == "6" || op == "7")
	{
		option = stoi(op);
	}
	else
	{
		customerProfile();
	}

	switch (option)
	{
	case 1:
		cin.ignore();
		cout << "New username : ";
		getline(cin, name);

		if (name != "")// if name not empty
		{
			//query start
			string cn = "UPDATE customer SET customername='" + name + "' WHERE customerid=" + sessionc + ";";
			const char* pnq = cn.c_str();
			qstate = mysql_query(conn, pnq);

			if (qstate)
			{
				cout << "Failed to update username " << mysql_errno(conn) << endl;
				cin.ignore();
				cout << "Press ENTER to back to profile..";
				cin.get();
			}// query end
		}
		customerProfile();

		break;
	case 2:
		cout << "New email : ";
		cin >> email;

		emailexist = "SELECT * FROM customer WHERE customeremail ='" + email + "';";
		eec = emailexist.c_str();
		qstate = mysql_query(conn, eec);

		mysql_free_result(result);
		result = mysql_store_result(conn);
		row = mysql_fetch_row(result);
		if (row != NULL)
		{
			cout << "Email already exist!" << endl;
			cin.ignore();
			cin.get();
			system("cls");
			customerProfile();
		}
		else {
			if (email != "")
			{
				//query start
				string cn = "UPDATE customer SET customeremail='" + email + "' WHERE customerid=" + sessionc + ";";
				const char* peeq = cn.c_str();
				qstate = mysql_query(conn, peeq);

				if (qstate)
				{
					cout << "Failed to update email " << mysql_errno(conn) << endl;
					cin.ignore();
					cout << "Press ENTER to back to profile..";
					cin.get();
				}// query end
			}
		}
		customerProfile();

		break;
	case 3:
		cout << "New phone number : 60";
		cin >> phone;

		for (int i = 0; i < phone.size(); i++)
		{
			int uppercaseChar = toupper(phone[i]); //Convert character to upper case version of character
			if (uppercaseChar < 'A' || uppercaseChar > 'Z') //If character is not A-Z
			{

			}
			else
			{
				cout << "Invalid input!" << endl;
				er = 1;
				break;
			}
		}

		if (er == 1)
		{
			cin.ignore();
			cout << "Press ENTER to back to profile..";
			cin.get();
			customerProfile();
		}

		phoneexist = "SELECT * FROM customer WHERE customerphone =" + phone + ";";
		pec = phoneexist.c_str();

		qstate = mysql_query(conn, pec);

		mysql_free_result(result);
		result = mysql_store_result(conn);
		row = mysql_fetch_row(result);
		if (row != NULL)
		{
			cout << "Phone already exist!" << endl;
			cin.ignore();
			cin.get();
			system("cls");
			customerProfile();
		}
		else {

			if (phone != "")
			{
				//query start
				string cn = "UPDATE customer SET customerphone='60" + phone + "' WHERE customerid=" + sessionc + ";";
				const char* ppq = cn.c_str();
				qstate = mysql_query(conn, ppq);

				if (qstate)
				{
					cout << "Failed to update phone number" << mysql_errno(conn) << endl;
					cin.ignore();
					cout << "Press ENTER to back to profile..";
					cin.get();
				}// query end
			}
		}
		customerProfile();

		break;
	case 4:
		cin.ignore();
		cout << "New address : ";
		getline(cin, address);

		if (address != "")
		{
			//query start
			string cn = "UPDATE customer SET customeraddress='" + address + "' WHERE customerid=" + sessionc + ";";
			const char* paq = cn.c_str();
			qstate = mysql_query(conn, paq);

			if (qstate)
			{
				cout << "Failed to update address " << mysql_errno(conn) << endl;
				cin.ignore();
				cout << "Press ENTER to back to profile..";
				cin.get();
			}// query end
		}
		customerProfile();

		break;
	case 5:
		cout << "Enter old password : ";
		cin >> oldpassword;

		oldpass = MD5(oldpassword).toStr();

		if (oldpassword != "")
		{
			string check = "SELECT customerpassword FROM customer WHERE customerid=" + sessionc + ";";
			const char* pk = check.c_str();
			qstate = mysql_query(conn, pk);
			if (qstate)// if query failed
			{
				cout << "Error in process " << mysql_errno(conn) << endl;
				cin.ignore();
				cout << "Press ENTER to back to profile..";
				cin.get();
				customerProfile();
			}
			mysql_free_result(result);
			result = mysql_store_result(conn);
			row = mysql_fetch_row(result);

			if (oldpass != row[0])
			{
				cout << "Wrong old password! " << endl;
				cin.ignore();
				cout << "Press ENTER to back to profile..";
				cin.get();
				customerProfile();
			}

			cout << "Enter new password : ";
			cin >> password;
			cout << "Re-type password : ";
			cin >> repassword;

			while (repassword != password)
			{
				cout << "Re-type password not match!" << endl;
				cout << "Re-type password : ";
				cin >> repassword;
			}

			pass = MD5(password).toStr();

			string cn = "UPDATE customer SET customerpassword='" + pass + "' WHERE customerid=" + sessionc + ";";
			const char* ppp = cn.c_str();
			qstate = mysql_query(conn, ppp);

			if (qstate)
			{
				cout << "Failed to update password " << mysql_errno(conn) << endl;
				cin.ignore();
				cout << "Press ENTER to back to profile..";
				cin.get();
			}// query end
			cout << "Successfully change password! If you not entering any password, then your password will change to null" << endl;
			cin.ignore();
			cout << "Press ENTER to back to profile..";
			cin.get();
		}
		customerProfile();

		break;
	case 6:
		cout << "Enter age : ";
		cin >> age;// please validate

		if (address != "")
		{
			//query start
			string chnge = "UPDATE customer SET customerage=" + age + " WHERE customerid=" + sessionc + ";";
			const char* cag = chnge.c_str();
			qstate = mysql_query(conn, cag);

			if (qstate)
			{
				cout << "Failed to update age " << mysql_errno(conn) << endl;
				cin.ignore();
				cout << "Press ENTER to back to profile..";
				cin.get();
			}// query end
		}
		customerProfile();

		break;
	case 7:
		customerPanel();

		break;
	default:
		cout << "Invalid option!" << endl;
		cin.ignore();
		cout << "Press ENTER to back to profile..";
		cin.get();
		customerProfile();
	}
}

void itemorder()
{
	system("cls");
	customerItem();

	string yn;
	cout << endl;
	cout << "Do you want to place an order?(y/n) ";
	cin >> yn;

	if (yn == "y" || yn == "Y")
	{
		createOrder();
	}
	else
	{
		customerPanel();
	}

}

void customerItem()
{
	qstate = mysql_query(conn, "SELECT * FROM item WHERE stocknumber!=0");

	mysql_free_result(result);
	result = mysql_store_result(conn);
	int num_fields = mysql_num_fields(result);
	cout << "+--------+--------------------------------------------------+------------+--------------+" << endl;
	cout << "| ItemId |                     Item name                    | item price | stock number |" << endl;
	cout << "+--------+--------------------------------------------------+------------+--------------+" << endl;
	while ((row = mysql_fetch_row(result)))
	{
		string row1 = string(row[0]);
		string row2 = string(row[1]);
		string row3 = string(row[2]);
		string row4 = string(row[4]);

		cout << "|" << left << setw(8) << row1;
		cout << "|" << left << setw(50) << row2;
		cout << "|" << left << setw(12) << row3;
		cout << "|" << left << setw(14) << row4 << "|";
		cout << endl;

		//printf("\n");
	}
	cout << "+--------+--------------------------------------------------+------------+--------------+" << endl;
}

void createOrder()
{
	// user add item if exist done
	// user add item if sufficient done partially
	// item quantity decrease done done
	// display total before confirm done
	string item[12];
	int quantity[12] = {0};
	string again;
	string ordid;
	int i = 0;

	do { // asking user input
		if (i == 12)
		{
			cout << "Reach maximum item!";
			break;
		}
		cout << "Enter item id : ";
		cin >> item[i];
		do {
			cout << "Quantity must not be 0" << endl; // check if item quantity is 0
			cout << "Enter quantity : ";
			cin >> quantity[i];
		} while (quantity[i] <= 0); // if quantity is 0 then keep looping
		cout << "Add more item?(y/n) ";
		cin >> again;
		i++;

	} while (again == "y" || again == "Y");

	cin.clear();
	string ag;
	cout << "Are you sure to place order now?(y/n) ";
	cin >> ag;
	
	if (ag == "n" || ag == "N") // escape action
	{
		cout << "Order cancel successfully!" << endl;
		cin.ignore();
		cout << "Press ENTER to back to order..";
		cin.get();
		itemorder();
	}
	else
	{
		//cin.ignore();
		//cout << "Press ENTER to confirm payment..";
		//cin.get();

		// create order
		string query1 = "INSERT INTO orders (orderstatus, orderdatetime, customerid) VALUES ('PENDING', now(), " + sessionc + ")";
		const char* co = query1.c_str();
		qstate = mysql_query(conn, co);

		cout << "placing order..." << endl;

		if (qstate)
		{
			cout << "Sorry failed to create order for now :( " << mysql_errno(conn) << endl;
			cin.ignore();
			cout << "Press ENTER to back to manage item..";
			cin.get();
			itemorder();
		}
		cout << "Order created!" << endl;

		string query2 = "select orderid from orders WHERE customerid=" + sessionc + " ORDER BY orderid DESC LIMIT 1;";
		const char* fi = query2.c_str();
		qstate = mysql_query(conn, fi);

		mysql_free_result(result);
		result = mysql_store_result(conn);
		row = mysql_fetch_row(result);
		ordid = row[0];

		//cout << "Fetching latest order " << ordid << endl;

		// validate every insert item and insert logic
		for (i = 0; quantity[i] != 0; i++)
		{
			string query3 = "SELECT * FROM item WHERE itemid=" + item[i] + ";";
			const char* sc = query3.c_str();
			qstate = mysql_query(conn, sc);

			mysql_free_result(result);
			result = mysql_store_result(conn);
			row = mysql_fetch_row(result);

			if (row != NULL)// validate if item exist
			{
				//check if the request quantity is sufficient
				if (quantity[i] <= atoi(row[4])) // compare if requested item is more than what in stock
				{
					string query4 = "INSERT INTO order_item VALUES (" + ordid + ", " + item[i] + ", " + to_string(quantity[i]) + ", " + to_string(atoi(row[2])*quantity[i]) + ");";
					const char* ni = query4.c_str();
					qstate = mysql_query(conn, ni);

					if (qstate) // if fail
					{
						cout << "Item id " << item[i] << " failed to add, maybe because duplicate item " << mysql_errno(conn) << endl;
					}
					else // if success, update stock number
					{
						int newstock = atoi(row[4]) - quantity[i];
						string query5 = "UPDATE item SET stocknumber=" + to_string(newstock) + " WHERE itemid=" + item[i] + ";";
						const char* ust = query5.c_str();
						qstate = mysql_query(conn, ust);

						if (qstate)
						{
							cout << "Failed to update stock number " << mysql_errno(conn) << endl;
						}
					}
				}
				else if (quantity[i] > atoi(row[4]))
				{
					cout << "We dont have enough item for itemid " << item[i] << ". This item will not be added to your cart " << row[4] << endl;
				}
			}
			else
			{
				cout << "Item with item id " << item[i] << " do not exist! This item will not be added to your cart" << endl;
			}

		}

		//cout << "Finished adding item to order item" << endl;

		// calculate total price
		string query6 = "SELECT priceperitem FROM order_item WHERE orderid=" + ordid + ";";
		const char* total = query6.c_str();
		qstate = mysql_query(conn, total);

		if (qstate)
		{
			cout << "Failed to calculate total. This order will not proceed " << mysql_errno(conn) << endl;
			//delete order!!
			string deleteitem = "DELETE FROM order_item WHERE orderid=" + ordid + ";";
			const char* doi = deleteitem.c_str();
			qstate = mysql_query(conn, doi);
			if (qstate)
			{
				cout << "Failed to delete item " << mysql_errno(conn) << endl;
			}

			string deleteorder = "DELETE FROM orders WHERE orderid=" + ordid + ";";
			const char* doo = deleteorder.c_str();
			qstate = mysql_query(conn, doo);
			if (qstate)
			{
				cout << "Failed to delete order " << mysql_errno(conn) << endl;
			}

			cin.ignore();
			cout << "Press ENTER to back to manage item..";
			cin.get();
			itemorder();
		}

		mysql_free_result(result);
		result = mysql_store_result(conn);

		int total_price[12] = { 0 };
		int i = 0;
		while (row = mysql_fetch_row(result))
		{
			total_price[i] = atoi(row[0]);
			i++;
		}

		int ttlprice = 0;
		for (int j = 0; j < 12; j++)
		{
			ttlprice = ttlprice + total_price[j];
		}

		string ins = "UPDATE orders SET totalprice='" + to_string(ttlprice) + "' WHERE orderid=" + ordid + ";";
		const char* ut = ins.c_str();
		qstate = mysql_query(conn, ut);

		if (qstate)
		{
			cout << "error update total " << mysql_errno(conn) << endl;
		}

		// confirm payment, put delete if cancel
		cin.ignore();
		cout << "Press ENTER to confirm payment..";
		cin.get();

		// display receipt
		system("cls");
		cout << "=================================================================================================================\n";
		cout << "                                               ORDER RECEIPT                                                     \n";
		cout << "=================================================================================================================\n\n";
		cout << "    EZ Order\n\n";
		cout << "    Item ID        Item name                              Quantity                   Total price\n";

		string query7 = "SELECT order_item.itemid, item.itemname, order_item.quantity, order_item.priceperitem FROM order_item INNER JOIN item ON order_item.itemid = item.itemid WHERE order_item.orderid = " + ordid + ";";
		const char* q7 = query7.c_str();
		qstate = mysql_query(conn, q7);

		if (qstate)
		{
			cout << "Failed to load receipt. Please try again later " << mysql_errno(conn) << endl;
		}
		else
		{
			mysql_free_result(result);
			result = mysql_store_result(conn);
			int i = 1;
			while (row = mysql_fetch_row(result))
			{
				string row1 = string(row[0]);
				string row2 = string(row[1]);
				string row3 = string(row[2]);
				string row4 = string(row[3]);

				cout << "  " << i << ".  " << left << setw(15) << row1 << left << setw(39) << row2 << left << setw(27) << row3 << row4 << endl;
				i++;
			}
			cout << "                                                                        Total\n";
			cout << "                                                                        RM " << to_string(ttlprice) << endl;
		}
	}

	cin.ignore();
	cout << "Press ENTER to go back to main menu..";
	cin.get();
	customerPanel(); // return function
}

void customerReceipt()
{
	string ans;
	cout << endl << "Enter order Id to see full receipt. Enter q to back to main menu : ";
	cin >> ans;

	if (ans == "q" || ans == "Q")
	{
		customerPanel();
	}
	else
	{
		//customerReceipt();
		// calculate total price
		string query9 = "SELECT priceperitem FROM order_item WHERE orderid=" + ans + " AND (SELECT customerid FROM orders WHERE orderid=" + ans + ")=" + sessionc + ";";
		const char* total = query9.c_str();
		qstate = mysql_query(conn, total);

		if (qstate)
		{
			if (mysql_errno(conn) == 1054)
			{
				cout << "Invalid input!" << endl;
			}
			else
			{
				cout << "Failed to calculate total. " << mysql_errno(conn) << endl;
			}

			cin.ignore();
			cout << "Press ENTER to back to panel..";
			cin.get();
			customerOrder();
		}

		mysql_free_result(result);
		result = mysql_store_result(conn);

		int total_price[12] = { 0 };
		int i = 0;
		while (row = mysql_fetch_row(result))
		{
			total_price[i] = atoi(row[0]);
			i++;
		}

		int ttlprice = 0;
		for (int j = 0; j < 12; j++)
		{
			ttlprice = ttlprice + total_price[j];
		}

		system("cls");
		cout << "=================================================================================================================\n";
		cout << "                                               ORDER RECEIPT                                                     \n";
		cout << "=================================================================================================================\n\n";
		cout << "    EZ Order\n\n";
		cout << "    Item ID        Item name                              Quantity                   Total price\n";

		string query10 = "SELECT order_item.itemid, item.itemname, order_item.quantity, order_item.priceperitem FROM order_item INNER JOIN item ON order_item.itemid = item.itemid WHERE order_item.orderid = " + ans + ";";
		const char* query10c = query10.c_str();
		qstate = mysql_query(conn, query10c);

		if (qstate)
		{
			cout << "Failed to load receipt. Please try again later " << mysql_errno(conn) << endl;
		}
		else
		{
			mysql_free_result(result);
			result = mysql_store_result(conn);
			int i = 1;
			while (row = mysql_fetch_row(result))
			{
				string row1 = string(row[0]);
				string row2 = string(row[1]);
				string row3 = string(row[2]);
				string row4 = string(row[3]);

				cout << "  " << i << ".  " << left << setw(15) << row1 << left << setw(39) << row2 << left << setw(27) << row3 << row4 << endl;
				i++;
			}
			cout << "                                                                        Total\n";
			cout << "                                                                        RM " << to_string(ttlprice) << endl;
		}
	}
	
	cin.ignore();
	cout << endl << "Press ENTER to go back to main menu..";
	cin.get();
	customerPanel();

}

void customerOrder()
{
	system("cls");
	cout << "    dMMMMMP dMMMMMP        .aMMMb  dMMMMb  dMMMMb  dMMMMMP dMMMMb " << endl;
	cout << "   dMP       .dMP\"        dMP\"dMP dMP.dMP dMP VMP dMP     dMP.dMP" << endl;
	cout << "  dMMMP    .dMP\"         dMP dMP dMMMMK\" dMP dMP dMMMP   dMMMMK\" " << endl;
	cout << " dMP     .dMP\"          dMP.aMP dMP\"AMF dMP.aMP dMP     dMP\"AMF   " << endl;
	cout << "dMMMMMP dMMMMMP         VMMMP\" dMP dMP dMMMMP\" dMMMMMP dMP dMP    " << endl << endl;
	cout << "Welcome back customer " << cusname << "!" << endl;
	
	string query = "SELECT * FROM orders WHERE customerid=" + sessionc + " AND orderstatus='PENDING';";
	const char* vco = query.c_str();
	qstate = mysql_query(conn, vco);

	if (qstate)
	{
		cout << "Failed to display orders. Please try again later " << mysql_errno(conn) << endl;
		cin.ignore();
		cout << "Press ENTER to go back to main menu..";
		cin.get();
		customerPanel();
	}

	cout << "+---------+--------------+-------------------+-------------+" << endl;
	cout << "| OrderId | Order Status |      Date Time    | Total Price |" << endl;
	cout << "+---------+--------------+-------------------+-------------+" << endl;

	mysql_free_result(result);
	result = mysql_store_result(conn);

	while (row = mysql_fetch_row(result))
	{
		string row1 = string(row[0]);
		string row2 = string(row[1]);
		string row3 = string(row[2]);
		string row4 = string(row[3]);
		cout << "|" << left << setw(9) << row1;
		cout << "|" << left << setw(14) << row2;
		cout << "|" << left << setw(19) << row3;
		cout << "|" << "RM " << left << setw(10) << row4 << "|";
		cout << endl;
	}
	cout << "+----------------------------------------------------------+" << endl;

	query = "SELECT * FROM orders WHERE customerid=" + sessionc + " AND orderstatus='COMPLETE';";
	const char* viewcomplete = query.c_str();
	qstate = mysql_query(conn, viewcomplete);
	mysql_free_result(result);
	result = mysql_store_result(conn);
	row = mysql_fetch_row(result);

	if (row != NULL)
	{
		while (row = mysql_fetch_row(result))
		{
			string row1 = string(row[0]);
			string row2 = string(row[1]);
			string row3 = string(row[2]);
			string row4 = string(row[3]);
			cout << "|" << row1 << setw(10 - row1.size());
			cout << "|" << row2 << setw(15 - row2.size());
			cout << "|" << row3 << setw(16 - row3.size());
			cout << "|" << "RM " << row4 << setw(11 - row4.size()) << "|";
			cout << endl;
		}
		cout << "+---------+--------------+-------------------+-------------+" << endl;
	}

	string cho;
	int ch;
	cout << "Enter choice:" << endl;
	cout << "	1. View receipt" << endl;
	cout << "	2. Cancel order" << endl;
	cout << "	3. Back to main menu" << endl;
	cout << "Choose : ";
	cin >> cho;

	// int validation
	if (cho == "1" || cho == "2" || cho == "3")
	{
		ch = stoi(cho);
	}
	else
	{
		customerOrder();
	}

	switch (ch)
	{
	case 1:
		customerReceipt();

		break;
	case 2:
		cancelOrder();

		break;
	case 3:
		customerPanel();

		break;
	default:
		cout << "Invalid option!" << endl;
		cin.ignore();
		cout << "Press ENTER to view order..";
		cin.get();
		customerOrder();
	}

}

void cancelOrder()
{
	string delid;
	string confirmation;
	cout << "Enter order ID to cancel : ";
	cin >> delid;

	cout << "Are you sure you want to cancel this order? (y/n)";
	cin >> confirmation;

	if (confirmation == "n" || confirmation == "N")
	{
		customerOrder();
	}
	else if (confirmation == "y" || confirmation == "N")
	{

	}
	else
	{
		cout << "invalid answer!" << endl;
		cin.ignore();
		cout << "Press ENTER to back to order..";
		cin.get();
		customerOrder();
	}

	string delquery1 = "DELETE FROM order_item WHERE orderid=" + delid + " AND (SELECT customerid FROM orders WHERE orderid = " + delid + ") = " + sessionc + " AND (SELECT orderstatus FROM orders WHERE orderid=" + delid + ")='PENDING';";
	string delquery2 = "DELETE FROM orders WHERE orderid = " + delid + " AND customerid=" + sessionc + ";";
	const char* delq1 = delquery1.c_str();
	const char* delq2 = delquery2.c_str();
	qstate = mysql_query(conn, delq1);

	if (qstate)
	{
		if (mysql_errno(conn) == 1054)
		{
			cout << "Invalid order ID!" << endl;
			cancelOrder();
		}
		else
		{
			cout << "Failed to delete item " << mysql_errno(conn) << endl;
			cin.ignore();
			cout << "Press ENTER to back to panel..";
			cin.get();
			customerPanel();
		}
	}

	qstate = mysql_query(conn, delq2);

	if (qstate)
	{
		cout << "Failed to cancel order " << mysql_errno(conn) << endl;
		cin.ignore();
		cout << "Press ENTER to back to panel..";
		cin.get();
		customerPanel();
	}

	cout << "Do you want to cancel another order? (y/n) ";
	string ag;
	cin >> ag;

	if (ag == "y" || ag == "Y")
	{
		cancelOrder();
	}
	else
	{
		customerOrder();
	}
}
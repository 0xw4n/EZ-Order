#include <iostream>
#include <sstream>
#include <string>
#include <sstream>
#include <vector>
#include <mysql.h>
#include "seller.h"
#include "dbresponse.h"
#include <iomanip>
#include "MD5.h"
#include <conio.h>

using namespace std;

string sessions;
string user = "seller";

void sellerLogin()
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
	cout << endl;

	pass = MD5(password).toStr();
	string query = "SELECT sellerid, sellername FROM seller WHERE selleremail='" + email + "' AND sellerpassword='" + pass + "';";
	const char* al = query.c_str();

	qstate = mysql_query(conn, al);

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
			sellerLogin();
		}
		else
		{
			sessions = string(row[0]);
			user = string(row[1]);
		}

		//mysql_free_result(result); //use this before calling issuing another query
		system("cls");
		sellerPanel();
	}
	else
	{
		cout << "error in " << mysql_errno(conn) << ", Make sure your credential is correct!\n";
		cout << "press ENTER to login again";
		cin.ignore();
		cin.get();
		system("cls");
		sellerLogin();
	}
}

void sellerPanel()
{
	system("cls");
	int choice;
	string ch;
	cout << "    dMMMMMP dMMMMMP        .aMMMb  dMMMMb  dMMMMb  dMMMMMP dMMMMb " << endl;
	cout << "   dMP       .dMP\"        dMP\"dMP dMP.dMP dMP VMP dMP     dMP.dMP" << endl;
	cout << "  dMMMP    .dMP\"         dMP dMP dMMMMK\" dMP dMP dMMMP   dMMMMK\" " << endl;
	cout << " dMP     .dMP\"          dMP.aMP dMP\"AMF dMP.aMP dMP     dMP\"AMF   " << endl;
	cout << "dMMMMMP dMMMMMP         VMMMP\" dMP dMP dMMMMP\" dMMMMMP dMP dMP    " << endl;

	cout << "\nChoose action :" << endl;
	cout << endl;
	cout << "	1. Profile" << endl;
	cout << "	2. Manage orders" << endl;
	cout << "	3. Manage items" << endl;
	cout << "	4. Logout" << endl;
	cout << "\nChoose: ";
	cin >> ch;

	// int validation
	if (ch == "1" || ch == "2" || ch == "3" || ch == "4")
	{
		choice = stoi(ch);
	}
	else
	{
		sellerPanel();
	}

	switch (choice)
	{
		case 1:
			//profile
			sellerProfile();

			break;
		case 2:
			//manage order
			viewOrder();

			break;
		case 3:
			//manage item
			sellerItem();

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
			sellerPanel();
	}
}

void sellerProfile()
{
	system("cls");
	cout << "Seller Profile" << endl;
	cout << endl;
	
	int opt;
	int er;
	string op;
	string name = "";
	string email = "";
	string phone = "";
	string address = "";
	string oldpassword = "";
	string password = "";
	string repassword = "";
	string oldpass = "";
	string pass = "";

	//mysql_free_result(result);
	string query = "select * from seller where sellerid=" + sessions+";";
	const char* pr = query.c_str();

	qstate = mysql_query(conn, pr);

	if (!qstate)
	{
		mysql_free_result(result);
		result = mysql_store_result(conn);
		row = mysql_fetch_row(result);

		cout << "Username : " << row[1] << endl;
		cout << "Email : " << row[3] << endl;
		cout << "Phone : " << row[4] << endl;
		cout << "Address : " << row[5] << endl;
	}
	else
	{
		cout << "Could not load profile " << mysql_errno(conn);
	}
	cout << endl;
	cout << "Change profile :" << endl;
	cout << "1.Username 2.Email 3.Phone 4.Address 5.Password 6.Back to menu" << endl;
	cout << endl << "Option:";
	cin >> op;

	// int validation
	if (op == "1" || op == "2" || op == "3" || op == "4" || op == "5" || op == "6")
	{
		opt = stoi(op);
	}
	else
	{
		sellerProfile();
	}

	switch (opt)
	{
	case 1:
		cin.ignore();
		cout << "New username : ";
		getline(cin, name);

		if (name != "")// if name not empty
		{
			//query start
			string cn = "UPDATE seller SET sellername='" + name + "' WHERE sellerid=" + sessions + ";";
			const char* cnq = cn.c_str();
			qstate = mysql_query(conn, cnq);

			if (qstate)
			{
				cout << "Failed to update username " << mysql_errno(conn) << endl;
				cin.ignore();
				cout << "Press ENTER to back to profile..";
				cin.get();
			}// query end
		}
		sellerProfile();

		break;
	case 2:
		cout << "New email : ";
		cin >> email;

		if (email != "")
		{
			//query start
			string cn = "UPDATE seller SET selleremail='" + email + "' WHERE sellerid=" + sessions + ";";
			const char* ceeq = cn.c_str();
			qstate = mysql_query(conn, ceeq);

			if (qstate)
			{
				cout << "Failed to update email " << mysql_errno(conn) << endl;
				cin.ignore();
				cout << "Press ENTER to back to profile..";
				cin.get();
			}// query end
		}
		sellerProfile();

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
			sellerProfile();
		}

		if (phone != "")
		{
			//query start
			string cn = "UPDATE seller SET sellerphone='60" + phone + "' WHERE sellerid=" + sessions + ";";
			const char* cpq = cn.c_str();
			qstate = mysql_query(conn, cpq);

			if (qstate)
			{
				cout << "Failed to update phone number" << mysql_errno(conn) << endl;
				cin.ignore();
				cout << "Press ENTER to back to profile..";
				cin.get();
			}// query end
		}
		sellerProfile();

		break;
	case 4:
		cin.ignore();
		cout << "New address : ";
		getline(cin, address);

		if (address != "")
		{
			//query start
			string cn = "UPDATE seller SET selleraddress='" + address + "' WHERE sellerid=" + sessions + ";";
			const char* caq = cn.c_str();
			qstate = mysql_query(conn, caq);

			if (qstate)
			{
				cout << "Failed to update address " << mysql_errno(conn) << endl;
				cin.ignore();
				cout << "Press ENTER to back to profile..";
				cin.get();
			}// query end
		}
		sellerProfile();

		break;
	case 5:
		cout << "Enter old password : ";
		cin >> oldpassword;

		oldpass = MD5(oldpassword).toStr();
		if (oldpassword != "")
		{
			string check = "SELECT sellerpassword FROM seller WHERE sellerid=" + sessions + ";";
			const char* ck = check.c_str();
			qstate = mysql_query(conn, ck);
			if (qstate)// if query failed
			{
				cout << "Error in process " << mysql_errno(conn) << endl;
				cin.ignore();
				cout << "Press ENTER to back to profile..";
				cin.get();
				sellerProfile();
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
				sellerProfile();
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
			string cn = "UPDATE seller SET sellerpassword='" + pass + "' WHERE sellerid=" + sessions + ";";
			const char* cpp = cn.c_str();
			qstate = mysql_query(conn, cpp);

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
		sellerProfile();

		break;
	case 6:
		sellerPanel();

		break;
	default:
		cout << "Invalid option!" << endl;
		cin.ignore();
		cout << "Press ENTER to back to profile..";
		cin.get();
		sellerProfile();
	}

}

void sellerItem()
{
	system("cls");
	int choose;
	string ch;
	// show all items
	viewItem();

	// panel
	cout << "Choose option : " << endl;
	cout << "	1. Add item" << endl;
	cout << "	2. Delete item" << endl;
	cout << "	3. Back to menu" << endl;
	cout << endl;
	cout << "Choose : ";
	cin >> ch;

	// int validation
	if (ch == "1" || ch == "2" || ch == "3" )
	{
		choose = stoi(ch);
	}
	else
	{
		sellerItem();
	}

	switch (choose)
	{
		case 1:
			// add item function
			addItem();

			break;
		case 2:
			//delete item function
			deleteItem();

			break;
		case 3:
			sellerPanel();

			break;
		default:
			cout << "Invalid option!" << endl;
			cin.ignore();
			cout << "Press ENTER to back to manage item..";
			cin.get();
			sellerItem();
	}

	// 
}

void addItem()
{
	string name, price, desc, stock, again;
	int err;
	cout << "Add item, please enter item details. Enter 'q' if you want to abort" << endl;
	cout << endl;
	cin.ignore();
	cout << "Item name : ";
	getline(cin, name);
	if (name == "q" || name == "Q")
	{
		sellerItem();
	}
	cout << "Item price : ";
	cin >> price;
	if (price == "q" || price == "Q")
	{
		sellerItem();
	}
	
	for (int i = 0; i < price.size(); i++)
	{
		int uppercaseChar = toupper(price[i]); //Convert character to upper case version of character
		if (uppercaseChar < 'A' || uppercaseChar > 'Z') //If character is not A-Z
		{
			
		}
		else
		{
			cout << "Invalid input!" << endl;
			err = 1;
			break;
		}
	}

	if (stoi(price) < 0)
	{
		cout << "Invalid price!" << endl;
		err = 1;
	}


	if (err == 1)
	{
		cin.ignore();
		cout << "Press ENTER to back to manage item..";
		cin.get();
		sellerItem();
	}

	cin.ignore();
	cout << "Item description : ";
	getline(cin, desc);
	if (desc == "q" || desc == "Q")
	{
		sellerItem();
	}
	cout << "Item stock number : ";
	cin >> stock;
	if (stock == "q" || stock == "Q")
	{
		sellerItem();
	}

	for (int i = 0; i < stock.size(); i++)
	{
		int uppercaseChar = toupper(stock[i]); //Convert character to upper case version of character
		if (uppercaseChar < 'A' || uppercaseChar > 'Z') //If character is not A-Z
		{

		}
		else
		{
			cout << "Invalid input!" << endl;
			err = 1;
			break;
		}
	}

	if (stoi(stock) < 0)
	{
		cout << "Invalid stock!" << endl;
		err = 1;
	}


	if (err == 1)
	{
		cin.ignore();
		cout << "Press ENTER to back to manage item..";
		cin.get();
		sellerItem();
	}

	string query = "INSERT INTO item (itemname, itemprice, itemdescription, stocknumber) VALUES ('"+name+"', "+price+", '"+desc+"', "+stock+");";
	const char* ni = query.c_str();
	qstate = mysql_query(conn, ni);

	if (qstate)
	{
		cout << "Failed to add item " << mysql_errno(conn) << endl;
		cin.ignore();
		cout << "Press ENTER to back to manage item..";
		cin.get();
		sellerItem();
	}

	cout << "Successfully added! Add another item?(y/n) ";
	cin >> again;
	if (again == "y" || again == "Y")
	{
		addItem();
	}
	else
	{
		sellerItem();
	}

}

void deleteItem()
{
	string id, confirm;
	cout << "Enter item ID : ";
	cin >> id;
	cout << "Are you sure you want to delete item " << id << " ?(y/n) ";
	cin >> confirm;
	if (confirm == "y" || confirm == "Y")
	{
		string query = "DELETE FROM item WHERE itemid=" + id + ";";
		const char* del = query.c_str();
		qstate = mysql_query(conn, del);
		if (qstate)
		{
			if (mysql_errno(conn) == 1054)
			{
				cout << "Invalid item ID!" << endl;
				cin.ignore();
				cout << "Press ENTER to back to manage item..";
				cin.get();
				sellerItem();
			}
			else
			{
				cout << "Failed to delete item " << mysql_errno(conn) << endl;
				cin.ignore();
				cout << "Press ENTER to back to manage item..";
				cin.get();
				sellerItem();
			}
		}
	}
	else
	{
		sellerItem();
	}

	cout << "Successfully to delete item " << endl;
	cin.ignore();
	cout << "Press ENTER to back to manage item..";
	cin.get();
	sellerItem();
	
}

void viewItem()
{
	qstate = mysql_query(conn, "SELECT * FROM item");

	mysql_free_result(result);
	result = mysql_store_result(conn);
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

void viewOrder()
{
	system("cls");
	int choice;
	string ch;
	cout << "View order by : " << endl;
	cout << "	1. Pending order" << endl;
	cout << "	2. Completed order" << endl;
	cout << "	3. Back to main menu" << endl;
	cout << "Choose : ";
	cin >> ch;

	// int validation
	if (ch == "1" || ch == "2" || ch == "3" )
	{
		choice = stoi(ch);
	}
	else
	{
		viewOrder();
	}

	switch (choice)
	{
		case 1:
			pending();

			break;
		case 2:
			complete();

			break;
		case 3:
			sellerPanel();

			break;
		default:
			cout << "Invalid option!" << endl;
			cin.ignore();
			cout << "Press ENTER to back to manage order..";
			cin.get();
			viewOrder();
	}
}

void pending()
{
	system("cls");
	cout << "+---------+-------------+--------------+-------------------+-------------+" << endl;
	cout << "| OrderId | customerId  | Order Status |     Date Time     | Total Price |" << endl;
	cout << "+---------+-------------+--------------+-------------------+-------------+" << endl;

	qstate = mysql_query(conn, "SELECT * FROM orders WHERE orderstatus='PENDING';");
	mysql_free_result(result);
	result = mysql_store_result(conn);

	while (row = mysql_fetch_row(result))
	{
		string row1 = string(row[0]);
		string row2 = string(row[4]);
		string row3 = string(row[1]);
		string row4 = string(row[2]);
		string row5 = string(row[3]);
		cout << "|" << left << setw(9) << row1;
		cout << "|" << left << setw(13) << row2;
		cout << "|" << left << setw(14) << row3;
		cout << "|" << left << setw(19) << row4;
		cout << "|" << "RM " << left << setw(10) << row5 << "|";
		cout << endl;
	}
	cout << "+---------+-------------+--------------+-------------------+-------------+" << endl;

	int choose;
	string ch;
	cout << endl;
	cout << "Choose : " << endl;
	cout << "	1. View detail order" << endl;
	cout << "	2. Mark order as complete" << endl;
	cout << "	3. Delete order" << endl;
	cout << "	4. Back to main menu" << endl;
	cout << ": ";
	cin >> ch;

	// int validation
	if (ch == "1" || ch == "2" || ch == "3" || ch == "4")
	{
		choose = stoi(ch);
	}
	else
	{
		pending();
	}

	string ordid;
	switch (choose)
	{
		case 1:
			detailOrder();

			break;
		case 2: 
			markAsComplete();

			break;
		case 3:
			deleteOrder();

			break;
		case 4:
			sellerPanel();

			break;
		default:
			cout << "Invalid option!" << endl;
			cin.ignore();
			cout << "Press ENTER to back to manage order..";
			cin.get();
			pending();
	}

}

void complete()
{
	system("cls");
	cout << "+---------+-------------+--------------+-------------------+-------------+" << endl;
	cout << "| OrderId | customerId  | Order Status |     Date Time     | Total Price |" << endl;
	cout << "+---------+-------------+--------------+-------------------+-------------+" << endl;

	qstate = mysql_query(conn, "SELECT * FROM orders WHERE orderstatus='COMPLETE';");
	mysql_free_result(result);
	result = mysql_store_result(conn);

	while (row = mysql_fetch_row(result))
	{
		string row1 = string(row[0]);
		string row2 = string(row[4]);
		string row3 = string(row[1]);
		string row4 = string(row[2]);
		string row5 = string(row[3]);
		cout << "|" << left << setw(9) << row1;
		cout << "|" << left << setw(13) << row2;
		cout << "|" << left << setw(14) << row3;
		cout << "|" << left << setw(19) << row4;
		cout << "|" << "RM " << left << setw(10) << row5 << "|";
		cout << endl;
	}
	cout << "+---------+-------------+--------------+-------------------+-------------+" << endl;

	cout << endl;
	sales();

	cin.ignore();
	cout << endl << "Press ENTER to go back to manage order..";
	cin.get();
	viewOrder();
}

void detailOrder()
{
	string id;
	string address;
	cout << endl;
	cout << "Enter order id : ";
	cin >> id;

	string query11 = "SELECT customeraddress FROM customer WHERE customerid=(SELECT customerid FROM orders WHERE orderid=" + id + ");";
	const char* q11 = query11.c_str();
	string querys = "SELECT priceperitem FROM order_item WHERE orderid=" + id + ";";
	const char* total = querys.c_str();
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
		sellerPanel();
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

	string query10 = "SELECT order_item.itemid, item.itemname, order_item.quantity, order_item.priceperitem FROM order_item INNER JOIN item ON order_item.itemid = item.itemid WHERE order_item.orderid = " + id + ";";
	const char* query10c = query10.c_str();
	qstate = mysql_query(conn, query10c);

	if (qstate)
	{
		cout << "Failed to load details. Please try again later " << mysql_errno(conn) << endl;
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
	}
	qstate = mysql_query(conn, q11);
	if (qstate)
	{
		cout << "failed to get address " << endl;
	}
	else
	{
		mysql_free_result(result);
		result = mysql_store_result(conn);
		row = mysql_fetch_row(result);
		address = string(row[0]);

	}
	cout << "                                                                        RM " << to_string(ttlprice) << endl;
	cout << address << endl;
	cin.ignore();
	cout << "Press ENTER to go back to view order..";
	cin.get();
	pending();
}

void markAsComplete()
{
	string orderid;
	string again;
	do 
	{
		cout << endl << "Enter order ID : ";
		cin >> orderid;

		string query = "UPDATE orders SET orderstatus='COMPLETE' WHERE orderid=" + orderid + ";";
		const char* upstat = query.c_str();
		qstate = mysql_query(conn, upstat);

		if (qstate)
		{
			cout << "Failed to update order status " << mysql_errno(conn) << endl;
		}
		cout << "Enter again?(y/n) ";
		cin >> again;

	} while (again == "Y" || again == "y");

	cin.ignore();
	cout << "Press ENTER to back to panel..";
	cin.get();
	pending();

}

void deleteOrder()
{
	string delid;
	cout << "Enter order ID to delete : ";
	cin >> delid;

	string delquery1 = "DELETE FROM order_item WHERE orderid=" + delid + ";";
	string delquery2 = "DELETE FROM orders WHERE orderid = " + delid + "; ";
	const char* delq1 = delquery1.c_str();
	const char* delq2 = delquery2.c_str();
	qstate = mysql_query(conn, delq1);

	if (qstate)
	{
		if (mysql_errno(conn) == 1054)
		{
			cout << "Invalid order ID!" << endl;
			deleteOrder();
		}
		else
		{
			cout << "Failed to delete order " << mysql_errno(conn) << endl;
			cin.ignore();
			cout << "Press ENTER to back to manage order..";
			cin.get();
			viewOrder();
		}
	}

	qstate = mysql_query(conn, delq2);

	if (qstate)
	{
		cout << "Failed to delete order " << mysql_errno(conn) << endl;
		cin.ignore();
		cout << "Press ENTER to back to manage order..";
		cin.get();
		viewOrder();
	}

	cout << "Delete order successfull! Do you want to delete another order? (y/n) ";
	string ag;
	cin >> ag;

	if (ag == "y" || ag == "Y")
	{
		deleteOrder();
	}
	else
	{
		viewOrder();
	}


}

void sales()
{
	string month, year;
	cout << "Find how much sales you got!" << endl;
	cout << "Enter month. Enter 'q' to abort: ";
	cin >> month;
	if (month == "q" || month == "Q")
	{
		viewOrder();
	}
	cout << "Enter year. Enter 'q' to abort: ";
	cin >> year;
	if (year == "q" || year == "Q")
	{
		viewOrder();
	}

	string findsale = "SELECT SUM(totalprice) FROM orders WHERE orderstatus='COMPLETE' AND MONTH(orderdatetime)='" + month + "' AND YEAR(orderdatetime)='" + year + "';";
	const char* fs = findsale.c_str();
	qstate = mysql_query(conn, fs);

	if (qstate)
	{
		cout << "Failed to find sales " << mysql_errno(conn) << endl;
		cin.ignore();
		cout << "Press ENTER to back to manage order..";
		cin.get();
		viewOrder();
	}
	mysql_free_result(result);
	result = mysql_store_result(conn);
	row = mysql_fetch_row(result);

	if (row[0] == NULL)
	{
		cout << "Your sale is: no sales" << endl;
		cin.ignore();
		cout << "Press ENTER to back to manage order..";
		cin.get();
		complete();
	}
	else {
		string totalsales = string(row[0]);
		cout << "Your sale is: RM " << totalsales << endl;
		cin.ignore();
		cout << "Press ENTER to back to manage order..";
		cin.get();
		complete();
	}

}


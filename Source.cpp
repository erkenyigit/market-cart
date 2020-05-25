#include <iostream>
#include <vector>
#include <string>
#include "strutils.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct item {

	string name = "";
	int quantity = 0;
	int price = 0;
};

bool sortHelper(const item& a, const item& b) {
	if ((a.price * a.quantity) < (b.price * b.quantity)) {
		return true;
	}
	else if ((a.price * a.quantity) == (b.price * b.quantity)) {
		return a.name > b.name;
	}
	else return false;
}

bool isInMarket(vector<item> v, string str) {
	int i;
	if (!v.empty()) {
		for (i = 0; i < v.size(); i++) {
			ToUpper(v[i].name);
			if (v[i].name == str) {
				return true;
			}
		}
		return false;
	}
	else return false;
}

void addItem(vector<item> &cart, vector<item> &market) {
	string tmp_name,raw, rawint;
	int tmp_quantity,j;
	item tmp_item;
	char c;
	cout << "Please enter the item name and quantity: ";
	cin.ignore();
	getline(cin, raw);
	
	int i = raw.size() - 1;

	while (raw[i])
	{
		c = raw[i];


		if (isspace(c)) { break; }

		i--;

		rawint.push_back(c);
		raw.pop_back();
		//i = raw.size() - 1;
	}
	reverse(rawint.begin(), rawint.end());
	raw.pop_back();
	
	tmp_quantity = atoi(rawint);
	ToUpper(raw);
	tmp_name = raw;
	
	if (isInMarket(market, tmp_name)) {
		
		if (!isInMarket(cart,tmp_name))
		{
			for (i = 0; i < market.size() && market[i].name != tmp_name; i++) {};

			if (market[i].quantity == 0) {
				cout << "None left in the market."<< endl;
			}
			else if (market[i].quantity < tmp_quantity) {
				cout << "Only " << market[i].quantity << " left in the market. Adding all to your cart!" << endl;
				tmp_item.name = tmp_name;
				tmp_item.quantity = market[i].quantity;
				tmp_item.price = market[i].price;
				cart.push_back(tmp_item);

				cout << "Added " << tmp_name << " with " << market[i].quantity << " quantity to your cart." << endl;
				market[i].quantity = 0;
			}
			else {
				cout << "Added " << tmp_name << " with " << tmp_quantity << " quantity to your cart." << endl;
				tmp_item.name = tmp_name;
				tmp_item.quantity = tmp_quantity;
				tmp_item.price = market[i].price;
				cart.push_back(tmp_item);
				market[i].quantity -= tmp_quantity;
			}
		}
		else {
			//for (i = 0; i < cart.size() && cart[i].name != tmp_name; i++) {};
			for (i = 0; i < market.size() && market[i].name != tmp_name; i++) {};

			if (market[i].quantity == 0) {
				cout << "None left in the market."<<endl;
			}
			else if (market[i].quantity < tmp_quantity) {
				cout << "Only " << market[i].quantity << " left in the market. Adding all to your cart!" << endl;
				for (j = 0; j < cart.size() && cart[j].name != tmp_name; j++) {};
				cart[j].quantity += market[i].quantity;
				cout << "Added " << tmp_name << " with " << market[i].quantity << " quantity to your cart." << endl;
				market[i].quantity = 0;
			}
			else {
				cout << "Added " << tmp_name << " with " << tmp_quantity << " quantity to your cart." << endl;
				for (j = 0; j < cart.size() && cart[j].name != tmp_name; j++) {};
				cart[j].quantity += tmp_quantity;
				market[i].quantity -= tmp_quantity;
			}
		}
	}
	else {
		cout << "There is no such item in the market!" << endl;
	}
}

void deleteItem(vector<item>& cart, vector<item>& market) {
	if (cart.empty()) {
		cout << "Your shopping cart is empty!" << endl;
	}
	else {
		string tmp_name,raw,rawint;
		int tmp_quantity;
		item tmp_item;
		char c;

		cout << "Please enter the item name and quantity: ";
		cin.ignore();
		getline(cin, raw);

		int i = raw.size() - 1;

		while (raw[i])
		{
			c = raw[i];


			if (isspace(c)) { break; }

			i--;

			rawint.push_back(c);
			raw.pop_back();
			//i = raw.size() - 1;
		}
		reverse(rawint.begin(), rawint.end());
		raw.pop_back();

		tmp_quantity = atoi(rawint);
		ToUpper(raw);
		tmp_name = raw;
		ToUpper(tmp_name);
		if (isInMarket(cart, tmp_name)) {
			for (i = 0; i < cart.size() && cart[i].name != tmp_name; i++) {};
			if (cart[i].quantity > tmp_quantity) {
				cout << "Removed " << tmp_name << " with quantity " << tmp_quantity << " from your cart." << endl;
				cart[i].quantity -= tmp_quantity;
				for (i = 0; i < market.size() && market[i].name != tmp_name; i++) {};
				market[i].quantity += tmp_quantity;
			}
			else if (cart[i].quantity < tmp_quantity) {
				cout << "You have only " << cart[i].quantity << " " << tmp_name << " in your cart. Removing all from your cart!" << endl;
				cart.erase(cart.begin() + i);
				for (i = 0; i < market.size() && market[i].name != tmp_name; i++) {};
				market[i].quantity += tmp_quantity;
			}
			else {
				cout << "Removed all " << tmp_name << " from your cart." << endl;
				cart.erase(cart.begin() + i);
				for (i = 0; i < market.size() && market[i].name != tmp_name; i++) {};
				market[i].quantity += tmp_quantity;
			}
		}
		else {
			cout << "There is no such item in your shopping cart!" << endl;
		}
	}
}

void printCartReverse(vector<item> cart) {
	if (!cart.empty()) {

		sort(cart.begin(), cart.end(), sortHelper);
		for (int i = 0; i < cart.size(); i++)
			cout << cart[i].name << ' '<< cart[i].quantity<<' '<< cart[i].price<<endl;
	}
	else {
		cout << "Your shopping cart is empty!" << endl;
	}
}

void printCart(vector<item> cart) {
	if (!cart.empty()) {

		sort(cart.begin(), cart.end(), sortHelper);
		reverse(cart.begin(), cart.end());
		for (int i = 0; i < cart.size(); i++)
			cout << cart[i].name << ' ' << cart[i].quantity << ' ' << cart[i].price << endl;
	}
	else {
		cout << "Your shopping cart is empty!" << endl;
	}
}

void estimateTotal(vector<item> cart) {
	if (!cart.empty()) {
		int total = 0;
		for (int i = 0; i < cart.size(); i++) {
			total += cart[i].price * cart[i].quantity;
		}
		cout << "The total cost of " << cart.size() << " kinds of items is: " << total << endl;
	}
	else {
		cout << "Your shopping cart is empty!" << endl;
	}
	
}
int main() {

	ifstream quantity_file, price_file;
	string qfile_name, pfile_name,temp_name;
	int temp_quantity, temp_price;

	while (!quantity_file.is_open()) {
		cout << "Please enter the name of the stock file: ";
		cin >> qfile_name;
		quantity_file.open(qfile_name);
		if (!quantity_file) {
			cout << "File failed to open!" << endl;
		}
	}
	while (!price_file.is_open()) {
		cout << "Please enter the name of the price file: ";
		cin >> pfile_name;
		price_file.open(pfile_name);
		if (!price_file) {
			cout << "File failed to open!" << endl;
		}
	}
	string s, line;

	vector<item> cart;
	vector<item> market;
	
	//CONSTRUCT MARKET WITH QUANTITES
	while (!quantity_file.eof()) {
		getline(quantity_file, s);
		stringstream ss(s);
		if (s == "") { break;}
		getline(ss, line, ';');	
		ToUpper(line);
		temp_name = line;
		
		getline(ss, line, ';');
		temp_quantity = atoi(line);
		
		if (isInMarket(market, temp_name)) {
			int i = 0;
			
			while (market[i].name != temp_name) {
				i++;
			}
		
			market[i].quantity += temp_quantity;
		}
		else {
			item temp_item;
			temp_item.name = temp_name;
			temp_item.quantity = temp_quantity;
			market.push_back(temp_item);
		}
	}
	//ADD PRICES TO MARKET ITEMS
	while (!price_file.eof()) {
		getline(price_file, s);
		stringstream ss(s);

		getline(ss, line, ';');
		ToUpper(line);
		temp_name = line;

		getline(ss, line, ';');
		temp_price = atoi(line);

		if (isInMarket(market, temp_name)) {
			int i = 0;
			
			while (market[i].name != temp_name) {
				i++;
			}
			market[i].price = temp_price;
		}

	}
	int choice;
	string input;
	while (true) {
		cout << "---" << endl << "MENU" << endl;
		cout << "1. Add item to the shopping cart" << endl;
		cout << "2. Delete item from the shopping cart" << endl;
		cout << "3. Print the shopping cart" << endl;
		cout << "4. Print the shopping cart in reverse order" << endl;
		cout << "5. Show total estimated cost of the cart" << endl;
		cout << "6. Exit" << endl << "---" << endl;
		cout << "Enter your choice: ";
		cin >> input;
		cout << "---" << endl;
		choice = atoi(input);
		switch (choice)
		{
		case 1:
			addItem(cart,market);
			break;
		case 2:
			deleteItem(cart, market);
			break;
		case 3:
			printCart(cart);
			break;
		case 4:
			printCartReverse(cart);
			break;
		case 5:
			estimateTotal(cart);
			break;
		case 6:
			cout << "Your order has been completed!" << endl;
			exit(0);
		default:
			cout << "This is not a valid option!" << endl;
		}
	}





	return 0;
}
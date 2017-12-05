#include <iostream>
#include <string>
#include <conio.h>
#include "lib\modes.h"
#include "lib\filters.h"
#include "lib\aes.h"

using namespace std;
using namespace CryptoPP;
const int maxsize = 1000;
const string KEY = "fi3mg9su5j1l0dua";
const string apass = "12345";

string usernameInput() {
	char u[17];
	u[0] = '\0';
	char temp;

	cout << "Username: ";
	int i = 0;
	while (1) {
		temp = _getch();
		if (i != 16) {
			if ((temp >= 'a'&&temp <= 'z') || (temp >= 'A'&&temp <= 'Z') || (temp >= '0'&&temp <= '9')) {
				u[i] = temp;
				i++;
				cout << temp;
			}
			if (temp == '\b' && i >= 1) {
				cout << "\b \b";
				i--;
			}
			if (temp == '\r') {
				u[i] = '\0';
				break;
			}

		}
		else if (i == 16) {
			if ((temp >= 'a'&&temp <= 'z') || (temp >= 'A'&&temp <= 'Z') || (temp >= '0'&&temp <= '9')) {

			}
			if (temp == '\b' && i >= 1) {
				cout << "\b \b";
				i--;
			}
			if (temp == '\r') {
				u[i] = '\0';
				break;
			}
		}
	}
	cout << endl;
	string user = u;
	return user;
}

string passwordInput() {
	char p[17];
	p[0] = '\0';
	char temp;
	cout << "Password: ";
	int i = 0;
	while (1) {
		temp = _getch();
		if (i != 16) {
			if ((temp >= 'a'&&temp <= 'z') || (temp >= 'A'&&temp <= 'Z') || (temp >= '0'&&temp <= '9')) {
				p[i] = temp;
				i++;
				cout << "*";
			}
			if (temp == '\b' && i >= 1) {
				cout << "\b \b";
				i--;
			}
			if (temp == '\r') {
				p[i] = '\0';
				break;
			}

		}
		else if (i == 16) {
			if ((temp >= 'a'&&temp <= 'z') || (temp >= 'A'&&temp <= 'Z') || (temp >= '0'&&temp <= '9')) {

			}
			if (temp == '\b' && i >= 1) {
				cout << "\b \b";
				i--;
			}
			if (temp == '\r') {
				p[i] = '\0';
				break;
			}
		}
	}
	cout << endl;
	string pass = p;
	return pass;

}

string dataInput() {
	char d[51];
	d[0] = '\0';
	char temp;

	int i = 0;
	while (1) {
		temp = _getch();
		if (i != 50) {
			if (temp >= 32 && temp <= 126) {
				d[i] = temp;
				i++;
				cout << temp;
			}
			if (temp == '\b' && i >= 1) {
				cout << "\b \b";
				i--;
			}
			if (temp == '\r') {
				d[i] = '\0';
				break;
			}

		}
		else if (i == 50) {
			if (temp >= 32 && temp <= 126) {

			}
			if (temp == '\b' && i >= 1) {
				cout << "\b \b";
				i--;
			}
			if (temp == '\r') {
				d[i] = '\0';
				break;
			}
		}
	}
	cout << endl;
	string data = d;
	return data;
}

string Encrypt(string in) {
	byte key[16];
	byte iv[16];
	for (int i = 0; i < 16; i++) {
		key[i] = KEY[i];
		iv[i] = KEY[i];
	}
	string output;
	CTR_Mode<AES>::Encryption encrypt((const byte*)key, AES::DEFAULT_KEYLENGTH, (const byte*)iv);
	StringSource(in, true, new StreamTransformationFilter(encrypt, new StringSink(output)));
	return output;
}

string Decrypt(string in) {
	byte key[16];
	byte iv[16];
	for (int i = 0; i < 16; i++) {
		key[i] = KEY[i];
		iv[i] = KEY[i];
	}

	string output;
	CTR_Mode<AES>::Decryption decrypt((const byte*)key, AES::DEFAULT_KEYLENGTH, (const byte*)iv);
	StringSource(in, true, new StreamTransformationFilter(decrypt, new StringSink(output)));
	return output;

}

struct user {
	user(string u = "", string p = "", string d = "") {
		username = u;
		password = p;
		data = d;
	}
	
	string username;
	string password;
	string data;
};

class AESHashTable {
private:
	struct Node {
		user user;
		Node* Next;
	};
	Node* userlist[maxsize];
	int usercount = 0;
public:
	AESHashTable() {
		for (int i = 0; i < maxsize; i++) {
			userlist[i] = NULL;
		}
	}
	int hash(string code) { //hash function
		int value = 1;
		
		for (unsigned int i = 0; i < code.size(); i++) {
			value = value * int(code[i]);
		}
		value = value % maxsize;
		if (value < 0) {
			value += maxsize;
		}
	
		return value;
	}
	void createAccount(user u) { //insert
		u.username = Encrypt(u.username); 
		u.password = Encrypt(u.password);
		int index = hash(u.username);
		
		Node *node = new Node;
		node->user = u;
		node->Next = userlist[index];
		userlist[index] = node;
	
		usercount++;
	}
		
	void viewdata(string u) {
		u = Encrypt(u);
		int index = hash(u);
		bool found = false;
		if (userlist[index] == NULL) {
			cout << endl;
			cout << "User not found. " << endl;
			cout << endl;
			system("PAUSE>NUL");
			return;
		}
		Node *curr = userlist[index];

		while (u != curr->user.username || found == false) {
			if (curr->user.username == u) {
				found = true;
			}
			else {
				if (curr->Next != NULL) {
					curr = curr->Next;
				}
				else if (curr->Next == NULL && found == false) {
					break;
				}
			}

		}

		if (found == true) {
			cout << endl;
			cout << "Username: " << curr->user.username << endl;
			cout << "Password: " << curr->user.password << endl;
			cout << "Data: " << curr->user.data << endl;
			cout << endl;
			system("PAUSE>NUL");
		}
		else {
			cout << endl;
			cout << "User not found. " << endl;
			system("PAUSE>NUL");
		}
	}

	void hashlogin(string u, string p) {
		u = Encrypt(u);
		p = Encrypt(p);
		int index = hash(u);
		bool found = false;
		if (userlist[index] == NULL) {
			cout << endl;
			cout << "Incorrect username or password." << endl;
			cout << endl;
			system("PAUSE>NUL");
			return;
		}
		Node *curr = userlist[index];
		
		while (u != curr->user.username || found == false ) {
			if (curr->user.username == u) {
				found = true;
			}
			else {	
				if (curr->Next != NULL) {
				curr = curr->Next;
			}
				else if (curr->Next == NULL && found == false) {
					break;
			}
		}
			
		}
	
	
		if (found==true) {
			if (curr->user.password == p) {
				u = Decrypt(u);
				system("CLS");
				cout << endl;
				cout << "Welcome " << u << "!" << endl;
				system("PAUSE>NUL");
				int m = 0;
				while (1) {
					m = 0;
					system("CLS");
					cout << "USER MENU" << endl;
					cout << "1. View Data." << endl;
					cout << "2. Edit Data." << endl;
					cout << "3. Logout." << endl;
					cin >> m;
					if (m == 1) {
						cout << endl;
						cout << "YOUR DATA: " << endl;
						string d = curr->user.data;
						d = Decrypt(d);
						cout << d << endl;
						cout << endl;
						system("PAUSE>NUL");
					}
					else if (m == 2) {
						cout << endl;
						cout << "Enter new data (This will overwrite old data): ";
						string buff = dataInput();
						buff = Encrypt(buff);
						curr->user.data = buff;
						cout << "Data Saved!" << endl;
						cout << endl;
						system("PAUSE>NUL");
					}
					else if (m == 3) {
						cout << endl;
						cout << "Goodbye" << endl;
						system("PAUSE>NUL");
						break;
					}

				}
			}
			else if (curr->user.password != p) {
				cout << endl;
				cout << "Incorrect username or password." << endl;
				cout << endl;
				system("PAUSE>NUL");
			}
		}
		else {
			cout << endl;
			cout << "Incorrect username or password. " << endl;
			cout << endl;
			system("PAUSE>NUL");
		}
	}
};


int main() {

	AESHashTable t;
	system("CLS");
	cout << endl;
	cout << "Welcome to Datasafe!" << endl;
	cout << endl;
	system("PAUSE>NUL");
	int m = 0;
	while (1) {
		m = 0;
		system("CLS");
		cout << "MAIN MENU: " << endl;
		cout << "1. Login" << endl;
		cout << "2. Create Account" << endl;
		cout << "3. Admin Login" << endl;
		cout << "4. Quit" << endl;
		cin >> m;
		if (m == 1) {
			string u = usernameInput();
			string p = passwordInput();
			t.hashlogin(u, p);
		}
		else if (m == 2) {
			string u1, p1, p2;
			cout << endl;
			u1 = usernameInput();
			cout << endl;
			cout << "Enter password twice to confirm" << endl;
			p1 = passwordInput();	
			p2 = passwordInput();
			if (p1 == p2) {
				t.createAccount(user(u1, p1, ""));
				cout << "Account Registered! " << endl;
				system("PAUSE>NUL");
			}
			else if (p1 != p2) {
				cout << endl;
				cout << "Passwords do not match!" << endl;
				cout << endl;
				system("PAUSE>NUL");
			}
			
		}
		else if (m == 3) {
			string ap;
			ap = passwordInput();
			if (ap == apass) {
				system("CLS");
				cout << "ADMIN MODE" << endl;
				cout << endl;
				cout << "Enter username to view raw data" << endl;
				string u3;
				cin >> u3;
				t.viewdata(u3);
			}
			else if (ap != apass) {
				cout << endl;
				cout << "Access Denied" << endl;
				system("PAUSE>NUL");
			}


		}
		else if (m == 4) {
			break;
		}
	}


	return 0;
}	
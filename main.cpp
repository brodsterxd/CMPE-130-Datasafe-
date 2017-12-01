#include <iostream>
#include <string>
#include <conio.h>
#include "lib\modes.h"
#include "lib\filters.h"
#include "lib\aes.h"
using namespace std;
using namespace CryptoPP;
const int maxsize = 1000;

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
		//hash function multiplies together the ascii codes for more unique hashes and a lower chance of collisions
		for (unsigned int i = 0; i < code.size(); i++) {
			value = value * int(code[i]);
		}
		value = value % maxsize;
		if (value < 0) {
			value += maxsize;
		}
		int l;
		return value;
	}
	void createAccount(user u) { //insert
		int index = hash(u.username);
		
		Node *node = new Node;
		node->user = u;
		node->Next = userlist[index];
		userlist[index] = node;
		
		usercount++;
	}
		
	void hashlogin(string u, string p) {
		int index = hash(u);
		Node *curr = userlist[index];
		bool found = false;
		while (u != curr->user.username || found == false ) {
			if (curr->user.username == u) {
				found = true;
			}
			else {
			curr = curr->Next;
			if (curr->Next == NULL && found == false) {
				break;
			}
		}

		}
		if (found) {
			cout << "Hello " << u << "!" << endl;
			cout << "found at index: " << index << endl;
		}
		else {
			cout << "User not found, please register. " << endl;
		}
	}
};

void login() {
	char u[16];
	char p[16];
	u[0] = '\0';//pass
	p[0] = '\0';
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
	cout << "Password: ";
	i = 0;
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
	cout << u << endl;
	cout << p << endl;
}
void registerAccount() {

}

int main() {

	cout << "test" << endl;
	//login();
	AESHashTable t;
	t.createAccount(user("weeee", "ayyy", "data tho"));
	t.createAccount(user("weeee", "ayy343y", "da33ta tho"));
	t.createAccount(user("weee3e", "ayyy", "data tho"));

	t.hashlogin("weeee", "ayyy");

		string plaintext = "ENCRYPT AND DECRYPT MY ASSS"; // encryp this

	cout << plaintext << endl;
	string KEY = "nguigmyy5treytyertjyertyyeyjterytjrejyrtyjwrteywejyy";
	byte key[16];
	byte iv[16];
	for (int i = 0; i < 16; i++) {
		key[i] = KEY[i];
		iv[i] = KEY[i];
	}

	string output;
	CTR_Mode<AES>::Encryption encrypt((const byte*)key, AES::DEFAULT_KEYLENGTH, (const byte*)iv);
	StringSource(plaintext, true, new StreamTransformationFilter(encrypt, new StringSink(output)));
	cout << "Encrypted: " << output << endl;

	for (int i = 0; i < output.size(); i++) {
		cout << int(output[i]) << endl;
	}

	string res;
	CTR_Mode<AES>::Decryption decrypt((const byte*)key, AES::DEFAULT_KEYLENGTH, (const byte*)iv);
	StringSource(output, true, new StreamTransformationFilter(decrypt, new StringSink(res)));
	cout << "Decrypted: " << res << endl;
	cin.get();


	cin.get();
	return 0;
}	
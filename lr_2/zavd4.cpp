#include <iostream>
#include <cstring>
#define MAX_SIZE 40
using namespace std;


class Card{
	char title[MAX_SIZE];
	char author[MAX_SIZE];
	unsigned given;
public:
	void store(const char* title, const char* author, unsigned given);
	void show();
};

void Card::store(const char* title, const char* author, unsigned given){
	if((strlen(title) >= MAX_SIZE) || (strlen(author)>= MAX_SIZE)){
		cout << "ERROR: Card wasn't created. The maximum size for strings is " << MAX_SIZE << endl;
		return;
	}
	strcpy(this->title, title);
	strcpy(this->author, author);
	this->given = given;
}

void Card::show(){
	cout << "Book title: " << title << "\n\t" << "Author: " << author << "\n\t\t" 
		<< "copies given: " << given << endl;
}	


int main(void){
	Card book1, book2;
	book1.store("1984", "George Orwell", 11);
	book2.store("Brave New World", "Aldous Huxley", 5);
	book1.show();
	book2.show();
	return 0;
}
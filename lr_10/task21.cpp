#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#define SIZE 40

class inventory {
    char item[SIZE]{}; // name of item
    int onhand{}; // number on hand
    double cost{}; // cost of item
public:
    inventory(const char *i, int o, double c) {
        strcpy(item, i);
        onhand = o;
        cost = c;
    }
    void store(ofstream &stream);
    void retrieve(ifstream &stream, int index);
    friend ostream &operator <<(ostream &stream, inventory obj);
    friend istream &operator >>(istream &stream, inventory &obj);
};

ostream &operator <<(ostream &stream, inventory obj) {
    stream << obj.item << ": " << obj.onhand;
    stream << " on hand at $" << obj.cost << '\n';
    return stream;
}
istream &operator >>(istream &stream, inventory &obj) {
    cout << "Enter item name: ";
    stream.getline(obj.item, SIZE-1);
    cout << "Enter number on hand: ";
    stream >> obj.onhand;
    cout << "Enter cost: ";
    stream >> obj.cost;
    stream.get();
    return stream;
}

void inventory::store(ofstream &stream){
    stream.write(item, sizeof(item));
    stream.write((char *)&onhand, sizeof(onhand));
    stream.write((char *)&cost, sizeof(cost));
}

void inventory::retrieve(ifstream &stream, int index){
    int indent = index * (sizeof(item) + sizeof(onhand) + sizeof(cost));
    stream.seekg(indent, stream.beg);
    stream.read(item, sizeof(item));
    stream.read((char *)&onhand, sizeof(onhand));
    stream.read((char *)&cost, sizeof(cost));
}

int main(){
    inventory obj("", 0, 0);
    ofstream fout("inventory.txt", ios::out | ios::binary);
    if(!fout)
        exit(1);
    cin >> obj;
    obj.store(fout);
    cin >> obj;
    obj.store(fout);
    cin >> obj;
    obj.store(fout);
    fout.close();
    ifstream fin("inventory.txt", ios::in | ios::binary);
    if(!fin)
        exit(1);
    cout << "\nlooking for an item with index = 1:" << endl; 
    obj.retrieve(fin, 1);
    cout << obj;
    return 0;
}
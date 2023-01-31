#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;

class HashTable {
private:
    string* t;
    int capacity;
    int size;
public:
    HashTable(int c);                //konstruktor tworz�cy pust� tablic� o pojemno�ci c
    bool empty();
    bool full();
    int hashFunction(string s);        //funkcja haszuj�ca dla klucza s
    int insert(string s);            //wstawienie klucza s (zwraca liczb� pr�b przy wyst�pieniu kolizji - 0 je�li kolizja nie wyst�pi�a)
    void traverse();
    void del(string s);                //usuwa element z kluczem s
    string search(string s);        //wyszukuje i zwraca s
    int search1(string s);            //wyszukuje s i zwraca liczb� pr�b przy wyst�pieniu kolizji - 0 je�li kolizja nie wyst�pi�a
    //friend ostream& operator<<(ostream& out, HashTable& ht); //wypisuje tablic� (z numerami p�l), pozostawia puste dla wolnych p�l
};

HashTable::HashTable(int c) { //konstruktor tworz�cy pust� tablic� o pojemno�ci c
    capacity = c;
    t = new string[capacity];
    size = 0;
    for (int i = 0; i < capacity; i++)
        t[i] = "";
}

bool HashTable::empty() {
    if (size == 0) return true;
    return false;
}

bool HashTable::full() {
    if (size == capacity) return true;
    return false;
}

int HashTable::hashFunction(string s) {        //funkcja haszuj�ca dla klucza s
    int hash = 0;

    for (int i = 0; i < s.size(); i++)
        hash = hash * 10 + (int)s[i] % capacity;

    return hash % capacity;
}

int HashTable::insert(string s) {            //wstawienie klucza s (zwraca liczb� pr�b przy wyst�pieniu kolizji - 0 je�li kolizja nie wyst�pi�a)
    int i = 0; //numer pr�by
    int hash = hashFunction(s);
    int temp;

    if (full()) return -1;
    temp = (hash + i) % capacity;

    while (t[temp] != "" && t[temp] != "FREE") {
        i++;
        temp = (hash + i) % capacity;
    }
    t[temp] = s;
    size++;
    return i;

}
void HashTable::traverse() {
    if (!empty())
        for (int i = 0; i < capacity; i++)
            cout << t[i] << " ";
}
void HashTable::del(string s) {                //usuwa element z kluczem s
    int i = 0;

    if (empty()) return;

    int hash = hashFunction(s);
    int temp = (hash + i) % capacity;

    while (t[temp] != "" && i < capacity) {
        if (t[temp] == s) {
            t[temp] = "FREE";
            size--;
            return;
        }
        i++;
        temp = (hash + i) % capacity;
    }

}
string HashTable::search(string s) {        //wyszukuje i zwraca s
    int i = 0;

    if (empty()) return "\0";

    int hash = hashFunction(s);
    int temp = (hash + i) % capacity;

    while (t[temp] != "" && i < capacity) {
        if (t[temp] == s) return t[temp];
        i++;
        temp = (hash + i) % capacity;
    }
    return "NULL";

}
int HashTable::search1(string s) {      //wyszukuje s i zwraca liczb� pr�b przy wyst�pieniu kolizji - 0 je�li kolizja nie wyst�pi�a
    int i = 0;

    if (empty()) return -1;

    int hash = hashFunction(s);
    int temp = (hash + i) % capacity;

    while (t[temp] != "" && i < capacity) {
        if (t[temp] == s) return i;
        i++;
        temp = (hash + i) % capacity;
    }
    return -1;

}

int main() {
    HashTable* h = new HashTable(8);

    h->insert("2");
    h->insert("4");
    h->insert("8");
    h->insert("16");
    h->insert("12");
    h->traverse();
    cout << endl;
    h->del("12");
    h->traverse();

    cout << endl << h->search("1") << endl;
    cout << endl << h->search1("16") << endl;
    cout << h->hashFunction("c");
}


#include <iostream>
#include <cstring>
using namespace std;

class Book{
private:
    char ISBN[20];
    char naslov[20];
    char avtor [20];
    float cena;
public:
    //isbn, title, author, price, url, size
    Book(const char *i="", const char *n="", const char *a="", const float c=0){
        strcpy(ISBN,i);
        strcpy(naslov,n);
        strcpy(avtor,a);
        cena = c;
    }

    //0-312-31677-1: The Moscow Vector, Robert Ludlum 7
    friend ostream &operator<<(ostream &out,Book &bb){
        out<<bb.ISBN<<": "<<bb.naslov<<", "<<bb.avtor<<" "<<bb.bookPrice()<<endl;
        return out;
    }
    bool operator>(Book &bb){
        return cena>bb.cena;
    }
     void setISBN(char *x){
         strcpy(ISBN,x);
         }
    virtual float getCena(){
       return cena;
   }
    virtual float bookPrice()=0;
};
//OnlineBook(isbn, title, author, price, url, size);
class OnlineBook : public Book{
private:
    char *url;
    int size;
public:
    OnlineBook(const char *i="", const char *n="", const char *a="", const float c=0, const char *u="", const int s=0):Book(i,n,a,c){
        url = new char [strlen(u)+1];
        strcpy(url,u);
        size=s;
    }
    OnlineBook(const OnlineBook &ob):Book(ob){
        url = new char [strlen(ob.url)+1];
        strcpy(url,ob.url);
        size=ob.size;
    }
    float bookPrice(){
        float total = getCena();
        if(size>20){
            return total * 1.2;
        }else{
            return total;
        }
    }

};
//			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
class PrintBook: public Book{
private:
    float masa;
    bool zaliha;
public:
    PrintBook(const char *i="", const char *n="", const char *a="", const float c=0, const float m=0, const bool s=false):Book(i,n,a,c){
        masa=m;
        zaliha=s;
    }
    float bookPrice(){
        float total = getCena();
        if(masa > 0.7){
            return total * 1.15;
        }
        else{
            return total;
        }
    }

};
void mostExpensiveBook (Book** books, int n){
    int isOnline=0,isPrinted=0;
    int maxi=-99999;
    int indeks = 0;
    for(int i=0; i<n; i++){
            OnlineBook *temp = dynamic_cast<OnlineBook *>(books[i]);
            if(temp!=0){
                isOnline++;
            }
            PrintBook *temp2 = dynamic_cast<PrintBook *>(books[i]);
            if(temp2!=0){
                isPrinted++;
            }
    }
    cout << "Total number of online books: " << isOnline << endl;
    cout << "Total number of print books: " << isPrinted << endl;
    for(int i=0; i<n; i++){

        if(books[i]->bookPrice()>maxi){
            maxi=books[i]->bookPrice();
            indeks = i;
        }
    }
    cout << "The most expensive book is: " << endl << *books[indeks];

}


int main(){

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;

			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}
        cout << "FINKI-Education" << endl;
		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;

	return 0;
}


#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde
class FudbalskaEkipa {
private:
    char ime_trener[100];
    int golovi[10];
public:
    FudbalskaEkipa(const char *i="", const int *g=0) {
        strcpy(ime_trener,i);
        for(int i=0; i<10; i++) {
            golovi[i]=g[i];
        }
    }
    char *getTrener() {
        return ime_trener;
    }
    virtual char *getIme()=0;



    FudbalskaEkipa &operator+=(int g){
        for(int i=0; i<9; i++){
            golovi[i]=golovi[i+1];
        }
        golovi[9]=g;
        return *this;


    }


    int Suma() {
        int total=0;
        for(int i=0; i<10; i++) {
            total+=golovi[i];
        }
        return total;
    }
    friend ostream &operator << (ostream &out, FudbalskaEkipa &fk) {
        out<<fk.getIme()<<endl;
        out<<fk.ime_trener<<endl;
        out<<fk.uspeh()<<endl;
        return out;
    }

    virtual int uspeh()=0;
};
class Klub: public FudbalskaEkipa {
    char klub_ime[100];
    int tituli;
public:
    Klub(const char *i="", const int *g=0, const char *x="", const int tg=0):FudbalskaEkipa(i,g) {
        strcpy(klub_ime,x);
        tituli=tg;
    }
    int uspeh() {
        int vkupno=0;
        vkupno=(Suma()*3)+(tituli*1000);
        return vkupno;
    }
    bool operator > ( Klub &kk) {
        return uspeh()>kk.uspeh();
    }
    char *getIme() {
        return klub_ime;
    }






};
class Reprezentacija: public FudbalskaEkipa {
    char zemja_ime[100];
    int nastapi;
public:
    Reprezentacija(const char *i="",int *g=0, const char *x="",  int tg=0):FudbalskaEkipa(i,g) {
        strcpy(zemja_ime,x);
        nastapi=tg;
    }
    int uspeh() {
        int vkupno=0;
        vkupno=(Suma()*3)+(nastapi*50);
        return vkupno;
    }
    bool operator > ( Reprezentacija &rr) {
        return uspeh()>rr.uspeh();
    }
    char *getIme() {
        return zemja_ime;
    }

};
void najdobarTrener(FudbalskaEkipa **ekipi, int n) {
    int maxi=-99999;
    int indeks=0;
    for(int i=0; i<n; i++) {
        if(ekipi[i]->uspeh()>maxi) {
            maxi=ekipi[i]->uspeh();
            indeks=i;
        }

    }
    cout<<*ekipi[indeks]<<endl;
}


int main() {

    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;

    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }

    }
//   Klub k("asd",goals,"zxc",3);
    //     cout<<k;
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;

    return 0;
}

#include <iostream>
#include <cstring>
using namespace std;

class Exception{
private:
public:
    Exception(){}
};
class Trud{
protected:
    char tip;
    int godinaTr;
public:
    Trud(){}
    Trud(char t, int g){
        tip = t;
        godinaTr = g;
    }
    Trud &operator =(Trud &t){
        if(this != &t){
            tip = t.tip;
            godinaTr = t.godinaTr;
        }
        return *this;
    }
    friend istream &operator >>(istream &in, Trud &t){
        in>>t.tip>>t.godinaTr;
        return in;
    }
    int getGod(){
        return godinaTr;
    }
    char getTip(){
        return tip;
    }
};

class Student{
protected:
    char ime[31];
    int index;
    int godinaUp;
    int polozeni[50];
    int brPolozeni;
public:
    Student(char * ime, int index, int godinaUp, int polozeni[], int brPolozeni){
        strcpy(this->ime, ime);
        this->index = index;
        this->godinaUp = godinaUp;
        this->brPolozeni = brPolozeni;
        for(int i=0; i<brPolozeni; i++)this->polozeni[i] = polozeni[i];
    }
    int getIndex(){
        return index;
    }
    virtual double rang(){
        double suma = 0;
        for(int i=0; i<brPolozeni; i++)suma+= polozeni[i];

        return suma/brPolozeni;
    }
    friend ostream &operator << (ostream &out, Student &p){
        out<<p.index<<" "<<p.ime<<" "<<p.godinaUp<<" "<<p.rang()<<endl;
        return out;
    }
    virtual Student &operator +=(Trud &t){
        cout<<"Ne postoi PhD student so indeks "<<this->index<<endl;
        return *this;
    }
};

class PhDStudent:public Student{
private:
    Trud *trudovi;
    int brTrudovi;
    static int poeniKonf;
    static int poeniSpisanie;
public:
    PhDStudent(char * ime, int index, int godinaUp, int polozeni[], int brPolozeni, Trud *t, int brTr):Student(ime, index, godinaUp, polozeni, brPolozeni){
        this->brTrudovi = brTr;
        trudovi = new Trud[brTr];
        for(int i=0; i<brTr; i++){
            try{
                if(t[i].getGod() < this->godinaUp)throw Exception();
                trudovi[i] = t[i];
            }catch(Exception &p){
                cout<<"Ne moze da se vnese dadeniot trud"<<endl;
            }
        }
    }
    Student &operator +=(Trud &t){
        if(t.getGod() < this->godinaUp)throw Exception();
        Trud * temp = trudovi;
        //delete [] trudovi;
        trudovi = new Trud[brTrudovi + 1];

        for(int i=0; i<brTrudovi; i++)trudovi[i] = temp[i];
        trudovi[brTrudovi] = t;
        brTrudovi++;
        //for(int i=0; i<brTrudovi; i++)cout<<" ["<<i<<"->"<<trudovi[i].getTip()<<"]";
        return *this;
    }
    double rang(){
        double vrati = Student::rang();
        for(int i=0; i<brTrudovi; i++){
            char tip = trudovi[i].getTip();
            if(tip == 'c' || tip == 'C') vrati += PhDStudent::poeniKonf;
            if(tip == 'j' || tip == 'J') vrati += PhDStudent::poeniSpisanie;
        }
        return vrati;
    }
    void static setKonf(int i){
        PhDStudent::poeniKonf = i;
    }
    void static setSpisanie(int i){
        PhDStudent::poeniSpisanie = i;
    }


};
int PhDStudent::poeniKonf = 1;
int PhDStudent::poeniSpisanie = 3;


int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        for(int i=0; i<m; i++){
            if(niza[i]->getIndex() == indeks)*niza[i]+=t;
        }

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2

        for(int i=0; i<m; i++){
            if(niza[i]->getIndex() == indeks){*niza[i]+=t;}
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;



    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        try{
            for(int i=0; i<m; i++){
                if(niza[i]->getIndex() == indeks)*niza[i]+=t;
            }
        }catch(Exception &p){
            cout<<"Ne moze da se vnese dadeniot trud"<<endl;
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setKonf(conf);
        PhDStudent::setSpisanie(journal);
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }



    return 0;
}

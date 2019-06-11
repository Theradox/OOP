#include<iostream>
#include<string.h>
using namespace std;

class Delo{
private:
    char ime[50];
    int godina;
    char zemja[50];
public:
    Delo(const char *ime2="", const int godina2=0, const char *zemja2=""){
        strcpy(ime,ime2);
        godina=godina2;
        strcpy(zemja,zemja2);
    }
    // getters
    char *getIme(){ return ime; }
    char *getZemja(){ return zemja; }
    int getGodina(){ return godina; }
    // setters
    void  setIme(char *x){ strcpy(ime,x); }
    void  setZemja(char *x){ strcpy(zemja,x); }
    void  setGodina(int x){ godina=x; }
    bool operator==(Delo &dd){
        if(strcmp(getIme(),dd.getIme())==0){
            return true;
        }
        else{
            return false;
        }
    }

};
class Pretstava{
private:
    Delo d;
    int brojProdadeni;
    char data[15];
public:
    int getProdadeni(){return brojProdadeni;}
    Delo getDelo(){ return d;}
    Pretstava(Delo dd=0,const int brojProdadeni2=0,const char *data2=""){
        strcpy(data,data2);
        brojProdadeni=brojProdadeni2;
        d=dd;
    }
    virtual int cena(){
    //cena = M + N;
    int M=0,N=0;
    {
        if(d.getGodina()>=1900){
            M=50;
        }
        else if(d.getGodina()>=1800&&d.getGodina()<1900){
            M=75;
        }
        else{
            M=100;
        }
    }
    //SEGA ZA N

        if(strcmp(d.getZemja(),"Italija")==0){
            N=100;
        }
        else if (strcmp(d.getZemja(),"Rusija")==0){
            N=150;
        }
        else{
            N=80;
        }

    return M+N;

}
};
class Opera:public Pretstava{
private:

public:
    Opera(Delo dd=0,const int brojProdadeni2=0,const char *data2=""):Pretstava(dd,brojProdadeni2,data2){
    }
};
class Balet:public Pretstava{
private:
    static int atribut;
public:
    Balet(Delo dd=0,const int brojProdadeni2=0,const char *data2=""):Pretstava(dd,brojProdadeni2,data2){
    }
    //get
    static int getAtribut() { return atribut;}
    static void setCenaBalet(int x){atribut=x;}
    int cena(){
        int total =0;
        total +=Pretstava::cena();
        return getAtribut()+total;

    }
};
int Balet::atribut = 150;

int prihod(Pretstava **pole, int n){
    int totalSum=0;
    for(int i=0;i<n;i++){
        totalSum+=pole[i]->cena() * pole[i]->getProdadeni();
    }
    return totalSum;

}

//brojPretstaviNaDelo(pole,n,f);
int brojPretstaviNaDelo(Pretstava **pole, int n,Delo d){
    int counter=0;
    for(int i=0;i<n;i++){
        if(pole[i]->getDelo()==d){
            counter++;
        }
    }
    return counter;
}




//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){

    int test_case;
    cin>>test_case;

    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;

    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;

    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();

        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

    }break;

    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();

        }
        cout<<prihod(pole,n);
    }break;

    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;

    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }

        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;

    };


return 0;
}

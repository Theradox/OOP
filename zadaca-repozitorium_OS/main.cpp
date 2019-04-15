#include <iostream>
#include<string.h>
using namespace std;
enum Tip{LINUX,UNIX,WINDOWS};
class OperativenSistem{
//        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
private:
    char *ime;
    float verzija;
    Tip tip;
    float golemina;
public:
    OperativenSistem(){}
    OperativenSistem(char *i,float v,Tip tip, float g){
    ime=new char[strlen(i)+1];
    strcpy(ime,i);
    verzija=v;
    this->tip=tip;
    golemina=g;
    }
    OperativenSistem(const OperativenSistem &os){

    ime=new char[strlen(os.ime)+1];
    strcpy(ime,os.ime);
    verzija=os.verzija;
    this->tip=os.tip;
    golemina=os.golemina;

    }

    OperativenSistem &operator=(const OperativenSistem &os){
        if(this!=&os){
            ime=new char[strlen(os.ime)+1];
    strcpy(ime,os.ime);
    verzija=os.verzija;
    this->tip=os.tip;
    golemina=os.golemina;
        }
        return *this;
    }
    void pecati(){
    //Ime: Ubuntu Verzija: 16.04 Tip: 1 Golemina:1.25GB
    cout<<"Ime: "<<ime<<" "<<"Verzija: "<<verzija<<" "<<"Tip: "<<tip<<" "<<"Golemina:"<<golemina<<"GB"<<endl;
    }


    bool ednakviSe(const OperativenSistem &os){
    return strcmp(ime,os.ime)==0 && verzija==os.verzija && tip==os.tip && golemina==os.golemina;
    }

    int sporediVerzija(const OperativenSistem &os){

    if(verzija==os.verzija){
        return 0;
    }
    else if (verzija <os.verzija){
        return -1;
    }
    else{
        return 1;
    }
}

    bool istaFamilija(const OperativenSistem &sporedba){

    return strcmp(ime,sporedba.ime)==0 && tip==sporedba.tip;
    }
    ~OperativenSistem(){delete[] ime;}
};

class Repozitorium{

//    Repozitorium repozitorium=Repozitorium(repoName);
private:
    char ime[20];
    OperativenSistem *operativni_sistemi;
    int br_os;
public:
    Repozitorium(){}
    Repozitorium(const char *ime){
    strcpy(this->ime,ime);
    br_os=0;
    operativni_sistemi=new OperativenSistem[br_os];
    }

    void pecatiOperativniSistemi(){
        cout<<"Repozitorium: "<<ime<<endl;
        for(int i=0;i<br_os;i++){
            operativni_sistemi[i].pecati();
        }
    }
    void dodadi(const OperativenSistem &nov){
        int flag =0;

        for(int i=0;i<br_os;i++){
            if((operativni_sistemi[i].istaFamilija(nov)==true)&&(operativni_sistemi[i].sporediVerzija(nov) == -1)){
                operativni_sistemi[i] = nov;
                flag =1;
                break;
            }
        }

        if(flag ==0){
            OperativenSistem *temp = new OperativenSistem[br_os+1];
            for(int i=0;i<br_os;i++){
                temp[i]=operativni_sistemi[i];
            }
            temp[br_os++]=nov;
            delete[] operativni_sistemi;
            operativni_sistemi=temp;
        }
    }

    void izbrishi(const OperativenSistem &operativenSistem){
    int newBr=0;
    for(int i=0,j=0;i<br_os;i++){
        if(operativni_sistemi[i].ednakviSe(operativenSistem)==false){
            operativni_sistemi[j++]=operativni_sistemi[i];
            newBr++;
        }
    }
    br_os=newBr;
    }

    ~Repozitorium(){delete[] operativni_sistemi;}

};


int main() {

    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
     cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();

    return 0;
}

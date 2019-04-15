#include <iostream>
#include<string.h>

using namespace std;

class List{
private:
    int *niza;
    int br_broevi;
public:
    List(){br_broevi=0;}

    List(int *niza, int n){
        br_broevi=n;
        for(int i=0;i<br_broevi;i++){
            this->niza[i]=niza[i];
            }
    }

    List(const List &li){
        br_broevi=li.br_broevi;
        for(int i=0;i<br_broevi;i++){
                this->niza[i]=li.niza[i];
                }
    }

    List &operator=(const List &li){
        if(this!=&li){
            br_broevi=li.br_broevi;
            delete[]niza;
            for(int i=0;i<br_broevi;i++){
                this->niza[i]=li.niza[i];
            }
        }
        return *this;
    }

    int sum(){
    int brNew=0;
    for(int i=0;i<br_broevi;i++){
        brNew+=niza[i];
    }
    return brNew;
    }
    double average(){
        return sum()/br_broevi;
    }
    void pecati(){
        for(int i=0;i<br_broevi;i++){
            cout<<"List Info: "<<br_broevi<<": "<<niza[i]<<"sum: "<<sum()<<" "<<"average: "<<average()<<endl;
        }
    }
    ~List(){delete[]niza;}
};


class ListContainer{
private:
    List *lista;
    int br_el;
    int br_obidi;
public:
    ListContainer(){br_obidi=0;br_el=0;lista=new List[br_el];}
    ListContainer(List *lista, int br_el, int br_obidi){
    this->br_el=br_el;
    this->br_obidi=br_obidi;
    this->lista = new List[br_el];
    for(int i=0;i<br_el;i++){
        this->lista[i]=lista[i];
    }
}
    ListContainer(const ListContainer &lc){
    this->br_el=lc.br_el;
    this->br_obidi=lc.br_obidi;
    this->lista = new List[br_el];
    for(int i=0;i<br_el;i++){
        this->lista[i]=lc.lista[i];
    }
}
    ListContainer &operator=(const ListContainer &lc){
    if(this!=&lc){
        this->br_el=lc.br_el;
        this->br_obidi=lc.br_obidi;
        this->lista = new List[br_el];
        for(int i=0;i<br_el;i++){
            this->lista[i]=lc.lista[i];
        }
    }
    return *this;
}
    int sum(){
        int suma=0;
        for(int i=0;i<br_el;i++){
                suma+=lista[i].sum();
        }
        return suma;
    }
    double average(){
        double prosek=0;
        for(int i=0;i<br_el;i++){
            prosek+=lista[i].average();
        }
        return sum()/prosek;
    }

    void addNewList(List nova){
    List *temp = new List[br_el+1];
    br_obidi++;
    for(int i=0;i<br_el-1;i++){
        for(int j=1;j<br_el;j++){
            if((lista[i].sum())!=(nova.sum())){
                for(int i=0;i<br_el;i++){
        temp[i]=lista[i];
    }
    temp[br_el++]=nova;
    delete[]lista;
    lista=temp;
            }
        }


    }




    }

    void print(){
    for(int i=0;i<br_el;i++){
        cout<<"List number: "<<i;
        lista[i].pecati();
    }
    cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;

    }


    ~ListContainer(){delete[]lista;}
};














int main() {
	/*
	ListContainer lc;
	int N;
	cin>>N;

	for (int i=0;i<N;i++) {
		int n;
		int niza[100];

		cin>>n;

		for (int j=0;j<n;j++){
			cin>>niza[j];

		}

		List l=List(niza,n);

		lc.addNewList(l);
	}


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }*/
    return 0;
}

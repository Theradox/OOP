#include <iostream>
#include <cstring>

using namespace std;

// vashiot kod ovde

class Vozac{
char ime[100];
int vozrast;
int broj_trki;
bool vet;
public:
    Vozac(const char *i="",const int v=0, const int br=0,bool vet=false){
        strcpy(ime,i);
        vozrast=v;
        broj_trki=br;
        this->vet=vet;
    }
    friend ostream &operator<<(ostream &out, Vozac &vv){
    //ime vozrast brtrki vet
        out<<vv.ime<<endl<<vv.vozrast<<endl<<vv.broj_trki<<endl;
        if(vv.vet==true){
            out<<"VETERAN"<<endl;
        }
        return out;
    }
    virtual float zarabotuvacka()=0;
    virtual float danok()=0;

    bool operator==(Vozac &vv){
        return zarabotuvacka()==vv.zarabotuvacka();
    }
    int getTrki(){ return broj_trki; }
    bool getVet(){ return vet; }
    virtual ~Vozac(){}
};
class Avtomobilist : public Vozac{
float cena_kola;
public:
    Avtomobilist(const char *i="",const int v=0, const int br=0,bool vet=false, const float cena=0.0):Vozac(i,v,br,vet){
        cena_kola=cena;
    }
    float getCena(){return cena_kola;}
    float zarabotuvacka(){
        return getCena()/5;
    }
    float danok(){
        if(getTrki()>10){
            return zarabotuvacka()*0.15;
        }
        else{
            return zarabotuvacka()*0.10;
        }
    }

};

class Motociklist : public Vozac{
int mokjnost;
public:
    Motociklist(const char *i="",const int v=0, const int br=0,bool vet=false, const float mokjnost=0.0):Vozac(i,v,br,vet){
        this->mokjnost=mokjnost;
    }
    float getMokjnost(){return mokjnost;}
    float zarabotuvacka(){
        return getMokjnost()*20;
    }
    float danok(){
        if(getVet()==true){
            return zarabotuvacka()*0.25;
        }
        else{
            return zarabotuvacka()*0.20;
        }
    }

};

int soIstaZarabotuvachka(Vozac **vv, int n, Vozac *v){
    int total=0;
    for(int i=0; i<n; i++){
        if(*vv[i]==*v){
            total++;
        }
    }

    return total;

}




int main() {


	int n, x;
	cin >> n >> x;
	Vozac **v = new Vozac*[n];
	char ime[100];
	int vozrast;
	int trki;
	bool vet;
	for(int i = 0; i < n; ++i) {
		cin >> ime >> vozrast >> trki >> vet;
		if(i < x) {
			float cena_avto;
			cin >> cena_avto;
			v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
		} else {
			int mokjnost;
			cin >> mokjnost;
			v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
		}
	}
	cout << "=== DANOK ===" << endl;
	for(int i = 0; i < n; ++i) {
		cout << *v[i];
		cout << v[i]->danok() << endl;
	}
	cin >> ime >> vozrast >> trki >> vet;
	int mokjnost;
	cin >> mokjnost;
	Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
	cout << "=== VOZAC X ===" << endl;
	cout << *vx;
	cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
	cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;


	return 0;
}

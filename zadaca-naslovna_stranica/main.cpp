#include<iostream>
#include<cstring>
using namespace std;

            //Category category(categoryName);

class Category{
private:
    char name[20];
public:
    Category(){strcpy(name,"unnamed");}
    Category(char*name){
        strcpy(this->name,name);
    }
    Category &operator=(const Category &cc){
        if(this!=&cc){
            strcpy(this->name,cc.name);
        }
        return *this;
    }
    void print(){
    cout<<"Category: "<<name<<endl;
    }
};
			//NewsArticle article(category, articleTitle);

class NewsArticle{
private:
    Category kategorija;
    char title[30];
public:
    NewsArticle(){strcpy(title,"untitled");}

    NewsArticle(Category kat, char *title){
    kategorija=kat;
    strcpy(this->title,title);
    }

    NewsArticle(const NewsArticle &na){
    kategorija=na.kategorija;
    strcpy(this->title,na.title);
    }
    void print(){
    cout<<"Article Title: "<<title<<endl;
    kategorija.print();
    }


};
class FrontPage{
private:
    NewsArticle article;
    float price;
    int editionNumber;
public:
    			//FrontPage frontPage(article, price, editionNumber);
    FrontPage(){price=0;editionNumber=0;}
    FrontPage(NewsArticle art, float p, int en){
    article=art;
    price=p;
    editionNumber=en;
    }
    void print(){
    cout<<"Price: "<<price<<", "<<"Edition number: "<<editionNumber<<endl;
    article.print();
    }

};



int main() {

	char categoryName[20];
	char articleTitle[30];
	float price;
	int editionNumber;

	int testCase;
	cin >> testCase;


	if (testCase == 1) {
		int iter;
		cin >> iter;
		while (iter > 0) {
			cin >> categoryName;
			cin >> articleTitle;
			cin >> price;
			cin >> editionNumber;
			Category category(categoryName);
			NewsArticle article(category, articleTitle);
			FrontPage frontPage(article, price, editionNumber);
			frontPage.print();
			iter--;
		}
	}
	else if (testCase == 2) {
		cin >> categoryName;
		cin >> price;
		cin >> editionNumber;
		Category category(categoryName);
		NewsArticle article(category,articleTitle);
		FrontPage frontPage(article, price, editionNumber);
		frontPage.print();
	}// test case 3
	else if (testCase == 3) {
		cin >> categoryName;
		cin >> articleTitle;
		cin >> price;
		Category category(categoryName);
		NewsArticle article(category,articleTitle);
		FrontPage frontPage(article, price, editionNumber);
		frontPage.print();
	}
    else {
    	FrontPage frontPage = FrontPage();
        frontPage.print();
    }
	return 0;
}

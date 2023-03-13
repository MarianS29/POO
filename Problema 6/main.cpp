#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <fstream>

using namespace std;

class Card{
private:
    int number;
    string nume_carte;
public:
    Card(int arg_number, string arg_nume){
        number = arg_number;
        nume_carte = arg_nume;
    }
    string getNume(){
        return nume_carte;
    }
    int getNumber(){
        return number;
    }
    void setNumber(int arg_number){
        number = arg_number;
    }
    void setNumeCarte(string arg_numecarte){
        nume_carte = arg_numecarte;
    }
    Card(const Card & altul){
        this->nume_carte = altul.nume_carte;
        this->number = altul.number;
    }
};

class Person {
private:
    bool aPierdut;
    bool areIntre17si21;
    string nume;
    int suma_de_bani;
    vector<Card> Carduri;
public:
    Person(string arg_nume, int arg_suma) {
        nume = arg_nume;
        suma_de_bani = arg_suma;
        aPierdut = false;
        areIntre17si21 = false;
    }

    bool getaPierdut() {
        return aPierdut;
    }

    bool getAreIntre17si21(){
        return areIntre17si21;
    }

    int getSumaDeBani() {
        return suma_de_bani;
    }

    string getPersonName() {
        return nume;
    }

    int getCardsSize() {
        return Carduri.size();
    }

    Card getCard(int position) {
        return Carduri[position];
    }

    void setaPierdut(bool arg_aPierdut) {
        aPierdut = arg_aPierdut;
    }

    void setAreIntre17si21(bool arg_areintre17si21){
        areIntre17si21 = arg_areintre17si21;
    }

    void setSumaDeBani(int suma) {
        suma_de_bani = suma;
    }

    void addCard(Card temp) {
        Carduri.push_back(temp);
    }
    void Clear(){
        Carduri.clear();
    }

    int getCardsSum() {
        int sum = 0;
        for (int i = 0; i < Carduri.size(); i++) {
            sum += Carduri[i].getNumber();
        }
        return sum;
    }
};

void ShuffleCards(vector<Card> & pachet, int a1, int c1, int x1, int a2, int c2, int x2) {
    uint8_t m = pachet.size(), index1, index2;
    for (uint8_t i = 0; i < 50; i++) {
        index1 = (a1 * x1 + c1) % m;
        index2 = (a2 * x2 + c2) % m;
        Card temp = pachet[index1];
        pachet[index1].setNumber(pachet[index2].getNumber());
        pachet[index1].setNumeCarte(pachet[index2].getNume());
        pachet[index2].setNumber(temp.getNumber());
        pachet[index2].setNumeCarte(temp.getNume());
        x1 = index1;
        x2 = index2;
    }
}

int main() {
    string commanda;
    cin>>commanda;
    int number;
    string tip_carte;
    char c;
    if(commanda == "check_cards"){
        set<pair<int,string>> carti_de_joculet;
        int masluit=0;
        while(cin>>number>>c>>tip_carte)
            if(number>=2 && number<=14 && (tip_carte=="rosu" || tip_carte=="negru" || tip_carte== "romb" || tip_carte== "trefla"))
                carti_de_joculet.insert(make_pair(number, tip_carte));
            else
            {
                cout<<"Pachet masluit"<<endl;
                masluit = 1;
                return 0;
            }
        if(masluit == 0){
            if(carti_de_joculet.size()==52)
                cout<<"Pachet OK"<<endl;
            else
                cout<<"Pregatit pentru Blackjack"<<endl;
        }
    }
    else
    if(commanda == "shuffle_cards"){
        int a0,c0,X0, a1, c1, X1,index1,index2;
        cin>>a0>>c0>>X0>>a1>>c1>>X1;
        vector<Card> carduri;
        while(cin>>number>>c>>tip_carte){
            carduri.push_back(Card(number,tip_carte));
        }
        ShuffleCards(carduri, a0, c0, X0, a1, c1, X1);
        for(int i=0; i<carduri.size(); i++){
            cout<<carduri[i].getNumber()<<","<<carduri[i].getNume()<<endl;
        }
    }
    else
    if (commanda == "play_game") {
        vector<Person> jucatori;
        vector<Card> Carduri;
        vector<Card> principal;
        for (int i = 2; i <= 14; i++) {
            if (i == 11)
                continue;
            if (i > 10)
                principal.push_back(Card{10, "rosu"});
            else
                principal.push_back(Card{i, "rosu"});
        }
        for (int i = 2; i <= 14; i++) {
            if (i == 11)
                continue;
            if (i > 10)
                principal.push_back(Card{10, "negru"});
            else
                principal.push_back(Card{i, "negru"});
        }
        for (int i = 2; i <= 14; i++) {
            if (i == 11)
                continue;
            if (i > 10)
                principal.push_back(Card{10, "romb"});
            else
                principal.push_back(Card{i, "romb"});
        }
        for (int i = 2; i <= 14; i++) {
            if (i == 11)
                continue;
            if (i > 10)
                principal.push_back(Card{10, "trefla"});
            else
                principal.push_back(Card{i, "trefla"});

        }
        int nr_jucatori;
        cin >> nr_jucatori;
        for (int i = 0; i < nr_jucatori; i++) {
            string nume_jucator;
            int suma_de_bani;
            cin >> nume_jucator >> suma_de_bani;
            jucatori.push_back(Person{nume_jucator, suma_de_bani});
        }
        int a0, c0, X0, a1, c1, X1;
        while (cin >> a0 >> c0 >> X0 >> a1 >> c1 >> X1) {

            ShuffleCards(principal, a0, c0, X0, a1, c1, X1);
            Carduri = principal;
            for (int i = 0; i < jucatori.size(); i++) {
                jucatori[i].addCard(Carduri.front());
                Carduri.erase(Carduri.begin());
                jucatori[i].addCard(Carduri.front());
                Carduri.erase(Carduri.begin());
            }

            Person dealer("",0);
            dealer.addCard(Carduri.front());
            Carduri.erase(Carduri.begin());
            dealer.addCard(Carduri.front());
            Carduri.erase(Carduri.begin());

            for (int i = 0; i < jucatori.size(); i++) {
                while(jucatori[i].getCardsSum() <= 16) {
                    jucatori[i].addCard(Carduri.front());
                    Carduri.erase(Carduri.begin());
                }
                if (jucatori[i].getCardsSum() > 21) {
                    jucatori[i].setSumaDeBani(jucatori[i].getSumaDeBani() - 10);
                }
            }
            while(dealer.getCardsSum() <= 16){
                dealer.addCard(Carduri.front());
                Carduri.erase(Carduri.begin());
            }
            if(dealer.getCardsSum() > 21){
                for(int i =0; i<jucatori.size(); i++){
                    if(17<=jucatori[i].getCardsSum() && jucatori[i].getCardsSum()<=21){
                        jucatori[i].setSumaDeBani(jucatori[i].getSumaDeBani() + 10);
                    }
                }
            }
            else{
                for (int j = 0; j < jucatori.size(); j++) {
                    if (17<=jucatori[j].getCardsSum() && jucatori[j].getCardsSum()<=21) {
                        if (jucatori[j].getCardsSum() < dealer.getCardsSum()) {
                            jucatori[j].setSumaDeBani(jucatori[j].getSumaDeBani() - 10);
                        } else if (jucatori[j].getCardsSum() > dealer.getCardsSum()) {
                            jucatori[j].setSumaDeBani(jucatori[j].getSumaDeBani() + 10);
                        }
                    }
                }
            }
            for(int i=0; i<jucatori.size(); i++){
                jucatori[i].Clear();
            }
            dealer.Clear();
            for(int i=0; i<jucatori.size(); i++)
                if (jucatori[i].getSumaDeBani() < 10) {
                    jucatori.erase(jucatori.begin() + i);
                    i--;
                }
        }
        for(int i =0; i< jucatori.size(); i++){
            cout<<jucatori[i].getPersonName()<<": "<<jucatori[i].getSumaDeBani()<<endl;
        }
    }
    return 0;
}
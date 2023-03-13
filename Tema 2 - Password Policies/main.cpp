#include <iostream>
#include <cctype>
#include <vector>

using namespace std;

class Policy {
protected:
    bool isChecked;

public:
    virtual void check(const string &parolica) = 0;

    bool getCheck() const{
        return isChecked;
    }

};

class LengthPolicy: public Policy{
private:
    uint16_t minLength, maxLength;
public:
    LengthPolicy(uint16_t arg_minl){
        minLength = arg_minl;
        maxLength = 255;
    }
    LengthPolicy(uint16_t arg_minl, uint16_t arg_maxl){
        minLength = arg_minl;
        maxLength = arg_maxl;
    }
    void check(const string &parolica){
        if(minLength <= parolica.size() && parolica.size() <= maxLength)
            isChecked = true;
        else
            isChecked = false;
    }
};

class ClassPolicy: public Policy {
private:
    uint16_t minClassCount;
public:
    ClassPolicy(uint16_t arg_minclass) {
        minClassCount = arg_minclass;
    }

    void check(const string &string1) {
        uint16_t nrUpper = 0, nrLower = 0, nrNumber = 0, nrOther = 0;
        for (int i = 0; i < string1.size(); i++) {
            if (isupper(string1[i])) nrUpper=1;
            else if (islower(string1[i])) nrLower=1;
            else if (isdigit(string1[i])) nrNumber=1;
            else nrOther=1;
        }
        uint16_t cc = nrUpper + nrLower + nrNumber + nrOther;
        if (minClassCount <= cc) {
            isChecked = true;
        } else {
            isChecked = false;
        }
    }
};

class IncludePolicy: public Policy {
private:
    char characterType;
public:
    IncludePolicy(char arg_chartype) {
        characterType = arg_chartype;
    }

 void check(const string &string1) override {
        isChecked = false;
        for (int i = 0; i < string1.size(); i++) {
            switch (characterType) {
                case 'a': {
                    if (string1[i]>='a' && string1[i]<='z') {
                        isChecked = true;
                    }
                    break;
                }
                case 'A': {
                    if (string1[i]>='A' && string1[i]<='Z') {
                        isChecked = true;
                    }
                    break;
                }
                case '0': {
                    if (string1[i]>='0' && string1[i]<='9') {
                        isChecked = true;
                    }
                    break;
                }
                case '$': {
                    if (!(string1[i]>='a' && string1[i]<='z') && !(string1[i]>='A' && string1[i]<='Z') && !(string1[i]>='0' && string1[i]<='9')) {
                        isChecked = true;
                    }
                    break;
                }
            }
        }
    }
};

class NotIncludePolicy: public Policy {
private:
    char characterType;
public:
    NotIncludePolicy(char arg_chartype) {
        characterType = arg_chartype;
    }

    void check(const string &string1) override {
        isChecked = true;
        for (int i = 0; i < string1.size(); i++) {
            switch (characterType) {
                case 'a': {
                    if (string1[i]>='a' && string1[i]<='z') {
                        isChecked = false;
                    }
                    break;
                }
                case 'A': {
                    if (string1[i]>='A' && string1[i]<='Z') {
                        isChecked = false;
                    }
                    break;
                }
                case '0': {
                    if (string1[i]>='0' && string1[i]<='9') {
                        isChecked = false;
                    }
                    break;
                }
                case '$': {
                    if (!(string1[i]>='a' && string1[i]<='z') && !(string1[i]>='A' && string1[i]<='Z') && !(string1[i]>='0' && string1[i]<='9')) {
                        isChecked = false;
                    }
                    break;
                }
            }
        }
    }
};

class RepetitionPolicy: public Policy {
private:
    uint16_t maxCount;
public:
    RepetitionPolicy(uint16_t arg_maxcount) {
        maxCount = arg_maxcount;
    }

    void check(const string &string1) override {
        if (maxCount >= string1.size()) {
            isChecked = true;
        } else {
            isChecked = true;
            for (int i = 0; i < string1.size(); i++) {
                uint16_t nrlitere = 1;
                char deComparat = string1[i];
                for (int j = i + 1; j < string1.size(); j++) {
                    if (string1[j] == string1[j - 1]) {
                        if (string1[j] == deComparat)
                            nrlitere++;
                    } else
                        break;
                }
                //cccbbbb
                if (nrlitere > maxCount) {
                    isChecked = false;
                    break;
                }
            }
        }
    }
};

class ConsecutivePolicy:public Policy {
private:
    uint16_t maxCount;
public:
    ConsecutivePolicy(uint16_t arg_maxcount) {
        maxCount = arg_maxcount;
    }

   void check(const string &string1) override {
        if (maxCount >= string1.size()) {
            isChecked = true;
        } else {
            isChecked = true;
            for (int i = 0; i < string1.size(); i++) {
                uint16_t nrlitere = 1;
                char deComparat = string1[i];
                for (int j = i + 1; j < string1.size(); j++) {
                    if (string1[j] == (char)(string1[j-1]+1)) {
                            nrlitere++;
                    } else
                        break;
                }
                //cccbbbb
                if (nrlitere > maxCount) {
                    isChecked = false;
                    break;
                }
            }
        }
    }
};

string checkPassword(string password, vector<Policy*> politicieni){
    for(int i = 0; i<politicieni.size(); i++){
        politicieni[i]->check(password);
        if(!politicieni[i]->getCheck()){
            return "NOK";
        }
    }
    return "OK";
}

int main() {
    uint16_t n;
    vector<Policy *> policiteni;
    string regula;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> regula;
        if (regula == "length") {
            uint16_t minlength;
            cin >> minlength;
            char c = getchar();
            if (c == '\n')
                policiteni.push_back(new LengthPolicy(minlength));
            else if (c == ' ') {
                uint16_t maxlength;
                cin >> maxlength;
                policiteni.push_back(new LengthPolicy(minlength, maxlength));
            }
        } else if (regula == "class") {
            uint16_t minClassCount;
            cin>>minClassCount;
            policiteni.push_back(new ClassPolicy(minClassCount));
        }
        else if (regula == "repetition") {
            uint16_t maxcount;
            cin >> maxcount;
            policiteni.push_back(new RepetitionPolicy(maxcount));
        }
        else if (regula == "include"){
            char caracter;
            cin>>caracter;
            policiteni.push_back(new IncludePolicy(caracter));
        }
        else if(regula == "ninclude"){
            char caracter;
            cin >> caracter;
            policiteni.push_back(new NotIncludePolicy(caracter));
        }
        else if(regula == "consecutive"){
            uint16_t maxcount;
            cin >> maxcount;
            policiteni.push_back(new ConsecutivePolicy(maxcount));
        }
    }
    string parola;
    while(cin>>parola){
        cout << checkPassword(parola, policiteni) << endl;
    }
    return 0;
}

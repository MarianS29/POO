#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

class Person {
public:
    string mName;
    uint16_t mAge;
    double mSalary;

    Person() {
        mName = "";
        mAge = 0;
        mSalary = 0;
    }

    Person(string name, uint16_t age, double salary) {
        mName = name;
        mAge = age;
        mSalary = salary;
    }

    Person(const Person &other){
        this->mName = other.mName;
        this->mSalary = other.mSalary;
        this->mAge = other.mAge;
    }

    bool operator==(const Person &other) const {
        if (this->mName == other.mName && this->mAge == other.mAge && this->mSalary == other.mSalary)
            return true;
        return false;
    }

    bool operator<(const Person &other) const {
        if (this->mName < other.mName)
            return true;
        return false;
    }
};

class Building {
protected:
    string mBuildingName;
    string mType;
    Person mCoordinator;
    vector<Person> mEmployees;
    vector<Person> mCitizens;
public:
    Building(string buildname, string buildtype): mBuildingName(buildname), mType(buildtype) {}

    Building(const Building& other){
        this->mCitizens = other.mCitizens;
        this->mEmployees = other.mEmployees;
        this->mCoordinator = other.mCoordinator;
        this->mBuildingName = other.mBuildingName;
        this->mType = other.mType;
    }

    Building():mBuildingName(""), mType(""), mCoordinator(Person()), mEmployees(), mCitizens(){}

    virtual void add(const Person &om) = 0;

    virtual void remove(const Person &om) = 0;

    virtual Building *operator+(const Person &other) = 0;

    virtual Building *operator-() {
        return nullptr;
    }

    virtual Building *operator-(const Person &other) {
        return nullptr;
    }

    string getBuildingName() const {
        return mBuildingName;
    }

    string getType() const {
        return mType;
    }

    uint16_t getEmployeesSize() const {
        return mEmployees.size();
    }

    uint16_t getCitizensSize() const {
        return mCitizens.size();
    }

    Person getEmployee(uint16_t position) const {
        return mEmployees[position];
    }

    Person getCitizen(uint16_t position) const {
        return mCitizens[position];
    }

    Person getCoordinator() const {
        return mCoordinator;
    }
};

class CityHall: public Building {
public:
    CityHall(string name) : Building(name, "CityHall") {
        mCitizens.clear();
        Person coordinator;
        mCoordinator = coordinator;
    }

    Building *operator+(const Person &other) {
        if (mCoordinator.mName.empty())
            mCoordinator = other;
        return this;
    }

    Building *operator-() override {
        mCoordinator = Person();
        return this;
    }

    void add(const Person &om) {
        mCitizens.push_back(om);
    }

    void remove(const Person &om) {
        for (int i = 0; i < mCitizens.size(); i++) {
            if (mCitizens[i] == om) {
                mCitizens.erase(mCitizens.begin() + i);
                break;
            }
        }
    }
};

class Hospital: public Building {
public:
    Hospital(string name) : Building(name, "Hospital") {
        mCitizens.clear();
        mEmployees.clear();
    }

    Building *operator+(const Person &other) {
        mEmployees.push_back(other);
        return this;
    }

    Building *operator-(const Person &other) {
        for (int i = 0; i < mEmployees.size(); i++) {
            if (mEmployees[i] == other) {
                mEmployees.erase(mEmployees.begin() + i);
                break;
            }
        }
        return this;
    }

    void add(const Person &other) {
        mCitizens.push_back(other);
    }

    void remove(const Person &other) {
        for (int i = 0; i < mCitizens.size(); i++) {
            if (mCitizens[i] == other) {
                mCitizens.erase(mCitizens.begin() + i);
                break;
            }
        }
    }
};

class PoliceStation: public Building{
public:
    PoliceStation(string name) : Building(name, "PoliceStation") {
        mCitizens.clear();
        mEmployees.clear();
    }

    Building *operator+(const Person &other) {
        mEmployees.push_back(other);
        return this;
    }

    Building *operator-(const Person &other) {
        for (int i = 0; i < mEmployees.size(); i++) {
            if (mEmployees[i] == other) {
                mEmployees.erase(mEmployees.begin() + i);
                break;
            }
        }
        return this;
    }

    void add(const Person &politist) {
        mCitizens.push_back(politist);
    }

    void remove(const Person &arestat) {
        for (int i = 0; i < mCitizens.size(); i++) {
            if (mCitizens[i] == arestat) {
                mCitizens.erase(mCitizens.begin() + i);
                break;
            }
        }
    }
};

class House: public Building {
private:
    uint16_t mMaxNumber;
public:
    House(string name, uint16_t maxnumber) : Building(name, "House"), mMaxNumber(maxnumber) {
        mCitizens.clear();
        Person alta;
        mCoordinator = alta;
    }

    House(const House& other){
        this->mCitizens = other.mCitizens;
        this->mEmployees = other.mEmployees;
        this->mCoordinator = other.mCoordinator;
        this->mBuildingName = other.mBuildingName;
        this->mType = other.mType;
        this->mMaxNumber = other.mMaxNumber;
    }

    Building *operator+(const Person &other) {
        if (mCoordinator.mName.empty())
            mCoordinator = other;
        return this;
    }

    Building *operator-() {
        Person alta;
        mCoordinator = alta;
        return this;
    }

    void add(const Person &locuitor) {
        if (mCitizens.size() + 1 <= mMaxNumber)
            mCitizens.push_back(locuitor);
    }

    void remove(const Person &major) {
        for (int i = 0; i < mCitizens.size(); i++) {
            if (mCitizens[i] == major && mCitizens[i].mAge >= 18) {
                mCitizens.erase(mCitizens.begin() + i);
                break;
            }
        }
    }
};

class Block : public Building {
private:
    uint16_t mMaxNumberPerFloor;
public:
    Block(string name, uint16_t NumberOfFloors, uint16_t maxnumberperfloor) : Building(name, "Block"), mMaxNumberPerFloor(maxnumberperfloor) {
        mCitizens.clear();
        mCoordinator = Person();
        for (int i = 0; i < NumberOfFloors* maxnumberperfloor; i++) {
            mCitizens.push_back(Person());
        }
    }

    Block(const Block &other){
        this->mCitizens = other.mCitizens;
        this->mEmployees = other.mEmployees;
        this->mCoordinator = other.mCoordinator;
        this->mBuildingName = other.mBuildingName;
        this->mType = other.mType;
        this->mMaxNumberPerFloor = other.mMaxNumberPerFloor;
    }

    Building *operator+(const Person &administrator) {
        if (mCoordinator.mName.empty())
            mCoordinator = administrator;
        return this;
    }

    Building *operator-() {
        Person alta;
        mCoordinator = alta;
        return this;
    }

//    virtual void add(const Person &locuitor) {
//        int k = 0;
//        for (int i = 0; i < mCitizens.size(); i++)
//            if (mCitizens[i].mName.empty())
//                k++;
//        if (k <= mCitizens.size()) {
//            for (int i = 0; i < mCitizens.size(); i++)
//                if (mCitizens[i].mName.empty()) {
//                    mCitizens[i] = locuitor;
//                    break;
//                }
//        }
//    }
    void add (const Person & person) {
        for (uint16_t i = 0; i < getCitizensSize(); i++) {
            if (mCitizens[i].mName == "") {
                mCitizens[i] = person;
                break;
            }
        }
    }

    void remove(const Person &locuitor) {
        for (int i = 0; i < mCitizens.size(); i++) {
            if (mCitizens[i] == locuitor && mCitizens[i].mAge >= 18) {
                Person alta;
                mCitizens[i] = alta;
                break;
            }
        }
    }
};

bool order(string a, string b){
    return a < b;
}

int main() {
    ifstream functionInput("input.txt");
    string action;

    string CladireSauPersoanaType;

    string CladireName;
    uint16_t NrMaxHouse;
    uint16_t NrEtajeBlock, NrPersMaxPerEtajBlock;

    string PersoanaName, CladireInCareAdaug, CladireDinCareSterg;
    uint16_t Age;
    double Salary;

    uint16_t NrCityHall = 0, NrHospital = 0, NrPoliceStation = 0, NrHouse = 0, NrBlock = 0;
    vector<Building *> cladiri;
    uint16_t NrPatientsHospitals = 0, NrDoctors = 0, NrCops = 0, NrMayors = 0, NrCityHallEmployees = 0, NrBusted = 0;
    double AvgSalaryDoctors = 0, AvgSalaryCops = 0, AvgSalaryMayors = 0, AvgSalaryCityHallEmployees = 0, AvgAgeBusted = 0;
    queue<uint16_t> MaxHouseVector, MaxBlockVector;
    vector<string> cuvintele;

    while (functionInput >> action) {

        if (action == "add") {
            functionInput >> CladireSauPersoanaType;
            if (CladireSauPersoanaType == "CityHall") {
                functionInput >> CladireName;
                cladiri.push_back(new CityHall(CladireName));
                NrCityHall++;

            } else if (CladireSauPersoanaType == "Hospital") {
                functionInput >> CladireName;
                cladiri.push_back(new Hospital(CladireName));
                NrHospital++;

            } else if (CladireSauPersoanaType == "PoliceStation") {
                functionInput >> CladireName;
                cladiri.push_back(new PoliceStation(CladireName));
                NrPoliceStation++;

            } else if (CladireSauPersoanaType == "House") {
                functionInput >> CladireName >> NrMaxHouse;
                cladiri.push_back(new House(CladireName, NrMaxHouse));
                NrHouse++;
                MaxHouseVector.push(NrMaxHouse);

            } else if (CladireSauPersoanaType == "Block") {
                functionInput >> CladireName >> NrEtajeBlock >> NrPersMaxPerEtajBlock;
                cladiri.push_back(new Block(CladireName, NrEtajeBlock, NrPersMaxPerEtajBlock));
                NrBlock++;
                MaxBlockVector.push(NrEtajeBlock * NrPersMaxPerEtajBlock);

            } else if (CladireSauPersoanaType == "coordinator") {
                functionInput>> PersoanaName >> Age >> Salary >> CladireInCareAdaug;
                for (int i = 0; i < cladiri.size(); i++) {
                    if (cladiri[i]->getBuildingName() == CladireInCareAdaug) {
                        cladiri[i] = *cladiri[i] + Person(PersoanaName, Age, Salary);
                    }
                }

            } else if (CladireSauPersoanaType == "citizen") {
                functionInput >> PersoanaName >> Age >> Salary >> CladireInCareAdaug;
                for (int i = 0; i < cladiri.size(); i++) {
                    if (cladiri[i]->getBuildingName() == CladireInCareAdaug) {
                        cladiri[i]->add(Person(PersoanaName, Age, Salary));
                    }
                }

            } else if (CladireSauPersoanaType == "employee") {
                functionInput >> PersoanaName >> Age >> Salary >> CladireInCareAdaug;
                for (int i = 0; i < cladiri.size(); i++) {
                    if (cladiri[i]->getBuildingName() == CladireInCareAdaug) {
                        cladiri[i] = *cladiri[i] + Person(PersoanaName, Age, Salary);
                        break;
                    }
                }
            }

        } else if (action == "remove") {
            functionInput >> CladireSauPersoanaType >> PersoanaName >> CladireDinCareSterg;
            if (CladireSauPersoanaType == "citizen") {
                for (int i = 0; i < cladiri.size(); i++) {
                    if (cladiri[i]->getBuildingName() == CladireDinCareSterg) {
                        for (int j = 0; j < cladiri[i]->getCitizensSize(); j++)
                            if (PersoanaName == cladiri[i]->getCitizen(j).mName) {
                                cladiri[i]->remove(cladiri[i]->getCitizen(j));
                            }
                    }
                }
            } else if (CladireSauPersoanaType == "employee") {
                for (int i = 0; i < cladiri.size(); i++) {
                    if (cladiri[i]->getBuildingName() == CladireDinCareSterg) {
                        for (int j = 0; j < cladiri[i]->getEmployeesSize(); j++) {
                            if (PersoanaName == cladiri[i]->getEmployee(j).mName) {
                                cladiri[i] = *cladiri[i] - cladiri[i]->getEmployee(j);
                                break;
                            }
                        }
                    }
                }
            } else if (CladireSauPersoanaType == "coordinator") {
                for (int i = 0; i < cladiri.size(); i++) {
                    if (cladiri[i]->getBuildingName() == CladireDinCareSterg) {
                        cladiri[i] = -*cladiri[i];
                    }
                }
            }
        }
    }
    for(int i=0; i<cladiri.size(); i++) {
        if (cladiri[i]->getType() == "CityHall") {
            for (int j = 0; j < cladiri[i]->getCitizensSize(); j++) {
                AvgSalaryCityHallEmployees += cladiri[i]->getCitizen(j).mSalary;
                NrCityHallEmployees++;
            }
            if(!cladiri[i]->getCoordinator().mName.empty()) {
                AvgSalaryMayors += cladiri[i]->getCoordinator().mSalary;
                NrMayors++;
            }
        } else if (cladiri[i]->getType() == "PoliceStation") {
            for(int j=0; j<cladiri[i]->getCitizensSize(); j++) {
                AvgAgeBusted += cladiri[i]->getCitizen(j).mAge;
                NrBusted++;
            }
            for (int j = 0; j < cladiri[i]->getEmployeesSize(); j++) {
                AvgSalaryCops += cladiri[i]->getEmployee(j).mSalary;
                NrCops++;
            }
        } else if (cladiri[i]->getType() == "Hospital") {
            NrPatientsHospitals+=cladiri[i]->getCitizensSize();
            for (int j = 0; j < cladiri[i]->getEmployeesSize(); j++) {
                AvgSalaryDoctors += cladiri[i]->getEmployee(j).mSalary;
                NrDoctors++;
            }
        }
    }
    cout << "Type: ";
    if (NrCityHall >= 3 && NrHospital >= 2 && NrPoliceStation >= 3 && NrHouse >= 8 && NrBlock >= 4) {
        cout << "Capital" << endl;
    } else if (NrCityHall >= 2 && NrHospital >= 1 && NrPoliceStation >= 2 && NrHouse >= 4 && NrBlock >= 1) {
        cout << "City" << endl;
    } else cout << "Village" << endl;
    cout << "Number of patients in hospitals: " << NrPatientsHospitals << endl;
    cout << "Average salary for doctors: ";
    if (NrDoctors == 0)
        cout << AvgSalaryDoctors << endl;
    else
        cout << AvgSalaryDoctors / NrDoctors << endl;
    cout << "Average salary for cops: ";
    if (NrCops == 0)
        cout << AvgSalaryCops << endl;
    else
        cout << AvgSalaryCops / NrCops << endl;
    cout << "Average salary for mayors: ";
    if (NrMayors == 0)
        cout << AvgSalaryMayors << endl;
    else
        cout << AvgSalaryMayors / NrMayors << endl;
    cout << "Average salary for city hall employees: ";
    if (NrCityHallEmployees == 0)
        cout << AvgSalaryCityHallEmployees << endl;
    else
        cout << AvgSalaryCityHallEmployees / NrCityHallEmployees << endl;
    cout << "Average age of busted in police sattions: ";
    if (NrBusted == 0)
        cout << AvgAgeBusted << endl;
    else
        cout << AvgAgeBusted / NrBusted << endl;
    for (int i = 0; i < cladiri.size(); i++) {
        if (cladiri[i]->getType() == "Block" || cladiri[i]->getType() == "House") {
            uint16_t NrInBlock = 0;
            if (cladiri[i]->getType() == "Block") {
                for (int j = 0; j < cladiri[i]->getCitizensSize(); j++) {
                    if (!cladiri[i]->getCitizen(j).mName.empty())
                        NrInBlock++;
                }
                if (!cladiri[i]->getCoordinator().mName.empty())
                    NrInBlock++;
                cout << "Number of people in Block " << cladiri[i]->getBuildingName() << ": ";
                if (cladiri[i]->getCoordinator().mName.empty()) {
                    if (NrInBlock >= MaxBlockVector.front()) {
                        cout << MaxBlockVector.front() << endl;
                        MaxBlockVector.pop();
                    } else {
                        cout << NrInBlock << endl;
                        MaxBlockVector.pop();
                    }
                } else {
                    if (NrInBlock >= MaxBlockVector.front()) {
                        cout << MaxBlockVector.front() << endl;
                        MaxBlockVector.pop();
                    } else {
                        cout << NrInBlock << endl;
                        MaxBlockVector.pop();
                    }
                }
            } else if (cladiri[i]->getType() == "House") {
                cout << "Number of people in House ";
                if (cladiri[i]->getCoordinator().mName.empty()) {
                    if (cladiri[i]->getCitizensSize() >= MaxHouseVector.front()) {
                        cout << cladiri[i]->getBuildingName() << ": " << MaxHouseVector.front() << endl;
                        MaxHouseVector.pop();
                    } else {
                        cout << cladiri[i]->getBuildingName() << ": " << cladiri[i]->getCitizensSize() << endl;
                        MaxHouseVector.pop();
                    }
                } else {
                    if (cladiri[i]->getCitizensSize() + 1 >= MaxHouseVector.front()) {
                        cout << cladiri[i]->getBuildingName() << ": " << MaxHouseVector.front() << endl;
                        MaxHouseVector.pop();
                    } else {
                        cout << cladiri[i]->getBuildingName() << ": " << cladiri[i]->getCitizensSize() + 1 << endl;
                        MaxHouseVector.pop();
                    }
                }
            }
        }
    }
    for (int i = 0; i < cladiri.size() - 1; i++) {
        for (int j = i + 1; j < cladiri.size(); j++) {
            if (cladiri[i]->getCoordinator() == cladiri[j]->getCoordinator() &&
                (cladiri[i]->getType() == "House" || cladiri[i]->getType() == "Block") &&
                (cladiri[j]->getType() == "House" || cladiri[j]->getType() == "Block") &&
                (!cladiri[i]->getCoordinator().mName.empty() && !cladiri[j]->getCoordinator().mName.empty())) {
                cuvintele.push_back(cladiri[i]->getCoordinator().mName);
                break;
            }
        }
    }
    sort(cuvintele.begin(), cuvintele.end(), order);
    cout << "Administrators of house and block:";
    if (cuvintele.empty())
        cout << " Nobody";
    else {
        for (int i = 0; i < cuvintele.size(); i++)
            cout << " " << cuvintele[i];
    }
//    double s1=0;
//    for(int i=0; i<cladiri.size(); i++){
//        if(cladiri[i]->getType() == "Hospital"){
//            s1+=cladiri[i]->getCitizensSize();
//        }
//    }
//    cout<<"Hospital patients nr= "<<s1<<endl;
    return 0;
}


#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<forward_list>
#include<stdexcept>

using namespace std;

// max loads for 737 and 767 as global constants
const int MAXLOAD737 = 46000;
const int MAXLOAD767 = 116000;

class Cargo {

    protected:

    string uldtype;
    string abbrev;
    string uldid;
    int aircraft;
    double weight;
    string destination;

    public:

    // Default constructor prototype
    Cargo();

    // Full constructor prototype
    Cargo(const string& type, const string& abbreviation, const string& id, const int& craftNum, const int& wght, const string& dstn);

    // Copy constructor prototype
    Cargo(const Cargo&);

    // Destructor prototype
    ~Cargo();

    // Mutator (setters) prototypes
    void setuldtype(string);
    void setabbrev(string);
    void setuldid(string);
    void setaircraft(int);
    void setweight(double);
    void setdestination(string);

    // Accessor (getters) prototypes
    string getuldtype() const;
    string getabbrev() const;
    string getuldid() const;
    int getaircraft() const;
    double getweight() const;
    string getdestination() const;

    // Virtual function to be overridden
    virtual void maxweight(double&, double) = 0;

    // Kilotopound friend function prototype
    friend void kilotopound(Cargo&);

    // Equality operator overload friend function prototype
    friend bool operator==(const Cargo& lhs, const Cargo& rhs);

    // Output function prototype
    void output();
};

class Boeing737 : public Cargo {

    private: 

    int totalWght;

    public:
    
    // Constructors inherited from Cargo class
    using Cargo::Cargo;

    // Destructor
    ~Boeing737() {};

    // Maxweight prototype overriding virtual function
    void maxweight(double&, double) override;

};

class Boeing767 : public Cargo {

    private: 

    int totalWght;

    public:
    
    // Constructors inherited from Cargo class
    using Cargo::Cargo;

    // Destructor
    ~Boeing767() {};

    // Maxweight prototype overriding virtual function
    void maxweight(double&, double) override;

};

// Input prototype
void input();

// Checker function prototypes
void checkPlane(int);
void checkType(string);
void checkAbrv(string, int);

int main () {

input();
return 0;

}

// Default constructor
Cargo::Cargo() {

    uldtype = "none";
    abbrev = "none";
    uldid = "none";
    aircraft = 0;
    weight = 0.0;
    destination = "none";

}

// Full constructor
Cargo::Cargo(const string& type, const string& abbreviation, const string& id, const int& craftNum, const int& wght, const string& dstn) {

    uldtype = type;
    abbrev = abbreviation;
    uldid = id;
    aircraft = craftNum;
    weight = wght;
    destination = dstn;

}

// Copy constructor
Cargo::Cargo(const Cargo& cargo1) {

    uldtype = cargo1.uldtype;
    abbrev = cargo1.abbrev;
    uldid = cargo1.uldid;
    aircraft = cargo1.aircraft;
    weight = cargo1.weight;
    destination = cargo1.destination;

}

// Destructor
Cargo::~Cargo() {}

// uldtype setter
void Cargo::setuldtype(string type) {

    uldtype = type;

}

// abbrev setter
void Cargo::setabbrev(string abrv) {

    abbrev = abrv;

}

// uldid setter
void Cargo::setuldid(string id) {

    uldid = id;

}

// aircraft setter
void Cargo::setaircraft(int aircraftNum) {

    aircraft = aircraftNum;

}

// weight setter
void Cargo::setweight(double wght) {

    weight = wght;

}

// destination setter
void Cargo::setdestination(string destinationCode) {

    destination = destinationCode;

}

// uldtype getter
string Cargo::getuldtype() const {

    return uldtype;

}

// abbrev getter
string Cargo::getabbrev() const {

    return abbrev;

}

// uldid getter
string Cargo::getuldid() const {

    return uldid;

}

// aircraft getter
int Cargo::getaircraft() const {

    return aircraft;

}

// weight getter
double Cargo::getweight() const {

    return weight;
}

// destination getter
string Cargo::getdestination() const {

    return destination;

}

// Create a Boeing737 object and add it to linked list if not too heavy
void load737(forward_list<Boeing737>& list737, const string type, const string abrv, const string id, const int craft, const double wt, const string dest, double& totwt737) {

    Boeing737 unit737(type,abrv,id,craft,wt,dest); 
    unit737.maxweight(totwt737,wt); 
    list737.push_front(unit737);

}

// Create a Boeing767 object and add it to linked list if not too heavy
void load767(forward_list<Boeing767>& list767, const string type, const string abrv, const string id, const int craft, const double wt, const string dest, double& totwt767) {

    Boeing767 unit767(type,abrv,id,craft,wt,dest); 
    unit767.maxweight(totwt767,wt); 
    list767.push_front(unit767); 

}

// Checks if 737 weight exceeds max weight
void Boeing737::maxweight(double& totwt737, double wt) {

    if (totwt737 > MAXLOAD737) {
        
        totwt737 -= wt; 
        throw runtime_error("too heavy for 737, removed\n\n");

    }
}

// Checks if 767 weight exceeds max weight
void Boeing767::maxweight(double& totwt767, double wt){

    if (totwt767 > MAXLOAD767) {

        totwt767 -= wt; 
        throw runtime_error("too heavy for 767, removed\n\n");

    }
}

// Input 
void input() {

    ifstream inputFile;
    string fileName;

    do {

        cout << "Name of input file: ";
        cin >> fileName;

        try {

            inputFile.clear();

            inputFile.open(fileName);

            if (!inputFile) {

                cout << "Error opening the file, file not found" << endl;
                throw runtime_error(fileName + " Bad filename\n\n");
                exit(99);

            }
        } catch(runtime_error &excpt) {

            cout << fileName << " " << excpt.what();

        }
    } while (!inputFile);

    string type;
    string abrv;
    string uld;
    int plane;
    double weight;
    string dest;
    double totwt737 = 0;
    double totwt767 = 0;
    int num737 = 0;
    int num767 = 0;
    forward_list<Boeing737> list737;
    forward_list<Boeing767> list767;

    while(inputFile >> type) {

        try {

            inputFile >> abrv;
            inputFile >> uld;
            inputFile >> plane;
            inputFile >> weight;
            inputFile >> dest;

            checkType(type);
            checkPlane(plane);

            if (plane == 737) {

                checkAbrv(abrv, plane);
                totwt737 += weight;
                load737(list737, type, abrv, uld, plane, weight, dest, totwt737);

            }

            if (plane == 767) {

                checkAbrv(abrv, plane);
                totwt767 += weight;
                load767(list767, type, abrv, uld, plane, weight, dest, totwt767);

            }    
            
        } catch(runtime_error &excpt){

            cout <<excpt.what();

        }
    }

    inputFile.close();

    for (Cargo& unit737 : list737) {

        num737++;
        cout << "Boeing 737 #" << num737 << endl;
        unit737.output();
        cout << endl;

    }

    for (Cargo& unit767 : list767) {

        num767++;
        cout << "Boeing 767 #" << num767 << endl;
        unit767.output();
        cout << endl;

    }

    cout << "total weight for 737 load is " << totwt737 << endl;
    cout << "total weight for 767 load is " << totwt767 << endl;
}

// Output
void Cargo::output() {

    cout << left << setw(30) << "Unit load type:" << uldtype << endl;
    cout << setw(30) << "Unit load abbreviation:" << abbrev << endl;
    cout << setw(30) << "Unit identifier:" << uldid << endl;
    cout << setw(30) << "Aircraft type:" << aircraft << endl;
    cout << setw(30) << "Unit Weight:" << weight << " pounds" << endl;
    cout << setw(30) << "Destination code:" << destination << endl;

}

// Checks for valid plane type
void checkPlane(int plane) {

    if (plane != 737 && plane != 767) {

        throw runtime_error(to_string(plane) + " bad airplane type\n\n");

    }
}

// Checks for valid load type
void checkType(string type) {

    if (type != "Container" && type != "Pallet") {

        throw runtime_error(type + " not Container or Pallet, rejected load\n\n");

    }
}

// Checks for valid abbreviation
void checkAbrv(string abrv, int plane) {

    if (plane == 737) {

        if (abrv != "AYF" && abrv != "AYK" && abrv != "AAA" && abrv != "AYY" && abrv != "PAG" && abrv != "PMC" && abrv != "PLA" ) {

            throw runtime_error(abrv + " bad type for 737\n\n");

        }
    }
        
    if (plane == 767) {

        if (abrv != "AKE" && abrv != "APE" && abrv != "AKC" && abrv != "AQP" && abrv != "AQF" && abrv != "AAP" && abrv != "P1P" && abrv != "P6P" ) {

            throw runtime_error(abrv + " bad type for 767\n\n");
        }
    }
}

// Kilotopound friend function
void kilotopound(Cargo& cargo) {

    cargo.weight *= 2.2;

}

// Equality operator overload friend function
bool operator==(const Cargo& lhs, const Cargo& rhs) {

    return (lhs.abbrev == rhs.abbrev) && (lhs.uldid == rhs.uldid);
    
}
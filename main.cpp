#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

class Client {
    string nume;
    char CNP[13];
public:
    Client (string, char*); //constructor de initializare si parametrizat
    Client (const Client&);  //constructor de copiere
    ~Client();
    Client& operator = (const Client&);   //supraincarea atribuirii
    friend istream& operator >> (istream&, Client&); //supraincarcarea citirii
    friend ostream& operator << (ostream&, Client&);   //supraincarcarea afisarii
    string getNume () {
        return nume;    //getter pentru nume client
    }
};

Client::Client (string n = "", char c[13] = "") {
    nume = n;
    strcpy (CNP, c);
    int ok;
    //tratarea exceptiei in caz ca numele contine cifre
    try {
        int i;
        ok = 1;
        for(i = 0; i < nume.size(); i++) {
            if (nume[i] - '0' >= 0 && nume[i] - '0' <= 9)
                ok = 0;
        }
        if(ok == 0)
            throw 1;
    }
    catch (int x) {
        cout << "Numele clientului nu este valid!";
        exit(0);
    }
    //tratarea exceptiei in caz ca CNP-ul este mai mic de 13 caractere,sau contine litere
    try {
        int i;
        ok = 1;
        if (strlen(CNP) == 13) {
            for(i = 0; i < 13; i++) {
                if(CNP[i] - '0' < 0 || CNP[i] - '0' > 9)
                    ok = 0;
            }
        }
        if (strlen(CNP) > 0 && strlen(CNP) < 13 || strlen(CNP) > 13)
            ok = 0;
        if (ok == 0)
            throw 'a';
    }
    catch (char x) {
        cout << "CNP-ul introdus nu este valid!" << endl;
        exit(0);
    }
}

Client::Client (const Client& c) {
    nume = c.nume;
    strcpy (CNP, c.CNP);
}

Client::~Client() {
    nume = "";
    strcpy (CNP, "");
}

Client& Client::operator = (const Client& c) {
    if(this != &c) {
        nume = c.nume;
        strcpy(CNP, c.CNP);
    }
    return *this;
}

istream& operator >> (istream& in, Client& c) {
    int ok;
    cout << "\nDati numele si prenumele clientului: ";
    string n, pr;
    in >> n >> pr;
    c.nume = n + " ";
    c.nume += pr;
    try {
        int i;
        ok = 1;
        for(i = 0; i < c.nume.size(); i++) {
            if(c.nume[i] - '0' >= 0 && c.nume[i] - '0' <= 9)
                ok = 0;
        }
        if(ok == 0)
            throw 1;
    }
    catch(int x) {
        cout << "Numele clientului nu este valid!";
        exit(0);
    }
    cout << "Dati CNP-ul clientului: ";
    in >> c.CNP;
    try {
        int i;
        ok = 1;
        if (strlen(c.CNP) == 13) {
            for(i = 0; i < 13; i++) {
                if(c.CNP[i] - '0' < 0 || c.CNP[i] - '0' > 9)
                    ok = 0;
            }
        }
        if(strlen(c.CNP) > 0 && strlen(c.CNP) < 13 || strlen(c.CNP) > 13)
            ok = 0;
        if(ok == 0)
            throw 'a';
    }
    catch(char x) {
        cout << "CNP-ul introdus nu este valid!" << endl;
        exit(0);
    }
    return in;
}

ostream& operator << (ostream& out, Client& c) {
    out << "\nNumele clientului: " << c.nume << endl;
    out << "CNP-ul clientului: " << c.CNP << endl;
}

class Locuinta {
protected:
    static int nr;
    string numeProprietar;
    double suprUtila;
    double discount;
    double pretMP;
public:
    virtual double calculChirie() = 0;   //functie virtuala pura pentru calculul chirie
    Locuinta (string, double, double, double);  //constructor parametrizat si de initializare
    Locuinta (const Locuinta&);  //constructor de copiere
    ~Locuinta ();    //destructor
    virtual void afisare (); //functie virtuala de afisare
    Locuinta& operator = (const Locuinta&);   //supraincarcarea atriburiii
    friend istream& operator >> (istream&, Locuinta&); //supraincarcarea citirii
    friend ostream& operator << (ostream&, Locuinta&); //supraincarcarea afisarii
};
int Locuinta::nr = 0;

Locuinta::Locuinta (string n = "", double s = 0, double d = 0, double p = 0) {
    int ok;
    nr++;
    numeProprietar = n;
    try {
        int i;
        ok = 1;
        for(i = 0; i < numeProprietar.size(); i++)
        {
            if(numeProprietar[i] - '0' >= 0 && numeProprietar[i] - '0' <= 9)
                ok = 0;
        }
        if(ok == 0)
            throw 1;
    }
    catch(int x) {
        cout << "Numele proprietarului nu este valid!";
        exit(0);
    }
    suprUtila = s;
    discount = d;
    try {
        if(discount < 0 || discount > 10)
            throw 1;
    }
    catch(int x) {
        cout << "Discount-ul aplicat este invalid!";
        exit(0);
    }
    pretMP = p;
}

Locuinta::Locuinta (const Locuinta& l) {
    numeProprietar = l.numeProprietar;
    suprUtila = l.suprUtila;
    discount = l.discount;
    pretMP = l.pretMP;
}

Locuinta::~Locuinta () {
    nr--;
    numeProprietar = "";
    suprUtila = 0;
    discount = 0;
    pretMP = 0;
}

void Locuinta::afisare() {
    cout << "\nNumarul total al locuintelor: " << nr << endl;
    cout << "Numele proprietarului: " << numeProprietar << endl;
    cout << "Suprafata utila: " << suprUtila << endl;
    cout << "Pretul pe metrul patrat: " << pretMP << endl;
    cout << "Discountul aplicat: " << discount << endl;
}

Locuinta& Locuinta::operator = (const Locuinta& l) {
    if(this != &l) {
        numeProprietar = l.numeProprietar;
        suprUtila = l.suprUtila;
        discount = l.discount;
        pretMP = l.pretMP;
    }
    return *this;
}

istream& operator >> (istream& in, Locuinta& l) {
    int ok;
    cout << "\nDati numele si prenumele proprietarului: ";
    string nume, prenume;
    in >> nume >> prenume;
    l.numeProprietar = nume + " ";
    l.numeProprietar += prenume;
    try {
        int i;
        ok = 1;
        for(i = 0; i < l.numeProprietar.size(); i++) {
            if (l.numeProprietar[i] - '0' >= 0 && l.numeProprietar[i] - '0' <= 9)
                ok = 0;
        }
        if(ok == 0)
            throw 1;
    }
    catch(int x) {
        cout << "Numele proprietarului nu este valid!";
        exit(0);
    }
    cout << "Dati suprafata utila: ";
    in >> l.suprUtila;
    cout << "Dati pretul pe metrul patrat: ";
    in >> l.pretMP;
    cout << "Dati discountul aplicat: ";
    in >> l.discount;
    try {
        if(l.discount < 0 || l.discount > 10)
            throw 1;
    }
    catch(int x) {
        cout << "Discount-ul aplicat este invalid!";
        exit(0);
    }
    return in;
}

ostream& operator << (ostream& out, Locuinta& l) {
    l.afisare();
}

class Apartament: public Locuinta {
    int etaj;
public:
    double calculChirie(); //functie pentru calculul chiriei
    Apartament (string,double,double,double,int);
    Apartament (const Apartament&);
    ~Apartament ();
    void afisare (); //functie de afisare rescrisa
    Apartament& operator = (Apartament&);
    friend istream& operator >> (istream&, Apartament&);
    friend ostream& operator << (ostream&, Apartament&);
};

Apartament::Apartament (string n = "", double s = 0, double d = 0, double p = 0,int e = 0): Locuinta(n, s, d, p) {
    etaj = e;
}

Apartament::Apartament(const Apartament& a) {
    numeProprietar = a.numeProprietar;
    suprUtila = a.suprUtila;
    discount = a.discount;
    pretMP = a.pretMP;
    etaj = a.etaj;
}

Apartament::~Apartament() {
    numeProprietar = "";
    suprUtila = 0;
    discount = 0;
    pretMP = 0;
    etaj = 0;
}

double Apartament::calculChirie() {
    double chirie = 0;
    chirie = pretMP*suprUtila;
    chirie -= discount / 100 *chirie;
    return chirie;
}

void Apartament::afisare() {
    Locuinta::afisare();
    cout << "Apartamentul se afla la etajul: " << etaj << endl;
    cout << "Pretul chiriei pentru apartament este de " << calculChirie() << " lei." << endl << endl;
}

Apartament& Apartament::operator = (Apartament& a) {
    if(this != &a) {
        numeProprietar = a.numeProprietar;
        suprUtila = a.suprUtila;
        discount = a.discount;
        pretMP = a.pretMP;
        etaj = a.etaj;
    }
    return *this;
}

istream& operator >> (istream& in, Apartament& a) {
    int ok;
    cout << "\nDati numele si prenumele proprietarului: ";
    string nume, prenume;
    in >> nume >> prenume;
    a.numeProprietar = nume + " ";
    a.numeProprietar += prenume;
    try {
        int i;
        ok = 1;
        for(i = 0; i < a.numeProprietar.size(); i++) {
            if(a.numeProprietar[i] - '0' >= 0 && a.numeProprietar[i] - '0' <= 9)
                ok = 0;
        }
        if(ok==0)
            throw 1;
    }
    catch(int x) {
        cout << "Numele proprietarului nu este valid!";
        exit(0);
    }
    cout << "Dati suprafata utila: ";
    in >> a.suprUtila;
    cout << "Dati pretul pe metrul patrat: ";
    in >> a.pretMP;
    cout << "Dati discountul aplicat: ";
    in >> a.discount;
    try {
        if(a.discount < 0 || a.discount > 10)
            throw 1;
    }
    catch(int x) {
        cout << "Discount-ul aplicat este invalid!";
        exit(0);
    }
    cout << "Dati etajul la care se afla apartamentul: ";
    in >> a.etaj;
    return in;
}

ostream& operator << (ostream& out, Apartament& a) {
    a.afisare();
}

class Casa:public Locuinta {
    double mpCurte;
    int nrEtaje;
    double pretmpCurte;
    vector <double> suprEtaje;
public:
    double calculChirie();
    Casa(string, double, double, double, double, int, double, vector < double > );
    Casa(const Casa&);
    ~Casa();
    void afisare();
    Casa& operator = (Casa&);
    friend istream& operator >> (istream&, Casa&);
    friend ostream& operator << (ostream&, Casa&);
};

Casa::Casa(string n = "", double s = 0, double d = 0, double p = 0,double m = 0, int nr_et = 0, double p_curte = 0, vector <double> s_e = vector < double > ()):Locuinta(n, s, d, p) {
    mpCurte = m;
    nrEtaje = nr_et;
    pretmpCurte = p_curte;
    int i;
    for(i = 0; i < s_e.size(); i++) {
        suprEtaje.push_back(s_e[i]);
    }
}

Casa::Casa(const Casa& c) {
    numeProprietar = c.numeProprietar;
    suprUtila = c.suprUtila;
    discount = c.discount;
    pretMP = c.pretMP;
    mpCurte = c.mpCurte;
    nrEtaje = c.nrEtaje;
    pretmpCurte = c.pretmpCurte;
    int i;
    for(i = 0; i < c.suprEtaje.size(); i++) {
        suprEtaje.push_back(c.suprEtaje[i]);
    }
}

Casa::~Casa() {
    numeProprietar = "";
    suprUtila = 0;
    discount = 0;
    pretMP = 0;
    mpCurte = 0;
    nrEtaje = 0;
    pretmpCurte = 0;
    suprEtaje.clear();
}

double Casa::calculChirie() {
    double chirie = 0;
    chirie = pretMP*suprUtila;
    chirie += pretmpCurte*mpCurte;
    chirie -= discount / 100 *chirie;
    return chirie;
}

void Casa::afisare() {
    Locuinta::afisare();
    cout << "Casa are " << nrEtaje << " etaje." << endl;
    int i;
    for(i = 0; i < suprEtaje.size(); i++) {
        cout << "Etajul " << i << " are o suprafata utila de " << suprEtaje[i] << " metri patrati." << endl;
    }
    cout << "Suprafata curtii: " << mpCurte << endl;
    cout << "Pretul pe metru patrat de curte: " << pretmpCurte << endl;
    cout << "Pretul chiriei pentru casa este de " << calculChirie() << " lei." << endl << endl;
}

Casa& Casa::operator = (Casa& c) {
    if(this !=  &c) {
        numeProprietar = c.numeProprietar;
        suprUtila = c.suprUtila;
        discount = c.discount;
        pretMP = c.pretMP;
        mpCurte = c.mpCurte;
        nrEtaje = c.nrEtaje;
        pretmpCurte = c.pretmpCurte;
        int i;
        for(i = 0; i < c.suprEtaje.size(); i++) {
            suprEtaje.push_back(c.suprEtaje[i]);
        }
    }
    return *this;
}

istream& operator >> (istream& in, Casa& c) {
    int ok;
    cout << "\nDati numele si prenumele proprietarului: ";
    string nume, prenume;
    in >> nume >> prenume;
    c.numeProprietar = nume + " ";
    c.numeProprietar += prenume;
    try {
        int i;
        ok = 1;
        for(i = 0;i < c.numeProprietar.size();i++) {
            if(c.numeProprietar[i] - '0' >= 0 && c.numeProprietar[i] - '0' <= 9)
                ok = 0;
        }
        if(ok==0)
            throw 1;
    }
    catch(int x) {
        cout << "Numele proprietarului nu este valid!";
        exit(0);
    }
    cout << "Dati suprafata utila: ";
    in >> c.suprUtila;
    cout << "Dati pretul pe metrul patrat: ";
    in >> c.pretMP;
    cout << "Dati discountul aplicat: ";
    in >> c.discount;
    try {
        if(c.discount < 0 || c.discount > 10)
            throw 1;
    }
    catch(int x) {
        cout << "Discount-ul aplicat este invalid!";
        exit(0);
    }
    cout << "Dati suprafata curtii: ";
    in >> c.mpCurte;
    cout << "Dati pretul pe metrul patrat al curtii: ";
    in >> c.pretmpCurte;
    cout << "Dati numarul de etaje al casei: ";
    in >> c.nrEtaje;
    double supr;
    cout << "Dati suprafata fiecarui etaj in parte" << endl;
    for(int i = 0; i < c.nrEtaje; i++) {
        cout << "Etajul " << i << " : ";
        in >> supr;
        c.suprEtaje.push_back(supr);
    }
    return in;
}

ostream& operator << (ostream& out, Casa& c) {
    c.afisare();
}


//clasa template gestiune
template <class T>
class Gestiune {
    vector <T> vLoc;
    static int nrCase, nrAp;
public:
    vector <T> operator += (Apartament);
    vector <T> operator += (Casa);
    friend ostream& operator << (ostream&, Gestiune < T > );
    int getNrCase(){return nrCase;};
    int getNrAp(){return nrAp;};
};
template <class T>
int Gestiune < T > ::nrCase = 0;
template <class T>
int Gestiune < T > ::nrAp = 0;

template <class T>
vector <T> Gestiune < T > ::operator += (Apartament a) {
    vLoc.push_back(new Apartament(a));
    nrAp++;
    return vLoc;
}

template <class T>
vector <T> Gestiune < T > ::operator += (Casa c) {
    vLoc.push_back(new Casa(c));
    nrCase++;
    return vLoc;
}

template <class T>
ostream& operator << (ostream& out, Gestiune < T >  g) {
    out << "Chiria aferenta fiecarei locuinte: " << endl;
    for(int i = 0; i < g.vLoc.size(); i++)
        out << g.vLoc[i].calculChirie() << endl;
    return out;
}

//specializare pentru clasa template, cu string ca tip de date, in care tin clientii firmei
template < >
class Gestiune < string >  {
    vector <string> vC;
    static int nrClienti;
public:
    vector <string> operator += (Client);
    int getNrClienti() {
        return nrClienti;
    }
    friend ostream& operator << (ostream&, Gestiune < string > );
};
int Gestiune < string > ::nrClienti = 0;

vector <string>Gestiune < string > ::operator += (Client c) {
    vC.push_back(c.getNume());
    nrClienti++;
    return vC;
}

ostream& operator << (ostream& out, Gestiune < string >  g) {
    out << "Clientii firmei: " << endl;
    for(int i = 0; i < g.vC.size(); i++) {
        out << g.vC[i] << endl;
    }
    return out;
}

int main() {
    //citirea a n obiecte
    int n, i, opt;
    cout << "Dati numarul de imobiliare: ";
    cin >> n;
    Locuinta** lp;
    lp = new Locuinta*[n];
    for(i = 0; i < n; i++) {
        cout << "1-Citirea informatiilor unui apartament\n2-Citirea informatiilor unei casa\n";
        cin >> opt;
        while(opt < 1 || opt > 2) {
            cout << "Optiune invalida! Alegeti 1 sau 2!";
            cin >> opt;
        }
        if(opt==1) {
            lp[i] = new Apartament;
        }
        else {
            lp[i] = new Casa;
        }
        if(Apartament *locuinta_curenta = dynamic_cast < Apartament* > (lp[i]))
            cin >> *locuinta_curenta;
        if(Casa *locuinta_curenta = dynamic_cast < Casa* > (lp[i]))
            cin >> *locuinta_curenta;
    }
    for(i = 0; i < n; i++) {
        cout << *lp[i] << endl;
    }
    Gestiune < string >  clienti;
    Client c1;
    cin >> c1;
    clienti += c1;
    cout << "Numarul total de clienti: " << clienti.getNrClienti() << endl;
    cout << clienti;

    Gestiune < Locuinta* >  loc;
    Casa c;
    Apartament a;
    cin >> c >> a;
    loc += c;
    loc += a;
    cout << "Numarul total de case: " << loc.getNrCase() << endl;
    cout << "Numarul total de apartamente: " << loc.getNrAp() << endl;
    return 0;
}

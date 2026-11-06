
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// Classe generique ArrayDyn
template <typename T>
class ArrayDyn {
private:
    T* data;
    size_t capacite;
    size_t taille;

public:

    // 1. Constructeur par defaut
    ArrayDyn() {
        data = nullptr;
        capacite = 0;
        taille = 0;
    }

    // 2. Constructeur avec capacite initiale
    ArrayDyn(size_t c) {
        capacite = c;
        taille = 0;

        if (capacite > 0)
            data = new T[capacite];
        else
            data = nullptr;
    }

    // 3. Constructeur de copie
    ArrayDyn(const ArrayDyn& autre) {
        taille = autre.taille;
        capacite = autre.capacite;

        if (capacite > 0) {
            data = new T[capacite];

            for (size_t i = 0; i < taille; i++) {
                data[i] = autre.data[i];
            }
        }
        else {
            data = nullptr;
        }
    }

    // 4. Operateur d'affectation
    ArrayDyn& operator=(const ArrayDyn& autre) {
        if (this != &autre) {

            T* nouveau = nullptr;

            if (autre.capacite > 0) {
                nouveau = new T[autre.capacite];

                for (size_t i = 0; i < autre.taille; i++) {
                    nouveau[i] = autre.data[i];
                }
            }

            delete[] data;

            data = nouveau;
            taille = autre.taille;
            capacite = autre.capacite;
        }

        return *this;
    }

    // 5. Destructeur
    ~ArrayDyn() {
        delete[] data;
    }

    // 6. Agrandir la capacite
    void agrandir() {
        size_t nouvelleCapacite =
            (capacite == 0) ? 1 : capacite * 2;

        T* nouveau = new T[nouvelleCapacite];

        for (size_t i = 0; i < taille; i++) {
            nouveau[i] = data[i];
        }

        delete[] data;

        data = nouveau;
        capacite = nouvelleCapacite;
    }

    // 7. Ajouter un element
    void push_back(const T& element) {
        if (taille == capacite) {
            agrandir();
        }

        data[taille] = element;
        taille++;
    }

    // 8. Supprimer le dernier element
    void pop_back() {
        if (taille == 0) {
            throw out_of_range("Tableau vide !");
        }

        taille--;
    }

    // 9. Acces avec controle des bornes
    T& operator[](size_t indice) {
        if (indice >= taille) {
            throw out_of_range("Indice invalide !");
        }

        return data[indice];
    }

    const T& operator[](size_t indice) const {
        if (indice >= taille) {
            throw out_of_range("Indice invalide !");
        }

        return data[indice];
    }

    // 10. Classe Iterator
    class Iterator {
    private:
        T* ptr;

    public:
        Iterator(T* p = nullptr) {
            ptr = p;
        }

        // Acces a l'element
        T& operator*() const {
            return *ptr;
        }

        // Incrementer
        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        // Decrementer
        Iterator& operator--() {
            --ptr;
            return *this;
        }

        // Comparaison
        bool operator!=(const Iterator& autre) const {
            return ptr != autre.ptr;
        }
    };

    // 11. Debut du tableau
    Iterator begin() {
        return Iterator(data);
    }

    // 12. Fin du tableau
    Iterator end() {
        return Iterator(data + taille);
    }

    // Afficher la taille
    size_t getTaille() const {
        return taille;
    }

    // Afficher la capacite
    size_t getCapacite() const {
        return capacite;
    }
};

// Classe personnelle pour le test
class Personne {
private:
    string nom;
    int age;

public:
    Personne() {
        nom = "";
        age = 0;
    }

    Personne(string n, int a) {
        nom = n;
        age = a;
    }

    void afficher() const {
        cout << "Nom : " << nom
             << ", Age : " << age << endl;
    }
};

// Programme principal
int main() {

    // TEST 1 : Tableau d'entiers
    cout << "===== TABLEAU D'ENTIERS =====" << endl;

    ArrayDyn<int> t1;

    t1.push_back(10);
    t1.push_back(20);
    t1.push_back(30);
    t1.push_back(40);

    for (auto &e : t1) {
        cout << e << " ";
    }

    cout << endl;

    // TEST 2 : Tableau de chaines
    cout << "\n===== TABLEAU DE STRINGS =====" << endl;

    ArrayDyn<string> t2;

    t2.push_back("Bonjour");
    t2.push_back("C++");
    t2.push_back("Programmation");

    for (auto &e : t2) {
        cout << e << endl;
    }

    // TEST 3 : Tableau d'objets Personne
    cout << "\n===== TABLEAU DE PERSONNES =====" << endl;

    ArrayDyn<Personne> t3;

    t3.push_back(Personne("Ali", 20));
    t3.push_back(Personne("Sara", 22));
    t3.push_back(Personne("Youssef", 25));

    for (auto &e : t3) {
        e.afficher();
    }

    // TEST 4 : Constructeur de copie
    cout << "\n===== CONSTRUCTEUR DE COPIE =====" << endl;

    ArrayDyn<int> t4(t1);

    for (auto &e : t4) {
        cout << e << " ";
    }

    cout << endl;

    // TEST 5 : Operateur d'affectation
    cout << "\n===== OPERATEUR D'AFFECTATION =====" << endl;

    ArrayDyn<int> t5;
    t5 = t1;

    for (auto &e : t5) {
        cout << e << " ";
    }

    cout << endl;

    // TEST 6 : pop_back
    cout << "\n===== SUPPRESSION =====" << endl;

    t1.pop_back();

    for (auto &e : t1) {
        cout << e << " ";
    }

    cout << endl;

    // TEST 7 : Acces avec []
    cout << "\n===== ACCES PAR INDICE =====" << endl;

    try {
        cout << "Element 0 : " << t1[0] << endl;

        t1[1] = 100;
        cout << "Nouvelle valeur : " << t1[1] << endl;

        cout << t1[10] << endl;
    }
    catch (const out_of_range& e) {
        cout << "Erreur : " << e.what() << endl;
    }

    // TEST 8 : Iterateur
    cout << "\n===== ITERATEUR =====" << endl;

    auto it = t1.begin();

    if (it != t1.end()) {
        cout << "Premier element : " << *it << endl;

        ++it;

        if (it != t1.end()) {
            cout << "Deuxieme element : " << *it << endl;
        }
    }

    return 0;
}

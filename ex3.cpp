
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstddef>
#include <utility>
using namespace std;

// Exception : pile pleine
class StackOverflow : public exception {
public:
    const char* what() const noexcept override {
        return "Erreur : la pile est pleine !";
    }
};

// Exception : pile vide
class StackUnderflow : public exception {
public:
    const char* what() const noexcept override {
        return "Erreur : la pile est vide !";
    }
};

// Classe Stack generique
template <typename T>
class Stack {
private:
    unique_ptr<T[]> data;
    size_t capacity;
    size_t top;

public:
    // Constructeur avec capacite par defaut
    Stack(size_t cap = 100)
        : data(make_unique<T[]>(cap)),
          capacity(cap),
          top(0) {
        if (cap == 0)
            throw invalid_argument("La capacite doit etre positive.");
    }

    // Constructeur a partir d'iterateurs
    template <typename Iterator>
    Stack(Iterator begin, Iterator end)
        : capacity(0), top(0) {

        // Calculer le nombre d'elements
        for (Iterator it = begin; it != end; ++it)
            ++capacity;

        data = make_unique<T[]>(capacity);

        // Copier les elements dans la pile
        for (Iterator it = begin; it != end; ++it)
            data[top++] = *it;
    }

    // Ajouter un element
    void push(const T& value) {
        if (top == capacity)
            throw StackOverflow();

        data[top++] = value;
    }

    // Retirer le dernier element
    void pop() {
        if (empty())
            throw StackUnderflow();

        --top;
    }

    // Consulter le sommet sans retirer l'element
    const T& peek() const {
        if (empty())
            throw StackUnderflow();

        return data[top - 1];
    }

    // Verifier si la pile est vide
    bool empty() const {
        return top == 0;
    }

    // Nombre d'elements
    size_t size() const {
        return top;
    }

    // Capacite maximale
    size_t getCapacity() const {
        return capacity;
    }
};

// Fonction principale
int main() {
    try {
        cout << "=== Test avec des entiers ===" << endl;

        Stack<int> s(3);

        s.push(10);
        s.push(20);
        s.push(30);

        cout << "Sommet : " << s.peek() << endl;

        try {
            s.push(40);
        }
        catch (const StackOverflow& e) {
            cout << e.what() << endl;
        }

        s.pop();
        cout << "Nouveau sommet : " << s.peek() << endl;


        cout << "\n=== Test avec une collection ===" << endl;

        vector<string> noms = {
            "Ali", "Sara", "Youssef"
        };

        Stack<string> s2(noms.begin(), noms.end());

        cout << "Sommet : " << s2.peek() << endl;

        s2.push("Amine");

        cout << "Nouveau sommet : " << s2.peek() << endl;


        cout << "\n=== Test avec un grand nombre d'objets ===" << endl;

        Stack<int> grandePile(100000);

        for (int i = 0; i < 100000; i++) {
            grandePile.push(i);
        }

        cout << "Nombre d'elements : "
             << grandePile.size() << endl;

        cout << "Sommet : "
             << grandePile.peek() << endl;


        cout << "\n=== Test StackUnderflow ===" << endl;

        Stack<double> vide(5);

        try {
            vide.pop();
        }
        catch (const StackUnderflow& e) {
            cout << e.what() << endl;
        }

    }
    catch (const exception& e) {
        cerr << "Erreur : " << e.what() << endl;
    }

    return 0;
}


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <cassert>
#include <concepts>
using namespace std;

// 1. Concept Sortable
template<typename T>
concept Sortable = requires(T a, T b) {
    { a < b } -> convertible_to<bool>;
};

// 2. Foncteur pour le tri croissant
template<typename T>
struct Asc {
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

// 3. Foncteur pour le tri decroissant
template<typename T>
struct Desc {
    bool operator()(const T& a, const T& b) const {
        return b < a;
    }
};

// 4. Fonction quickSort
template<Sortable T, typename Comp = less<T>>
void quickSort(vector<T>& v, Comp comp = Comp{}) {

    if (v.size() <= 1)
        return;

    // Utilisation de sort avec le comparateur
    sort(v.begin(), v.end(), comp);
}

// 5. Structure utilisateur
struct Personne {
    string nom;
    int age;

    // Operateur <
    bool operator<(const Personne& p) const {
        return age < p.age;
    }
};

// 6. Affichage d'un vecteur
template<typename T>
void afficher(const vector<T>& v) {
    for (const auto& element : v)
        cout << element << " ";

    cout << endl;
}

// Surcharge de << pour Personne
ostream& operator<<(ostream& os, const Personne& p) {
    return os << p.nom << "(" << p.age << ")";
}

// 7. Tests
int main() {

    // Test 1 : vector<int>
    cout << "=== Test avec int ===" << endl;

    vector<int> nombres = {8, 3, 6, 1, 9, 2};

    quickSort(nombres, Asc<int>{});
    afficher(nombres);

    assert(is_sorted(nombres.begin(), nombres.end()));

    quickSort(nombres, Desc<int>{});
    afficher(nombres);

    assert(is_sorted(nombres.begin(), nombres.end(),
                     Desc<int>{}));


    // Test 2 : vector<string>
    cout << "\n=== Test avec string ===" << endl;

    vector<string> mots = {
        "Banane", "Pomme", "Abricot", "Orange"
    };

    quickSort(mots, Asc<string>{});
    afficher(mots);

    assert(is_sorted(mots.begin(), mots.end()));

    quickSort(mots, Desc<string>{});
    afficher(mots);

    assert(is_sorted(mots.begin(), mots.end(),
                     Desc<string>{}));


    // Test 3 : structure Personne
    cout << "\n=== Test avec Personne ===" << endl;

    vector<Personne> personnes = {
        {"Ali", 25},
        {"Sara", 19},
        {"Youssef", 30},
        {"Amine", 22}
    };

    quickSort(personnes, Asc<Personne>{});
    afficher(personnes);

    assert(is_sorted(personnes.begin(), personnes.end()));

    quickSort(personnes, Desc<Personne>{});
    afficher(personnes);

    assert(is_sorted(personnes.begin(), personnes.end(),
                     Desc<Personne>{}));

    cout << "\nTous les tests sont reussis !" << endl;

    return 0;
}


#include <iostream>
using namespace std;

// Classe generique Matrice
template <typename T, int N, int M>
class Matrice {
private:
    T data[N][M];

public:

    // 1. Constructeur par defaut
    Matrice() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j] = 0;
            }
        }
    }

    // 2. Constructeur avec liste d'initialisation
    Matrice(T valeurs[N][M]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j] = valeurs[i][j];
            }
        }
    }

    // 3. Surcharge de l'operateur +
    Matrice operator+(const Matrice& autre) const {
        Matrice resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                resultat.data[i][j] =
                    data[i][j] + autre.data[i][j];
            }
        }

        return resultat;
    }

    // 4. Surcharge de l'operateur -
    Matrice operator-(const Matrice& autre) const {
        Matrice resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                resultat.data[i][j] =
                    data[i][j] - autre.data[i][j];
            }
        }

        return resultat;
    }

    // 5. Multiplication de matrices
    template <int P>
    Matrice<T, N, P> operator*(
        const Matrice<T, M, P>& autre) const {

        Matrice<T, N, P> resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < P; j++) {
                resultat.data[i][j] = 0;

                for (int k = 0; k < M; k++) {
                    resultat.data[i][j] +=
                        data[i][k] * autre.data[k][j];
                }
            }
        }

        return resultat;
    }

    // 6. Fonction amie pour afficher la matrice
    template <typename U, int L, int C>
    friend ostream& operator<<(
        ostream& os, const Matrice<U, L, C>& mat);
};

// Definition de l'operateur <<
template <typename T, int N, int M>
ostream& operator<<(ostream& os,
                    const Matrice<T, N, M>& mat) {

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            os << mat.data[i][j] << "\t";
        }
        os << endl;
    }

    return os;
}

// Programme principal
int main() {

    // TEST 1 : Matrices d'entiers
    cout << "===== MATRICES D'ENTIERS =====" << endl;

    int a[2][2] = {
        {1, 2},
        {3, 4}
    };

    int b[2][2] = {
        {5, 6},
        {7, 8}
    };

    Matrice<int, 2, 2> A(a);
    Matrice<int, 2, 2> B(b);

    cout << "\nMatrice A :" << endl;
    cout << A;

    cout << "\nMatrice B :" << endl;
    cout << B;

    // Addition
    Matrice<int, 2, 2> S = A + B;

    cout << "\nA + B :" << endl;
    cout << S;

    // Soustraction
    Matrice<int, 2, 2> D = A - B;

    cout << "\nA - B :" << endl;
    cout << D;

    // Multiplication
    Matrice<int, 2, 2> P = A * B;

    cout << "\nA * B :" << endl;
    cout << P;


    // TEST 2 : Matrices de doubles
    cout << "\n===== MATRICES DE DOUBLES =====" << endl;

    double x[2][2] = {
        {1.5, 2.5},
        {3.5, 4.5}
    };

    double y[2][2] = {
        {2.0, 3.0},
        {4.0, 5.0}
    };

    Matrice<double, 2, 2> X(x);
    Matrice<double, 2, 2> Y(y);

    cout << "\nMatrice X :" << endl;
    cout << X;

    cout << "\nMatrice Y :" << endl;
    cout << Y;

    Matrice<double, 2, 2> Z = X + Y;

    cout << "\nX + Y :" << endl;
    cout << Z;

    Matrice<double, 2, 2> R = X * Y;

    cout << "\nX * Y :" << endl;
    cout << R;


    // TEST 3 : Multiplication de tailles differentes
    cout << "\n===== MULTIPLICATION 2x3 PAR 3x2 =====" << endl;

    int c[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    int d[3][2] = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    Matrice<int, 2, 3> C(c);
    Matrice<int, 3, 2> E(d);

    Matrice<int, 2, 2> F = C * E;

    cout << "\nResultat :" << endl;
    cout << F;

    return 0;
}

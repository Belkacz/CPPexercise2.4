#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

int take(string question) {
    int data;
    cout << question << endl;
    cin >> data;
    cout << endl;
    return data;
}

void randomData(int N, int A[][6], int minNum, int maxNum) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % (maxNum - minNum + 1) + minNum;
        }
    }
}

void wroteMatrix(int matrix[0][6], int N, string text){
    cout << text << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << " " << setw(2) << matrix[i][j] << " |";
        }
        cout << endl;
    }
}

string saveToFile(int matrix[][6], int N){
    string filename;
    cout << "Podaj nazwę pliku: ";
    cin >> filename;
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                file << matrix[i][j] << "|";
            }
            file << endl;
        }
    } else {
        cout << "Ups, coś poszło nie tak nie mogę otworzyć plisku" << endl;
    }
    file.close();
    return filename;
}

void loadFromFile(int matrix[][6], int N, string filename){
    ifstream file(filename);
    int tempMatrix[6][6]; 
    if (file.is_open()) {
        int row = 0;
        int column = 0;
        while(!file.eof()){
            cout << file.get();
        if(file.get() != '|'){
            row++;
        }else{
            file >> tempMatrix[column][row];
        }
        if(row >=6){
            row = 0;
            column ++;
        }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matrix[i][j] = tempMatrix[j][i];
            }
        }
    } else {
        cout << "Ups, coś poszło nie tak nie mogę otworzyć plisku" << endl;
    }
    file.close();
}

void menu() {
    const int N = 6;
    int A[6][6];
    int minNum, maxNum;
    string filename;
    srand(time(0));

    minNum = take("Podaj poczatek zakresu (liczbe minimalna): ");
    maxNum = take("Podaj koniec zakresu (liczbe maksymalna): ");
    randomData(N, A, minNum, maxNum);
    wroteMatrix(A, N, "macierz 6x6: ");
    filename = saveToFile(A, N);
    loadFromFile(A, N, filename);
    wroteMatrix(A, N, "macierz odwrocna 6x6: ");
}

int main() {
    menu();
    return 0;
}

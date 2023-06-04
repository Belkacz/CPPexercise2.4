#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

const int N = 6;

struct Pracownik{
    string nazwisko;
    int staz;
    int pensja;
};

int take(string question) {
    int data;
    cout<< endl;
    cout << question << endl;
    cin >> data;
    cout << endl;
    return data;
}

void randomData(int A[][N], int minNum, int maxNum) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % (maxNum - minNum + 1) + minNum;
        }
    }
}

void wroteMatrix(int matrix[0][N], int N, string text){
    cout << text << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << " " << setw(2) << matrix[i][j] << " |";
        }
        cout << endl;
    }
}

string saveToFile(int matrix[][N], int N){
    string filename;
    cout << endl;
    cout << "Podaj nazwę pliku:";
    cin >> filename;
    cout << endl;
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

void loadFromFile1(int matrix[][N], int N, string filename){
    int tempMatrix[N][N];

    ifstream file(filename);
    if (file.is_open()) {
        int row = 0;
        int column = 0;
        char element;

        string array = "";
        while(!file.eof()){
            file.get(element);
            if(element != '|'){
                array += element;
                if(element == '\n'){
                    row ++;
                    column = 0;
                }
            } else {
                matrix[column][row] = stoi(array);
                array = "";
                column ++;
            }
        }
    } else {
        cout << "Ups, coś poszło nie tak nie mogę otworzyć plisku" << endl;
    }
    file.close();
}

void loadFromFile2(Pracownik* tab, string filename){
    ifstream file(filename);
    if (file.is_open()) {
        int whiteSpace = 0;
        int row = 0;
        string array = "";
        int tempStaz = 0;
        int tempPensja = 0;
        while(file.peek()!=EOF){
            char element;
            file.get(element);
            if(element == ' ' || element == '\n'){
                if(whiteSpace == 0){
                    tab[row].nazwisko = array;
                    //cout <<" nazwisko "<< array;
                }
                if(whiteSpace == 1){
                    //cout <<" staz "<< array;
                    tab[row].staz = stoi(array);
                }
                if(whiteSpace == 2){
                    //cout <<" pensja "<< array;
                    tab[row].pensja = stoi(array);
                }
                if(element == ' '){
                    whiteSpace ++;
                }
                if(element == '\n'){
                    row ++;
                    whiteSpace = 0;
                }
                array = "";
            } else {
                array += element;
            }
        }
        tab[row].pensja = stoi(array);
        file.close();
    }
}

void wroteWorkers(Pracownik* tab, int L, string text){
    cout << endl;
    cout << text << endl;
    for(int i = 0; i < L; i ++){
        cout << left << "| nazwisko: " << setw(9) << tab[i].nazwisko << " | staż: " << setw(2) << tab[i].staz << " | pensja: " << setw(4) <<tab[i].pensja << " |" << endl;
    }
}

void sortWorkers(Pracownik* tab, int L){
    bool workersSorted = false;

    while(workersSorted != true){
        Pracownik tempWorker;
        int swaps = 0;
        for(int i = 0; i < L; i++){
            if(i != 0){
                if(tab[i].staz > tab[i-1].staz){
                    tempWorker = tab[i-1];
                    tab[i-1] = tab[i];
                    tab[i] = tempWorker;
                    swaps ++;
                }
            }
        }
        if(swaps == 0){
            workersSorted = true;
        }
    }

}

// double avaregeStaz(Pracownik* tab, int L, int S){
    
// }

void menu() {
    // ZADANIE 1
    int A[N][N];
    int minNum, maxNum;
    string filename;
    srand(time(0));

    minNum = take("Podaj poczatek zakresu (liczbe minimalna): ");
    maxNum = take("Podaj koniec zakresu (liczbe maksymalna): ");
    randomData(A, minNum, maxNum);
    wroteMatrix(A, N, "macierz 6x6: ");
    filename = saveToFile(A, N);
    loadFromFile1(A, N, filename);
    wroteMatrix(A, N, "macierz odwrocna 6x6: ");

    // ZADANIE 2
    int S = 0;
    int L = 10;
    Pracownik* tab = new Pracownik[L];
    S = take("Podaj minimalna wysokość stażu do wyliczeń (średnia pensja) ");
    Pracownik* topWorkersTab = new Pracownik[S];
    loadFromFile2(tab, "pracownicy.txt");
    wroteWorkers(tab, L, "Lista pracowników ");
    sortWorkers(tab, L);
    wroteWorkers(tab, L, "Lista pracowników posortowana stazem ");

}

int main() {
    menu();
    return 0;
}

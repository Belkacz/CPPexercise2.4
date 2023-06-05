// Łukasz Belka nr. indeksu 156162
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

    cout << question << endl;
    cin >> data;
    cout<< endl;
    return data;
}

void randomData(int A[][N], int minNum, int maxNum) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % (maxNum - minNum + 1) + minNum;
        }
    }
}

void wroteMatrix(int matrix[][N], int N, string text){
    cout << text << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << " " << setw(2) << matrix[i][j] << " |";
        }
        cout << endl;
    }
}

string saveToFile(int matrix[][N], int N, bool &cantOpenFileFlag){
    string filename;
    cout << endl;
    cout << "Podaj nazwę pliku: ";
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
        cout << "Ups, cos poszlo nie tak nie moge otworzyc pliku, zamykam" << endl;
        cantOpenFileFlag = true;
    }
    file.close();
    cout << "dane zapisane pomyslnie do pliku: " << filename << endl;
    return filename;
}

void loadFromFile(int matrix[][N], int N, string filename, bool &cantOpenFileFlag){
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
        cout << "Ups, cos poszlo nie tak nie moge otworzyc pliku, zamykam" << endl;
        cantOpenFileFlag = true;
    }
    file.close();
}


int getNumberOfWorkers(string filename, bool &cantOpenFileFlag){
    ifstream file(filename);
    int L = 0;
    //int userInput = 0;
    //cout << "ilu chesz swczytac pracownikow? " << endl;
    //cin >> userInput;
    if (file.is_open()) {
        string line;
        while (!file.eof()){
            getline (file, line);
            L ++;
        }
    } else {
        cout << "Ups, cos poszlo nie tak nie moge otworzyc pliku, zamykam" << endl;
        cantOpenFileFlag = true;
    }
    // if(userInput > L){
    //     cout << "podana liczba przekracza maksymlna liczbe wczytanych praconików, wczytno" << L << endl;
    //     return L;
    // } else {
    //     return userInput;
    // }
    return L;
}

void loadFromFile(Pracownik* tab, string filename, bool &cantOpenFileFlag){
    ifstream file(filename);
    if (file.is_open()) {
        int whiteSpace = 0;
        int row = 0;
        string array = "";
        int tempStaz = 0;
        int tempPensja = 0;
        while(file.peek()!= EOF){
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
    } else {
        cout << "Ups, cos poszlo nie tak nie moge otworzyc pliku, zamykam" << endl;
        cantOpenFileFlag = true;
    }
}

void wroteWorkers(Pracownik* tab, int L, string text){
    cout << endl;
    cout << text << endl;
    for(int i = 0; i < L; i ++){
        cout << left << "| nazwisko: " << setw(9) << tab[i].nazwisko << " | staz: " << setw(2) << tab[i].staz << " | pensja: " << setw(4) <<tab[i].pensja << " |" << endl;
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

void avaregeTopSalary(Pracownik* tab, int L, int S){
    double avgSallary = 0;
    double avgTopSalary = 0;
    int odestWorker = 0;
    for(int i = 0; i < L; i++){
        if(i > 0 && tab[i].staz > tab[i-1].staz){
            odestWorker = i;
        }
        avgSallary += tab[i].pensja;
    }
    avgSallary = avgSallary / L;
    int numberOfTopWorkers = 0;
    for(int i = 0; i < L; i++){
        if(tab[i].staz >= S){
            avgTopSalary += tab[i].pensja;
            numberOfTopWorkers ++;
        }
        
    }
    cout << "srednia pensja ogolem: " << avgSallary << endl;
    cout << endl;
    if(numberOfTopWorkers == 0){
        avgTopSalary = 0;
        cout << "podany staz " << S <<" jest wiekszy niz maksymalny staz ktoregokolwiek pracownika, nawet wielce zalozonego Pana "
            << tab[odestWorker].nazwisko << " z niebagatelnym stazem " << tab[odestWorker].staz << " jednostek " << endl;
    } else {
        avgTopSalary = avgTopSalary / numberOfTopWorkers;
        cout << "srednia pensja pracownikow ze stazem rownym lub wiekszym " << S <<", wynosi: " << avgTopSalary << endl;
    }

}

void analphabeticSort(Pracownik* tab, int L){
    bool workersSorted = false;

    while(workersSorted != true){
        Pracownik tempWorker;
        int swaps = 0;
        for(int i = 0; i < L; i++){
            if(i != 0){
                if(tab[i].nazwisko < tab[i-1].nazwisko){
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

string saveToFile(Pracownik* matrix, int N, bool &cantOpenFileFlag){
    string filename;
    cout << endl;
    cout << "Podaj nazwe pliku: ";
    cin >> filename;
    cout << endl;
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < N; i++) {
            file << matrix[i].nazwisko << " | ";
            file << matrix[i].staz << " | ";
            file << matrix[i].pensja << " | ";
            file << endl;
        }
    } else {
        cout << "Ups, cos poszlo nie tak nie moge otworzyc pliku, zamykam" << endl;
        cantOpenFileFlag = true;
    }
    file.close();
    return filename;
}

int menu() {
    // ZADANIE 1
    cout << "Lukasz Belka nr. indeksu 156162, grupa D1, semestr 2, rok 1" << endl;
    int A[N][N];
    int minNum, maxNum;
    bool cantOpenFileFlag = false;
    string filename;
    srand(time(0));
    cout<< endl;
    minNum = take("Podaj poczatek zakresu (liczbe minimalna): ");
    maxNum = take("Podaj koniec zakresu (liczbe maksymalna): ");
    randomData(A, minNum, maxNum);
    wroteMatrix(A, N, "macierz 6x6: ");
    filename = saveToFile(A, N,cantOpenFileFlag);
    if(cantOpenFileFlag == true){
        return 0;
    }
    loadFromFile(A, N, filename, cantOpenFileFlag);
    if(cantOpenFileFlag == true){
        return 0;
    }
    wroteMatrix(A, N, "macierz odwrocona 6x6: ");

    // ZADANIE 2
    int S = 0;
    //int L = 10; //basic value
    int L = getNumberOfWorkers("pracownicy.txt", cantOpenFileFlag);
    if(cantOpenFileFlag == true){
        return 0;
    }
    Pracownik* tab = new Pracownik[L];

    loadFromFile(tab, "pracownicy.txt", cantOpenFileFlag);
    if(cantOpenFileFlag == true){
        delete [] tab;
        return 0;
    }
    wroteWorkers(tab, L, "Lista pracownikow ");
    sortWorkers(tab, L);
    wroteWorkers(tab, L, "Lista pracownikow posortowana stazem ");
    cout << endl;
    S = take("Podaj minimalna wysokosc stazu do wyliczen (srednia pensja) ");
    avaregeTopSalary(tab, L, S);
    analphabeticSort(tab, L);
    wroteWorkers(tab, L, "Lista pracownikow posortowana alfabetycznie ");
    string workerListFileName = saveToFile(tab, L, cantOpenFileFlag);
    if(cantOpenFileFlag == true){
        delete [] tab;
        return 0;
    }
    cout << "Posortowana tablica pracownikow zapisana do pliku o nazwie: " << workerListFileName << endl;

    delete [] tab;
    return 0;
}

int main() {
    menu();
    return 0;
}

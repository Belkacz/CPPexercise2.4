// £ukasz Belka indeks nr. 156162

#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

int take(string qestion){
    int data;
    cout << qestion << endl;
    cin >> data >> endl;
    return data
}


void randomData(int N, int A[][N], int minNum, int maxNum){
    for (int i = 0; i < numberOfYears; i++)
    {
        for (int j = 0; j < numberOfMonths; j++)
        {
            A[i][j] = rand() % maxNum + minNum;
        }
    }
}
void menu(){
    const int range = 6;
    int N = 6;
    int A[N][N];
    int minNum, maxNum;
    srand(time(0));
    
    int minNum = take("podaj poczatek zakresu (iczbe minimalna) : ");
    int maxNum = take("podaj koniec zakresu (iczbe maksymalna) : ");
    randomData(N, A, minNum, maxNum);
}


int main(){

    menu();

    return 0;
}

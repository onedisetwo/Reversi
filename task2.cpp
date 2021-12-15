#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin;
ofstream fout;

class board{
public:
    vector<vector<short> > board;

    //Изменение размера и заполнение до стартовой позиции
    void start(){
        board.resize(9);
        for(int i=0;i<9;i++){
            board[i].resize(9);
            for(int k=0;k<9;k++){
                board[i][k]=0;
                if((i==4 && k==4) || (i==5 && k==5)){
                    board[i][k]=1;
                }
                if((i==5 && k==4) || (i==4 && k==5)){
                    board[i][k]=2;
                }
            }
        }
    }

    //Ввод доски
    void input(){
        for(int i=1;i<9;i++){
            string s;
            fin>>s;
            for(int k=1;k<9;k++){
                board[k][9-i]=(int)(s[k-1])-48;
            }
        }
    }

    //Напечатать доску
    void print(){
        fout<<endl;
        for(int i=1;i<9;i++){
            for(int k=1;k<9;k++){
                fout<<board[k][9-i];
            }
            fout<<endl;
        }
    }

    //Проверка выигрыша: победитель, кол-во черных, кол-во белых
    vector<short> wincheck_3(){
        vector<short> v(3,0);
        for(int i=1;i<9;i++){
            for(int k=1;k<9;k++){
                v[board[i][k]]++;
            }
        }
        if(v[1]==0) return {2,0,v[2]}; //0 - ничья
        if(v[2]==0) return {1,v[1],0};
        if(v[0]!=0) return {-1,v[1],v[2]}; //-1 - игра не окончена
        if(v[1]>v[2]) v[0]=1;
        if(v[2]>v[1]) v[0]=2;
        if(v[1]==v[2]) v[0]=0;
        return v;
    }
};

board b1;

void task2(){ //Задание 2
    b1.input();
    for(auto i:b1.wincheck_3()){
        fout<<i<<" ";
    }
}

int main()
{
    fin.open("input.txt");
    fout.open("output.txt");
    b1.start();
    task2();
    fin.close();
    fout.close();
}

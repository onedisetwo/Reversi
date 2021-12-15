#include <iostream>
#include <vector>
#include <string>

/*первая коорд. - буква, вторая цифра. т.е.
5 - - - - -
4 - - - - -
3 - - - - -
2 - - - - -
1 - - - - -
- A B C D E
*/

using namespace std;

short changePl(short player){ //Смена игрока
    if(player==1)
        return 2;
    else
        return 1;
}

class coord{
public:
    short x,y;
    void input(){
        string s;
        cin>>s;
        x=(int)(s[0])-64;
        y=(int)(s[1])-48;
    }
    void set(short a, short b){
        x=a;
        y=b;
    }
};

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
            cin>>s;
            for(int k=1;k<9;k++){
                board[k][9-i]=(int)(s[k-1])-48;
            }
        }
    }

    //Получить значение поля доски
    short get(coord a){
        return board[a.x][a.y];
    }

    //Напечатать доску
    void print(){
        cout<<endl;
        for(int i=1;i<9;i++){
            for(int k=1;k<9;k++){
                cout<<board[k][9-i];
            }
            cout<<endl;
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

    //Проверка выигрыщша: победитель
    short wincheck_p(){
        return wincheck_3()[0];
    }

    //Вспомогательная функция для vecIsMovePossible(...)
    bool possibility(coord a, short y, short x, short player){
        if(get({y+a.x,x+a.y})!=changePl(player))
            return 0;
        for(int i=2;y-i>0 && x-i>0;i++){
            if(board[y+i*a.x][x+i*a.y]==0){
                return 0;
            }
            if(board[y+i*a.x][x+i*a.y]==player){
                return 1;
            }
        }
    }

    //Возможность хода в клетку и в какой стороне он окажет влияние
    vector<bool> vecIsMovePossible(coord a,short player){
        /*- - - - -
          - 2 3 4 -
          - 1 X 5 -
          - 0 7 6 -
          - - - - -*/
        short y=a.x,x=a.y;
        vector<bool> v(8,0);
        if(board[y][x]!=0)
            return v;
        if(y>0 && x>0)
            v[0]=possibility({-1,-1},y,x,player);
        if(y>0)
            v[1]=possibility({-1,0},y,x,player);
        if(y>0 && x+1<=8)
            v[2]=possibility({-1,1},y,x,player);
        if(x+1<=8)
            v[3]=possibility({0,1},y,x,player);
        if(y+1<=8 && x+1<=8)
            v[4]=possibility({1,1},y,x,player);
        if(y+1<=8)
            v[5]=possibility({1,0},y,x,player);
        if(y+1<=8 && x>0)
            v[6]=possibility({1,-1},y,x,player);
        if(x>0)
            v[7]=possibility({0,-1},y,x,player);
        return v;
    }

    //Можно ли сделать ход в данную клетку
    bool isMovePossible(coord c,short player){
        vector<bool> v=vecIsMovePossible(c,player);
        for(auto i:v){
            if(i==true)
                return true;
        }
        return false;
    }

    //Вспомогательная функция для change(...)
    bool ksgchanger(coord a,short player,coord da){
        if(board[a.x][a.y]!=player){
            board[a.x][a.y]=player;
            ksgchanger({a.x+da.x,a.y+da.y},player,da);
        }
        if(board[a.x][a.y]==player)
            return 0;
    }

    //Изменение доски после хода
    void change(coord a,short player){
        if(get(a)!=0)
            return  ;
        vector<bool> v=vecIsMovePossible(a,player);
        vector<coord> cov={{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};
        for(int i=0;i<8;i++){
            if(v[i]!=0){
                ksgchanger(a,player,cov[i]);
                board[a.x][a.y]=changePl(player);
            }
        }
        board[a.x][a.y]=player;
    }

    //Варианты хода из заданного положения
    vector<coord> moveVariants(short player){
        vector<coord> v;
        for(short i=1;i<9;i++){
            for(short k=1;k<9;k++){
                if(isMovePossible({i,k},player)==true){
                    v.push_back({i,k});
                }
            }
        }
        return v;
    }
};

board b1;

//Перевод координат в запись #A1
string toStr(coord a){
    string s;
    s+=(char)(a.x+64);
    s+=(char)(a.y+48);
    return s;
}

///Задания

void task1(){ //Задание 1
    b1.input();
    int s=0;
    for(int i=1;i<9;i++){
        for(int k=1;k<9;k++){
            if(b1.board[i][k]!=0){
                s++;
            }
        }
    }
    cout<<s-4;
}

void task2(){ //Задание 2
    b1.input();
    for(auto i:b1.wincheck_3()){
        cout<<i<<" ";
    }
}

void task3(){ //Задание 3
    short player;
    board b2;
    b2.start();
    b1.input();
    cin>>player;
    b2.input();
    cin>>player;
    coord c={0,0};
    for(int i=1;i<9;i++){
        for(int k=1;k<9;k++){
            if(b1.board[i][k]==0 && b2.board[i][k]!=0){
                c.set(i,k);
                i=9;
                break;
            }
        }
    }
    if(c.x==0){
        cout<<0;
        return  ;
    }
    b1.change(c,player);
    if(b1.board==b2.board){
        cout<<toStr(c);
    }
    else
        cout<<0;
}

void task4(){ //Задание 4
    coord c;
    short player;
    b1.input();
    cin>>player;
    c.input();
    if(b1.isMovePossible(c,changePl(player))!=0){
        player=changePl(player);
        b1.change(c,player);
    }
    b1.print();
    cout<<player;
}

void task5(){ //Задание 5
    b1.input();
    short player;
    cin>>player;
    vector<coord> v=b1.moveVariants(changePl(player));
    cout<<changePl(player)<<endl<<v.size()<<endl;
    for(auto i:v){
        cout<<toStr(i)<<" ";
    }
}

void task6(){ //Задание 6
    b1.input();
    short player;
    vector<coord> v;
    int p=-1;
    cin>>player;
    for(auto i:b1.moveVariants(changePl(player))){
        if(b1.isMovePossible(i,changePl(player))==0){
            continue;
        }
        board b=b1;
        b.change(i,changePl(player));
        if(b.wincheck_p()==changePl(player)){
            p=b.wincheck_p();
            v.push_back(i);
        }
    }
    if(v.size()==0){
        player=changePl(player);
        for(auto i:b1.moveVariants(changePl(player))){
            if(b1.isMovePossible(i,changePl(player))==0){
                continue;
            }
            board b=b1;
            b.change(i,changePl(player));
            if(b.wincheck_p()==changePl(player)){
                p=b.wincheck_p();
                v.push_back(i);
            }
        }
    }
    if(p>0){
        cout<<p<<endl;
        for(auto i:v){
            cout<<toStr(i)<<" ";
        }
    }
    else
        cout<<0;
}

void task7(){ //Задание 7
    short player;
    b1.input();
    cin>>player;
    int ma=INT_MIN;
    vector<coord> ot;
    short a1=b1.wincheck_3()[player];
    player=changePl(player);
    for(int i=1;i<9;i++){
        for(int k=1;k<9;k++){
            board b2;
            b2.start(); b2=b1;
            b2.change({i,k},player);
            //cout<<endl<<toStr({i,k});
            //b2.print();
            short a2=b2.wincheck_3()[changePl(player)];
            if(abs(a2-a1)>ma){
                ot.clear();
                ma=abs(a2-a1);
                ot.push_back({i,k});
            }
            else
                if(abs(a2-a1)==ma)
                    ot.push_back({i,k});
            //cout<<abs(a2-a1)<<endl;
        }
    }
    cout<<player<<endl<<ma<<endl;
    for(auto i:ot){
        cout<<toStr(i)<<" ";
    }
}

void task_switch(){ //Выбор заданий
    short task_number=7;
    cout<<"Task number: ";
    cin>>task_number;
    switch(task_number){
    case 1: //+
        task1();
        break;
    case 2: //+
        task2();
        break;
    case 3: //+
        task3();
        break;
    case 4: //+
        task4();
        break;
    case 5: //+
        task5();
        break;
    case 6: //+
        task6();
        break;
    case 7: //+
        task7();
        break;
    default:
        cout<<"Not yet";
        break;
    }
}

int main()
{
    b1.start();
    task_switch();
}

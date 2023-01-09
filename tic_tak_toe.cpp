#include <bits/stdc++.h>
using namespace std;

#define Computer 1
#define Human 2
#define side 3
#define ComputerMove 'O'
#define HumanMove 'X'

void ShowBord(char board[][side]){
    printf("\t\t\t %c | %c | %c \n",board[0][0],board[0][1],board[0][2]);
    printf("\t\t\t---------\n ");
    printf("\t\t\t %c | %c | %c \n",board[1][0],board[1][1],board[1][2]);
    printf("\t\t\t---------\n ");
    printf("\t\t\t %c | %c | %c \n",board[2][0],board[2][1],board[2][2]);
    printf("\t\t\t---------\n ");
}

void ShowInstruction(){
    cout<<"Choose a cell from 1 to 9\n";
    cout<<"\t\t\t 1 | 2 | 3 \n";
    cout<<"\t\t\t ----------\n";
    cout<<"\t\t\t 4 | 5 | 6 \n";
    cout<<"\t\t\t ----------\n";
    cout<<"\t\t\t 7 | 8 | 9 \n";
}


void Init(char board[][side]){
    for(int i=0;i<side;i++){
        for(int j=0;j<side;j++) 
            board[i][j] = '+';
    }
}

void Winner(int turn){
    if(turn == Computer) cout<<"Computer Won"<<endl;
    else cout<<"Human won"<<endl;

}

bool RowCheck(char board[][side]){
    for(int i=0;i<side;i++){
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2]!='+')
            return true;
    }
    return false;
}

bool ColumnCheck(char board[][side]){
    for(int i=0;i<side;i++){
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[2][i]!='+')
            return true;
    }
    return false;
}

bool DiagonalCheck(char board[][side]){
    for(int i=0;i<side;i++){
        if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2]!='+')
            return true;
        if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1]!='+')
            return true;
    }
    return false;
}

bool GameOver(char board[][side]){
    bool f = RowCheck(board) || ColumnCheck(board) || DiagonalCheck(board);
    return f;
}

int minimax(char board[][side], int d, bool Ai){
    int score = 0;
    int bestScore = 0;
    if(GameOver(board) == true){
        if(Ai == true) return -10;
        else return +10;
    }
    else{
        if(d < 9){
            if(Ai == true){
                bestScore = INT_MIN;
                for(int i=0;i<side;i++){
                    for(int j=0;j<side;j++){
                        if(board[i][j] == '+'){
                            board[i][j] = ComputerMove;
                            score = minimax(board,d+1,false);
                            board[i][j] = '+';
                            if(score > bestScore) bestScore = score;
                        }
                    }
                }
                return bestScore;
            }
            else{
                bestScore = INT_MAX;
                for(int i=0;i<side;i++){
                    for(int j=0;j<side;j++){
                        if(board[i][j] == '+'){
                            board[i][j] = HumanMove;
                            score = minimax(board,d+1,true);
                            board[i][j] = '+';
                            if(score < bestScore) bestScore = score;
                        }
                    }
            }
            return bestScore;
        }
    }
    else return 0;
}
}

int bestMove(char board[][side], int index) {
    int x = -1, y = -1;
    int score = 0;
    int bestScore = INT_MIN;
    for(int i=0;i<side;i++){
        for(int j=0;j<side;j++){
            if(board[i][j] == '+'){
                board[i][j] = ComputerMove;
                score = minimax(board,index+1,false);
                board[i][j] = '+';
                if(score > bestScore){
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x*3+y;
}

void Play(int turn){
    char board[side][side];
    int index = 0,x = 0, y = 0;
    Init(board);
    ShowInstruction();
    while(GameOver(board) == false && index != 9){
        int n;
        if(turn == Computer){
            n = bestMove(board, index);
            x = n / side;
            y = n % side;
            board[x][y] = ComputerMove;
            cout<<"Computer has put O in cell "<<n+1<<endl;
            ShowBord(board);
            index++;
            turn = Human;
        }
        else if(turn == Human){
            cout<<"Insert in these positions : ";
            for(int i=0;i<side;i++){
                for(int j=0;j<side;j++){
                    if(board[i][j] == '+') cout<< (i*3+j)+1 <<" ";
                }
            }
            cout<<endl;
            cout<<"Enter the position : ";
            cin>>n;
            cout<<endl;
            n--;
            x = n / side;
            y = n % side;
            if(board[x][y] == '+' && n < 9 && n >= 0){
                board[x][y] = HumanMove;
                cout<<"\n Human put X in cell "<<n+1<<endl;
                ShowBord(board);
                index++;
                turn = Computer;
            }
            else if(board[x][y] != '+' && n < 9 && n >=0){
                cout<<"Position taken"<<endl;
            }
            else if(n <0 || n > 8){
                cout<<"Inavlid position"<<endl;
            }
        }
    }
    if(GameOver(board) == false && index == side*side) cout<<"its a draw"<<endl;
    else{
        if(turn == Computer) turn = Human;
        else if(turn == Human) turn = Computer;
        Winner(turn);
    }
}

int main(){
    cout<<"Tic-Tack-Toe"<<endl<<endl;
    char c = 'y';
    do{
        char ch;
        cout<<"Want to start first ? (y/n) : ";
        cin>>ch;
        cout<<endl;
        if(ch == 'n') Play(Computer);
        else if(ch == 'y') Play(Human);
        else cout<<"Invalid choice"<<endl;
        cout<<"Do you want to quit ? (y/n) : ";
        cin>>c;
        cout<<endl;
    }while(c == 'n');
    return 0;
}
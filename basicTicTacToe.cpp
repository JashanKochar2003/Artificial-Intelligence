#include<iostream>
#include<vector>
using namespace std;

int possibleWins(int value,vector<int>& board){
    if(value==3){
        if(board[1]*board[2]*board[3]==18){
            if(board[1]==2)
            return 1;
            if(board[2]==2)
            return 2;
            if(board[3]==2)
            return 3;
        }
        if(board[4]*board[5]*board[6]==18){
            if(board[4]==2)
            return 4;
            if(board[5]==2)
            return 5;
            if(board[6]==2)
            return 6;
        }
        if(board[7]*board[8]*board[9]==18){
            if(board[7]==2)
            return 7;
            if(board[8]==2)
            return 8;
            if(board[9]==2)
            return 9;
        }
        if(board[1]*board[4]*board[7]==18){
            if(board[1]==2)
            return 1;
            if(board[4]==2)
            return 4;
            if(board[7]==2)
            return 7;
        }
        if(board[2]*board[5]*board[8]==18){
            if(board[2]==2)
            return 2;
            if(board[5]==2)
            return 5;
            if(board[8]==2)
            return 8;
        }
        if(board[3]*board[6]*board[9]==18){
            if(board[3]==2)
            return 3;
            if(board[6]==2)
            return 6;
            if(board[9]==2)
            return 9;
        }
        if(board[1]*board[5]*board[9]==18){
            if(board[1]==2)
            return 1;
            if(board[5]==2)
            return 5;
            if(board[9]==2)
            return 9;
        }
        if(board[3]*board[5]*board[7]==18){
            if(board[3]==2)
            return 3;
            if(board[5]==2)
            return 5;
            if(board[7]==2)
            return 7;
        }
    }
    if(value==5){
            if(board[0]*board[1]*board[2]==50){
            if(board[0]==2)
            return 0;
            if(board[1]==2)
            return 1;
            if(board[2]==2)
            return 2;
        }
        if(board[3]*board[4]*board[5]==50){
            if(board[3]==2)
            return 3;
            if(board[4]==2)
            return 2;
            if(board[5]==2)
            return 5;
        }
        if(board[6]*board[7]*board[8]==50){
            if(board[6]==2)
            return 6;
            if(board[7]==2)
            return 7;
            if(board[8]==2)
            return 8;
        }
        if(board[0]*board[3]*board[6]==50){
            if(board[0]==2)
            return 0;
            if(board[3]==2)
            return 3;
            if(board[6]==2)
            return 6;
        }
        if(board[1]*board[4]*board[7]==50){
            if(board[1]==2)
            return 1;
            if(board[4]==2)
            return 4;
            if(board[7]==2)
            return 7;
        }
        if(board[2]*board[5]*board[8]==50){
            if(board[2]==2)
            return 2;
            if(board[5]==2)
            return 5;
            if(board[8]==2)
            return 8;
        }
        if(board[0]*board[4]*board[8]==50){
            if(board[0]==2)
            return 0;
            if(board[4]==2)
            return 4;
            if(board[8]==2)
            return 8;
        }
        if(board[2]*board[4]*board[6]==50){
            if(board[2]==2)
            return 2;
            if(board[4]==2)
            return 4;
            if(board[6]==2)
            return 6;
        }
    }
    return 0;
}

void display(vector<int> &board){
    int count = 0;
    for(int i=1;i<10;i++){
        if(board[i]==2)
        cout<<"-"<<" ";
        else if(board[i]==3)
        cout<<"X"<<" ";
        else
        cout<<"O"<<" ";
        count++;
        if(count==3){
            count = 0;
            cout<<endl;
        }
    }
}



void go(int place ,int value , vector<int> &board){            
  board[place] = value;
}

bool checkWins(int value,vector<int> board){
    if(value==3){
        if(board[1]*board[2]*board[3]==27)
        return true;
        if(board[4]*board[5]*board[6]==27)
        return true;
        if(board[7]*board[8]*board[9]==27)
        return true;
        if(board[1]*board[4]*board[7]==27)
        return true;
        if(board[2]*board[5]*board[8]==27)
        return true;
        if(board[3]*board[6]*board[9]==27)
        return true;
        if(board[1]*board[5]*board[9]==27)
        return true;
        if(board[3]*board[5]*board[7]==27)
        return true;
    }
    if(value==5){
        if(board[1]*board[2]*board[3]==125)
        return true;
        if(board[4]*board[5]*board[6]==125)
        return true;
        if(board[7]*board[8]*board[9]==125)
        return true;
        if(board[1]*board[4]*board[7]==125)
        return true;
        if(board[2]*board[5]*board[8]==125)
        return true;
        if(board[3]*board[6]*board[9]==125)
        return true;
        if(board[1]*board[5]*board[9]==125)
        return true;
        if(board[3]*board[5]*board[7]==125)
        return true;
    }
    return false;
}

int make2(vector<int> &board){
    if(board[6]==2)
    return 6;
    else if(board[5]==2)
    return 5;
    else if(board[2]==2)
    return 2;
     else if(board[4]==2)
    return 4;
     else if(board[8]==2)
    return 8;
    else
    return 0;
}

int make1(vector<int> &board){
    if(board[7]==2)
    return 7;
     else if(board[5]==2)
    return 5;
    else if(board[1]==2)
    return 1;
     else if(board[3]==2)
    return 3;
    
     else if(board[9]==2)
    return 9;
    else
    return 0;
}

void game(int turn,int player,int competor,int value,int comValue ,vector<int> &board) {
  if(turn>1){
  display(board);
  }
  if(turn>9){
    cout<<"IT'S A DRAW"<<endl;
    return;
  }
  if(checkWins(comValue,board)){
    if(competor==0)
    cout<<"USER WINS"<<endl;
    else
    cout<<"COMPUTER WINS"<<endl;
    return;
  }
  if(player==0){
    bool flag=false;
    while(!flag){
    cout<<"Enter value : "<<endl;
    int place;
    cin>>place;
    if(place>0 && place < 10 && board[place]==2){
        go(place,value,board);
        flag = true;
    }    
    else{
        cout<<"Enter value not valid , enter other value "<<endl;
    }
    }
  }
  else{
    cout<<"COMPUTER'S TURN NOW"<<endl;
    if (turn == 1) {
      go(make1(board),value,board); 
    } else if (turn == 2) {
      if (board[5] == 2)
       go(make2(board),value,board); 
      else
        go(1,value,board);
    } else if (turn == 3) {
      if (board[9] == 2)
        go(make1(board),value,board);
    } else if (turn == 4) {
      if(board[7]==2)
       go(7,value,board);
      else{ 
      int winMoveX = possibleWins(comValue,board);
      if (winMoveX != 0)
        go(winMoveX,value,board);
      else if (possibleWins(value,board) != 0)
        go(possibleWins(value,board),value,board);
      else{
        int moveX = make2(board);
        if(moveX!=0)
        go(moveX,value,board) ;
    }
      } 
    }
    else if (turn == 5) {
      int winMoveX = possibleWins(value,board);
      if (winMoveX != 0)
        go(winMoveX,value,board);
      else if (possibleWins(comValue,board) != 0)
        go(possibleWins(comValue,board),value,board);
      else if(make1(board)!=0){
        int moveX = make1(board);
        go(moveX,value,board) ;
      }
      else{
        int moveX = make2(board);
        if(moveX!=0)
        go(moveX,value,board) ;
      }
    } else if (turn == 6) {
      if (possibleWins(comValue,board) != 0)
        go(possibleWins(comValue,board),value,board); 
    else if(make2(board)!=0){
        int moveX = make2(board);
        if(moveX!=0)
        go(moveX,value,board) ;
      }
      else{
        int moveX = make1(board);
        if(moveX!=0)
        go(moveX,value,board) ;
      }

    } else if (turn == 7) {
      int winMoveX = possibleWins(value,board);
      if (winMoveX != 0)
        go(winMoveX,value,board); 
      else if (possibleWins(comValue,board) != 0)
        go(possibleWins(comValue,board),value,board);
     else if(make1(board)!=0){
        int moveX = make1(board);
        go(moveX,value,board) ;
      }
      else{
        int moveX = make2(board);
        if(moveX!=0)
        go(moveX,value,board) ;
      }
    } else if (turn == 8) {
      if (possibleWins(comValue,board) != 0)
        go(possibleWins(comValue,board),value,board); 
      else if (possibleWins(value,board) != 0)
        go(possibleWins(value,board),value,board); 
     else if(make2(board)!=0){
        int moveX = make2(board);
        go(moveX,value,board) ;
      }
      else{
        int moveX = make1(board);
        if(moveX!=0)
        go(moveX,value,board) ;
      }
    } else if (turn == 9) {
     if (possibleWins(value,board) != 0)
        go(possibleWins(value,board),value,board);  
      else if (possibleWins(comValue,board) != 0)
        go(possibleWins(comValue,board),value,board);  
      else if(make1(board)!=0){
        int moveX = make1(board);
        go(moveX,value,board) ;
      }
      else{
        int moveX = make2(board);
        if(moveX!=0)
        go(moveX,value,board) ;
      }
    }
  }
    game(turn+1,competor,player,comValue,value,board);
  }


int main(){
    vector<int> board(10,2);
    int toss = 0;
    int turn=1;
    int computer=1;
    int user = 0;
    if(toss%2==0)
    game(turn,user,computer,3,5,board);
    else
    game(turn,computer,user,3,5,board);
    return 0;
}

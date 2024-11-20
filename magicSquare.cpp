#include<iostream>
#include<vector>
using namespace std;

int possibleWins(int value,vector<int>& board,vector<int> values){
      for(int i=1;i<10;i++){
        if(board[i]==value){
          for(int j=i;j<10;j++){
            if(board[j]==value){
              int require = 15-(values[i]+values[j]);
              for(int k=1;k<10;k++){
                if(values[k]==require && board[k]==2)
                return k;
              }
            }
          }
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

bool checkWins(int value,vector<int> board,vector<int> values){
  for(int i=1;i<10;i++){
    if(board[i]==value){
      for(int j=i+1;j<10;j++){
        if(board[j]==value){
          for(int k=j+1;k<10;k++){
            if(board[k]==value && values[i]+values[j]+values[k]==15)
            return true;
          }
        }
      }
    }
  }
  return false;
}

int make2(vector<int> &board){
    if(board[5]==2)
    return 5;
    else if(board[2]==2)
    return 2;
     else if(board[4]==2)
    return 4;
     else if(board[6]==2)
    return 6;
     else if(board[8]==2)
    return 8;
    else
    return 0;
}

int make1(vector<int> &board){
    if(board[5]==2)
    return 5;
    else if(board[1]==2)
    return 1;
     else if(board[3]==2)
    return 3;
     else if(board[7]==2)
    return 7;
     else if(board[9]==2)
    return 9;
    else
    return 0;
}

void game(int turn,int player,int competor,int value,int comValue ,vector<int> &board,vector<int> values) {
  if(turn>1){
  display(board);
  }
  if(turn>9){
    cout<<"IT'S A DRAW"<<endl;
    return;
  }
  if(checkWins(comValue,board,values)){
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
      go(1,value,board); 
    } else if (turn == 2) {
      if (board[5] == 2)
       go(5,value,board); 
      else
        go(1,value,board);
    } else if (turn == 3) {
      if (board[9] == 2)
        go(9,value,board);
      else
        go(3,value,board); 
    } else if (turn == 4) {
      int winMoveX = possibleWins(comValue,board,values);
      if (winMoveX != 0)
        go(winMoveX,value,board);
      else if (possibleWins(value,board,values) != 0)
        go(possibleWins(value,board,values),value,board);
      else{
        int moveX = make2(board);
        if(moveX!=0)
        go(moveX,value,board) ;
    } 
    }
    else if (turn == 5) {
      int winMoveX = possibleWins(value,board,values);
      if (winMoveX != 0)
        go(winMoveX,value,board);
      else if (possibleWins(comValue,board,values) != 0)
        go(possibleWins(comValue,board,values),value,board);
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
      if (possibleWins(comValue,board,values) != 0)
        go(possibleWins(comValue,board,values),value,board); 
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
      int winMoveX = possibleWins(value,board,values);
      if (winMoveX != 0)
        go(winMoveX,value,board); 
      else if (possibleWins(comValue,board,values) != 0)
        go(possibleWins(comValue,board,values),value,board);
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
      if (possibleWins(comValue,board,values) != 0)
        go(possibleWins(comValue,board,values),value,board); 
      else if (possibleWins(value,board,values) != 0)
        go(possibleWins(value,board,values),value,board); 
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
     if (possibleWins(value,board,values) != 0)
        go(possibleWins(value,board,values),value,board);  
      else if (possibleWins(comValue,board,values) != 0)
        go(possibleWins(comValue,board,values),value,board);  
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
    game(turn+1,competor,player,comValue,value,board,values);
  }


int main(){
    vector<int> board(10,2);
    vector<int> values = {0,8,3,4,1,5,9,6,7,2};
    int toss = rand();
    int turn=1;
    int computer=1;
    int user = 0;
    if(toss%2==0)
    game(turn,user,computer,3,5,board,values);
    else
    game(turn,computer,user,3,5,board,values);
    return 0;
}

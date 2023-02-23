#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>


std::string pastBoards[100][16];
int curSize=0;
void generate(std::string board[]){
  for(int x=0;x<16;x++){
    board[x]="";
  }    
  for(int x=1;x<17;x++){
    int num =  rand()%16;
    std::string vNum = std::to_string(x);
    if(board[num]==""){
      board[num]=vNum;
    }
    else{
      while(board[num]!=""){
	num=rand()%16;
	if(board[num]==""){
	 board[num]=vNum;
	 break;
	}
      }
    }
  }

  //Check if board is valid}
  int row=0;
  int invCount=0;
  for(int t=0;t<8;t++){
    for(int y=t+1;y<8;y++){
      if(stoi(board[t])>stoi(board[y])&&board[t]!="16"&&board[y]!="16"){
	invCount++;
      }
     
    }
  }

  for(int t=8;t<16;t++){
    for(int y=t+1;y<16;y++){
      if(stoi(board[t])>stoi(board[y])&&board[t]!="16"&&board[y]!="16"){
	invCount++;
      }
     
    }
  }
  for(int x=0;x<8;x++){
    for(int j=8;j<16;j++){
      if(stoi(board[x])>stoi(board[j])&&board[x]!="16"&&board[j]!="16"){
	invCount++;
      }
    }
  }

  for(int x=0;x<16;x++){
    if(board[x]=="16"){
      row=(x/4)+1;
    }
  }
  //std::cout<<row<<" "<<invCount<<std::endl;
  if(row%2!=invCount%2){
    generate(board);
  }
}

void printBoard(std::string board[]){

  printf("\033[2J\033[1;1H");
 
  for(int x=0;x<16;x++){
    if(board[x]=="16"){
      std::cout<<"_"<<" ";
    }
    else if(stoi(board[x])/10!=1){
      std::cout<<board[x]<<"  ";
    }
    else{
    	std::cout<<board[x]<<" ";
    }
   
    if(x!=0&&(x%4)==3){
      std::cout<<"\n";
    }
  }
  std::cout<<"\n";
}

bool checkUnique(std::string board[],int row,int col, int curRow,int curCol){
    	board[(curRow*4)+(curCol)]=board[(row*4)+(col)];
    	board[(row*4)+(col)]="16";
    	
    	int count=0;
    	for(int x=0;x<curSize;x++){
	    	for(int y=0;y<16;y++){
	    		if(pastBoards[x][y]==board[y]){
	    			count++;
	    		}
	    	}
    	}
    	if(count==16){
    		return false;
    	}
    	board[(row*4)+(col)]=board[(curRow*4)+(curCol)];
    	board[(curRow*4)+(curCol)]="16";
    	
    	for(int x=0;x<16;x++){
    		pastBoards[curSize][x].assign(board[x]);
    	}
    	curSize++;
    	if(curSize>99){
    		curSize=0;
    	}
	return true;
}


bool isSolved(std::string board[]){
  for(int x=0;x<15;x++){
    if(stoi(board[x])>stoi(board[x+1])){
      return false;
    }
  }
  return true;
}

//dir is so that  we ddont go in loop back and forth
//in other words 1 2 3 4 is up right down left with 0 being no move
void solve(std::string board[],int row, int col){
  //BASE CASE: if board is in order
  if(isSolved(board)){
    exit(0);
  }
  
  int curRow;
    int curCol;
    for(int x=0;x<16;x++){
      if(board[x]=="16"){
	curRow=(x/4);
	curCol=(x%4);
      }
    }
  //||checkUnique(board,row,col,curRow,curCol)==false
  if(row>3||row<0||col>3||col<0){
    return;
  }
  else{
    board[(curRow*4)+(curCol)]=board[(row*4)+(col)];
    board[(row*4)+(col)]="16";
   
  }

  usleep(80000);
  printBoard(board);
  solve(board,row-1,col);	
  solve(board,row,col+1);
  solve(board,row+1,col);
  solve(board,row,col-1);
}

void solve(std::string board[]){

  //Get inital blank space
  int row;
  int col;
  for(int x=0;x<16;x++){
    if(board[x]=="16"){
      row=(x/4);
      col=(x%4);
      std::cout<<x<<" "<<row<<" "<<col<<std::endl;
      break;
    }
  }

  //BASE CASE
  if(isSolved(board)){
    exit(0);
  }
  for(int x=0;x<16;x++){
  	pastBoards[0][x].assign(board[x]);
  }
  curSize++;
  solve(board,row,col);
 
}

int main(){
 
  std::string board[16];
  for(int x=0;x<16;x++){
    board[x]="";
  }
  srand(time(NULL));
  generate(board);
  printBoard(board);
  solve(board);

 
  return 0;
}


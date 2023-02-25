#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

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
void printValues(std::string board[]){
	for(int x=0;x<16;x++){
		std::cout<<board[x]<<" ";
	}
	std::cout<<std::endl;
}
void printBoard(std::string board[]){

  printf("\033[2J\033[1;1H");
  std::cout<<"--------"<<std::endl;
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
  std::cout<<"--------"<<std::endl;
  std::cout<<"\n\n";
}

std::string pastBoards[100][16];
int curSize=0;

void addPast(std::string board[]){
	for(int x=0;x<16;x++){
		pastBoards[curSize][x]=board[x];
	}
	curSize++;
	if(curSize>99){
		curSize=0;
	}
}

bool sameBoard(std::string boardA[], std::string boardB[]){
	for(int x=0;x<16;x++){
		//std::cout<<boardA[x]<<" "<<boardB[x]<<std::endl;
		if(boardA[x]!=boardB[x]){
			return false;
		}
	}
	return true;
}
bool checkUnique(std::string board[],int curRow,int curCol,int row,int col){
	std::string testBoard[16];
	for(int x=0;x<16;x++){
		testBoard[x]=board[x];
	}
	testBoard[(curRow*4)+(curCol)]=testBoard[(row*4)+(col)];
    	testBoard[(row*4)+(col)]="16";
	for(int x=0;x<curSize;x++){
		//std::cout<<sameBoard(pastBoards[x],testBoard)<<std::endl;
		if(sameBoard(pastBoards[x],testBoard)){
			return false;
		}
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

int bestMove(std::string board[],int curRow,int curCol){
	int curIndex=(curRow*4)+curCol;
	
}

void solve(std::string board[],int curRow, int curCol,int row, int col){
  //BASE CASE: if board is in order
  if(isSolved(board)){
  	printValues(board);
    exit(0);
  }
  if(row>3||row<0||col>3||col<0||checkUnique(board,curRow,curCol,row,col)==false){
    return;
  }
  
    board[(curRow*4)+(curCol)]=board[(row*4)+(col)];
    board[(row*4)+(col)]="16";
    addPast(board);

  usleep(80000);
  printBoard(board);
  solve(board,row,col,row-1,col);	
  solve(board,row,col,row,col+1);
  solve(board,row,col,row+1,col);
  solve(board,row,col,row,col-1);
}

void solve(std::string board[]){

  //Get inital blank space
  int curRow;
  int curCol;
  for(int x=0;x<16;x++){
    if(board[x]=="16"){
      curRow=(x/4);
      curCol=(x%4);
      break;
    }
  }

  //BASE CASE
  if(isSolved(board)){
    exit(0);
  }
  addPast(board);
  solve(board,curRow,curCol,curRow-1,curCol);
  solve(board,curRow,curCol,curRow,curCol+1);	
  solve(board,curRow,curCol,curRow+1,curCol);	
  solve(board,curRow,curCol,curRow,curCol-1);		
 
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


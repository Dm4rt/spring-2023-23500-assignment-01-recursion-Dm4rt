#include  <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

const int boardSize=5;
const int boardSpaces=boardSize*boardSize;
int startingPos;
void printBoard(std::string board[]){
	printf("\033[2J\033[1;1H");
	std::cout<<"---------"<<std::endl;
	for(int x=0;x<boardSize*boardSize;x++){
		std::cout<<board[x]<<" ";
		if(x%boardSize==(boardSize-1)){
			std::cout<<"\n";
		}
	}
	std::cout<<"---------"<<std::endl;
	std::cout<<"\n";
}
//x in string shows what spot I've visited
int movesOrder[boardSpaces];
int curSize=0;
void printMoves(){
	printf("\033[2J\033[1;1H");
	std::string orderBoard[boardSpaces];
	std::cout<<"Starting postition: ";
	for(int x=0;x<curSize;x++){
		std::cout<<movesOrder[x]<<" -> ";
	}
	std::cout<<std::endl;
	for(int x=0;x<boardSpaces;x++){
		orderBoard[movesOrder[x]]=std::to_string((x+1));
	}
	std::cout<<"---------------"<<std::endl;
	for(int x=0;x<boardSpaces;x++){
		std::cout<<orderBoard[x]+":";
		if(x%boardSize==(boardSize-1)){
			std::cout<<"\n";
		}
	}
	std::cout<<"---------------"<<std::endl;
	
	std::cout<<"\n";
}

bool move(std::string board[],int curIndex,int moveValue){
	if(curIndex+moveValue>(boardSpaces)-1||curIndex+moveValue<0||board[curIndex+moveValue]=="x"){
		return false;
	}
	int curRow=curIndex/boardSize;
	int curCol=curIndex%boardSize;
	int row=(curIndex+moveValue)/boardSize;
	int col=(curIndex+moveValue)%boardSize;
	if((abs(curCol-col)==2&&abs(curRow-row)==1)||(abs(curCol-col)==1&&abs(curRow-row)==2)){
		board[curIndex]="x";
		board[curIndex+moveValue]="N";
		//std::cout<<(curRow*5)+curCol<<" "<<(row*5)+col<<std::endl;
		return true;
	}
	return  false;
}
void backTrack(std::string board[]){
	int curPos;
	for(int x=0;x<boardSpaces;x++){
		if(board[x]=="N"){
			curPos=x;
			break;
		}
	}
	board[curPos]=".";
	board[movesOrder[curSize-1]]="N";
	curSize--;
	//usleep(100000);
	printBoard(board);
}


bool genMove(std::string board[],int nextSpot){
	int curIndex;
	for(int x=0;x<boardSpaces;x++){
		if(board[x]=="N"){
			curIndex=x;
		}
	}
	int curRow=curIndex/boardSize;
	int curCol=curIndex%boardSize;
	int row=nextSpot/boardSize;
	int col=nextSpot%boardSize;
	if((abs(curCol-col)==2&&abs(curRow-row)==1)||(abs(curCol-col)==1&&abs(curRow-row)==2)){
		board[curIndex]=".";
		board[nextSpot]="N";
		return true;
	}
	return  false;
}
void overrideStart(std::string board[],int newStart){
	for(int x=0;x<boardSpaces;x++){
		if(board[x]=="N"){
			board[x]=".";
			board[newStart]="N";
			startingPos=newStart;
			break;
		}
	}
}
void generate(std::string board[]){
	for(int x=0;x<boardSpaces;x++){
		board[x]=".";
		if(x==(boardSpaces)/2){
			board[x]="N";
		}
	}
	for(int x=0;x<1000;x++){
		int num=rand()%(boardSpaces);
		genMove(board,num);
	}
	for(int x=0;x<boardSpaces;x++){
		if(board[x]=="N"){
			startingPos=x;
		}
	}
}
bool checkSolved(std::string board[]){
	for(int x=0;x<boardSpaces;x++){
		if(board[x]=="."){
			return false;
		}
	}
	return true;
}
void solve(std::string board[], int moveValue){
	int curPos;
	for(int x=0;x<boardSpaces;x++){
		if(board[x]=="N"){
			curPos=x;
		}
	}
	//Base Case
	if(checkSolved(board)){
		movesOrder[curSize]=curPos;
		curSize++;	
		printMoves();
		exit(0);
	}
	if(move(board,curPos,moveValue)==false){
		return;
	}
	//usleep(100000);
	printBoard(board);
	movesOrder[curSize]=curPos;
	curSize++;
	solve(board,boardSize+boardSize+1);
	solve(board,boardSize+boardSize-1);
	solve(board,boardSize+2);
	solve(board,boardSize-2);
	solve(board,-1*(boardSize-2));
	solve(board,-1*(boardSize+2));
	solve(board,-1*(boardSize+boardSize-1));
	solve(board,-1*(boardSize+boardSize+1));
	backTrack(board);
}

void solve(std::string board[]){
	//Base Case
	if(checkSolved(board)){
		printMoves();
		exit(0);
	}
	int curPos;
	for(int x=0;x<boardSpaces;x++){
		if(board[x]=="N"){
			curPos=x;
		}
	}
	solve(board,boardSize+boardSize+1);
	solve(board,boardSize+boardSize-1);
	solve(board,boardSize+2);
	solve(board,boardSize-2);
	solve(board,-1*(boardSize-2));
	solve(board,-1*(boardSize+2));
	solve(board,-1*(boardSize+boardSize-1));
	solve(board,-1*(boardSize+boardSize+1));
}
int main(){
	srand(time(NULL));
	std::string board[boardSpaces];
	generate(board);
	//works for 5x5 on  knight starting index 20;
	overrideStart(board,20);
	solve(board);
	printBoard(board);
	return 0;
}

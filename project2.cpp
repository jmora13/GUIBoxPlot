//Jose Mora
//CS 256
//Project 2
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std; 

string word = "Project 2";
const char ESC = 27;
char borderType = 'x';
char matrix[ 10 ][ 80 ][ 25 ];

int numberOfBoxes = 1; 
int hDimension = 14; 
int vDimension = 7; 
int timer = 500;  

    void pause( int milliseconds ){
        int limit = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
        while ( clock() < limit ) {
    // Do nothing...just wait
        }
    }
    
    void clear(){
        cout << ESC << "[2J" << flush;
        cout << ESC << "[0;0f";
    }

    void setms(int n){
         pause(n);
    }

    void setfg( int n ){
	    cout << ESC << "[" << n << ";" << "47"  <<  "m"; 
    }

    void setbg( int n ){
        cout << ESC << "[39;" << n  <<  "m"; 
    }   

    void slow(){
	    pause(timer); 
    }

    void fast(){
        pause(0);
    }

    void hplot(int row, int col, char cha, char cnt){
	    for(int z = 0; z < numberOfBoxes; z++){
	        for(int i = 0; i < cnt; i++){
	            matrix[z][row + i][col] = cha; 	 
	            matrix[z][row+i][col+5] = cha; 
	        }
	    }
    }

    void vplot(int row, int col, char cha, char cnt){
	    for(int z = 0; z < numberOfBoxes; z++){
	        for(int i = 0; i < cnt; i++){
	            matrix[z][row][col + i] = cha;                
	            matrix[z][row + (hDimension-1)][col+i] = cha; 
	        }
	    }
    
    }
    
    void text(int row, int col, string word){
	    char wordArray[word.size() + 1]; 
	    strcpy(wordArray, word.c_str());
	    for(int z = 0; z < numberOfBoxes; z++){
		    for(int i = 0; i < word.size() + 1; i++){
			    matrix[z][row + 3 + i][col + 2] = wordArray[i];
		    }
	    }

    }

    void plot(int row, int col, char cha){
	    borderType = cha; 
	        if(numberOfBoxes == 1){
		        for(int i = 0; i < 80; i++){
			        for(int j = 0; j < 25; j++){
				        matrix[ 0 ][ i ][ j ] = ' '; 
			        }
		        }
		
	        }
        text(row, col, word); 
	    hplot(row, col, borderType, hDimension);
	    vplot(row, col, borderType, vDimension); 

	    for(int z = 0; z < numberOfBoxes; z++){
		    for(int x = 0; x < 80; x++){
			    for(int y = 0; y < 25; y++){
				    cout << ESC << "[" << y << ";" << x<< "f";
				    cout << matrix[z][x][y] << flush;
				    cout << ESC << "[0;0f";
			    }
		    }
	    }

    }

    void move(int row, int col, int h, int w, int Dr, int Dc){
	    plot(row + Dr, col + Dc, borderType); 
	    pause(100);
    }

    void copy(int row, int col, int h, int w, int Dr, int Dc){
	    for(int i = 0; i < 80; i++){
		    for(int j = 0; j < 25; j++){
			    matrix[numberOfBoxes][i + Dr][j + Dc] = matrix[numberOfBoxes-1][i][j];
		    }
	    }
        numberOfBoxes++;
        plot(row, col, borderType); 
    }

    int main(int argc, char *args[]){

	ifstream myFile;
    ofstream log_file; 
    string fileName, cmd; 
    char cha;
    int n, row, col, h , w , Dr, Dc;
    int counter = 1; 

    if(!args[1]){
      fileName = "project2.input"; 
      myFile.open( "project2.input" ); 
    } else {
      myFile.open( args[1] ); 
    }

    log_file.open( "myprogram.log" ); 

    if(!myFile){
      cout << "Error: unable to open " + fileName << endl; 
    }
    while(myFile >> cmd){
    	if(cmd == "clear"){
    		clear();
    	} else if(cmd == "setms"){ 
    		myFile >> n; 
    		setms(n);
    	} else if(cmd == "setfg"){
    		myFile >> n; 
    		setfg(n); 
    	} else if(cmd == "setbg"){
    		myFile >> n; 
    		setbg(n); 
    	} else if(cmd == "pause"){
            myFile >> n;
    		pause(n); 
    	} else if(cmd == "plot"){
    		slow(); 
            myFile >> row >> col >> cha; 
    		plot(row, col, cha); 
    	} else if(cmd == "move"){
    		myFile >> row >> col >> h >> w >> Dr >> Dc;
    		move(row, col, h, w, Dr, Dc ); 
    	} else if(cmd == "copy"){ 
            myFile >> row >> col;
            copy(row, col, 1, 1, 2, 2);
    	} else {
    		log_file << "Error: Line " << counter << " - bad command '" << cmd
                  << "' ,skipping." << endl; 
    	}
    	counter++;
    }
    log_file.close();
    myFile.close();
	return 0; 
}



















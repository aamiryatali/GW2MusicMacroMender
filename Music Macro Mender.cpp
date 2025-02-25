#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

bool isHigh(char ch){
	if((ch >= 'a' && ch <= 'g') && ch != 'c'){
		return true;
	}
	return false;
}

bool isMid(char ch){
	if((ch >= 'A' && ch <= 'G') || ch == 'c'){
		return true;
	}
	return false;
}

bool isNote(char ch){
	if(isHigh(ch) || isMid(ch) || ch == ','){
		return true;
	}
	return false;
}

//Takes the string of characters in a chord, scans the chord and flags if high notes/low notes are present
//If both high and low notes are present, this means this chord would need a triple octave swap which is not possible
//due to the 100ms delay that broke all the macros. This function will move all low notes to the middle scale
//by default, leaving only mid and high notes, and limiting every chord to only 2 swaps, if both low and high are present in the chord

//Additionally:
//If a high note precedes a chord, then that chord cannot contain a low note otherwise 3 swaps would be needed, hence lows are removed
//If a low note precedes a chord, then that chord cannot contain a high note, hence highs are removed
//If a mid note precedes a chord, then by default the low notes will be removed if the chord contains both high and low within itself
string evalChord(string chord, char prev, bool removeChars){
	bool hasHigh = false, hasLow = false, prevLow = false, prevHigh = false;
	//Stores positions of high/low notes and the amount of them
	int commaPos[5], commaCount = 0, highPos[5], highCount = 0;
	int len = chord.length();
	
	if(prev == ','){ //, signifies a low note in MB notation
		prevLow = true;
	} else if (isHigh(prev)){
		prevHigh = true;
	}
	
	for(int i = 0; i < len; i++){
		if(isHigh(chord[i])){
			hasHigh = true;
			highPos[highCount] = i;
			highCount++;
		} else if(chord[i] == ','){
			hasLow = true;
			commaPos[commaCount] = i;
			commaCount++;
		}
	}
	
	if(hasHigh == true && hasLow == true){ //If the chord would require 3 octave swaps
		if(prevLow){ //If note before the chord is low, then the chord cannot contain high, hence remove high
			for(int i = 0; i < highCount; i++){
				chord[highPos[i]] = 'R'; //Placeholder for removal
			}
		} else { //Otherwise remove low
			if(removeChars == false){
				for(int i = 0; i < commaCount; i++){
					chord[commaPos[i]] = 'R';
				}
			} else {
				if(removeChars == true){
					for(int i = 0; i < commaCount; i++){
						chord[commaPos[i]-1] = 'R';
						chord[commaPos[i]] = 'R';
					}
				}
			}
		}
	}
	
	//Build the new chord
	string newChord;
	for(int i = 0; i < chord.length(); i++){
		if(chord[i] != 'R'){
			newChord += chord[i];
		}
	}
	return newChord;
}


int main(){
	//Declarations and file stuff
	bool removeChars = false;
	char curr, prev, filename[100], choice;
	string chord, newFilename, sFilename;
	
	ifstream input;
	ofstream output;
	
	cout << "Enter filename" << endl;
	cin.getline(filename, 100);
	input.open(filename);
	if(!input.is_open()){
  		cout << "Error opening file. Check the filename and ensure the file is in the same directory as the .exe\n";
  		system("pause");
  		exit(1);
	}
	
	sFilename = filename;
	newFilename = "Fixed " + sFilename;
	output.open(newFilename.c_str());
	
	cout << "\nWould you like to completely remove low notes instead of scaling them up to the middle scale? (y/n)" << endl;
	cin >> choice;
	if(choice == 'y'){
		removeChars = true;
	}

	
	input >> noskipws >> curr;
	while(!input.eof()){
		output << curr;
		
		//If a chord is about to follow
		if(curr == '['){
			//Combine all characters in the chord in a string
			while(curr != ']'){
				input >> curr;
				chord += curr;
			}
			//"Fix" chord
			chord = evalChord(chord, prev, removeChars);
			output << chord;
			chord = "";
		}
		
		if(isNote(curr)){ //Store previous note
			prev = curr;
		}
		input >> noskipws >> curr;
	}
	
	input.close();
	output.close();
	cout << "\nFixed file created as " << newFilename << endl;
	system("pause");
	exit(0);
}

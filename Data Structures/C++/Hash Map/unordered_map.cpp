#include <bits/stdc++.h>
using namespace std;

//Implementation of unordered_map

//Problem : Output the number of occurrence of a paricular word in the given string and print -1 if that word is not present.

//Input : Hactober fest is the best fest amongst all the fests. (fest) 
//Output : 2

//Algorithm: 1.Split the words from string and store their counts in map.
//           2.Search for the word using find function.
//			     3.If word is found print its occurrence else print -1.

int countOccurences(char str[] , string word) {
	
	unordered_map<string,int> m;
	char *p = strtok(str," ");

    //spliting and storing frequency of each word in the sentence.
	while(p!=NULL) {    
		m[p]++;
		p=strtok(NULL," ");
	}

	if(m.find(word)==m.end()) {   //if word is not found
		return -1;
	}else {
		return m[word];
	}
 }



int main() {
	char str[] = "Hactober fest is the best fest amongst all the fests .";
	string word="fests";
	cout<<countOccurences(str,word)<<endl;
	return 0;
}

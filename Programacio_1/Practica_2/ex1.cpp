#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define MAX_WORDS 10
#define MAX_CHARS 50
#define END_TEXT_CHAR '.'


/*
converts a string to uppercase
*/
void str_toupper(char str[MAX_CHARS]){
	for(int i=0;i<(int)strlen(str);i++){
		str[i]=toupper(str[i]);
	}
}


/*
compares to stings by first converting them to uppercase and then comparing them with strcmp from string.h
*/
int strcompare(char str1[MAX_CHARS],char str2[MAX_CHARS]){
	char copy1[MAX_CHARS],copy2[MAX_CHARS];
	strcpy(copy1,str1);
	strcpy(copy2,str2);
	str_toupper(copy1);
	str_toupper(copy2);
	return strcmp(copy1,copy2);
}


/*
checks if a char is a letter from a to Z
returns 1 if it is, and 0 if it isn't
*/
int is_letter(char c){
	if((c>='a'&&c<='z')||(c>='A'&&c<='Z')){
		return 1;
	}
	return 0;
}

/*
searches a char in a string and returns the position if exists and -1 if it dosen't exist
*/
int find_char(char c,char str[MAX_CHARS]){
	for(int i=0;i<(int)strlen(str);i++){
		if(toupper(str[i])==toupper(c)){
			return i;
		}
	}
	return -1;
}


/*
compacts a string by moving every char since the start_post one position left
*/
void compact_string(char str[MAX_CHARS],int start_pos){
	for(int i=start_pos;i<(int)strlen(str);i++){
		str[i]=str[i+1];
	}
}
/*
check if the str is anagram of anagram variable
return 1 if is anagram and 0 if is not an anagram
*/
int is_anagram(char anagram[MAX_CHARS],char str[MAX_CHARS]){
	char copy[MAX_CHARS]="";
	char temp[MAX_CHARS]="";
	int pos;
	if(strcompare(anagram,str)==0){
		return 1;
	}
	strcpy(copy,str);
	if((int)strlen(anagram)!=(int)strlen(copy)){
		return 0;
	}
	for(int i=0;i<(int)strlen(anagram);i++){
		pos=find_char(anagram[i],copy);
		if(pos==-1){
			return 0;
		}
		temp[i]=copy[pos];
		compact_string(copy,pos);
	}
	if(strcompare(temp,anagram)==0){
		return 1;
	}
	return 0;
}
/*
search for an anagram of the str string in a array of strings 
returns -1 if is not an anagram and the position of the anagram if it is
*/
int search_anagrams(int n_words,char searching_words[MAX_WORDS][MAX_CHARS],char str[MAX_CHARS],int found[MAX_WORDS]){
	int ret=0;
	for(int i=0;i<n_words;i++){
		if(is_anagram(searching_words[i],str)==1){
			found[i]++;
			ret=1;
		}
	}
	return ret;
}

int get_next_word(char end,char str[MAX_CHARS]){
	char c;
	int i=0;
	scanf("%c",&c);
	while(is_letter(c)){
		str[i]=c;
		i++;
		scanf("%c",&c);
	}
	str[i]='\0';
	if(c==end){
		return 1;
	}
	return 0;
}
int get_search_words(char words[MAX_WORDS][MAX_CHARS],char end_char){
	char buff[MAX_CHARS]="";
	int end,i=0;
	do{
		end=get_next_word(end_char,buff);
		if(strlen(buff)>=1){
			strcpy(words[i],buff);
			i++;
		}
	}while(!end&&i<MAX_WORDS);
	return i;
}
int main(){
	int n_search_words,end,index,start=0;
	int n_found[MAX_WORDS]={0};
	char search_words[MAX_WORDS][MAX_CHARS];
	char actual_word[MAX_CHARS];
	printf("Input the words to search ended by %c:\n",END_TEXT_CHAR);
	n_search_words=get_search_words(search_words,END_TEXT_CHAR);
	printf("\nInput a text to search the anagramsby %c:\n",END_TEXT_CHAR);
	scanf("%");
	do{
		end=get_next_word(END_TEXT_CHAR,actual_word);
		index=search_anagrams(n_search_words,search_words,actual_word,n_found);
		if(index){
			if(!start){
				printf("\nFound Anagrams:\n");
				start=1;
			}
			printf("%s, ",actual_word);
		}
	}while(!end);
	printf("\n\nNum of found anagrams:\n");
	for(int i=0;i<n_search_words;i++){
		printf("%s -> %i\n",search_words[i],n_found[i]);
	}
}
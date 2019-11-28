#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define MAX_WORDS 10
#define MAX_CHARS 50
#define END_TEXT_CHAR '.'
void str_toupper(char str[MAX_CHARS]){
	for(int i=0;i<strlen(str);i++){
		str[i]=toupper(str[i]);
	}
}
int strcompare(char str1[MAX_CHARS],char str2[MAX_CHARS]){
	char copy1[MAX_CHARS],copy2[MAX_CHARS];
	strcpy(copy1,str1);
	strcpy(copy2,str2);
	str_toupper(copy1);
	str_toupper(copy2);
	return strcmp(copy1,copy2);
}
int is_letter(char c){
	if((c>='a'&&c<='z')||(c>='A'&&c<='Z')){
		return 1;
	}
	return 0;
}
int find_char(char c,char str[MAX_CHARS]){
	for(int i=0;i<strlen(str);i++){
		if(toupper(str[i])==toupper(c)){
			return i;
		}
	}
	return -1;
}
void compact_string(char str[MAX_CHARS],int start_pos){
	for(int i=start_pos;i<strlen(str);i++){
		str[i]=str[i+1];
	}
}
//return 1 if is anagram and 0 if is not an anagram
int is_anagram(char anagram[MAX_CHARS],char str[MAX_CHARS]){
	char copy[MAX_CHARS]="";
	char temp[MAX_CHARS]="";
	int pos,len;
	strcpy(copy,str);
	//printf("(%s)",copy);
	if(strlen(anagram)!=strlen(copy)){
		return 0;
	}
	for(int i=0;i<strlen(anagram);i++){
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
//returns -1 if is not an anagram and the position of the searching word if it is
int find_anagram(int n_words,char words[MAX_WORDS][MAX_CHARS],char str[MAX_CHARS]){
	for(int i=0;i<n_words;i++){
		if(is_anagram(words[i],str)==1){
			return i;
		}
	}
	return -1;
}
//get chars from stdin ended by end char
int get_words(char words[MAX_WORDS][MAX_CHARS],char end_char){
	char c;
	char str[MAX_CHARS]="";
	int i=0,j=0;
	do{
		scanf("%c",&c);
		while(is_letter(c)){
			str[i]=c;
			i++;
			scanf("%c",&c);
		}
		str[i]='\0';
		if(i>=1){
			strcpy(words[j],str);
			str[0]='\0';
			j++;
			i=0;
		}
	}while(c!=end_char);
	return j;
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
int main(){
	int n_search_words,end,index;
	int n_found[MAX_WORDS]={0};
	char search_words[MAX_WORDS][MAX_CHARS];
	char actual_word[MAX_CHARS];
	n_search_words=get_words(search_words,END_TEXT_CHAR);
	printf("Found Anagrams:\n");
	end=get_next_word(END_TEXT_CHAR,actual_word);
	while(!end){
		index=find_anagram(n_search_words,search_words,actual_word);
		if(index!=-1){
			n_found[index]++;
			printf("%s(%s), ",actual_word,search_words[index]);
		}
		end=get_next_word(END_TEXT_CHAR,actual_word);
	}
	printf("\nNum of found anagrams:\n");
	for(int i=0;i<n_search_words;i++){
		printf("%s -> %i\n",search_words[i],n_found[i]);
	}
}

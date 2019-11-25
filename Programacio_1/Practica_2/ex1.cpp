#define MAX_WORDS 10
#define MAX_CHARS 50
int find_char(char c,char str[MAX_CHARS]){
	for(int i=0;i<strlen(str);i++){
		if(str[i]==c){
			return i;
		}
	}
	return -1;
}
void compact_string(char str[MAX_CHARS],int start_pos){
	for(int i=start_pos;i<strle(str);i++){
		str[i]=str[i+1];
	}
}
int is_anagram(char word[MAX_CHARS],char str[MAX_CHARS]){
	char temp[MAX_CHARS]="";
	int pos;
	if(strlen(word)!=strlen(str)){
		return 0;
	}
	for(int i=0;i<strlen(word);i++){
		pos=find_char(word[i],str)
		if(pos==-1){
			return 0;
		}
		temp[i]=str[pos];
		compact_string(str,pos);
	}
}
//returns -1 if is not an anagram and the position of the searching word if it is
int find_anagram(int n_words,char words[MAX_WORDS][MAX_CHARS],char str[MAX_CHARS]){
	for(int i=0;i<n_words;i++){
		for
	}
}
void get_searching_words(char words[MAX_WORDS][MAX_CHARS]){
	char c;
	char str[MAX_CHARS]="";
	int i=0,j=0;
	scanf("%c",&c);
	while(c!='.'){
		i=0;
		while(c!=' '){
			str[i]=c;
			i++;
		}
		str[i]='\0';
		strcpy(words[j],str);
	}
}

int main(){
	char words[MAX_WORDS][MAX_CHARS];
	char word[MAX_CHARS];
}

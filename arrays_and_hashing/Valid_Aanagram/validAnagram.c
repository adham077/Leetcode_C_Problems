#define TABLE_SIZE  27

bool isAnagram(char* s, char* t) {
    int i = 0;
    int freqArr[TABLE_SIZE];
    for(i=0;s[i];i++){
        freqArr[s[i]-'a']++;
    }
    for(i=0;t[i];i++){
        freqArr[t[i]-'a']--;
    }
    for(i=0;i<TABLE_SIZE;i++){
        if(freqArr[i]){
            return false;
        }
    }
    return true;
}
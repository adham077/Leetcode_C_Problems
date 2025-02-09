#define LETTERS_TABLE_SIZE 27

 int isAnagarm(char *str1, char *str2)
 {
     int HashTable[LETTERS_TABLE_SIZE] = {0};
     for(int i=0;str1[i];i++){
         HashTable[str1[i]-'a']++;
     }
     for(int i=0;str2[i];i++){
         HashTable[str2[i]-'a']--;
     }
     for(int i=0;i<LETTERS_TABLE_SIZE;i++){
         if(HashTable[i]){
             return 0;
         }
     }
     return 1;
 }
 
 struct node
 {
     char *str;
     int index;
     struct node *next;
 };
 
 typedef struct node node;
 
 int *freqArrHash(char *str){
     int *freqArr = (int *)malloc(sizeof(int) * LETTERS_TABLE_SIZE);
     for (int i = 0; str[i]; i++){
         freqArr[str[i] - 'a']++;
     }
     return freqArr;
 }
 
 int calcHash(int *freqArr, int tableSize){
     int hashVal = 0;
     for (int i = 0; i < LETTERS_TABLE_SIZE; i++){
         hashVal = (hashVal * 31 + freqArr[i]) % tableSize;
     }
     return (hashVal + tableSize) % tableSize;
 }
 
 void add_beg(node **head, char *str, int index){
     node *new_node = (node *)malloc(sizeof(node));
     new_node->str = str;
     new_node->index = index;
     new_node->next = *head;
     *head = new_node;
 }
 
 int search_list(node *head, char *str, int *index)
 {
     while (head){
         if (isAnagarm(str, head->str)){
             *index = head->index;
             return 1;
         }
         head = head->next;
     }
     return 0;
 }
 
 void free_list(node* head){
     node* temp = head;
     while(head){
         head = head->next;
         free(temp);
         temp = head;
     }
 }
 
 char ***groupAnagrams(char **strs, int strsSize, int *returnSize, int **returnColumnSizes)
 {
     node **HashMap = (node **)malloc(strsSize * sizeof(node *));
     int no_of_groups = 0;
     int index = 0;
     int* freqArr = NULL;
     int pos = 0;
     int* groupMap = (int*)calloc(strsSize,sizeof(int));
 
     for (int i = 0; i < strsSize; i++){
         HashMap[i] = NULL;
     }
     for (int i = 0; i < strsSize; i++){
         freqArr = freqArrHash(strs[i]);
         index = calcHash(freqArr,strsSize);
         free(freqArr);
         freqArr = NULL;
         if(!search_list(HashMap[index],strs[i],&pos)){
             groupMap[i] =  no_of_groups++;
         }
         else{
             groupMap[i] = groupMap[pos];
         }
         add_beg(&HashMap[index],strs[i],i);
     }
     *returnColumnSizes = (int*)calloc(no_of_groups,sizeof(int));
     for(int i=0;i<strsSize;i++){
         (*returnColumnSizes)[groupMap[i]]++;
     }
     char*** Groups = (char***)malloc(sizeof(char**)*no_of_groups);
     for(int i=0;i<no_of_groups;i++){
         Groups[i] = (char**)malloc(sizeof(char*)*
     ((*returnColumnSizes)[i]));
         (*returnColumnSizes)[i] = 0;
     }
     index = 0;
     for(int i=0;i<strsSize;i++){
         int groupNO = groupMap[i];
         Groups[groupNO][((*returnColumnSizes)[groupNO])++] = strs[i];
     }
     *returnSize = no_of_groups;
     for(int i=0;i<strsSize;i++){
         free_list(HashMap[i]);
     }
     free(HashMap);
     return Groups;
 }
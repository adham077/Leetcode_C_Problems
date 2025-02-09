/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

 struct node{
    int val;
    int index;
    struct node* next;
};

typedef struct node node;

void add_beg(node** head,int val,int index){
    node* new_node = (node*)malloc(sizeof(node));
    new_node->val = val;
    new_node->index = index;
    new_node->next = *head;
    *head = new_node;
}

int searchList(node* head,int val,int* index){
    while(head){
        if(head->val==val){
            *index = head->index;
            return 1;
        }
        head = head->next;        
    }
    return 0;
}   

void freeList(node* head){
    node* temp = head;
    while(head){
        head = head->next;
        free(temp);
        temp = head;
    }
}

int hashFn(int val,int table_size){
    return abs(val%table_size);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* ret = (int*)malloc(sizeof(int)*(*returnSize));
    node** hashMap = (node**)malloc(sizeof(node*)*numsSize);
    int index = 0;
    int toTarget =0;
    for(int i=0;i<numsSize;i++){
        hashMap[i] = NULL;
    }
    for(int i=0;i<numsSize;i++){
        toTarget = target - nums[i];
        index = hashFn(toTarget,numsSize);
        if(searchList(hashMap[index],toTarget,&ret[0])){
            ret[1] = i;
            for(int j=0;j<numsSize;j++){
                freeList(hashMap[j]);
            }
            free(hashMap);
            return ret;
        }
        index = hashFn(nums[i],numsSize);
        add_beg(&hashMap[index],nums[i],i);
    }
    for(int j=0;j<numsSize;j++){
        freeList(hashMap[j]);
    }
    free(hashMap);
    return ret;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int key;
    int degree;
    int check;
    struct Node* child;
    struct Node* sibling; 
}Node;

Node* create(int key){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->degree = 0;
    node->check = 0;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}

void print(Node**root){
    for(int i = 0;i<100;i++){//degree
        for(int k = 0;k<100;k++){
            if(root[k]){
                if(root[k]->degree==i){
                    Node* out[100] = {NULL};
                    out[0] = root[k];
                    root[k]->check = 1;
                    int j = 0;
                    int num = 1;
                    
                    while(out[j]!=NULL){
                        if(out[j]->child){ 
                            out[num++] = out[j]->child;
                            out[j]->child->check = 1;
                            Node*current = out[j]->child;
                            while(current ){
                                if(current->sibling){
                                    out[num++] = current->sibling;
                                    current->sibling->check = 1;
                                }
                                current = current->sibling;
                            }
                        }
                        j++; 
                    }
                    for(int j = 0;j<num;j++){
                        if(out[j]){
                            printf("%d ",out[j]->key);
                        }
                    }
                    printf("\n");
                }
            }
            
        }
        
    }
    for (int k = 0; k < 100; k++) {
        if (root[k]) {
            Node* current = root[k];
            while (current) {
                current->check = 0;
                if (current->child) {
                    Node* child = current->child;
                    while (child) {
                        child->check = 0;
                        child = child->sibling;
                    }
                }
                current = current->sibling;
            }
        }
    }
}

void insert(Node**root,int key,Node** min){
    Node* node = create(key);
    for(int i = 0;i<100;i++){
        if(root[i]==NULL){
            root[i] = node;
            root[i]->sibling = NULL;
            if(node->key < (*min)->key){
                *min = node;
            }
            break;
        }
    }
    return;
}

void newRoot(Node**root,Node*node,Node**min){
    for(int i = 0;i<100;i++){
        if(root[i]==NULL){
            root[i] = node;
            root[i]->sibling = NULL;
            if(node->key < (*min)->key){
                *min = node;
            }
            break;
        }
    }
}

void decrease(Node**root,int key,int value,Node** min){
    for(int i = 0;i<100;i++){
        if(root[i]){
            Node* out[100] = {NULL};
            out[0] = root[i];
                
            int j = 0;
            int num = 1;
            while(out[j]!=NULL){
                if(out[j]->key==key){
                    out[j]->key = key-value;
                    root[i] = out[j];
                    if(root[i]->key < (*min)->key) *min = root[i];
                    break;
                }
                if(out[j]->child){ 
                    out[num++] = out[j]->child;
                    if(out[j]->child->key == key){
                        out[j]->child->key = key-value;
                        if(out[j]->child->key < out[j]->key){
                            newRoot(root,out[j]->child,min);
                            if(out[j]->child->sibling)out[j]->child = out[j]->child->sibling;
                            else out[j]->child = NULL;
                            out[j]->degree--;
                            break;
                            }
                    }
                    Node*current = out[j]->child;
                    while(current ){
                        if(current->sibling){
                            out[num++] = current->sibling;
                            if(current->sibling->key == key){
                                current->sibling->key = key-value;
                                if(current->sibling->key < out[j]->key){   
                                    newRoot(root,current->sibling,min);
                                    if(current->sibling->sibling)current->sibling = current->sibling->sibling;
                                    else current->sibling = NULL;
                                    out[j]->degree--;
                                    break;
                                }
                            }
                        }
                        current = current->sibling;
                    }
                }
                j++; 
            }
        }
    }
    for(int i = 0;i<100;i++){
        if(root[i]){
            root[i]->sibling = NULL;
        }
    }
}

void adjust(Node**root,Node* node,Node**min){
    if(node->child){
        Node *current = node->child;
        while(current ){
            
                for(int j = 0;j<100;j++){
                    if(root[j]==NULL){
                        root[j] = current;
                        
                        if(*min==NULL || root[j]->key <(*min)->key) *min = root[j];
                        break;
                    }
                }
            
            if(current->sibling)current = current->sibling;
            else current = NULL;
        }
        
        for(int i = 0;i<100;i++){
            if(root[i]&&root[i]->sibling){
                root[i]->sibling = NULL;
            }
        }
    }
    return;
}

// 
void delete(Node** root, int key, Node** min) {
    for (int i = 0; i < 100; i++) {
        if (root[i]) {
            if (root[i]->key == key) {  
                adjust(root, root[i], min); 
                free(root[i]);  
                root[i] = NULL;  
                return;
            } 
            else if (root[i]->child) {
                Node* current = root[i]->child;
                Node* prev = NULL;
                while (current) {
                    if (current->key == key) { 
                        if (prev) {
                            prev->sibling = current->sibling;  
                        } else {
                            root[i]->child = current->sibling;  
                        }
                        adjust(root, current, min); 
                        free(current);  
                        root[i]->degree--;  
                        return;
                    }
                    prev = current;
                    current = current->sibling;
                }
            }
        }
    }
}


void meld(Node**root,int degreeNum){
    int degree[100];
    for(int i = 0;i<100;i++){
        degree[i] = -1;
    }
    int num = 0;
    for(int i=0;i<100;i++){
        if(root[i]){
            if(root[i]->degree==degreeNum){
                degree[num++] = i;
                for(int k = 0;k<num;k++){
                    if(root[degree[k]]->key > root[degree[num-1]]->key){
                        int tmp = degree[k];
                        degree[k] = degree[num-1];
                        degree[num-1] = tmp;
                    }
                }
            }
        }
    }
    for(int i = 0;i<100;i++){
        if(degree[i]!=-1 &&root[degree[i]]){
            int j = i+1;
            for(j = i+1;j<100;j++){
                if(degree[j]!=-1 && root[degree[j]]) break;
            }
            if((!root[degree[i]]->child) && j<100&&degree[j]!=-1){
                root[degree[i]]->child = root[degree[j]];
                root[degree[i]]->degree++;
                root[degree[j]] = NULL;
                degree[j] = -1;
                
            }
            else if(root[degree[i]]->child && j<100&&degree[j]!=-1){
                Node* current = root[degree[i]]->child;
                if(current->key > root[degree[j]]->key){
                    root[degree[j]]->sibling = root[degree[i]]->child;
                    root[degree[i]]->child = root[degree[j]];
                    root[degree[i]]->degree++;
                    root[degree[j]] = NULL;
                    
                }
                else {
                    int checkk = 0;
                    while(current){
                        if(current->sibling && current->sibling->key > root[degree[j]]->key){
                            root[degree[j]]->sibling = current->sibling;
                            current->sibling = root[degree[j]];
                            checkk = 1;
                            break;
                        }
                        current = current->sibling;
                    }
                    if(!checkk){
                        current = root[degree[i]]->child;
                        while(current){
                            if(current->sibling == NULL){
                                current->sibling = root[degree[j]];
                                //print(root);
                                break;
                            }
                            current = current->sibling;
                        }
                        
                        root[degree[i]]->degree++;
                        root[degree[j]] = NULL;
                        
                    } 
                }
                degree[j] = -1;
                
                break;
            }
            
        }
        degree[i] = -1;
        
    }

}

void extract_min(Node**root,Node**min){
    for(int i = 0;i<100;i++){
        if(root[i]==*min) root[i] = NULL;
    }

    Node* tmp = *min;
    *min = NULL;
    if(tmp->child) adjust(root,tmp,min);
    free(tmp);
    for (int i = 0; i < 100; i++) {
        if (root[i]) {
            if (*min == NULL || root[i]->key < (*min)->key) {
                *min = root[i];
            }
        }
    }
}



int main(){
    Node* min = create(10001);
    Node* root[100];
    for(int i = 0;i<100;i++){
        root[i] = NULL;
    }
    while(1){
        char input[15];
        scanf("%s",input);
        if(strcmp(input,"exit")==0) break;
        else{
            int key;
            
            if(strcmp(input,"insert")==0){
                scanf("%d",&key);
                insert(root,key,&min);
            }
            else if(strcmp(input,"delete")==0){
                scanf("%d",&key);
                delete(root,key,&min);
                for(int i = 0; i<100;i++){
                    meld(root,i);
                }
            }
            else if(strcmp(input,"decrease")==0){
                scanf("%d",&key);
                int value;
                scanf("%d",&value);
                decrease(root,key,value,&min);

            }
            else{
                extract_min(root,&min);
                for(int i = 0; i<100;i++){
                    meld(root,i);
                    
                }
            }
        }
        //print(root);
    }
    print(root);
}
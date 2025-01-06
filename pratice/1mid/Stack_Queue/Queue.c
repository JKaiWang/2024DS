// First in First out
// we need some function
// Enqueue() the function is used to add some data at the last position
// Dequeue() the function is used to delete the data at the first position
// getFirst() the function is used to return the first data
// getLast() the function is used to return the last data
// getsize() the function is used to return the size of this Queue
// isEmpty() to check whether the queue is empty or not
#include <stdio.h>
#include <stdlib.h>
#define maxVolume 16	//定義佇列的最大容量

int Queue[maxVolume];	//佇列的陣列宣告 
int First = -1;		//佇列的前端(第一筆)
int Last = -1;		//佇列的尾端(最後一筆)		
int Size = 0;		//佇列目前的大小

void Enqueue(int a);	//從佇列尾端存入資料，在main函數之後定義
int Dequeue();		//從佇列前端移除資料，在main函數之後定義
int getFirst();		//回傳佇列前端(第一筆)的資料，在main函數之後定義
int getLast();		//回傳佇列尾端(最後一筆)的資料，在main函數之後定義
int getSize();		//回傳佇列目前的大小，在main函數之後定義
int isEmpty();		//檢查佇列是否為空，在main函數之後定義

int main() {

	for(int i =0; i<10;i++){
		Enqueue(rand()%36);
	}  
	
	if(isEmpty()){
		printf("the first data in the queue is: NULL\n");
		printf("the last data in the queue is: NULL\n");
	}else{
		printf("the first data in the queue is:%d\n",getFirst());
		printf("the last data in the queue is:%d\n",getLast());
	}
	printf("the total num of queue is:%d\n\n",getSize());
	while(!isEmpty()){
		printf("the data that is removed in the queue is:%d\n",Dequeue());	
	}
	Dequeue();
	return 0;
}

void Enqueue(int a){
	if(Last >= maxVolume){
		printf("the queue is full");
	}else{
		Queue[++Last] = a;
		Size+=1;
		if(First == -1){First = 0;}
	}
}

int Dequeue(){   
	if(isEmpty()){
		printf("the queue is empty\n");
	}else{ 
		int data;
		data = Queue[First];
		for(int i=First; i<=Last;i++){
			Queue[i] = Queue[i+1];
		}
		Last -=1;
		Size -= 1;
		return data;
	}
}

int getFirst(){
	if(!isEmpty()){return Queue[First];}
}

int getLast(){
	if(!isEmpty()){return Queue[Last];}
}

int getSize(){
	return Size;
}

int isEmpty(){
	if(Size<=0){
		First = -1;
		Last = -1;
		return 1;
	}else{
		return 0;
	}
}
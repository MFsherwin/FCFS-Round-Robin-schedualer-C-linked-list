/*CS 410 Programming Assignment 0
You are only allowed to modify void insert(),  void dequeue(), void pop(), and void sort()
DO NOT MAKE ANY CHANGES TO OTHER PART OF THE CODE
You may modify the main() to test your program but change it back to the orignal main()
when you turn in your code.
*/
#include <stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//round robin and FCFS algorithm implementation using doubly linked circular list. extra list
//functionality added for use with other projects 
struct task {
	
	struct task *next;
	struct task *previous;
    int waitTimeForP;
    int flag;
    int timeSinceLastEx;
	int pid;
    int burst;
    
};

struct task *head = NULL;
struct task *tail = NULL;


void print(){
	struct task *current = head;
        
	while(current!=NULL){
                printf("%d ", current->pid);
                current=current->next;

        }
	free(current);
	printf("\n");

}

//returns length as int
int* length(){
	
	struct task *current = malloc(sizeof(struct task));
	int length =0;
    int *ptr;
    ptr = &length;
	if (head == NULL){
		return 0;
	}
	
	
	while(current != tail){
		length++;
		current = current->next;
	}
	free(current);
	ptr = &length;
    return ptr;

}

//added to clean code up a bit
bool isEmpty(){
	bool ifn = false;
	if (head==NULL){
		ifn = true;
		return ifn;
	}
	else{
		return ifn;
	}
		
}


//adds node to beginning of list for both stack and queue functionality
void insertFirst(int burst, int pid){
	
	struct task *newTask = (struct task*) malloc(sizeof(struct task));
	
	newTask->pid = pid;
	newTask->burst = burst;
	
	if(isEmpty()){
		head = newTask;
		tail = head;

		newTask->next = tail;
		newTask->previous = head;
	}

	else{
		newTask->next = head;
		head->previous = newTask;
		newTask->previous = tail;
		tail->next = newTask;
		head = newTask;
	}

	
	return;
	

}


//not needed but adds more functionality for use in other projects
void append(int burst, int pid){
	//adds new
    struct task *newTask = malloc(sizeof(struct task));

	newTask->pid = pid;
	newTask->burst = burst;

	if (isEmpty()){
		head = newTask;
		tail = head;

		newTask->next = tail;
		newTask->previous = head;
	}
	else{
		tail->next = newTask;
		newTask->previous =tail;
		newTask->next = head;
		head->previous = newTask;
		tail = newTask;
	}
	return;
}

void dequeue(){
	//removes node from end of list for queue functionality
	
	if(isEmpty()){
		return;
	}
	
	struct task *tmp = malloc(sizeof(struct task));
	
	tmp = tail;
	tail = tail->previous;
	tail->next = head;
	head->previous =tail;
	free(tmp);

return;
}

//removes node from start of list for stack functionality. added free() function
void pop(){
	
	struct task *tmp = NULL;
	
	if (isEmpty()){
		return;

	}
	
	tmp = head;

	head = head->next;
	head->previous = tail;
	tail->next = head;
	//free(tmp);

	
	return;

}



void sort(){
	
	int a;
	
	//init temp nodes for iteration of linked list
	
	struct task *tmp1 = malloc(sizeof(struct task));
	struct task *tmp2 = malloc(sizeof(struct task));
	
	//goes through linked list and swaps data to sort
	//not ideal but works for this purpose 
	for(tmp1=head; tmp1->next != head; tmp1=tmp1->next){
		
		for (tmp2=tmp1->next ; tmp2!=tail ; tmp2=tmp2->next){
			
			if(tmp2->burst < tmp1->burst){
				a = tmp1->burst;
				tmp1->burst = tmp2->burst;
				tmp2->burst = a;

			}
		}
	}

}

void FCFS(int numps, int tburst){
    int size = numps;
    int time=0;
    float waitTime=0;
    int count=0;
    float turnaroundTime=0;
    struct task *current = malloc(sizeof(struct task));
	current = head;
	
    while (1){
        for(int i=0; i<current->burst;i++){
            
            time++;
        }
        turnaroundTime+=time;
        printf("P%d " ,current->pid );
        
        if((current->pid>1) && (current->pid<size)){
            waitTime += time;
        }
        current = current->next;
        count++;
        if (count == size){
            break;
        }
    }
    
    waitTime = (turnaroundTime - tburst)/size;    
    turnaroundTime = turnaroundTime / size;
    printf("/naverage wait time: %f\n",waitTime);
    printf("average totalTurnaroundTime: %f\n",turnaroundTime);

	return;

}


void roundRobin(int numOfProcesses, int totalBurstTime){
    struct task *exec = malloc(sizeof(struct task));
    float waitTime;
    int size = numOfProcesses;
	float totalTurnaroundTime=0;
	int time=0;
    int count=0;
	exec = head;
	exec->flag=0;
	
	while(1){
		
        if ((exec->flag == 0) && (exec->burst>10)){
            printf("P%d ",exec->pid );
            
			
            exec->burst = exec->burst -10;
            time+=10;
            exec->flag=0;
            
            if (exec->burst==0){
                exec->flag =1;
                totalTurnaroundTime+=time;
                
            }
        }
        
        else if (exec->burst <= 10 && exec->flag!=1){
            printf("P%d ",exec->pid );
            exec->flag=1;
            time += exec->burst;
            totalTurnaroundTime+=time;
            exec->burst = 0;
            
        }
        
        
        struct task *cur = head;
        for (int i=0; i<size;i++){
            if(cur->flag == 0){
                count++;
            }
            cur = cur->next;
        }
        if (count==0){
            break;
        }
        count =0;
        exec = exec->next;
        
    }
    waitTime = (totalTurnaroundTime - totalBurstTime)/size;
    totalTurnaroundTime = totalTurnaroundTime/size;
    
    	
    printf("\naverage wait time: %f\n",waitTime);
    printf("average total TurnaroundTime: %f\n",totalTurnaroundTime);
		
	return;

}


int main(int argc, char * argv[]){


	if (argc != 3|| (atoi(argv[1])!=0 && atoi(argv[1])!= 1)){
		fprintf(stderr, "Usage: ./scheduler <option> <filename>\nAvailable options:\n 		0: FCFS\n 		1: Round robin\n" );
		return(0);
	}    
    

    FILE *input = fopen("data.txt","r");    
    int burst_time;
    int pid=0;
    int totalBurst;
    int count=0;
    
    while(fscanf(input,"%d",&burst_time)!=EOF){
        totalBurst = totalBurst + burst_time;
        append(burst_time, pid);
        count+=1;
        pid+=1;
        //printf("%d\n",burst_time);
    }
    
    int np = count ;//length();
    int choice = atoi(argv[1]);
    

    switch (choice){
    	case 0:
    		FCFS(np, totalBurst);
    		break;
    	case 1:
    		roundRobin(np, totalBurst);
    		break;
    }


	return 0;

}

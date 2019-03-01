#include <stdio.h>
#include <stdlib.h>


int stackIsFull(int* stack_top,int SIZE){
    if(*stack_top==SIZE-1){
        return 1;
    }
    return 0;
}

int stackIsEmpty(int* stack_top){


    if(*stack_top == -1)
      return 1;
   else
      return 0;

}

int queueIsFull(int* front,int* rear,int SIZE){

    if( (*front == *rear + 1) || (*front == 0 && *rear == SIZE-1))
        return 1;
    return 0;

}

int queueIsEmpty(int* front){
    if(*front == -1) {
            return 1;
    }
    else{
    return 0;
   }
}





void enQueue(char* que,int* front,int* rear,int SIZE,char element){

   if(queueIsFull(front,rear,SIZE)){
      //printf("\n Circular Queue is Full!");
   }
    else
    {
        if(*front == -1){
            *front = 0;
        }
        *rear = (*rear + 1) % SIZE;
        que[*rear] = element;
        //printf("\n Inserted Queue -> %c", element);

    }

}
void deQueue(int* front,int* rear,int SIZE)
{
    if(queueIsEmpty(front)) {
        //printf("\n Queue is empty !! \n");

    } else {
        if (*front == *rear){
            *front = -1;
            *rear = -1;
        }
        else {
            *front = (*front + 1) % SIZE;

        }

    }
}


void push(char* stackk,int* stack_top,int SIZE,char element){

    if(stackIsFull(stack_top,SIZE)){
        //printf("\n Stack is Full!!");
    }
    else{

        *stack_top+=1;
        stackk[*stack_top]=element;
        //printf("\n Inserted Stack -> %c", element);


    }
}
void pop(int* stack_top){

    if(stackIsEmpty(stack_top)){

    }
    else{
        *stack_top-=1;
    }



}




int main (int argc, char *argv[]) {

typedef struct{

    int queue_size;
    int stack_size;
    int front;
    int rear;
    int stack_top;
    char *queue;
    char *stack;
    char logHistory[10000];
    int log_top;

} data;




    int client_server_sayisi;
    FILE *files1;
    files1=fopen(argv[1],"r");
    fscanf(files1,"%d",&client_server_sayisi);

    data server_client[client_server_sayisi];

    int x;

    for(x=0;x<client_server_sayisi;x++){

       int a;
       fscanf(files1,"%d",&server_client[x].queue_size);
       fscanf(files1,"%d",&server_client[x].stack_size);
       server_client[x].front=-1;
       server_client[x].rear=-1;
       server_client[x].stack_top=-1;
       server_client[x].log_top=-1;

       server_client[x].queue=malloc(server_client[x].queue_size*sizeof(char));
        server_client[x].stack=malloc(server_client[x].stack_size*sizeof(char));

    }

    fclose(files1);


    FILE *files2;
    files2=fopen(argv[2],"r");

    char value1;
    int value2;
    char value3;
    int operationsTime;
    fscanf(files2,"%d",&operationsTime);

    int serverNum=client_server_sayisi;

    int ii;
    for(ii=0;ii<operationsTime;ii++){
        fscanf(files2,"%s ",&value1);


        if(value1=='A'){

            fscanf(files2,"%d ",&value2);
            fscanf(files2,"%c ",&value3);



            if(queueIsFull(&server_client[value2-1].front,&server_client[value2-1].rear,server_client[value2-1].queue_size)){
                push(server_client[value2-1].logHistory,&server_client[value2-1].log_top,10000,'1');
            }
            else{
                enQueue(server_client[value2-1].queue ,&server_client[value2-1].front,&server_client[value2-1].rear,server_client[value2-1].queue_size,value3);
            }
        }

        else if(value1=='I'){
            fscanf(files2,"%d ",&value2);
            fscanf(files2,"%c ",&value3);
            if(stackIsFull(&server_client[value2-1].stack_top,server_client[value2-1].stack_size)){
                push(server_client[value2-1].logHistory,&server_client[value2-1].log_top,10000,'2');
                }
            else{
                push(server_client[value2-1].stack ,&server_client[value2-1].stack_top,server_client[value2-1].stack_size,value3);

            }




        }

        else if(value1=='S'){
           fscanf(files2,"%d ",&value2);
           fscanf(files2,"%c ",&value3);

                if(stackIsEmpty(&server_client[value2-1].stack_top)){
                    if(queueIsEmpty(&server_client[value2-1].front)){
                        push(server_client[value2-1].logHistory,&server_client[value2-1].log_top,10000,'3');
                    }
                    else if(queueIsFull(&server_client[serverNum-1].front,&server_client[serverNum-1].rear,server_client[serverNum-1].queue_size)){
                        char valuee =server_client[value2-1].queue[server_client[value2-1].front];
                        push(server_client[value2-1].logHistory,&server_client[value2-1].log_top,10000,valuee);
                        push(server_client[serverNum-1].logHistory,&server_client[serverNum-1].log_top,10000,'1');

                        deQueue(&server_client[value2-1].front,&server_client[value2-1].rear,server_client[value2-1].queue_size);

                    }
                    else{
                        char valuee =server_client[value2-1].queue[server_client[value2-1].front];
                        push(server_client[value2-1].logHistory,&server_client[value2-1].log_top,10000,valuee);
                        enQueue(server_client[serverNum-1].queue,&server_client[serverNum-1].front,&server_client[serverNum-1].rear,server_client[serverNum-1].queue_size,valuee);
                        deQueue(&server_client[value2-1].front,&server_client[value2-1].rear,server_client[value2-1].queue_size);
                    }

                }

                else{
                    if(queueIsFull(&server_client[serverNum-1].front,&server_client[serverNum-1].rear,server_client[serverNum-1].queue_size)){
                        //char valuee =server_client[value2-1].queue[server_client[value2-1].front];
                        char valuee =server_client[value2-1].stack[server_client[value2-1].stack_top];

                        push(server_client[value2-1].logHistory,&server_client[value2-1].log_top,10000,valuee);
                        push(server_client[serverNum-1].logHistory,&server_client[serverNum-1].log_top,10000,'1');
                        pop(&server_client[value2-1].stack_top);
                        }
                    else{

                        char valuee =server_client[value2-1].stack[server_client[value2-1].stack_top];
                        push(server_client[value2-1].logHistory,&server_client[value2-1].log_top,10000,valuee);
                        enQueue(server_client[serverNum-1].queue,&server_client[serverNum-1].front,&server_client[serverNum-1].rear,server_client[serverNum-1].queue_size,valuee);
                        pop(&server_client[value2-1].stack_top);
                }

           }

        }
        else if(value1=='O'){
           fscanf(files2,"%c ",&value2);
           fscanf(files2,"%c ",&value3);
           if(stackIsEmpty(&server_client[serverNum-1].stack_top)){
                if(queueIsEmpty(&server_client[serverNum-1].front)){
                        push(server_client[serverNum-1].logHistory,&server_client[serverNum-1].log_top,10000,'3');
                    }

                else{

                    char valeee=server_client[serverNum-1].queue[server_client[serverNum-1].front];
                    push(server_client[serverNum-1].logHistory,&server_client[serverNum-1].log_top,10000,valeee);
                    deQueue(&server_client[serverNum-1].front,&server_client[serverNum-1].rear,server_client[serverNum-1].queue_size);

                }

           }
            else{

                char valeee=server_client[serverNum-1].stack[server_client[serverNum-1].stack_top];
                push(server_client[serverNum-1].logHistory,&server_client[serverNum-1].log_top,10000,valeee);
                pop(&server_client[serverNum-1].stack_top);

            }
        }







    }
    FILE *write;
    write=fopen(argv[3],"w");

    int aa;
    int bb;
    for(aa=0;aa<serverNum;aa++){
            for(bb=0;bb<server_client[aa].log_top+2;bb++){
                fprintf(write,"%c ",server_client[aa].logHistory[bb]);
            }
        fprintf(write, "\n");
    }
	
    int emptyMemory;
    for(emptyMemory=0;emptyMemory<serverNum;emptyMemory++){
        free(server_client[emptyMemory].queue);
        free(server_client[emptyMemory].stack);
    }


    return 0;
}























#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

void dropWhites(char *str){
  char *ptr = strchr(str, '\n');
  if(ptr != NULL){
    *ptr = '\0';
  }
}

void displayList(){
  FILE *todo = fopen("TODO.list", "r");
  if(todo != NULL){
    //printf("File opened successfully\n");

    char ch;
    ch = fgetc(todo);
    if(ch == EOF) {
      printf("No tasks pending soon\n");
    } else {
      //printf("");
      while(ch != EOF){
        //printf("%c", ch);
        if(ch == '\n'){
          printf("%c ", ch);
        } else {
          printf("%c", ch);
        }
        ch = fgetc(todo);
      }
    }
    fclose(todo);
  } //else {
      //printf("Unable to open file\n");
  //}
}

void displayHist(){
  FILE *hist = fopen("history.list", "r");
  if(hist != NULL){
    //printf("File opened successfully\n");

    char ch;
    ch = fgetc(hist);
    if(ch == EOF) {
      printf("Empty history\n");
    } else {
      //printf("");
      while(ch != EOF){
        //printf("%c", ch);
        if(ch == '\n'){
          printf("%c ", ch);
        } else {
          printf("%c", ch);
        }
        ch = fgetc(hist);
      }
    }
    fclose(hist);
  } //else {
    //printf("Unable to open file\n");
  //}
}

void addTask(){
  char buffer[200];
  FILE *todo = fopen("TODO.list", "a");
  FILE *hist = fopen("history.list", "a");
  if(todo != NULL && hist != NULL){
    //printf("File opened for appending\n");

    printf("Enter new task for your todo list: ");
    fgets(buffer, 200, stdin);
    dropWhites(buffer);
    
    fputc('\n', todo);
    fputs(buffer, todo);//paste task in todo list
    
    fputc('\n', hist);
    fputs(buffer, hist);//paste task in history list

    printf("Added successfully\n");

    fclose(hist);
    fclose(todo);
  } else {
    printf("Cannot append file\n");
  }
}

void markDone(int index){
  FILE *todo = fopen("TODO.list", "r");
  if(todo != NULL){
    //printf("Opened successfully\n");
    int currentLine=0;
    
    FILE *temp = fopen("buffer.temp", "w");
    char ch = fgetc(todo);
    while(ch != EOF){
      if(ch == '\n'){
        currentLine++;
      }
      if(currentLine != index){
        fputc(ch, temp);
      }
      ch = fgetc(todo);
    }
    fclose(temp);
    fclose(todo);
    //Now copy contents of buffer.temp to todo.list and delete buffer.temp
    FILE *buff = fopen("buffer.temp", "r");
    FILE *todoList = fopen("TODO.list", "w");
    char buffch;
    buffch = fgetc(buff);
    while(buffch != EOF){
      fputc(buffch, todoList);
      buffch = fgetc(buff);
    }
    fclose(buff);
    remove("buffer.temp");
    fclose(todoList);
    printf("Marked as Done.");
  } else {
    printf("Cannot mark as done\n");
  }
}

int main(){
  int flag = TRUE;
  int op;
  do {
    
    system("clear");
    displayList();
    printf("\n\nWhat do you want to do ?\n");
    printf("1.Add a task\t2.Mark Task as done\n3.View History\t4.Exit\n");
    scanf("%d%*c", &op);
    
    switch(op){
      case 1:{
               addTask();break;
             }
      case 2:{
               printf("Enter index of task which is done:\n");
               int index;
               scanf("%d%*c", &index);
               markDone(index);
               break;
             }
      case 3:{
               displayHist();
               printf("\n");
               flag = FALSE;
               break;
             }
      case 4:{
               flag = FALSE;break;
             }
    }
  }while(flag);
  return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main(){
    char label[20],opcode[20],operand[20],code[20],mnuemonic[20];
    int length,start,locctr;
    FILE *OUTPUT,*INPUT,*SYMTAB,*OPTAB;

    INPUT=fopen("INPUT.txt","r");
    OPTAB=fopen("OPTAB.txt","r");
    SYMTAB=fopen("SYMTAB.txt","w");
    OUTPUT=fopen("OUTPUT.txt","w");

    fscanf(INPUT,"%s\t%s\t%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0){
        start=atoi(operand);
        locctr=start;
        fprintf(OUTPUT,"\t%s\t%s\t%s\t",label,opcode,operand);
        fscanf(INPUT,"%s\t%s\t%s",label,opcode,operand);
    }else{
        locctr=0;
    }
    while(strcmp(opcode,"END")!=0){
        fprintf(OUTPUT,"%d",locctr);
        if(strcmp(label,"-")!=0){
            fprintf(SYMTAB,"%s\t%s",label,locctr);
        }
        fscanf(OPTAB,"%s\t%s",code,mnuemonic);
        while(strcmp(code,"END")!=0){
            if(strcmp(opcode,code)==0){
            locctr=locctr+3;
            break;
            }
            fscanf(OPTAB,"%s\t%s",code,mnuemonic);
            
        }
        if(strcmp(opcode,"WORD")==0){
            locctr=locctr+3;
        }
        else if(strcmp(opcode,"RESW")){
            locctr+=(3*atoi(operand));
        }
        else if(strcmp(opcode,"RESB")){
            locctr+=atoi(operand);
        }
        else if(strcmp(opcode,"BYTE")){
            ++locctr;
        }
        fprintf(OUTPUT,"%s\t%s\t%s",label,opcode,operand);
        fscanf(INPUT,"%s\t%s\t%s",label,opcode,operand);

    }
    fprintf(OUTPUT,"%d\t%s\t%s\t%s",locctr,label,opcode,operand);
    length=locctr-start;
    printf("The length of the code is %d",locctr);
    fclose(OUTPUT);
    fclose(INPUT);
    fclose(SYMTAB);
    fclose(OPTAB);

}
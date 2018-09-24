#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int max ( int a, int b ) { return a > b ? a : b; }

int lossFunc(const char* X, const char* Y, int i, int j){  //delta
    if(X[i]==Y[j]) 
        return 1;
    else    
        return -0;   
}

void costFunc(int***V,const char* X, const char* Y, int i, int j){ //
    int a = (*V)[i-1][j-1] + 2*lossFunc(X,Y,i-1,j-1)-1;   
    int b = (*V)[i-1][j]   -1; 
    int c = (*V)[i][j-1]   -1;
    (*V)[i][j] = max(max(a,b),max(c,0));
}

int** fillV(const char* X, const char* Y, int n,int m){
    int** V = (int**)calloc(n,sizeof(int*));
    for(int i = 0; i<n;++i)
        V[i] = (int*)calloc(m,sizeof(int));
    for(int j = 1;j<m;++j)
        for(int i = 1; i<n;++i)
            costFunc(&V,X,Y,i,j);
    return V;
}
void freeV(int***V,int n){
    for(int i = 0; i<n; ++i)
        free((*V)[i]);
    free(*V);
}
int* fillTuple(int**V,int n, int m){
    int* tuple = (int*)calloc(3,sizeof(int));
    for(int j = 1;j<m;++j)
        for(int i = 1; i<n;++i)
            if(V[i][j]>tuple[0]){
                tuple[0] = V[i][j]+1;
                tuple[1] = i-tuple[0]+1;
                tuple[2] = j+1;
            }
    return tuple;
}
int* smithWatermanAlgo(const char*X,const char*Y){
    int n = strlen(X);
    int m = strlen(Y);
    int** V = fillV(X,Y,n,m);        //V[n][m] where V[:][0], V[0][:] is a mask of ZEROES
    int* tuple = fillTuple(V,n,m);   // rank 3 vector: allignment, prefixed indecies for X_i and Y_i

    freeV(&V,n);
    return tuple;
}

char* strWithProperGap(const char* X,int i){
    char* str = (char*)calloc(256,sizeof(char));
    strncat(str,X,i);
    str[i] = '-';
    strcat(str,X+i);
    return str;
}
void printStuff(const char* S1in, const char* S2in){
    int* tuple = smithWatermanAlgo(S1in,S2in);
    char* S1out = strWithProperGap(S1in,tuple[1]);
    char* S2out = strWithProperGap(S2in,tuple[2]);
    printf("Input\n");
    printf("S1 = %s\n",S1in);
    printf("S2 = %s\n",S2in);
    printf("Output\n");
    printf("S1 = %s\n",S1out);
    printf("S2 = %s\n",S2out);
    free(S1out);
    free(S2out);
    free(tuple);
}

char** getStrings(){
    char** lines = (char**)malloc(sizeof(char*)*2);
    lines[0] = (char*)malloc(sizeof(char)*256);
    lines[1] = (char*)malloc(sizeof(char*)*256);
    fgets(lines[0],256,stdin);
    fgets(lines[1],256,stdin);
    lines[0][255]='\0';
    lines[1][255]='\0';
    return lines;

}
void freeStrings(char***lines){
    free((*lines)[0]);
    free((*lines)[1]);
    free(*lines);
}
int main(){
    char** S1_andS2 = getStrings();
   printStuff(S1_andS2[0],S1_andS2[1]);
    freeStrings(&S1_andS2);
    return 0;
}
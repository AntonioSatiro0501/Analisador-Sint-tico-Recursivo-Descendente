/*
 * Integrantes:
 * NOME: Aline Barbosa Vidal RA: 10721348
 * NOME: Antonio Costa Satiro de Souza RA: 10723636
 * NOME: Yating Zheng RA: 10439511
 *
 */

#include <stdio.h>
#include <stdlib.h>

char lookahead;     // Variável Global

/* PROTOTIPOS */
int E(char palavra[], int *pos);
int A(char palavra[], int *pos);
int T(char palavra[], int *pos);
int B(char palavra[], int *pos);
int F(char palavra[], int *pos);
int N(char palavra[], int *pos);
int X(char palavra[], int *pos);

/* MATCH */
int match(char t, char palavra[], int *pos){
    if(lookahead == t){
        lookahead = palavra[++(*pos)];
        return 1;
    }
    return 0;
}

/*
    E -> T A
*/
int E(char palavra[], int *pos){
    if(T(palavra,pos) && A(palavra,pos)){
        return 1;
    }
    return 0;
}

/*
    A -> + E A
    A -> - E A
    A -> e
*/
int A(char palavra[], int *pos){

    if(lookahead == '+'){
        if(match('+',palavra,pos) &&
           E(palavra,pos) &&
           A(palavra,pos)){
            return 1;
        }
        return 0;
    }
    else if(lookahead == '-'){
        if(match('-',palavra,pos) &&
           E(palavra,pos) &&
           A(palavra,pos)){
            return 1;
        }
        return 0;
    }
    else if(lookahead == ')' || lookahead == '\0'){
        return 1;
    }

    return 0;
}

/*
    T -> F B
*/
int T(char palavra[], int *pos){
    if(F(palavra,pos) && B(palavra,pos)){
        return 1;
    }
    return 0;
}

/*
    B -> * T B
    B -> / T B
    B -> e
*/
int B(char palavra[], int *pos){

    if(lookahead == '*'){
        if(match('*',palavra,pos) &&
           T(palavra,pos) &&
           B(palavra,pos)){
            return 1;
        }
        return 0;
    }
    else if(lookahead == '/'){
        if(match('/',palavra,pos) &&
           T(palavra,pos) &&
           B(palavra,pos)){
            return 1;
        }
        return 0;
    }
    else if(lookahead == '+' ||
            lookahead == '-' ||
            lookahead == ')' ||
            lookahead == '\0'){
        return 1;
    }

    return 0;
}

/*
    F -> (X)
    F -> -N
    F -> N
*/
int F(char palavra[], int *pos){

    if(lookahead == '('){
        if(match('(',palavra,pos) &&
           X(palavra,pos) &&
           match(')',palavra,pos)){
            return 1;
        }
        return 0;
    }
    else if(lookahead == '-'){
        if(match('-',palavra,pos) &&
           N(palavra,pos)){
            return 1;
        }
        return 0;
    }
    else{
        return N(palavra,pos);
    }
}

/*
    N -> 0X | 1X | 2X | 3X | 4X
    N -> 5X | 6X | 7X | 8X | 9X
*/
int N(char palavra[], int *pos){

    if(lookahead >= '0' && lookahead <= '9'){
        if(match(lookahead,palavra,pos) &&
           X(palavra,pos)){
            return 1;
        }
        return 0;
    }

    return 0;
}

/*
    X -> N
    X -> e
*/
int X(char palavra[], int *pos){

    if(lookahead >= '0' && lookahead <= '9'){
        return N(palavra,pos);
    }
    else if(lookahead == '+' ||
            lookahead == '-' ||
            lookahead == '*' ||
            lookahead == '/' ||
            lookahead == ')' ||
            lookahead == '\0'){
        return 1;
    }

    return 0;
}

/* TRATAMENTO DE ERRO */
void trataErro(){
    printf("\n\nERRO DE SINTAXE!\n\n");
}

/* MAIN */
int main(){

    char palavra[] = "10+20*3";
    int pos = 0;

    lookahead = palavra[pos];

    printf("\nExpressao analisada: %s\n", palavra);

    if(E(palavra, &pos) && lookahead == '\0'){
        printf("\nExpressao reconhecida!\n\n");
    }
    else{
        trataErro();
    }

    system("PAUSE");
    return 0;
}


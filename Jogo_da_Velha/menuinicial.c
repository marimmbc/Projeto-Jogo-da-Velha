#include <stdio.h>
#include <stdlib.h>

int main()
{
    //estrutura de dados - matriz 
    int linha, coluna;
    char jogo[3][3];

    //como inicializar nossa estrutura de dados?
    for(linha = 0; linha < 3; linha++){
        for(coluna = 0; coluna < 3; coluna++){
            jogo[linha][coluna] = ' ';
        }
    }

    //imprimir jogo
    for(linha = 0; linha < 3; linha ++){
        for(coluna = 0; coluna < 3; coluna ++){
            printf("%c", jogo[linha][coluna]);
        }
        printf("\n");
    }
    //salvar coordenadas

    //alguem ganhou por linha

    //alguem ganhou por coluna

    //alguem ganhou na diagonal principal

    //alguem ganhou na diagonal secundaria

    return 0;
}

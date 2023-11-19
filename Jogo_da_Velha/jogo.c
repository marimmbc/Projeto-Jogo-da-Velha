#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// variáveis globais
char jogo[3][3]; // matriz do jogo
int l, c;        // índices para linha e coluna

void imprimirCabecalho()
{
    cli_clear();
    printf("Jogo da Velha\n\n");
}

// procedimento para inicializar todas as posições da matriz com um espaço
void inicializarMatriz()
{
    for (l = 0; l < 3; l++)
    {
        for (c = 0; c < 3; c++)
            jogo[l][c] = ' ';
    }
}

// Função para imprimir o tabuleiro do jogo
void imprimirTabuleiro()
{
    printf("\n\t 0   1   2\n\n");
    for (l = 0; l < 3; l++)
    {
        for (c = 0; c < 3; c++)
        {
            if (c == 0)
                printf("\t");
            printf(" %c ", jogo[l][c]);
            if (c < 2)
                printf("|");
            if (c == 2)
                printf("   %d", l);
        }
        printf("\n");
        if (l < 2)
            printf("\t-----------\n");
    }
}

// função para verificar vitória do jogador c na linha l
int ganhouPorLinha(int l, char c)
{
    return (jogo[l][0] == c && jogo[l][1] == c && jogo[l][2] == c);
}

// função para verificar vitória do jogador c nas linhas
int ganhouPorLinhas(char c)
{
    int ganhou = 0;
    for (l = 0; l < 3; l++)
    {
        ganhou += ganhouPorLinha(l, c);
    }
    return ganhou;
}

// função para verificar vitória do jogador j na coluna c
int ganhouPorColuna(int c, char j)
{
    return (jogo[0][c] == j && jogo[1][c] == j && jogo[2][c] == j);
}

// função que verifica vitória do jogador j por colunas
int ganhouPorColunas(char j)
{
    int ganhou = 0;
    for (c = 0; c < 3; c++)
    {
        ganhou += ganhouPorColuna(c, j);
    }
    return ganhou;
}

// função para verificar vitória do jogador c na diagonal principal
int ganhouPorDiagPrin(char c)
{
    return (jogo[0][0] == c && jogo[1][1] == c && jogo[2][2] == c);
}

// função para verificar vitória do jogador c na diagonal secundária
int ganhouPorDiagSec(char c)
{
    return (jogo[0][2] == c && jogo[1][1] == c && jogo[2][0] == c);
}

// função que diz se uma coordenada é válida ou não
int ehValida(int l, int c)
{
    return (l >= 0 && l < 3 && c >= 0 && c < 3 && jogo[l][c] == ' ');
}

// procedimento para ler as coordenadas digitadas pelo jogador
void lerCoordenadas(char j)
{
    int linha, coluna;

    printf("Digite linha e coluna: ");
    scanf("%d %d", &linha, &coluna);

    while (!ehValida(linha, coluna))
    {
        printf("Coordenadas inválidas! Digite outra linha e coluna: ");
        scanf("%d %d", &linha, &coluna);
    }
    jogo[linha][coluna] = j;
}

// função que retorna a quantidade de posições ainda vazias (não jogadas)
int quantVazias()
{
    int quantidade = 0;

    for (l = 0; l < 3; l++)
    {
        for (c = 0; c < 3; c++)
            if (jogo[l][c] == ' ')
                quantidade++;
    }
    return quantidade;
}

// procedimento jogar com o loop (repetição) principal do jogo
void jogar()
{
    int jogador = 1, vitoriaX = 0, vitoria0 = 0;
    char jogador1 = 'X', jogador2 = '0';

    do
    {
        imprimir();
        if (jogador == 1)
        {
            lerCoordenadas(jogador1);
            jogador++;
            vitoriaX += ganhouPorLinhas(jogador1);
            vitoriaX += ganhouPorColunas(jogador1);
            vitoriaX += ganhouPorDiagPrin(jogador1);
            vitoriaX += ganhouPorDiagSec(jogador1);
        }
        else
        {
            lerCoordenadas(jogador2);
            jogador = 1;
            vitoria0 += ganhouPorLinhas(jogador2);
            vitoria0 += ganhouPorColunas(jogador2);
            vitoria0 += ganhouPorDiagPrin(jogador2);
            vitoria0 += ganhouPorDiagSec(jogador2);
        }
    } while (vitoriaX == 0 && vitoria0 == 0 && quantVazias() > 0);

    imprimir();

        if (vitoria0 == 1){
            cli_info("Parabéns Jogador 2. Você venceu!!!\n");
        }
        else if (vitoriaX == 1){
            cli_info("Parabéns Jogador 1. Você venceu!!!\n");
        }
        else{
            cli_info("Que pena. O jogo terminou em empate!\n");
        }
    
}

int main()
{
    int opcao;

    cli_init();
    do
    {
        inicializarMatriz();
        jogar();

        printf("\nDigite 1 para jogar novamente: ");
        scanf("%d", &opcao);
    } while (opcao == 1);

    cli_destroy();
    return 0;
}

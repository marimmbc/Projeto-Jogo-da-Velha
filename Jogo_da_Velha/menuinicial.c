#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void limpaTela()
{
    system("clear || printf '\033c'");
}

void iniciaTabuleiro(char tabuleiro[3][3])
{
    int linha, coluna;
    for (linha = 0; linha < 3; linha++)
    {
        for (coluna = 0; coluna < 3; coluna++)
        {
            tabuleiro[linha][coluna] = '-';
        }
    }
}

void exibeTabuleiro(char tabuleiro[3][3])
{
    int linha, coluna;
    printf("\n");
    for (linha = 0; linha < 3; linha++)
    {
        for (coluna = 0; coluna < 3; coluna++)
        {
            printf("%c", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }
}

int confereTabuleiro(char tabuleiro[3][3])
{
    int linha, coluna;

    for (linha = 0; linha < 3; linha++)
    {
        if (tabuleiro[linha][0] == 'X' && tabuleiro[linha][0] == tabuleiro[linha][1] && tabuleiro[linha][1] == tabuleiro[linha][2])
        {
            return 1;
        }
        else if (tabuleiro[linha][0] == 'O' && tabuleiro[linha][0] == tabuleiro[linha][1] && tabuleiro[linha][1] == tabuleiro[linha][2])
        {
            return 2;
        }
    }

    for (coluna = 0; coluna < 3; coluna++)
    {
        if (tabuleiro[0][coluna] == 'X' && tabuleiro[0][coluna] == tabuleiro[1][coluna] && tabuleiro[1][coluna] == tabuleiro[2][coluna])
        {
            return 1;
        }
        else if (tabuleiro[0][coluna] == 'O' && tabuleiro[0][coluna] == tabuleiro[1][coluna] && tabuleiro[1][coluna] == tabuleiro[2][coluna])
        {
            return 2;
        }
    }

    if (tabuleiro[0][0] != '-' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2])
    {
        return (tabuleiro[0][0] == 'X') ? 1 : 2;
    }

    if (tabuleiro[0][2] != '-' && tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0])
    {
        return (tabuleiro[0][2] == 'X') ? 1 : 2;
    }

    return 0;
}

void exibeInstrucoes()
{
    printf("\nMapa de Posicoes:");
    printf("\n 7 | 8 | 9");
    printf("\n 4 | 5 | 6");
    printf("\n 1 | 2 | 3");
}

void jogo(char nomeDoJogadorUm[50], char nomeDoJogadorDois[50], int pontuacaoJogadorUm, int pontuacaoJogadorDois);

void menuInicial()
{
    int opcao = 0;
    char nomeDoJogadorUm[50], nomeDoJogadorDois[50];

    while (opcao < 1 || opcao > 3)
    {
        limpaTela();
        printf("Bem-vindo ao Jogo da Velha\n");
        printf("1 - Jogar\n");
        printf("2 - Sobre\n");
        printf("3 - Sair\n");
        printf("Escolha uma opcao e tecle ENTER:");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o nome do jogador 1:");
            scanf("%s", nomeDoJogadorUm);
            printf("Digite o nome do jogador 2:");
            scanf("%s", nomeDoJogadorDois);
            jogo(nomeDoJogadorUm, nomeDoJogadorDois, 0, 0);
            break;
        case 2:
            printf("Informacoes do jogo\n");
            break;
        case 3:
            printf("Ate mais!\n");
            break;
        }
    }
}

void jogo(char nomeDoJogadorUm[50], char nomeDoJogadorDois[50], int pontuacaoJogadorUm, int pontuacaoJogadorDois)
{
    char nomeDoJogadorAtual[50];
    char tabuleiro[3][3];
    int linha, coluna, linhaJogada, colunaJogada, posicaoJogada;
    int estadoDeJogo = 1;
    int turnoDoJogador = 1;
    int rodada = 0;
    int opcao;
    int posicionouJogada;

    iniciaTabuleiro(tabuleiro);

    while (rodada < 9 && estadoDeJogo == 1)
    {
        limpaTela();

        printf("\nRodada:%d\n", rodada);
        printf("Pontuacao:%s %d x %d %s\n", nomeDoJogadorUm, pontuacaoJogadorUm, pontuacaoJogadorDois, nomeDoJogadorDois);

        exibeTabuleiro(tabuleiro);

        exibeInstrucoes();

        if (turnoDoJogador == 1)
        {
            strcpy(nomeDoJogadorAtual, nomeDoJogadorUm);
        }
        else
        {
            strcpy(nomeDoJogadorAtual, nomeDoJogadorDois);
        }

        posicionouJogada = 0;

        int posicoes[9][2] = {{2, 0}, {2, 1}, {2, 2}, {1, 0}, {1, 1}, {1, 2}, {0, 0}, {0, 1}, {0, 2}};

        do
        {
            printf("\n%s Digite uma posicao conforme o mapa acima:", nomeDoJogadorAtual);
            scanf("%d", &posicaoJogada);

            if (posicaoJogada < 1 || posicaoJogada > 9)
            {
                printf("Posicao invalida. Escolha uma posicao entre 1 e 9.\n");
            }
            else
            {
                linhaJogada = posicoes[posicaoJogada - 1][0];
                colunaJogada = posicoes[posicaoJogada - 1][1];

                if (tabuleiro[linhaJogada][colunaJogada] == '-')
                {
                    posicionouJogada = 1;

                    if (turnoDoJogador == 1)
                    {
                        tabuleiro[linhaJogada][colunaJogada] = 'X';
                        turnoDoJogador = 2;
                    }
                    else
                    {
                        tabuleiro[linhaJogada][colunaJogada] = 'O';
                        turnoDoJogador = 1;
                    }
                }
                else
                {
                    printf("Posicao ocupada. Escolha outra posicao.\n");
                }
            }
        } while (!posicionouJogada);

        int resultado = confereTabuleiro(tabuleiro);

        if (resultado == 1)
        {
            printf("O jogador X venceu\n");
            pontuacaoJogadorUm++;
            estadoDeJogo = 0;
        }
        else if (resultado == 2)
        {
            printf("O jogador O venceu\n");
            pontuacaoJogadorDois++;
            estadoDeJogo = 0;
        }

        rodada++;
    }

    exibeTabuleiro(tabuleiro);
    printf("Fim de jogo\n");
    printf("O que deseja fazer?\n");
    printf("1-Continuar Jogando\n");
    printf("2-Menu Inicial\n");
    printf("3-Sair\n");
    scanf("%d", &opcao);

    if (opcao == 1)
    {
        jogo(nomeDoJogadorUm, nomeDoJogadorDois, pontuacaoJogadorUm, pontuacaoJogadorDois);
    }
    else if (opcao == 2)
    {
        menuInicial();
    }
}

int main()
{
    srand(time(NULL));

    menuInicial();
    return 0;
}

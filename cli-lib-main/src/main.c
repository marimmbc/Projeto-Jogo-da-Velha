#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define MAXX 80
#define MINX 0
#define MAXY 24
#define MINY 0

// Variáveis globais
char board[3][3];                   // Representação do tabuleiro do jogo da velha
char player1[50], player2[50];      // Nomes dos jogadores
int currentPlayer;                  // Número do jogador atual (1 ou 2)
int pontuacao1 = 0, pontuacao2 = 0; // Pontuações dos jogadores

// Inicializa o tabuleiro com espaços em branco
void initializeBoard()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            board[i][j] = ' ';
        }
    }
}

// Imprime o tabuleiro na tela
void printBoard()
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(0, 0);
    printf("Jogo da Velha\n\n");

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            printf(" %c ", board[i][j]);
            if (j < 2)
            {
                printf("|");
            }
        }
        printf("\n");
        if (i < 2)
        {
            printf("-----------\n");
        }
    }
}

// Verifica se há um vencedor no jogo
int checkWinner()
{
    // Verificar linhas e colunas
    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
        {
            return board[i][0]; // Linha
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
        {
            return board[0][i]; // Coluna
        }
    }

    // Verificar diagonais
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
    {
        return board[0][0]; // Diagonal principal
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
    {
        return board[0][2]; // Diagonal secundária
    }

    return 0; // Nenhum vencedor
}

// Verifica se o tabuleiro está completamente preenchido
int isBoardFull()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == ' ')
            {
                return 0; // Ainda há espaço vazio no tabuleiro
            }
        }
    }
    return 1; // Tabuleiro está cheio
}

// Alterna entre os jogadores
void switchPlayer()
{
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

// Realiza a jogada do jogador na posição escolhida
void makeMove(int choice)
{
    char symbol = (currentPlayer == 1) ? 'O' : 'X';
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (board[row][col] == ' ')
    {
        board[row][col] = symbol;
        switchPlayer();
    }
    else
    {
        printf("Posição já ocupada. Escolha outra.\n");
    }
}

// Gera uma jogada aleatória para o jogador automático (single player)
int getRandomMove()
{
    int move;
    do
    {
        move = rand() % 9 + 1;
    } while (board[(move - 1) / 3][(move - 1) % 3] != ' ');

    return move;
}

// Imprime mensagem de boas-vindas
void printHello()
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(0, 0);
    printf("Bem-vindo ao Jogo da Velha no Terminal!\n\n");
}

// Imprime a tecla pressionada no rodapé da tela
void printKey(int ch)
{
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(35, 22);
    printf("%s %d - %s %d ", player1, pontuacao1, player2, pontuacao2);

    screenGotoxy(34, 23);
    printf("            ");

    if (ch == 27)
    {
        screenGotoxy(36, 23);
    }
    else
    {
        screenGotoxy(39, 23);
    }

    printf("%d ", ch);
    while (keyhit())
    {
        printf("%d ", readch());
    }
}

// Função principal
int main()
{
    static int ch = 0;

    // Inicializa o ambiente gráfico, o teclado e o temporizador
    screenInit(1);
    keyboardInit();
    timerInit(50);

    printHello();
    screenUpdate();

    // Pede o número de jogadores
    int numPlayers;
    printf("Digite o número de jogadores (1 ou 2): ");
    scanf("%d", &numPlayers);

    // Obtém os nomes dos jogadores
    if (numPlayers == 1)
    {
        printf("Digite o nome do jogador 1: ");
        scanf("%s", player1);
        strcpy(player2, "Jogador 2");
    }
    else if (numPlayers == 2)
    {
        printf("Digite o nome do jogador 1: ");
        scanf("%s", player1);
        printf("Digite o nome do jogador 2: ");
        scanf("%s", player2);
    }
    else
    {
        printf("Número inválido de jogadores. Encerrando o jogo.\n");
        return 1;
    }

    initializeBoard();
    currentPlayer = 1;

    // Loop principal do jogo
    while (ch != 10)
    { // Enter
        printBoard();

        // Se for single player e a vez do jogador 2, realiza uma jogada aleatória
        if (numPlayers == 1 && currentPlayer == 2)
        {
            int move = getRandomMove();
            printf("%s escolheu %d\n", player2, move);
            makeMove(move);
        }
        else
        {
            // Solicita a jogada do jogador atual
            printf("%s, escolha um número de 1 a 9: ", (currentPlayer == 1) ? player1 : player2);
            scanf("%d", &ch);

            // Verifica se a jogada é válida
            if (ch < 1 || ch > 9)
            {
                printf("Número inválido. Escolha um número de 1 a 9.\n");
                continue;
            }

            // Realiza a jogada do jogador
            makeMove(ch);
        }

        // Atualiza a tela
        screenUpdate();

        // Verifica se há um vencedor ou se o jogo empatou
        int winner = checkWinner();
        if (winner)
        {
            printf("Parabéns, %s! Você venceu!\n", (winner == 'O') ? player1 : player2);
            if (winner == 'O')
            {
                pontuacao1++;
            }
            else
            {
                pontuacao2++;
            }
            printf("Pontuação atual: %s %d - %s %d\n", player1, pontuacao1, player2, pontuacao2);
            initializeBoard();
        }
        else if (isBoardFull())
        {
            printf("O jogo empatou!\n");
            initializeBoard();
        }
    }

    // Encerra o ambiente gráfico, o teclado e o temporizador
    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}

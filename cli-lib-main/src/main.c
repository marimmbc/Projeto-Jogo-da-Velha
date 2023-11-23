#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define MAXX 80
#define MAXY 24

// Constantes para definir a largura e altura do tabuleiro
#define BOARD_WIDTH 13
#define BOARD_HEIGHT 7

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

// Libera a memória alocada para o tabuleiro (função desnecessária neste caso)
void freeBoard()
{
    // Não há alocação dinâmica no tabuleiro original, então não é necessário liberar memória aqui
}

// Imprime o tabuleiro na tela
void printBoard()
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy((MAXX - strlen("Jogo da Velha")) / 2, 0);
    printf("Jogo da Velha\n\n");

    // Ajuste nas posições de impressão para centralizar
    int rowOffset = 3;
    int colOffset = (MAXX - BOARD_WIDTH) / 2;

    // Desenha o conteúdo do tabuleiro na tela
    for (int i = 0; i < 3; ++i)
    {
        screenGotoxy(colOffset, i * 4 + rowOffset);
        for (int j = 0; j < 3; ++j)
        {
            char symbol = board[i][j];
            if (symbol == 'O')
            {
                screenSetColor(MAGENTA, DARKGRAY);
            }
            else if (symbol == 'X')
            {
                screenSetColor(MAGENTA, DARKGRAY);
            }
            else
            {
                screenSetColor(CYAN, DARKGRAY);
            }

            printf(" %c ", symbol);
            if (j < 2)
            {
                printf("|");
            }
        }
        printf("\n");
        if (i < 2)
        {
            screenGotoxy(colOffset, i * 4 + 1 + rowOffset);
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
    screenSetColor(GREEN, GREEN);
    screenGotoxy(0, 0);
    printf("Bem-vindo ao Jogo da Velha!\n\n");
}

// Função para verificar se o usuário deseja jogar novamente
int askToPlayAgain()
{
    printf("Deseja jogar novamente? Digite S ou N : ");
    while (1)
    {
        char playAgain;
        scanf(" %c", &playAgain);

        if (playAgain == 's' || playAgain == 'S')
        {
            return 1; // Reinicializar o jogo
        }
        else if (playAgain == 'n' || playAgain == 'N')
        {
            printf("Jogo encerrado. Obrigado por jogar!\n");
            return 0; // Sair do programa
        }
        else
        {
            printf("Opção inválida. Digite 'S' para jogar novamente ou 'N' para sair: ");
        }
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

    // Loop principal do jogo
    do
    {
        initializeBoard();
        currentPlayer = 1;

        // Remover a condição ch != 10 do loop principal
        while (1)
        {
            printBoard();

            if (numPlayers == 1 && currentPlayer == 2)
            {
                int move = getRandomMove();
                printf("%s escolheu %d\n", player2, move);
                makeMove(move);
            }
            else
            {
                int validMove = 0;

                while (!validMove)
                {
                    printf("%s, escolha um número de 1 a 9: ", (currentPlayer == 1) ? player1 : player2);
                    if (scanf("%d", &ch) == 1)
                    {
                        if (ch >= 1 && ch <= 9 && board[(ch - 1) / 3][(ch - 1) % 3] == ' ')
                        {
                            validMove = 1;
                        }
                        else
                        {
                            printf("Posição inválida. Escolha outra.\n");
                        }
                    }
                    else
                    {
                        printf("Entrada inválida. Digite apenas um número.\n");
                        while (getchar() != '\n')
                            ;
                    }
                }

                makeMove(ch);
            }

            screenUpdate();

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
                break; // Sair do loop se houver um vencedor
            }
            else if (isBoardFull())
            {
                printf("O jogo empatou!\n");
                initializeBoard();
                break; // Sair do loop se o jogo empatar
            }

            // Pergunta ao jogador se deseja jogar novamente
            if (!askToPlayAgain())
            {
                break; // Sair do loop principal se o jogador não quiser jogar novamente
            }
        }

    } while (1); // Loop principal agora é infinito, pois a condição de saída está dentro do loop interno

    // Libera a memória alocada para o tabuleiro
    freeBoard();

    // Encerra o ambiente gráfico, o teclado e o temporizador
    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
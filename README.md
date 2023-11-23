Estamos desenvolvendo um programa em linguagem C para implementar o Jogo da Velha

Instruções de usa

# Jogo da Velha em C

Este é um projeto simples de Jogo da Velha implementado em C. O código permite que dois jogadores humanos ou um jogador humano e um jogador automático (computador) joguem entre si. Abaixo estão as instruções detalhadas sobre como compilar, executar e jogar o Jogo da Velha.

## Instruções de Uso

### Compilação:

Certifique-se de ter um compilador C instalado no seu sistema.

1. Abra um terminal.
2. Navegue até o diretório do projeto.
3. Compile o código usando o seguinte comando:

    ```bash
    gcc -o jogo_da_velha main.c screen.c keyboard.c timer.c -lm
    ```

### Execução:

1. Após a compilação, execute o jogo usando o seguinte comando:

    ```bash
    ./jogo_da_velha
    ```

### Regras do Jogo:

1. **Número de Jogadores:**
    - O jogo suporta 1 ou 2 jogadores. Você será solicitado a inserir o número de jogadores no início.

2. **Nomes dos Jogadores:**
    - Se estiver jogando com dois jogadores, você será solicitado a inserir os nomes dos jogadores.

3. **Jogando o Jogo:**
    - O tabuleiro é numerado de 1 a 9, de cima para baixo e da esquerda para a direita.
    - Digite o número correspondente à posição desejada quando for sua vez de jogar.

4. **Fim do Jogo:**
    - O jogo termina quando um jogador vence preenchendo 3 espaços consecutivos na horizontal, vertical ou diagonal, ou quando o tabuleiro está completamente preenchido (empate).

5. **Pontuação:**
    - Após cada jogo, a pontuação é exibida na tela, indicando o número de vitórias de cada jogador.

6. **Jogar Novamente:**
    - Ao final de cada jogo, você será perguntado se deseja jogar novamente. Digite 'S' para jogar novamente ou 'N' para encerrar o jogo.

### Observações:

- Certifique-se de seguir as instruções exibidas na tela durante o jogo.
- As cores utilizadas na exibição do tabuleiro podem variar dependendo do ambiente de execução.

Aproveite jogando o Jogo da Velha em C! Se tiver sugestões ou encontrar problemas, sinta-se à vontade para contribuir ou reportar issues. Divirta-se!


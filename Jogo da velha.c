#include <stdio.h>

void printEspacos(int n, int line[n]) {
    char xo[3] = {' ', 'X', 'O'};
    printf("|");
    for(int i = 0; i < n; i++) {
        printf("%c", xo[line[i]]);
        printf("|");
    }
    printf("\n");
}

void printTabuleiro(int n, int matrix[n][n]) {
    printf("\n");
    printEspacos(n, matrix[0]);
    for(int j = 1; j < n; j++) {
        printEspacos(n, matrix[j]);
    }
}

int existeGanhador(int n, int matrix[n][n]) { // 0 - continua jogo | 1 - x ganhou | 2 - o ganhou | 3 - empate
    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] != 0) {
                ++count;
            }
        }    
    }

    if (count == n*n) return 3;
    
    for (int jogador = 1; jogador < 3; jogador++) {
        for (int i = 0; i < n; i++) {
            int countPos = 0;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == jogador) ++countPos;
            }
            if (countPos == n) return jogador;
        }
        for (int i = 0; i < n; i++) {
            int countPos = 0;
            for (int j = 0; j < n; j++) {
                if (matrix[j][i] == jogador) ++countPos;
            }
            if (countPos == n) return jogador;
        }
        int countPos = 0;
        for (int i = 0; i < n; i++) {
            if (matrix[i][i] == jogador) ++countPos;
        }
        if (countPos == n) return jogador;
        countPos = 0;
        for (int i = 0; i < n; i++) {
            if (matrix[n-i-1][i] == jogador) ++countPos;
        }
        if (countPos == n) return jogador;
    }
    
    return 0;
}

int main(){
    
    printf("################################\n");
    printf("######  JOGO DA VELHA  #########\n");
    printf("################################\n\n");

    int n = 0;
    
    while(n < 3 || n > 5) {
        printf("Insira o tamanho do tabuleiro (3, 4 ou 5): ");
        scanf("%d", &n);
        if (n < 3 || n > 5) printf("Insira um tamanho valido.\n\n");
    }
    
    int matrix[n][n];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
    
    printTabuleiro(n, matrix);
    
    int jogador = 1;
    
    while(1) {
        int l = n+1;
        int c = n+1;
        
        if (jogador == 1) {
            printf("\nVEZ do X");
        } else {
            printf("\nVEZ do O");
        }
        
        while(l > n || l < 1) {
            printf("\nLinha para marcar (de 1 a %d): ", n);
            scanf("%d", &l);
            if (l > n || l < 1) printf("Escolha uma linha valida.\n");
        }
        while(c > n || c < 1) {
            printf("Coluna para marcar (de 1 a %d): ", n);
            scanf("%d", &c);
            if (c > n || c < 1) printf("Escolha uma coluna valida.\n");
        }
        
        if (matrix[l-1][c-1] != 0) {
            printf("\nEsta posição ja esta marcada. Escolha outra por favor.\n");
            printTabuleiro(n, matrix);
        } else {
            matrix[l-1][c-1] = jogador;
            printTabuleiro(n, matrix);
            if (jogador == 1) {
                jogador = 2;
            } else {
                jogador = 1;
            }
            
            if (existeGanhador(n, matrix) != 0) {
                switch (existeGanhador(n, matrix)) {
                    case 3:
                        printf("\nHouve um empate!");
                    break;
                    case 2:
                        printf("\nO 'O' GANHOU!!!");
                    break;
                    case 1:
                        printf("\nO 'X' GANHOU!!!");
                    break;
                }
                return 0;
            }
        }
    }
    
}
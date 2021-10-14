#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

int n; 
int** g;
int* color;

bool dfs(int OLDv, int v) {                   //функция для проверки на цикличность графа
    color[v] = 1;
    for (size_t i = 0; i < n; i++) {
        if ((g[v][i] > 0) && (i != OLDv)) {
            if ((color[i] == 0) && (dfs(v, i))) return true;
            else if (color[i] == 1) {
            return true;
            }
        }
    }
color[v] = 2;
return false;
}

int main(void) {
    scanf("%d", &n);

    color = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    color[i] = 0;                       
    
    g = (int**)malloc(n * sizeof(int*));    // Выделение памяти под указатели на строки
    for (int i = 0; i < n; i++) {           // ввод элементов массива (цикл по строкам)

    g[i] = (int*)malloc(n * sizeof(int));   // Выделение памяти под хранение строк
    for (int j = 0; j < n; j++) {           // ввод элементов массива (цикл по столбцам)
        printf("a[%d][%d] = ", i, j);
        scanf("%d", &g[i][j]);
    }
    }

    bool b = 0;
    for (int i = 0; i < n; i++)
        if (dfs(-1, i)) {
            b = 1;
            break;
        }
    if (b) printf("Cyclic\n");
    else printf("ACyclic\n");

    FILE* file = fopen("f.txt", "w"); //открытие файла
    fprintf(file, "graph table {\n");

    for (int i = 0; i < n; i++) {
        b = 1;
        for (int j = 0; j <= i; j++)
        if (g[i][j] > 0) {
            b = 0;
            for (int k = 0; k < g[i][j]; k++)
            fprintf(file, "%c -- %c;\n", (char)(65 + i), (char)(65 + j));
        }
        if (b) fprintf(file, "%c\n", (char)(65 + i));
    }

    fprintf(file, "}");
    fclose(file);

    system ("dot -Tpng f.txt -o f.png");
    system ("wslview f.png");

    free(g);
    return 0;
}

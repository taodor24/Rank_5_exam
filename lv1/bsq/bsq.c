#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t r, c;
    char empty, obst, full;
    char **grid;
} t_map;

// free memory
void free_map(t_map *m) {
    if (m->grid) {
        for (size_t i = 0; i < m->r; i++)
            free(m->grid[i]);
        free(m->grid);
    }
}

// header check 
int parse_header(FILE *f, t_map *m) {
    if (fscanf(f, "%zu%c%c%c\n", &m->r, &m->empty, &m->obst, &m->full) != 4) return 0;
    if (m->r == 0 || m->empty == m->obst || m->empty == m->full || m->obst == m->full) return 0;
    return 1;
}

// readin' a grid and checkin' the validity 
int read_grid(FILE *f, t_map *m) {
    m->grid = calloc(m->r, sizeof(char *));
    char *line = NULL;
    size_t cap = 0;
    for (size_t i = 0; i < m->r; i++) {
        ssize_t len = getline(&line, &cap, f);
        if (len <= 0) { free(line); return 0; }
        if (line[len - 1] == '\n') line[--len] = '\0';
        if (i == 0) m->c = len;
        if ((size_t)len != m->c || len == 0) { free(line); return 0; }
        m->grid[i] = malloc(m->c + 1);
        for (size_t j = 0; j < m->c; j++) {
            if (line[j] != m->empty && line[j] != m->obst) { free(line); return 0; }
            m->grid[i][j] = line[j];
        }
        m->grid[i][m->c] = '\0';
    }
    free(line);
    return 1;
}

// biggest square search algorithm (Dynamic Programming) 
void solve(t_map *m) {
    size_t max_s = 0, b_r = 0, b_c = 0;
    int **dp = malloc(m->r * sizeof(int *));
    for (size_t i = 0; i < m->r; i++) {
        dp[i] = malloc(m->c * sizeof(int));
        for (size_t j = 0; j < m->c; j++) {
            if (m->grid[i][j] == m->obst) dp[i][j] = 0;
            else {
                if (i == 0 || j == 0) dp[i][j] = 1;
                else {
                    int min = dp[i-1][j] < dp[i][j-1] ? dp[i-1][j] : dp[i][j-1];
                    dp[i][j] = (min < dp[i-1][j-1] ? min : dp[i-1][j-1]) + 1;
                }
                if ((size_t)dp[i][j] > max_s) {
                    max_s = dp[i][j]; b_r = i; b_c = j;
                }
            }
        }
    }
    for (size_t i = 0; i < max_s; i++)
        for (size_t j = 0; j < max_s; j++)
            m->grid[b_r - i][b_c - j] = m->full;
    for (size_t i = 0; i < m->r; i++) {
        fputs(m->grid[i], stdout);
        fputc('\n', stdout);
        free(dp[i]);
    }
    free(dp);
}

void process(FILE *f) {
    t_map m = {0};
    if (!parse_header(f, &m) || !read_grid(f, &m))
        fprintf(stderr, "map error\n"); // error   in a stderr like in a subj. 
    else
        solve(&m);
    free_map(&m);
}

// main 
int main(int argc, char **argv) {
    if (argc == 1) {
        process(stdin);
    } else {
        for (int i = 1; i < argc; i++) {
            FILE *f = fopen(argv[i], "r");
            if (!f) fprintf(stderr, "map error\n");
            else {
                process(f);
                fclose(f);
            }
            if (i < argc - 1) fputc('\n', stdout); // between maps 
        }
    }
    return 0;
}
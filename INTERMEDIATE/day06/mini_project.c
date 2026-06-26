/*
 * Int Day 06 Mini-Project — Maze Solver (DFS backtracking)
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>
#include <string.h>

#define ROWS 8
#define COLS 8

char maze[ROWS][COLS+1] = {
    "S.######",
    "...#....",
    "#.##.##.",
    "#....##.",
    "##.###..",
    "...#....",
    ".###.###",
    "....#..E"
};

int visited[ROWS][COLS];
int path_r[64], path_c[64], path_len=0;

int solve(int r, int c) {
    if (r<0||r>=ROWS||c<0||c>=COLS) return 0;
    if (maze[r][c]=='#'||visited[r][c]) return 0;
    visited[r][c]=1;
    path_r[path_len]=r; path_c[path_len++]=c;
    if (maze[r][c]=='E') return 1;
    if (solve(r+1,c)||solve(r,c+1)||solve(r-1,c)||solve(r,c-1)) return 1;
    path_len--;
    return 0;
}

int main(void) {
    printf("=== Maze Solver (DFS Backtracking) ===\nMaze:\n");
    for(int r=0;r<ROWS;r++) printf("  %s\n",maze[r]);

    memset(visited,0,sizeof(visited));
    if (solve(0,0)) {
        /* Mark path */
        for(int i=1;i<path_len-1;i++) maze[path_r[i]][path_c[i]]='*';
        printf("\nSolved (path length %d):\n", path_len);
        for(int r=0;r<ROWS;r++) printf("  %s\n",maze[r]);
    } else {
        printf("No path found.\n");
    }
    return 0;
}

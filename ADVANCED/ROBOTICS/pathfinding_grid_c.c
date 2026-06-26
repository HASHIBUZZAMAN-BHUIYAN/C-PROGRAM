/*
 * A* Pathfinding on a Grid
 * Compile: gcc pathfinding_grid_c.c -o pathfinding_grid_c.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ROWS 15
#define COLS 25
#define INF  999999

typedef struct { int r, c; } Pos;

char grid[ROWS][COLS] = {
    ".........................",
    "....#................#...",
    "....#....#########...#...",
    "....#................#...",
    "....######...........#...",
    ".............#######.#...",
    ".............#.......#...",
    ".............#.###...#...",
    ".............#...#.....E.",
    "...S.........#...#.......",
    ".............#...#.......",
    "...........###...#.......",
    ".....................#...",
    "....#####............#...",
    "........................."
};

int came_from_r[ROWS][COLS], came_from_c[ROWS][COLS];
int g_cost[ROWS][COLS], f_cost[ROWS][COLS];
int closed[ROWS][COLS];

int heuristic(int r1, int c1, int r2, int c2) {
    return abs(r1-r2) + abs(c1-c2);  /* Manhattan distance */
}

/* Simple priority queue (min-heap by f_cost) */
typedef struct { Pos pos; int f; } PQNode;
PQNode pq[ROWS*COLS*4]; int pq_size = 0;

void pq_push(Pos p, int f) {
    pq[pq_size++] = (PQNode){p, f};
    /* bubble up */
    for (int i = pq_size-1; i > 0; ) {
        int parent = (i-1)/2;
        if (pq[parent].f <= pq[i].f) break;
        PQNode tmp = pq[i]; pq[i] = pq[parent]; pq[parent] = tmp;
        i = parent;
    }
}

Pos pq_pop(void) {
    Pos top = pq[0].pos;
    pq[0] = pq[--pq_size];
    for (int i = 0; ;) {
        int left = 2*i+1, right = 2*i+2, smallest = i;
        if (left  < pq_size && pq[left].f  < pq[smallest].f) smallest = left;
        if (right < pq_size && pq[right].f < pq[smallest].f) smallest = right;
        if (smallest == i) break;
        PQNode tmp = pq[i]; pq[i] = pq[smallest]; pq[smallest] = tmp;
        i = smallest;
    }
    return top;
}

int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};

int astar(Pos start, Pos goal) {
    for (int r=0;r<ROWS;r++) for(int c=0;c<COLS;c++){
        g_cost[r][c]=INF; f_cost[r][c]=INF; closed[r][c]=0;
        came_from_r[r][c]=-1; came_from_c[r][c]=-1;
    }
    g_cost[start.r][start.c] = 0;
    f_cost[start.r][start.c] = heuristic(start.r, start.c, goal.r, goal.c);
    pq_size = 0;
    pq_push(start, f_cost[start.r][start.c]);

    while (pq_size > 0) {
        Pos cur = pq_pop();
        if (cur.r==goal.r && cur.c==goal.c) return 1;
        if (closed[cur.r][cur.c]) continue;
        closed[cur.r][cur.c] = 1;

        for (int d=0;d<4;d++) {
            int nr=cur.r+dr[d], nc=cur.c+dc[d];
            if (nr<0||nr>=ROWS||nc<0||nc>=COLS) continue;
            if (grid[nr][nc]=='#') continue;
            if (closed[nr][nc]) continue;
            int ng = g_cost[cur.r][cur.c] + 1;
            if (ng < g_cost[nr][nc]) {
                g_cost[nr][nc] = ng;
                f_cost[nr][nc] = ng + heuristic(nr,nc,goal.r,goal.c);
                came_from_r[nr][nc] = cur.r;
                came_from_c[nr][nc] = cur.c;
                pq_push((Pos){nr,nc}, f_cost[nr][nc]);
            }
        }
    }
    return 0;
}

int main(void) {
    Pos start={0,0}, goal={0,0};
    for(int r=0;r<ROWS;r++) for(int c=0;c<COLS;c++){
        if(grid[r][c]=='S') start=(Pos){r,c};
        if(grid[r][c]=='E') goal=(Pos){r,c};
    }

    printf("=== A* Pathfinding ===\nGrid (%dx%d), S=start, E=goal, #=wall\n\n", ROWS, COLS);
    for(int r=0;r<ROWS;r++) { printf("  "); for(int c=0;c<COLS;c++) printf("%c",grid[r][c]); printf("\n"); }

    if (!astar(start, goal)) { printf("No path found!\n"); return 1; }

    /* Trace path back and mark with '*' */
    int r=goal.r, c=goal.c, path_len=0;
    while (r!=start.r || c!=start.c) {
        grid[r][c]='*'; path_len++;
        int pr=came_from_r[r][c], pc=came_from_c[r][c];
        r=pr; c=pc;
    }
    grid[start.r][start.c]='S';
    grid[goal.r][goal.c]='E';

    printf("\nPath found! Length=%d\n", path_len);
    for(int rr=0;rr<ROWS;rr++) { printf("  "); for(int cc=0;cc<COLS;cc++) printf("%c",grid[rr][cc]); printf("\n"); }
    return 0;
}


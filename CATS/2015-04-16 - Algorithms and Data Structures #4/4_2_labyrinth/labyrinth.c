#include <stdio.h>
#include <stdlib.h>

#define new(x) (x*)malloc(sizeof(x))
#define WALL '#'

typedef struct QueueNode* pQueueNode;
typedef struct QueueNode
{
  pQueueNode next;
  int x;
  int y;
} QueueNode;

typedef struct Queue* pQueue;
typedef struct Queue
{
  pQueueNode First;
  pQueueNode Last;
} Queue;

void QueueAdd(pQueue q, int x, int y)
{
  if (q -> First == NULL)
  {
    q -> First = new(QueueNode);
    q -> Last = q -> First;
  }
  else
  {
    q -> Last -> next = new(QueueNode);
    q -> Last = q -> Last -> next;
  }
  q -> Last -> next = NULL;
  q -> Last -> x = x;
  q -> Last -> y = y;
}

void QueueDel(pQueue q, int* x, int* y)
{
  *x = q -> First -> x;
  *y = q -> First -> y;

  pQueueNode next = q -> First -> next;
  free(q -> First);
  q -> First = next;
}

int main()
{
  FILE* fin = fopen("input.txt", "r");
  FILE* fout = fopen("output.txt", "w");

  int i, x, y, n, x0, y0, x1, y1;
  fscanf(fin, "%d %d %d %d %d", &n, &x0, &y0, &x1, &y1);

  char lab[n+2][n+2];
  int dist[n+2][n+2];
  dist[x0][y0] = 0;
  for (i = 0; i <= n+1; ++i)
  {
    lab[0][i] = WALL;
    lab[i][0] = WALL;
    lab[n+1][i] = WALL;
    lab[i][n+1] = WALL;
  }
  char row[n+1];
  for (y = 1; y <= n; ++y)
  {
    fscanf(fin, "%s", &row);
    for (x = 1; x <= n; ++x)
    {
      lab[x][y] = row[x-1];
    }
  }

  Queue q;
  q.First = NULL;
  q.Last = NULL;
  int curdist;
  lab[x0][y0] = WALL;
  while ((x0 != x1) || (y0 != y1))
  {
    curdist = dist[x0][y0] + 1;
    if (lab[x0][y0-1] != WALL) { QueueAdd(&q, x0, y0-1);
                                 dist[x0][y0-1] = curdist;
                                  lab[x0][y0-1] = WALL; }
    if (lab[x0-1][y0] != WALL) { QueueAdd(&q, x0-1, y0);
                                 dist[x0-1][y0] = curdist;
                                  lab[x0-1][y0] = WALL; }
    if (lab[x0][y0+1] != WALL) { QueueAdd(&q, x0, y0+1);
                                 dist[x0][y0+1] = curdist;
                                  lab[x0][y0+1] = WALL; }
    if (lab[x0+1][y0] != WALL) { QueueAdd(&q, x0+1, y0);
                                 dist[x0+1][y0] = curdist;
                                  lab[x0+1][y0] = WALL; }
    QueueDel(&q, &x0, &y0);
  }

  fprintf(fout, "%d", dist[x1][y1]);
  fclose(fin);
  fclose(fout);

  while (q.First != NULL) QueueDel(&q, &x, &y);
  return 0;
}

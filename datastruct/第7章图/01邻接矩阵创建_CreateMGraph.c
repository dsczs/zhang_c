#include "stdio.h"
#include "stdlib.h"
#include "io.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* ��󶥵�����Ӧ���û����� */
#define INFINITY 65535

typedef int Status;    /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef char VertexType; /* ��������Ӧ���û�����  */
typedef int EdgeType; /* ���ϵ�Ȩֵ����Ӧ���û����� */
typedef struct {
    VertexType vexs[MAXVEX]; /* ����� */
    EdgeType arc[MAXVEX][MAXVEX];/* �ڽӾ��󣬿ɿ����߱� */
    int numNodes, numEdges; /* ͼ�е�ǰ�Ķ������ͱ���  */
} MGraph;

/* ����������ͼ���ڽӾ����ʾ */
void CreateMGraph(MGraph *G) {
    int i, j, k, w;
    printf("���붥�����ͱ���:\n");
    scanf("%d,%d", &G->numNodes, &G->numEdges); /* ���붥�����ͱ��� */
    for (i = 0; i < G->numNodes; i++) /* ���붥����Ϣ,��������� */
        scanf(&G->vexs[i]);
    for (i = 0; i < G->numNodes; i++)
        for (j = 0; j < G->numNodes; j++)
            G->arc[i][j] = INFINITY;    /* �ڽӾ����ʼ�� */
    for (k = 0; k < G->numEdges; k++) /* ����numEdges���ߣ������ڽӾ��� */
    {
        printf("�����(vi,vj)�ϵ��±�i���±�j��Ȩw:\n");
        scanf("%d,%d,%d", &i, &j, &w); /* �����(vi,vj)�ϵ�Ȩw */
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j]; /* ��Ϊ������ͼ������Գ� */
    }
}

int main(void) {
    MGraph G;
    CreateMGraph(&G);

    return 0;
}


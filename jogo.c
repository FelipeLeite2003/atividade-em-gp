#include <stdio.h>
 #ifdef DEBUG
#define DPRINTF(fmt, args...) fprintf(stderr,"%s %s " fmt,_FILE, __FUNCTION_, ##args )
#else
#define DPRINTF(fmt, args...) 
#endif
#define memset
#define MAXDISCO 10
#define QTDPINOS 3
 
struct Pino
{
	int qtd;
	int discos[MAXDISCO];
};
 
typedef struct Pino Pino;
 
 
static Pino pinos[QTDPINOS];
int         count = 0;
int         quantidade = 4;
 
void DesenhaDisco(int tam )
{
	int i;
 
	for (i=0;i<11-tam;i++)
	{
		printf(" ");
	}
 
	if (tam==0)
	{
		printf("|");	
	}
	else
	for (i=0;i<tam<<1;i++)
	{
		if (i==tam)printf("|");
		printf("=");
	}
 
	for (i=0;i<11-tam;i++)
	{
		printf(" ");
	}
}
 
void MostraPinos()
{
	int i, j, k;
 
	for (i=quantidade-1;i>=0;i--)
	{
		for (j=0;j<QTDPINOS;j++)
		{
 
			k=pinos[j].discos[i];
 
			DesenhaDisco(k);
		}
 
		printf("\n");
	}
	printf("          (0)                    (1)                    (2)\n");
	getchar();
}
 
 
void IniciaPinos()
{
	int i;
 
	if (quantidade>MAXDISCO)
	{
		printf("Erro: qtd disco invalido\n");
		return;
	}
 
	memset(pinos,0,sizeof(Pino)*QTDPINOS);
 
	for (i=0;i<quantidade;i++)
	{
		pinos[0].discos[i]=quantidade-i;
 
		pinos[0].qtd++;
 
	}
 
}
 
 
int MovePino( int orig, int dest )
{
	DPRINTF("orig=%d dest=%d\n",orig,dest);
 
	pinos[dest].discos[ pinos[dest].qtd  ] = pinos[orig].discos[ pinos[orig].qtd-1 ];
	pinos[orig].discos[ pinos[orig].qtd-1] = 0;
	pinos[dest].qtd++;
	pinos[orig].qtd--;
 
	return dest;
}

void TorreHanoi(int origem, int destino, int auxiliar, int quantidade)
{
  if( quantidade == 1 )
  {
    printf("Move de %d para %d:\n\n", origem, destino);
    MovePino(origem, destino);
    MostraPinos();
    count+=1;
  }
  else
  {
    TorreHanoi(origem,   auxiliar, destino, quantidade-1);
    TorreHanoi(origem,   destino,  auxiliar, 1);
    TorreHanoi(auxiliar, destino,  origem, quantidade-1);
  }
}
 
 
int main() 
{
	IniciaPinos();
 
	TorreHanoi(0,2,1,quantidade);
 
	printf("DISCOS=%d RESOLVIDO EM %d MOVIMENTOS!\n",quantidade,count);
 
	return 0;
}

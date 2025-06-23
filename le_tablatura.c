#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 
	Link com as frequências das notas
	https://jpsoft.com/help/beep.htm
	
	Link da tablatura
	https://www.cifras.com.br/tablatura/franz-peter-schubert/ave-maria
*/

int main(int argc,char *argv[])
{
	static char braco_guitarra[6][24][5] =
	{
		{"NE2", "NF2", "NFs2", "NG2", "NGs2", "NA2", "NAs2", "NB2", "NC2", "NCs2", "ND2", "NDs2", "NE3", "NF3", "NFs3", "NG3", "NGs3", "NA3", "NAs3", "NB3", "NC3", "NCs3", "ND3", "NDs3"},
		{"NB1", "NC1", "NCs1", "ND1", "NDs1", "NE2", "NF2", "NFs2", "NG2", "NGs2", "NA2", "NAs2", "NB2", "NC2", "NCs2", "ND2", "NDs2", "NE3", "NF3", "NFs3", "NG3", "NGs3", "NA3", "NAs3"},
		{"NG1", "NGs1", "NA1", "NAs1", "NB1", "NC1", "NCs1", "ND1", "NDs1", "NE2", "NF2", "NFs2", "NG2", "NGs2", "NA2", "NAs2", "NB2", "NC2", "NCs2", "ND2", "NDs2", "NE3", "NF3", "NFs3"},
		{"ND0", "NDs0", "NE1", "NF1", "NFs1", "NG1", "NGs1", "NA1", "NAs1", "NB1", "NC1", "NCs1", "ND1", "NDs1", "NE2", "NF2", "NFs2", "NG2", "NGs2", "NA2", "NAs2", "NB2", "NC2", "NCs2"},
		{"NA0", "NAs0", "NB0", "NC0", "NCs0", "ND0", "NDs0", "NE1", "NF1", "NFs1", "NG1", "NGs1", "NA1", "NAs1", "NB1", "NC1", "NCs1", "ND1", "NDs1", "NE2", "NF2", "NFs2", "NG2", "NGs2"},
		{"NE0", "NF0", "NFs0", "NG0", "NGs0", "NA0", "NAs0", "NB0", "NC0", "NCs0", "ND0", "NDs0", "NE1", "NF1", "NFs1", "NG1", "NGs1", "NA1", "NAs1", "NB1", "NC1", "NCs1", "ND1", "NDs1"}
	};
	
	int i;
	int j;
	FILE *entrada;
	int nada;
	
	char tablatura[6][256];
	
	if (argc != 2)
	{
		printf("Uso: %s <ArquivoDeTablatura>\n", argv[0]);
		return 1;
	}
	
	if (!(entrada = fopen(argv[1], "r")))
	{
		perror("Erro ao abrir arquivo");
		return 1;
	}
	
	for (i=0; i<6; i++)
	{
		for (j=0; j<24; j++)
		{
			printf("%-3s ", braco_guitarra[i][j]);
		}
		puts("");
	}
	
	while (!feof(entrada))
	{
		if ((j=fgetc(entrada)) == EOF)
			break;
		else
			if (j == '\n')
				continue;
		ungetc(j, entrada);
		
		for (i=0; i<6; i++)
			fgets(tablatura[i], 255, entrada);
		
		for (i=0; i<strlen(tablatura[0]); i++)
		{
			nada = 1;
			for (j=0; j<6; j++)
			{
				if (isdigit(tablatura[j][i]))
				{
					//printf("beep(%s, 500);\n", braco_guitarra[j][tablatura[j][i]-'0']);
					printf("beep(%s, DURACAO);\n", braco_guitarra[j][atoi(&tablatura[j][i])]);
					
					#ifdef DEBUG
					printf("Lido: %d\n", atoi(&tablatura[j][i]));
					#endif
					
					if (isdigit(tablatura[j][i+1]))
						i++;
					j=6;
					nada = 0;
				}
			}
			if (nada)
				puts("delay(INTERVALO);");
		}
	}
	
	fclose(entrada);
	
	return 0;
}

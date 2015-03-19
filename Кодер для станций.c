#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <locale.h>

FILE * input = NULL;
FILE * output = NULL;

struct station
{
	char * name;
	unsigned short int number;
};

unsigned short stnum = 1;
struct station ** lines = NULL;  //массив указателей на массив структур


void newline(unsigned short lnum)
{
	assert(lnum > 0);
	if (lnum > 12)
	{
		lines = (struct station **)realloc(lines, (1 + lines[0][0].number + 1)*sizeof(* lines));
		lines[0][0].number += 1;
	}
	lines[lnum] = (struct station *)calloc(11, sizeof(struct station));     //!!!помн€т ли указатели длину своего массива?
	assert(lines[lnum]);
	lines[lnum][0].number = 10;
	lines[lnum][0].name = NULL;
}

void line_resize(unsigned short lnum)
{
	lines[lnum] = realloc(lines[lnum], (lines[lnum][0].number + 6)*sizeof(* lines[lnum]));
	memset(lines[lnum] + lines[lnum][0].number + 1, 0, 5 * sizeof(*lines[lnum]));
	lines[lnum][0].number += 5;
	//printf("Size of %hd line was increased to %hd\n", lnum, lines[lnum][0].number);
	//system("pause");assert(0);
}

void add_station(unsigned short lnum, unsigned short stnum_on_line)
{
	/*static*/ char st_name [30] = "";
	unsigned short i = 0;
	char * nameadd = NULL;
	fscanf(input, "%s", st_name);
	for (i = 0; st_name[i] != '\0'; i++)
		if (st_name[i] == '_')
			st_name[i] = ' ';

	if (lines[lnum][0].number < stnum_on_line)
		line_resize(lnum);
	lines[lnum][stnum_on_line].name = (nameadd = (char *)calloc(i + 1, sizeof(char)));
	strcpy(nameadd, st_name);
	lines[lnum][stnum_on_line].number = stnum++;	
	while (fgetc(input) != '.');
	fgetc(input);
}

unsigned short getline(unsigned short lnum)
{
	unsigned short int line = 0;
	short k = 0;
	unsigned short int stnum_on_line = 1;
	int c = 0;
	
	k = fscanf_s(input, "%hd :\n", &line);
	if (k == -1)
		return 0;
	else if (k != 1) assert(0);
	
	//printf("New line %hd\n", line);
	//system("pause");

	assert(line == lnum);
	newline(lnum);
	
	do
	{
		add_station(lnum,stnum_on_line++);
	} while ((c = fgetc(input)) == ',');
	assert(c == '.');
	c = fgetc(input);  //it's important
	return 1;

}

/*void fix_stations()
{

}
*/

int main()
{
	input = fopen("MosMetro.txt", "r");
	output = fopen("GraphMosMetro.txt", "w");
	setlocale(LC_ALL, "Rus"); 
	lines = (struct station **)calloc(13, sizeof(*lines));
	lines[0] = (struct station *)calloc(1, sizeof(struct station));
	assert(lines[0]);
	lines[0][0].number = 12;
	lines[0][0].name = (char *)calloc(9, sizeof(char));
	*lines[0][0].name = "»м€ћетро";

	unsigned short lnum = 0;
	unsigned short i = 0, j = 0, line_len = 0;
	while (!feof(input))
	{
		lnum += getline(lnum + 1);
	}
	for (i = 1; i <= lnum; i++)
	{
		line_len = lines[i][0].number;
		printf ("New line %hd:\n\n", i);
		for (j = 1; (j <= line_len && lines[i][j].name != NULL); j++)
		{
			printf("Station '%s'; Number %hd\n", lines[i][j].name, lines[i][j].number);
		}
		printf("\n");
	}
	printf("There were %hd stations on %hd lines\n", stnum - 1, lnum);
	system("pause");
	fseek(input, 0, 0);

	fclose(input);
	fclose(output);
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <locale.h>

FILE * input = NULL, * output = NULL, * base_file = NULL;

struct station
{
	char * name;
	unsigned short trans_num;
	unsigned short int number;
};

unsigned short stnum = 1, stcounter = 1;
struct station ** lines = NULL;  //массив указателей на массив структур

void newline(unsigned short lnum)
{
	assert(lnum > 0);
	if (lnum > 12)
	{
		lines = (struct station **)realloc(lines, (1 + lines[0][0].number + 1)*sizeof(* lines));
		lines[0][0].number += 1;
	}
	lines[lnum] = (struct station *)calloc(11, sizeof(struct station));  
	assert(lines[lnum]);
	lines[lnum][0].number = 10;			
	lines[lnum][0].name = NULL;
}

void line_resize(unsigned short lnum)
{
	lines[lnum] = (struct station *)realloc(lines[lnum], (lines[lnum][0].number + 6)*sizeof(* lines[lnum]));
	memset(lines[lnum] + lines[lnum][0].number + 1, 0, 5 * sizeof(*lines[lnum]));
	lines[lnum][0].number += 5;
	//printf("Size of %hd line was increased to %hd\n", lnum, lines[lnum][0].number);
	//system("pause");assert(0);
}

void add_station(unsigned short lnum, unsigned short stnum_on_line)
{
	/*static*/ char st_name [30] = "";
	unsigned short i = 0;
	int c = 0;
	struct station * this_st = NULL;
	fscanf(input, "%s", st_name);
	for (i = 0; st_name[i] != '\0'; i++)
		if (st_name[i] == '_')
			st_name[i] = ' ';

	if (lines[lnum][0].number < stnum_on_line)
		line_resize(lnum);
	this_st = lines[lnum] + stnum_on_line;
	this_st->trans_num = 0;
	this_st->name = (char *)calloc(i + 1, sizeof(char));
	strcpy(this_st->name, st_name);
	this_st->number = stcounter++;
	while ((c = fgetc(input)) != '.')
		if (c == ',')
			this_st->trans_num++;
	fgetc(input);
}

unsigned short getline(unsigned short lnum)
{
	unsigned short int line = 0;
	short k = 0;
	unsigned short int stnum_on_line = 1;
	int c = 0;

	k = fscanf(input, "%hd :\n", &line);
	if (k == -1)
		return 0;
	else if (k != 1) assert(0);

	//printf("New line %hd\n", line);

	assert(line == lnum);
	newline(lnum);
	if (lnum > 1)
		fprintf(base_file, "%hd\n", stcounter);
	do
	{
		add_station(lnum,stnum_on_line++);
	} while ((c = fgetc(input)) == ',');
	assert(c == '.');
	c = fgetc(input);  //it's important
	return 1;
}

void putstation(struct station * this_st)
{
	char s[30] = "";
	unsigned short trans_num = 0, i = 0, j = 0, nline = 0, l_len = 0;

	fgetc(input);
	fscanf(input, "%*s ");
	fscanf(input, "%s :\n", s);
	fprintf(output, "%s %hd\n", s, (trans_num = this_st->trans_num));
	for (i = 0; i < 2; i++)
	{
		fscanf(input, "%s ", s);
		if (strcmp(s, "Конечная") == 0)
		{
			fprintf(output, "0 0:00\n");
			fscanf(input, "%*s ");
		}
		else
		{
			fprintf(output, "%hd ", (i == 0 ? stcounter : (stcounter + 2)));			//stcounter will be increased only in the end of function
			fscanf(input, "%s ", s);
			fprintf(output, "%s\n", s);
		}
	}
	for (i = 0; i < trans_num; i++)
	{
		fscanf(input, ",\n");
		fscanf(input, "%s %hd", s, &nline);
		for (j = 0; s[j] != '\0'; j++)
			if (s[j] == '_')
				s[j] = ' ';
		l_len = lines[nline][0].number;
		for (j = 1; (j <= l_len && lines[nline][j].name != NULL && strcmp(s, lines[nline][j].name) != 0); j++);
		if (j > l_len)
			assert(("Wrong station to transit", 0));
		fscanf(input, "%s ", s);
		fprintf(output, "%hd %s\n", lines[nline][j].number, s);
	}
	assert(fgetc(input) == '.');
	stcounter++;
	fprintf(output, "\n");
	fgetc(input);			//it's important
}

void putline(unsigned short line_num)
{
	unsigned short stnum_on_line = 1;
	int c = 0;
	fscanf(input, "%*hd :\n");
	do
	{
		putstation(lines[line_num] + stnum_on_line++);
	} while ((c = fgetc(input)) == ',');
	assert(c == '.');
}

int main()
{
	input = fopen("MosMetro.txt", "r");
	base_file = fopen("MosMetro_base.txt", "w");
	fprintf(base_file, "   \n");			//place for number of lines
	output = fopen("GraphMosMetro.txt", "w");
	setlocale(LC_ALL, "Rus");
	lines = (struct station **)calloc(13, sizeof(*lines));
	lines[0] = (struct station *)calloc(1, sizeof(struct station));
	assert(lines[0]);
	lines[0][0].number = 12;
	lines[0][0].name = (char *)calloc(9, sizeof(char));
	strcpy(lines[0][0].name, "ИмяМетро");

	unsigned short lnum = 0;
	unsigned short i = 0, j = 0, line_len = 0;
	while (!feof(input))
	{
		lnum += getline(lnum + 1);
	}

	stnum = stcounter - 1;
	fseek(base_file, 0, 0);
	fprintf(base_file, "%hd", lnum);
	fseek(base_file, 0, SEEK_END);
	fprintf(base_file, "%hd", stnum);

	for (i = 1; i <= lnum; i++)
	{
		line_len = lines[i][0].number;
		printf ("New line %hd:\n\n", i);
		for (j = 1; (j <= line_len && lines[i][j].name != NULL); j++)
		{
			printf("Station '%s'; Number %hd\n", lines[i][j].name, lines[i][j].number);
			fprintf(base_file, "\n%s", lines[i][j].name);
		}
		printf("\n");
	}
	printf("There were %hd stations on %hd lines\n", stnum, lnum);
	fclose(base_file);
	system("pause");
	fseek(input, 0, 0);

	stcounter = 0;
	fprintf(output, "%hd\n", stnum);
	for (i = 1; i <= lnum; i++)
		putline(i);

	fclose(input);
	fclose(output);
	return 0;
}

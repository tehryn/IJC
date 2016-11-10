/*
 * Author: Jiri Matejka
 * Login: xmatej52
 * School: VUT FIT, Brno
 * Date: 22-4-2016
 * Module: IJC-DU2 tail.cc
 * gcc version 4.9.2 (Debian 4.9.2-10)
 */
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include "strnum.h"
using namespace std;
/*
 * Detect source file, -n switch and save value to adress pointed by *argc.
 * If source is stdin, set value pointed by stdin_check to 0, otherwise
 * value will not be changed
 * Return pointer to file or NULL when error, also print errors on stderr.
 */
char *get_source_name(int *argc, char **argv, int *stdin_check);

int main(int argc, char **argv) {
	ios::sync_with_stdio(false); //TODO leaks leaks leaks! why should we use this!
	int lines = argc; // number of last n lines
	int stdin_check = 1; // check if source is stdin
	char *source_name = get_source_name(&lines, argv, &stdin_check);
	if (source_name == NULL && stdin_check) return 1;

	istream *input;
	ifstream source;

	if (!stdin_check)
		input = &cin;

	else {
		source.open(source_name, ios::in);
		if (!source.is_open()) {
			cerr << "tail: \"" << source_name << "\" nelze otevřít pro čtení: " 
			                                 "Adresář nebo soubor neexistuje\n";
			return 1;
		}
		input = &source;
	}


	queue<string> buff;
	string line;
	
	/* Load lines into the "stack" */
	while (getline(*input, line))
		buff.push(line);

	int buff_size = buff.size();
	for(int j = 0; j < buff_size; j++) {
		if (j > buff_size - lines - 1)
			cout << buff.front() << "\n";
		buff.pop();
	}
	
	if (source.is_open())
		source.close();

	return 0;
}

/* Detect and set source file, set NULL in case of error */
char *get_source_name(int *argc, char **argv, int *stdin_check) {
	int arg_num = *argc;
	string n = "-n";
	
	if (arg_num == 1) {
		*argc = 10;
		*stdin_check = 0;
		return NULL;
	}
	
	if (arg_num == 2) {
		if (!n.compare(argv[1])) {
			cerr << "tail: přepínač vyžaduje argument – „n“\n";
			return NULL;
		}
		
		else {
			*argc = 10;
			return argv[1];
		}
	}

	int i = 1;
	/* Looking for -n */
	for (; i < arg_num; i++)
		if (!n.compare(argv[i])) 
			break;

	/* if arg_num == i, -n was not found*/
	if (i != arg_num) {
		if (i == arg_num - 1 || !is_int(argv[i+1])) {
			cerr << "tail: přepínač vyžaduje argument – „n“\n";
			return NULL;
		}
		else {
			*argc = string_to_uint(argv[i+1]);
			if (*argc < 0) {
				cerr << "Owerflow detected\n";
				return NULL;
			}
			if (arg_num == 3) {
				*stdin_check = 0;
				return NULL;
			}
			else {
				if (arg_num > 3 && i == 1)
					return argv[3];
				else
					return argv[1];
			}
		}
	}

	/* -n was not found*/
	else {
		return argv[1];
	}
	return NULL; // unknow error
}

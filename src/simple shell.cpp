//============================================================================
// Name        : simple.cpp
// Author      : Mahmoud sharshar
// Version     :
// Copyright   : Your copyright notice
// Description : simple shell
//============================================================================

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include<sstream>
#include<vector>

using namespace std;
const char** parseInput(string input);
void executeCommand(const char **&command);

int main() {
	string input;
	while (true) {
		cout << "simple shell$ ";
		//wait for user input
		getline(cin, input);
		// parse user input
		const char **command = parseInput(input);
		// execute command
		executeCommand(command);
		// free location of command after excution
		delete[] command;
	}

	return 0;
}

// split string input to construct the corresponding command
const char** parseInput(string input) {
	stringstream ss(input);
	// create vector to hold parts of input
	vector<string> words;
	while (ss) {
		string word;
		ss >> word;
		words.push_back(word);
	}
	// create dynamic array of type char array to hold parts of command
	const char **command = new const char*[words.size()];
	for (int i = 0; i < (int) words.size(); i++) {
		if (i < (int) words.size() - 1)
			command[i] = words[i].c_str();
		else
			command[i] = NULL; // insert null to the end of command
		//cout << command[i] << endl;
	}
	return command;
}

void executeCommand(const char **&command) {
	pid_t pid = fork();
	if (strcmp(command[0], "exit") == 0) {
		exit(0);
	}
	if (pid == 0) {
		execvp(command[0], (char* const*) command);
	} else if (pid > 0) {
		wait(NULL);
	}
}

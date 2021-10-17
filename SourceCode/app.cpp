#include	<iostream>
#include 	<fstream>
#include	<string>
#include	<cstdlib>
#include	"List.h"
#include	"Student.h"

using namespace std;


bool BuildStuList(char *, List *);
bool DeleteRecord(List *, char *);
bool Display(List, int); 
bool InsertResult(char *, List *);
bool printStatistic(List);
bool findEligibleFYPStudent(List, List *);
bool identifyGoodPoorStudent(List, List *, List *);
int menu();

using namespace std;


int main() {
	
	system("pause");
	return 0;
}








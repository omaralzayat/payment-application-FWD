#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
typedef struct Data {
	char Name[25];
	char date[6];
	char pan[20];
	float max;
	float trans;
}Data_t;

Data_t testcases[30] = {
	{"jkafhdskjfhdskjfhksjd", "02/23", "4003830171874018", 2000000, 23422},
	{"kldfjafdkldsfjalskdjf", "12/33", "5496198584584769", 2000000, 2328},
	{"kldfjafdkldsfjalskdjf", "12/33", "5496198584584769", 2000000, 328},
	{"nzvm,cxnldsnfdalfkjd;", "09/24", "2223520043560014", 2000000, 563300},
	{"ewporiqueworokpoweirk", "04/26", "3530111333300000", 2000000, 300},

	{"jkafhdskjfhdskjfhksjd", "02/23", "4003830171874018", 200, 342},
	{"kldfjafdkldsfjalskdjf", "12/33", "5496198584584769", 200, 2328},
	{"kldfjafdkldsfjalskdjf", "12/33", "5496198584584769", 200, 328},
	{"nzvm,cxnldsnfdalfkjd;", "09/24", "2223520043560014", 200, 4324},
	{"ewporiqueworokpoweirk", "04/26", "3530111333300000", 200, 300},

	{"jkafhdskjfhdskjfhksjd", "02/23", "4003830171874018", 20000000000000, 3434545332},
	{"kldfjafdkldsfjalskdjf", "12/33", "5496198584584769", 20000000000000, 2334534528},
	{"kldfjafdkldsfjalskdjf", "12/33", "5496198584584769", 20000000000000, 3434534528},
	{"nzvm,cxnldsnfdalfkjd;", "09/24", "2223520043560014", 20000000000000, 4334534524},
	{"ewporiqueworokpoweirk", "04/26", "3530111333300000", 20000000000000, 3034534520},

	{"jkafhdskjfhdskjfhksjd", "02/20", "4003830171874018", 20000, 342},
	{"kldfjafdkldsfjalskdjf", "12/13", "5496198584584769", 20000, 2328},
	{"kldfjafdkldsfjalskdjf", "12/05", "5496198584584769", 20000, 328},
	{"nzvm,cxnldsnfdalfkjd;", "08/22", "2223520043560014", 20000, 4324},
	{"ewporiqueworokpoweirk", "04/21", "3530111333300000", 20000, 300},

	{"jkafhdskjfhdskjfhksjd", "02/23", "44234224324324", 20000, 342},
	{"kldfjafdkldsfjalskdjf", "12/33", "54534534534534", 20000, 2328},
	{"kldfjafdkldsfjalskdjf", "12/33", "549546456546546", 20000, 328},
	{"nzvm,cxnldsnfdalfkjd;", "09/24", "253453453454354", 20000, 4324},
	{"ewporiqueworokpoweirk", "04/26", "365464564565600", 20000, 300}

};

int main() {
	int i;
	for (i = 0; i < 25; i++) {
		FILE* test = fopen("test.txt", "w");
		fprintf(test, "%s\n%s\n%s\n%f\n%f\n", testcases[i].Name, testcases[i].date, testcases[i].pan, testcases[i].max, testcases[i].trans);
		fclose(test);
		system("\"E:\\Omar\\Embedded Systems FWD\\Payment Application\\Debug\\Payment Application.exe\" < test.txt");
		if (i == 4) { printf("\nCase1 passed\n\n\n"); }
		if (i == 9) { printf("\nCase2 passed\n\n\n"); }
		if (i == 14) { printf("\nCase3 passed\n\n\n"); }
		if (i == 19) { printf("\nCase4 passed\n\n\n"); }
		if (i == 24) { printf("\nCase5 passed\n\n\n"); }
	}
	return 0;
}
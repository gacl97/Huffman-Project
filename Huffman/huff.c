#include "header.h"
#include "compact.h"
#include "descompact.h"

int main () {

	char choice;
	while (true) {
		
		printf("#####################################\n");
		printf("#                                   #\n");
		printf("#------------- WELCOME -------------#\n");
		printf("# [1] COMPRESS FILE                 #\n");
		printf("# [2] DESCOMPRESS FILE              #\n");
		printf("# [0] END THE PROGRAM               #\n");
		printf("#####################################\n");
		printf("===> ");
		scanf(" %c", &choice);
		if (choice == '1') {
			compact();
		} else if (choice == '2') {
			descompact();
		} else if(choice == '0'){
			break;
		} else {
			printf("Invalid option, try again\n");
		}
	}
		

    return 0;
}
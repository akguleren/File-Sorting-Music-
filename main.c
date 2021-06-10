#include <stdio.h>
#include <stdlib.h>
//Eren Akgül 150119028. Purpose of this program is to make a linked list from the given file and add new elements to the list or delete existing elements from the list. And print them to console or file in different orders.
int count = 0;

typedef struct song {
	char songName[25];
	int duration;
	struct song *chrono_next;
	struct song *alpha_next;
	struct song *duration_next;
	struct song *random_next;
} Song;

typedef struct song Song;
typedef Song *SongPtr;
//We declare the function prototypes.
void instructions();
void insertSong(SongPtr *chrono_head, SongPtr *alpha_head, SongPtr *duration_head, SongPtr *random_head, char name[]);
int getDuration(char durationStr[]);
void printList(SongPtr chrono_head, SongPtr alpha_head, SongPtr duration_head, SongPtr *random_head);
void printListToFile(SongPtr chrono_head, SongPtr alpha_head, SongPtr duration_head, SongPtr *random_head);
void deleteSong(SongPtr *chrono_head, SongPtr *alpha_head, SongPtr *duration_head, SongPtr *random_head, char name[]);

void instructions() {	//We use this funciton to get instructions.
	puts("\n\nEnter your choice: \n"
			"1 to insert a song to the list. \n"
			"2 to delete a song from the list. \n"
			"3 to print the songs in the list. \n"
			"4 to print the songs to an output file. \n"
			"5 to end.");
}

void insertSong(SongPtr *chrono_head, SongPtr *alpha_head, SongPtr *duration_head, SongPtr *random_head, char name[]) {
	char *token;	
	char durationStr[6];
	char tempDuration[6];
	token = strtok(name, "\t");	//We use tokenizer to split name of the song and the duration of the song.
	char *nameToken = token;
	token = strtok(NULL, "\t");
	char *durationToken = token;
	durationToken[5] = '\0';
	strcpy(durationStr, durationToken);	//We copy the contents of the tokenizers in to strings.
	strcpy(tempDuration, durationStr);

	SongPtr newPtr = malloc(sizeof(Song));	//We use malloc to allocate memory for songs.
	if (newPtr != NULL) {
		strcpy(newPtr->songName, nameToken);	//We update the variables of songs using the pointer.
		newPtr->duration = getDuration(tempDuration);
		newPtr->chrono_next = NULL;

		SongPtr previousPtr = NULL;		//First we insert the song chronologically.
		SongPtr currentPtr = *chrono_head;

		while (currentPtr != NULL) {	//This loop used if the song is not added to first element.
			previousPtr = currentPtr;		//Loop goes until it gets null element.
			currentPtr = currentPtr->chrono_next;
		}

		if (previousPtr == NULL) {	//If there isn't any element in the list we directly insert the element in to the header.
			newPtr->chrono_next = *chrono_head;
			*chrono_head = newPtr;
		}

		else {		//After we get a null element in chrono_next we insert our song in it.
			previousPtr->chrono_next = newPtr;
			newPtr->chrono_next = currentPtr;
		}

	} else {
		printf("No memory available.\n");
	}
	//We do the same operations with different pointers from this line.
	newPtr = malloc(sizeof(Song));
	strcpy(tempDuration, durationStr);
	if (newPtr != NULL) {
		strcpy(newPtr->songName, nameToken);
		newPtr->duration = getDuration(tempDuration);
		newPtr->chrono_next = NULL;

		SongPtr previousPtr = NULL;
		SongPtr currentPtr = *alpha_head;

		while (currentPtr != NULL && strcmp(currentPtr->songName, nameToken) < 0) {	//strcmp method compares strings alphabetically.
			previousPtr = currentPtr;
			currentPtr = currentPtr->alpha_next;
		}

		if (previousPtr == NULL) {
			newPtr->alpha_next = *alpha_head;
			*alpha_head = newPtr;
		}

		else {
			previousPtr->alpha_next = newPtr;
			newPtr->alpha_next = currentPtr;
		}
	} else {
		printf("No memory available.\n");
	}
	newPtr = malloc(sizeof(Song));
	strcpy(tempDuration, durationStr);
	if (newPtr != NULL) {
		strcpy(newPtr->songName, nameToken);
		newPtr->duration = getDuration(tempDuration);
		newPtr->duration_next = NULL;

		SongPtr previousPtr = NULL;
		SongPtr currentPtr = *duration_head;

		while (currentPtr != NULL && newPtr->duration > currentPtr->duration) {	//We compare the durations.
			previousPtr = currentPtr;
			currentPtr = currentPtr->duration_next;
		}

		if (previousPtr == NULL) {
			newPtr->duration_next = *duration_head;
			*duration_head = newPtr;
		}

		else {
			previousPtr->duration_next = newPtr;
			newPtr->duration_next = currentPtr;
		}
	} else {
		printf("No memory available.\n");
	}
	newPtr = malloc(sizeof(Song));	//We just do the same operation with chronological.But we randomize the list in printList or printListToFile.
	strcpy(tempDuration, durationStr);
	if (newPtr != NULL) {
		count++;
		strcpy(newPtr->songName, nameToken);
		newPtr->duration = getDuration(tempDuration);
		newPtr->random_next = NULL;

		SongPtr previousPtr = NULL;
		SongPtr currentPtr = *random_head;

		while (currentPtr != NULL) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->random_next;
		}

		if (previousPtr == NULL) {
			newPtr->random_next = *random_head;
			*random_head = newPtr;
		}

		else {
			previousPtr->random_next = newPtr;
			newPtr->random_next = currentPtr;
		}

	} else {
		printf("No memory available.\n");
	}
}

int getDuration(char durationStr[]) {
	char *token = strtok(durationStr, ":");	//We use tokenizer to split minutes and seconds.
	char minute[2];
	char second[2];
	int duration;
	char *minuteToken = token;	//We put minutes and seconds to different pointers.
	strcpy(minute, minuteToken);	//We copy the content of minute token to minute.
	duration = atoi(minute) * 60;	//We use atoi method to convert strings to integers.And we calculate the duration in seconds.
	token = strtok(NULL, "\t");
	char *secondsToken = token;
	strcpy(second, secondsToken);
	duration += atoi(second);	//We add the remaining seconds to duration part.
	durationStr[2] = ':';	//To prevent errors i put ':' in the second element of the array.Because the tokenizer removes it.
	return duration;	//We return the duration.
}

void printList(SongPtr chrono_head, SongPtr alpha_head, SongPtr duration_head, SongPtr* random_head) {
	SongPtr currentPtr = chrono_head;
	int a = 0;		//This value holds the ranking numbers.
	printf("List in chronological order:\n");	
	while (currentPtr != NULL) {		//We scan the list and print it.
		printf("\n%d.%s %02d:%02d", (a + 1), currentPtr->songName, currentPtr->duration / 60, currentPtr->duration % 60);
		currentPtr = currentPtr->chrono_next;	//We change currentPtr with the next element of currentPtr to move further in the list.
		a++;	
	}
	a = 0;
	currentPtr = alpha_head;	//We change the header.
	printf("\n\n");
	printf("List in alphabetical order:\n");
	while (currentPtr != NULL) {
		printf("\n%d.%s %02d:%02d", (a + 1), currentPtr->songName, currentPtr->duration / 60, currentPtr->duration % 60);
		currentPtr = currentPtr->alpha_next;
		a++;
	}
	a = 0;
	currentPtr = duration_head;
	printf("\n\n");
	printf("List in duration order:\n");
	while (currentPtr != NULL) {
		printf("\n%d.%s %02d:%02d", (a + 1), currentPtr->songName, currentPtr->duration / 60, currentPtr->duration % 60);
		currentPtr = currentPtr->duration_next;
		a++;
	}
	SongPtr previousPtr = NULL;
	SongPtr temp_head = *random_head;	//temp_head value holds the not randomized list.
	currentPtr = *random_head;
	srand(time(0));
	int b;
	int temp_count = count;		//temp_count variable holds the not randomized list's element number.
	int randomNumber = (rand() % (count));	//We take a random number.

	if (randomNumber == 0) {	//If the random number is 0, we get the first element of not randomized list and make it the first element of our randomized list.
		temp_head = temp_head->random_next;	//We update the temp header value to keep the links of the not randomized list.
		(*random_head)->random_next = NULL;	//We update the random_next variable of random_head.
	} else {
		currentPtr = temp_head;
		for (b = 0; b < randomNumber + 1; b++) {	//We traverse the list to the random number and get the element from the last iteration.
			if (b == (randomNumber)) {
				previousPtr->random_next = currentPtr->random_next;	//We arrange the links.
				*random_head = currentPtr;		//We update the random head.
				(*random_head)->random_next = NULL;	
			}
			previousPtr = currentPtr;	//We skip the elements until we get the header.
			currentPtr = currentPtr->random_next;
		}
	}
	count--;	//We decrement the count to hold the current number of elements in the not randomized list.
	SongPtr current_head = *random_head;	
	while (count != 0) {
		srand(time(0));		//We give another seed to get a new series of random numbers.
		randomNumber = (rand() % (count));	
		currentPtr = temp_head;

		if (randomNumber == 0) {	//If the random number is 0, we get the first element in the not randomized list and add it to the headers next element.
			current_head->random_next = temp_head;
			current_head = current_head->random_next;
			temp_head = temp_head->random_next;	//We update the temp_head to not to lose the head of list.
			current_head->random_next = NULL;	
		} else {
			currentPtr = temp_head;		//We get the head of the not randomized list.
			for (b = 0; b < randomNumber + 1; b++) {
				if (b == (randomNumber)) {	
					previousPtr->random_next = currentPtr->random_next;	//We arrange the links.
					current_head->random_next = currentPtr;	//We add the element to the list.
					current_head = current_head->random_next;	//We update the last element of the randomized list.
					current_head->random_next = NULL;
				}
				previousPtr = currentPtr;	//We skip the elements.
				currentPtr = currentPtr->random_next;
			}
		}
		count--;	//We decrement the count each time an element is inserted.
	}
	count = temp_count;	//We initialize the count to prevent errors in the second iteration of printList.
	a = 0;
	currentPtr = *random_head;
	printf("\n\n");
	printf("List in random order:\n");	//We print the randomized list.
	while (currentPtr != NULL) {
		printf("\n%d.%s %02d:%02d", (a + 1), currentPtr->songName, currentPtr->duration / 60, currentPtr->duration % 60);
		currentPtr = currentPtr->random_next;
		a++;
	}
}
//printListToFile function almost the same as printList function. We just changed printf format to fprintf.
void printListToFile(SongPtr chrono_head, SongPtr alpha_head, SongPtr duration_head, SongPtr *random_head) {
	FILE *file = fopen("output.txt", "w");	//Opening a new file for writing purposes.
	SongPtr currentPtr = chrono_head;
	int a = 0;
	fprintf(file,"List in chronological order:\n");
	while (currentPtr != NULL) {
		fprintf(file,"\n%d.%s %02d:%02d", (a + 1), currentPtr->songName, currentPtr->duration / 60, currentPtr->duration % 60);
		currentPtr = currentPtr->chrono_next;
		a++;
	}
	a = 0;
	currentPtr = alpha_head;
	fprintf(file, "\n\n");
	fprintf(file, "List in alphabetical order:\n");
	while (currentPtr != NULL) {
		fprintf(file, "\n%d.%s %02d:%02d", (a + 1), currentPtr->songName, currentPtr->duration / 60, currentPtr->duration % 60);
		currentPtr = currentPtr->alpha_next;
		a++;
	}
	a = 0;
	currentPtr = duration_head;
	fprintf(file, "\n\n");
	fprintf(file, "List in duration order:\n");
	while (currentPtr != NULL) {
		fprintf(file, "\n%d.%s %02d:%02d", (a + 1), currentPtr->songName, currentPtr->duration / 60, currentPtr->duration % 60);
		currentPtr = currentPtr->duration_next;
		a++;
	}
	SongPtr previousPtr = NULL;
	SongPtr temp_head = *random_head;
	currentPtr = *random_head;
	srand(time(0));
	int b;
	int temp_count = count;
	int randomNumber = (rand() % (count));

	if (randomNumber == 0) {
		temp_head = temp_head->random_next;
		(*random_head)->random_next = NULL;
	} else {
		currentPtr = temp_head;
		for (b = 0; b < randomNumber + 1; b++) {

			if (b == (randomNumber)) {
				previousPtr->random_next = currentPtr->random_next;
				*random_head = currentPtr;
				(*random_head)->random_next = NULL;
			}
			previousPtr = currentPtr;
			currentPtr = currentPtr->random_next;
		}
	}
	count--;
	SongPtr current_head = *random_head;
	while (count != 0) {
		srand(time(0));
		randomNumber = (rand() % (count));
		currentPtr = temp_head;

		if (randomNumber == 0) {
			current_head->random_next = temp_head;
			current_head = current_head->random_next;
			temp_head = temp_head->random_next;
			current_head->random_next = NULL;
		} else {
			currentPtr = temp_head;
			for (b = 0; b < randomNumber + 1; b++) {

				if (b == (randomNumber)) {
					previousPtr->random_next = currentPtr->random_next;
					current_head->random_next = currentPtr;
					current_head = current_head->random_next;
					current_head->random_next = NULL;
				}
				previousPtr = currentPtr;
				currentPtr = currentPtr->random_next;
			}
		}
		count--;
	}
	count = temp_count;
	a = 0;
	currentPtr = *random_head;
	fprintf(file, "\n\n");
	fprintf(file, "List in random order:\n");
	while (currentPtr != NULL) {		
		fprintf(file, "\n%d.%s %02d:%02d", (a + 1), currentPtr->songName, currentPtr->duration / 60, currentPtr->duration % 60);
		currentPtr = currentPtr->random_next;
		a++;
	}
	fclose(file);		//We close the file to make a successful print operation.
}

void deleteSong(SongPtr *chrono_head, SongPtr *alpha_head, SongPtr *duration_head, SongPtr *random_head, char name[]) {
	SongPtr previousPtr = NULL;
	SongPtr currentPtr = *chrono_head;	//Firstly we are going to delete an element from chronological list.

	if (currentPtr == NULL)
		printf("There is no item in the list.");

	while (currentPtr != NULL) {
		if (strcmp(currentPtr->songName, name) == 0) {
			if (previousPtr == NULL) {
				*chrono_head = currentPtr->chrono_next;  //If it's the first element we update the header.
				currentPtr->chrono_next = NULL;			//We remove the old link.
				break;
			} else {
				previousPtr->chrono_next = currentPtr->chrono_next;		//We arrange the links
				currentPtr->chrono_next = NULL;
				break;
			}
		}
		previousPtr = currentPtr;			//We skip the elements with this two operations.
		currentPtr = currentPtr->chrono_next;
	}

	previousPtr = NULL;			//We update the currentPtr with alphabetical header to delete element from alphabetical list.
	currentPtr = *alpha_head;

	if (currentPtr == NULL)
		printf("There is no item in the list.");

	while (currentPtr != NULL) {
		if (strcmp(currentPtr->songName, name) == 0) {
			if (previousPtr == NULL) {
				*alpha_head = currentPtr->alpha_next; 	//If it's the first element we update the header.
				currentPtr->alpha_next == NULL;			//We remove the old link.
				break;
			} else {
				previousPtr->alpha_next = currentPtr->alpha_next;   //We arrange the links
				currentPtr->alpha_next = NULL;
				break;
			}
		}
		previousPtr = currentPtr;				//We skip the elements with this two operations.
		currentPtr = currentPtr->alpha_next;
	}

	previousPtr = NULL;				//We update the currentPtr with duration header to delete element from duraiton ordered list.
	currentPtr = *duration_head;

	if (currentPtr == NULL)
		printf("There is no item in the list.");

	while (currentPtr != NULL) {
		if (strcmp(currentPtr->songName, name) == 0) {
			if (previousPtr == NULL) {
				*duration_head = currentPtr->duration_next; 		//If it's the first element we update the header.
				currentPtr->duration_next = NULL;				//We remove the old link.
				break;
			} else {
				previousPtr->duration_next = currentPtr->duration_next; 	//We arrange the links.
				currentPtr->duration_next = NULL;
				break;
			}
		}
		previousPtr = currentPtr;					//We skip the elements with this two operations.
		currentPtr = currentPtr->duration_next;
	}

	previousPtr = NULL;				//We update the currentPtr with random header to delete element from random list.
	currentPtr = *random_head;

	if (currentPtr == NULL)
		printf("There is no item in the list.");

	while (currentPtr != NULL) {
		if (strcmp(currentPtr->songName, name) == 0) {
			if (previousPtr == NULL) {
				*random_head = currentPtr->random_next;					//If it's the first element we update the header.
				currentPtr->random_next = NULL;							//We remove the old link.
				break;
			} else {
				previousPtr->random_next = currentPtr->random_next;		//We arrange the links.
				currentPtr->random_next = NULL;							
				break;
			}
		}
		previousPtr = currentPtr;				//We skip the elements with this two operations.
		currentPtr = currentPtr->random_next;
	}
	count--;	//We decrement this value to hold the number of elements in the random list.
}

int main(int argc, char *argv[]) {
	char name[25];			//We initialize the variables.
	unsigned int choice;
	FILE *fPtr;
	SongPtr chrono_head = NULL;
	SongPtr alpha_head = NULL;
	SongPtr duration_head = NULL;
	SongPtr random_head = NULL;

	if ((fPtr = fopen("songs.txt", "r")) == NULL) {	//If file can't be opened we give an error message.
		printf("File couldn't found");
	} else {
		char str[40];
		while (fgets(str, 40, fPtr) != NULL) {
			printf("%s", str);	//We print the existing songs in the .txt file.
			insertSong(&chrono_head, &alpha_head, &duration_head, &random_head, str);
		}
	}
	while (choice != 5) {		//Actions will continue until the user enter 5 as a choice.
		instructions();			//We call the instructions.
		scanf("%u", &choice);	//We get the choice from the user..
		char x;
		scanf("%c", &x);	//Scanf function causes a problem.If we use another gets function after first scanf, gets function will get passed.
		switch (choice) {	//That's why i used this junk scanf function.
		case 1:
			printf("Enter a song name with a duration: ");
			gets(&name);	//We take the name input of the song that the user wants to insert.
			insertSong(&chrono_head, &alpha_head, &duration_head, &random_head, name);
			break;
		case 2:
			printf("Enter a song name: ");	
			gets(&name);	//We take the name input of the song that the user wants to delete.
			deleteSong(&chrono_head, &alpha_head, &duration_head, &random_head,	name);	//Calling the delete function.
			break;
		case 3:
			printList(chrono_head, alpha_head, duration_head, &random_head);	//Calling the method to print the list.
			break;
		case 4:
			printListToFile(chrono_head, alpha_head, duration_head, &random_head);	//Calling the method for printing list to the file.
			break;
		}
	}
}

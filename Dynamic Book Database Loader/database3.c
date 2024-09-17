#include "database_main.h"
#include "unistd.h"

/* removes the prefix from the word */
char *remove_prefix(char *word, char *prefix) {
	char *remnant, *pos;
	
	if ((pos=strchr(word, '\n')) != NULL)
		*pos = '\0';

    if(strlen(prefix)>strlen(word)) {
		fprintf(stderr, "the file is \"corrupted\"");
		exit(-1);
	}

    remnant = (char *) malloc(sizeof(char) * strlen(word));

    if(strncmp(word, prefix, strlen(prefix))==0) {
    	strncpy(remnant, &word[strlen(prefix)], strlen(word) - strlen(prefix));
    }

   	return remnant;
}

/* read file containing database of books */
void read_book_database ( char *file_name )
{
	FILE *fp;
	char line[256], *title, *author, *str_year, *result;
	struct Book *book;
	int year;
		
	fp = fopen(file_name, "r");
	if(fp == NULL) {
		perror("Error opening file");
		return;
	}
	while(1) {
		book = (struct Book *) malloc(sizeof(struct Book));

		result = fgets(line, sizeof(line), fp);
		if(result==NULL)
			break;
		title = remove_prefix(line, "Title: ");
	
		result = fgets(line, sizeof(line), fp);
		if(result==NULL)
			break;
		author = remove_prefix(line, "Author: ");
		
		result = fgets(line, sizeof(line), fp);
		if(result==NULL)
			break;
		str_year = remove_prefix(line, "Year: ");
		year = atoi(str_year);
		if(year==0) {
			fprintf(stderr, "the file is \"corrupted\"");
			exit(-1);
		}

		result = fgets(line, sizeof(line), fp);

		strcpy(book->title, title);
		strcpy(book->author, author);
		book->year=year;
		book->left=NULL;
		book->right=NULL;

		if(book_tree==NULL) {
			book_tree=book;
			continue;
		}

		struct Book *current = book_tree;
		while(1) {
			if(strcmp(book->title, current->title) > 0) {
				if(current->right==NULL) {
					current->right = book;
					break;
				}

				current = current->right;
			}
			else if(strcmp(book->title, current->title) < 0) {
				if(current->left==NULL) {
					current->left = book;
					break;
				}

				current = current->left;
			}
			else {
				if(current->year==-1) {
					strcpy(current->author, book->author);
					current->year = book->year;
					break;
				}
			}
		}
    }

	fclose(fp);
}


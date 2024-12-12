#include "video.h"
#include "linkedList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_BUFF 200


/* Function saves the gif to a textual file.
Input: pointer to head of the list, file path where project will be saved.
Output: none. */
void saveVideo(FrameNode* curr, char* filePath)
{
	FILE* savedFile = fopen(filePath, "w");
	if (savedFile == NULL)
	{
		printf("Error creating file at %s. Try again.\n", filePath);
		return NULL;
	}
	while (curr)
	{
		fprintf(savedFile, "%s|%d|%s\n", curr->frame->name, curr->frame->duration, curr->frame->path);
		curr = curr->next;
	}
	printf("File successfully saved! Find file at: %s\n", filePath);
	fclose(savedFile);
}


/* Function loads a frameNode linked list from a file.
Input: the file path of the saved project.
Output: pointer to head of the created linked list, 
NULL if file wasn't found or an error occured. */
FrameNode* loadVideo(char* filePath)
{
	FrameNode* newFrameNode = NULL;
	FILE* file = NULL;
	char str[MAX_BUFF] = { 0 };
	char* input = NULL;
	FrameNode* first = NULL;
	FrameNode* curr = NULL;
	Frame* newFrame = NULL;
	

	file = fopen(filePath, "r");
	if (!file)
	{
		printf("File at %s not found, try again.\n", filePath);
		return NULL;
	}

	while (fgets(str, MAX_BUFF, file))
	{
		newFrameNode = (FrameNode*)malloc(sizeof(FrameNode));
		newFrame = (Frame*)malloc(sizeof(Frame));

		str[strcspn(str, "\n")] = 0;

		// separating string into tokens, by '|' character
		input = strtok(str, "|"); 
		newFrame->name = (char*)malloc((strlen(input) + 1) * sizeof(char));
		if (newFrame->name == NULL)
		{
			printf("Memory allocation failed.\n");
			return NULL;
		}
		strcpy(newFrame->name, input);

		input = strtok(NULL, "|"); 
		newFrame->duration = atoi(input);

		input = strtok(NULL, "|"); 
		newFrame->path = (char*)malloc((strlen(input) + 1) * sizeof(char));
		if (newFrame->path == NULL)
		{
			printf("Memory allocation failed.\n");
			return NULL;
		}
		strcpy(newFrame->path, input);

		newFrameNode->frame = newFrame;
		newFrameNode->next = NULL;

		if (first)
		{
			curr->next = newFrameNode;
			curr = curr->next;
		}
		else
		{
			first = newFrameNode;
			curr = first;
		}
	}
	fclose(file);
	printf("\nProject loaded! Continue: ");
	return first;
}

#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STR_LEN 100


/* Function creates a new FrameNode.
Input: name, duration, path.
Output: the new FrameNode. */
FrameNode* createFrameNode(char* name, int dur, char* path)
{
	FrameNode* frameNode = (FrameNode*)malloc(sizeof(FrameNode));
	Frame* frame = (Frame*)malloc(sizeof(Frame));
	frame->path = path;
	frame->duration = dur;
	frame->name = name;

	frameNode->frame = frame;
	frameNode->next = NULL;
	return frameNode;
}


/* Function frees a FrameNode variable.
Input: a FrameNode node.
Output: none. */
void freeFrameNode(FrameNode* nodeToFree)
{
	free(nodeToFree->frame->name);
	free(nodeToFree->frame->path);
	free(nodeToFree->frame);
	free(nodeToFree);
}


/* Function finds the frame node previous to the inputed one, by name.
Input: pointer to head of the list, the frame name.
Output: the previous node to the node with the inputed name, the node if it is the 
head of the list, and NULL if node wasn't found.*/
FrameNode* findPrevFrame(FrameNode* list, char* frameName)
{
	FrameNode* curr = list;
	if (list == NULL)
	{
		return NULL;
	}
	if (strcmp(curr->frame->name, frameName) == 0)
	{
		return curr;
	}
	while (curr->next && strcmp(curr->next->frame->name, frameName))
	{
		curr = curr->next;
	}
	return curr->next && !strcmp(curr->next->frame->name, frameName) ? curr : NULL;
} 


/* Function recursively calculates length of a linked list.
Input: pointer to head of the list.
Output: length of the list. */
int getListLen(FrameNode* first)
{
	if (first == NULL)
	{
		return 0;
	}
	return getListLen(first->next) + 1;
}


/* Function gets frame values from user and adds a frameNode to frameNode list.
Input: pointer to pointer to head of the list.
Output: none. */
void addFrame(FrameNode** list)
{
	char pathBuffer[MAX_STR_LEN] = { 0 };
	char nameBuffer[MAX_STR_LEN] = { 0 };
	char* path = NULL;
	char* name = NULL;
	unsigned int dur = 0;
	FILE* pathToCheck = NULL;
	Frame* frame = NULL;
	FrameNode* newFrameNode = NULL;
	FrameNode* curr = NULL;

	printf("Enter path of the wanted image: ");
	fgets(pathBuffer, MAX_STR_LEN, stdin);
	pathBuffer[strcspn(pathBuffer, "\n")] = 0;

	printf("Enter duration in milliseconds: ");
	scanf("%d", &dur);
	getchar();

	printf("Enter name of the frame: ");
	fgets(nameBuffer, MAX_STR_LEN, stdin);
	nameBuffer[strcspn(nameBuffer, "\n")] = 0;
	while (findPrevFrame(*list, nameBuffer) != NULL)
	{
		printf("The frame name %s is already taken! Enter new frame name: ", nameBuffer);
		fgets(nameBuffer, MAX_STR_LEN, stdin);
		nameBuffer[strcspn(nameBuffer, "\n")] = 0;
	}

	pathToCheck = fopen(pathBuffer, "rb");
	if (pathToCheck == NULL)
	{
		printf("Can't create frame... Path doesn't exist or can't be opened\n");
		return NULL;
	}
	fclose(pathToCheck);

	path = (char*)malloc(sizeof(char) * (strlen(pathBuffer) + 1));
	if (path == NULL)
	{
		printf("Memory allocation error.\n");
		return NULL;
	}
	name = (char*)malloc(sizeof(char) * (strlen(nameBuffer) + 1));
	if (name == NULL)
	{
		printf("Memory allocation error.\n");
		free(path);
		return NULL;
	}

	strcpy(path, pathBuffer);
	strcpy(name, nameBuffer);

	newFrameNode = createFrameNode(name, dur, path);

	if (!(*list))
	{
		*list = newFrameNode;
	}
	else
	{
		curr = *list;
		while (curr->next)
		{
			curr = curr->next;
		}
		curr->next = newFrameNode;
	}
}

/* Function removes a frameNode from list and frees it.
Input: a pointer to pointer to head of the list, the frame name to be deleted.
Output: none. */
void removeFrame(FrameNode** list, char* frameName)
{
	FrameNode* toDelete = NULL;
	FrameNode* curr = NULL; 
	curr = findPrevFrame(*list, frameName);

	if (curr == NULL)
	{
		printf("Frame name not found.\n");
		return NULL;
	}

	if (strcmp(curr->frame->name, frameName) == 0) // if the node to delete is the first one
	{
		toDelete = *list;
		*list = (*list)->next;
	}
	else
	{
		toDelete = curr->next;
		curr->next = toDelete->next;
	}

	freeFrameNode(toDelete);
}


/* Function changes the location of a frame.
Input: a FrameNode node.
Output: none. */
void changeFrameLoc(FrameNode** list)
{
	char frameName[MAX_STR_LEN] = { 0 };
	int newIndex = 0, i = 0;
	FrameNode* prev = NULL;
	FrameNode* curr = NULL;
	FrameNode* toReplace = NULL;

	printf("Enter name of the frame you'd like to change the placement of: ");
	fgets(frameName, MAX_STR_LEN, stdin);
	frameName[strcspn(frameName, "\n")] = 0;
	prev = findPrevFrame(*list, frameName);
	if (prev == NULL)
	{
		printf("Frame name '%s' doesn't exist.\n", frameName);
		return NULL; 
	}

	printf("Enter new index of the frame '%s': ", frameName);
	scanf("%d", &newIndex);
	getchar();
	if (newIndex < 1 || newIndex > getListLen(*list))
	{
		printf("Index %d is outside of the list indexes.\n", newIndex);
		return NULL;
	}

	if (strcmp(prev->frame->name, frameName) == 0)
	{
		if (newIndex == 1) // if its the first node and wants to be transferred to first index.
		{
			return NULL;
		}
		toReplace = *list;
		*list = (*list)->next;
	}
	else
	{
		toReplace = prev->next;
		prev->next = toReplace->next;
	}

	curr = *list;
	if (newIndex == 1)
	{
		*list = toReplace;
		toReplace->next = curr;
		return NULL;
	}
	for (i = 1; i < newIndex - 1 && curr->next; i++)
	{
		curr = curr->next;
	}

	toReplace->next = curr->next;
	curr->next = toReplace;
}


/* Function changes duration of an inputed frame.
Input: pointer to the first frame node.
Output: none. */
void changeFrameLen(FrameNode* list)
{
	char frameName[MAX_STR_LEN] = { 0 };
	int newDuration = 0;
	FrameNode* toChange = NULL;

	printf("Enter frame name you'd like to change the duration of: ");
	fgets(frameName, MAX_STR_LEN, stdin);
	frameName[strcspn(frameName, "\n")] = 0;

	toChange = findPrevFrame(list, frameName);
	if (toChange == NULL)
	{
		printf("Frame name '%s' doesn't exist.\n", frameName);
		return NULL;
	}
	printf("Enter new duration (ms) of frame %s: ", frameName);
	scanf("%d", &newDuration);
	getchar();

	if (strcmp(toChange->frame->name, frameName) == 0) // checking if it's the first node
	{
		toChange->frame->duration = newDuration;
	}
	else
	{
		toChange->next->frame->duration = newDuration;
	}

}


/* Function changes duration of all frames.
Input: pointer to the first frame node, the new duration.
Output: none. */
void changeAllLen(FrameNode* list, int newLen)
{
	FrameNode* curr = list;
	while (curr)
	{
		curr->frame->duration = newLen;
		curr = curr->next;
	}
}


/* Function prints information about each frame.
Input: pointer to head of the list of frames (first frame).
Output: none. */
void printFrames(FrameNode* list)
{
	FrameNode* curr = list;
	char* name = "";
	char* path = "";
	int dur = 0;
	printf("\n\tName\t\t Duration \t\t Path\n");
	while (curr)
	{
		name = curr->frame->name;
		dur = curr->frame->duration;
		path = curr->frame->path;
		printf("\t%s\t\t %dms \t\t\t %s\n", name, dur, path);
		curr = curr->next;
	}
	printf("\n");
}


/* Function inverts a linked list. 
Input: pointer to pointer to head of list. 
Output: none. */
void invertList(FrameNode** list)
{
	FrameNode* curr = *list;
	FrameNode* prev = NULL;
	FrameNode* next = NULL;

	while (curr)
	{
		next = curr->next; 
		curr->next = prev; 

		prev = curr; 
		curr = next;
	}

	*list = prev; 
}


/* Function deletes the video and fress the frameNodes.
Input: pointer to pointer to head of the list.
Output: none. */
void deleteVideo(FrameNode** first)
{
	FrameNode* curr = *first;
	FrameNode* temp = NULL;
	while (curr)
	{
		temp = curr->next;
		freeFrameNode(curr);
		curr = temp;
	}
	*first = NULL;
}

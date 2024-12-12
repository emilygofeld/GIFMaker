#define CV_IGNORE_DEBUG_BUILD_GUARD
#define _CRT_SECURE_NO_WARNINGS

#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>

#include <stdio.h>
#include <stdlib.h>

#include "linkedList.h"
#include "view.h"
#include "video.h"

#define MAX_STR_LEN 150

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int getChoice();
FrameNode* beginProject();


int main(void)
{
	FrameNode* gifList = beginProject();
	char userInput[MAX_STR_LEN] = { 0 };
	int choice = 0, newDuration = 0;
	do
	{
		choice = getChoice();
		
		switch (choice)
		{
		case 0:
			printf("Goodbye!");
			break;
		case 1:
			addFrame(&gifList);
			break;
		case 2:
			printf("Enter name of the frame you'd like to remove: ");
			fgets(userInput, MAX_STR_LEN, stdin);
			userInput[strcspn(userInput, "\n")] = 0;
			removeFrame(&gifList, userInput);
			break;
		case 3:
			changeFrameLoc(&gifList);
			break;
		case 4:
			changeFrameLen(gifList);
			break;
		case 5:
			printf("Enter new duration (ms) of all frames: ");
			scanf("%d", &newDuration);
			getchar();
			changeAllLen(gifList, newDuration);
			break;
		case 6:
			printFrames(gifList);
			break;
		case 7:
			play(gifList);
			break;
		case 8:
			printf("Enter path and name of file where project will be saved: ");
			fgets(userInput, MAX_STR_LEN, stdin);
			userInput[strcspn(userInput, "\n")] = 0;
			saveVideo(gifList, userInput);
			break;
		case 9:
			playBackwards(&gifList);
			break;
		case 10:
			playInfinitely(gifList);
			break;
		default:
			printf("Invalid option.\n");
			break;
		}
	} while (choice != 0);

	deleteVideo(&gifList);
//	printf("leaks: %d", _CrtDumpMemoryLeaks());

	getchar();
	return 0;
}


/* Function prints menu and gets user choice.
Input: none.
Output: the number of the choice. */
int getChoice()
{
	int choice = 0;
	printf("\nChoose an option!\n0 - Exit\n1 - Add new frame\n2 - Remove frame\n3 - Change frame location\n4 - Change frame duration\n5 - Change all frame duration\n6 - Print list of frames\n7 - Play video\n8 - Save video\n9 - Play video backwards\n10 - Play video infinitely\n");
	scanf("%d", &choice);
	getchar();

	return choice;
}


/* Function prints initial menu and gets user choice as to beggining the project.
Input: none.
Output: head of the frameNode linked list if user chose 1, otherwise NULL. */
FrameNode* beginProject()
{
	FrameNode* head = NULL;
	char path[MAX_STR_LEN] = { 0 };
	int opt = 0;
	do
	{
		printf("\nWelcome to Emily's GIF maker!\nChoose an option:\n[0] Create new project\n[1] Load existing project\n");
		scanf("%d", &opt);
		getchar();
		switch (opt)
		{
		case 0:
			return NULL;
		case 1:
			break;
		default:
			printf("Wrong option!\n");
		}
	} while (opt != 0 && opt != 1);

	do
	{
		printf("Enter path of existing project: ");
		fgets(path, MAX_STR_LEN, stdin);
		path[strcspn(path, "\n")] = 0;
		head = loadVideo(path);
	} while (!head);

	return head;
}

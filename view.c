/*********************************
* Class: MAGSHIMIM Final Project *
* Play function				 	 *
**********************************/

#include "view.h"

/**
play the movie!!
display the images each for the duration of the frame one by one and close the window
input: a linked list of frames to display
output: none
**/
void play(FrameNode* list)
{
	cvNamedWindow("Display window", CV_WINDOW_AUTOSIZE); //create a window
	FrameNode* head = list;
	int imgNum = 1, playCount = 0;
	IplImage* image;
	while (playCount < GIF_REPEAT)
	{
		while (list != 0)
		{
			image = cvLoadImage(list->frame->path, 1);
			IplImage* pGrayImg = 0;
			pGrayImg = cvCreateImage(cvSize(image->width, image->height), image->depth, 1);
			if (!image) //The image is empty - shouldn't happen since we checked already.
			{
				printf("Could not open or find image number %d", imgNum);
			}
			else
			{
				cvShowImage("Display window", image); //display the image
				cvWaitKey(list->frame->duration); //wait
				list = list->next;
				cvReleaseImage(&image);
			}
			imgNum++;
		}
		list = head; // rewind
		playCount++;
	}
	cvDestroyWindow("Display window");
	return;
}


/* Function plays video backwards. 
Input: pointer to pointer to head of the frame list.
Output: none. */
void playBackwards(FrameNode** list)
{
	invertList(list);
	play(*list);
	invertList(list);
}


/* Function plays the video infinitely until any key is pressed.
Input: pointer to head of linked list of frames.
Output: none. */
void playInfinitely(FrameNode* list)
{
	cvNamedWindow("Display window", CV_WINDOW_AUTOSIZE); // create a window
	FrameNode* head = list;
	int imgNum = 1;
	IplImage* image;

	while (1) // infinite loop
	{
		while (list != NULL)
		{
			image = cvLoadImage(list->frame->path, 1);
			IplImage* pGrayImg = cvCreateImage(cvSize(image->width, image->height), image->depth, 1);

			if (!image) // The image is empty - shouldn't happen since we checked already.
			{
				printf("Could not open or find image number %d", imgNum);
			}
			else
			{
				cvShowImage("Display window", image); // display the image
				int key = cvWaitKey(list->frame->duration); 

				if (key != -1) // a key has been pressed
				{
					cvReleaseImage(&image);
					cvDestroyWindow("Display window");
					return;
				}

				list = list->next;
				cvReleaseImage(&image);
			}
			imgNum++;
		}
		list = head; // rewind
	}
}


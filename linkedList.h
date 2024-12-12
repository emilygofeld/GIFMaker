#ifndef LINKEDLISTH
#define LINKEDLISTH

#define FALSE 0
#define TRUE !FALSE
#define _CRT_SECURE_NO_WARNINGS

// Frame struct
typedef struct Frame
{
	char*		name;
	unsigned int	duration;
	char*		path;  
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;


void addFrame(FrameNode** list);
void removeFrame(FrameNode** list, char* frameName);
void changeFrameLoc(FrameNode** list);
void changeFrameLen(FrameNode* list);
void changeAllLen(FrameNode* list, int newLen);
void printFrames(FrameNode* list);
FrameNode* findPrevFrame(FrameNode* list, char* frameName);
int getListLen(FrameNode* first);
FrameNode* createFrameNode(char* name, int dur, char* path);
void freeFrameNode(FrameNode* nodeToFree);
void invertList(FrameNode** list);
void deleteVideo(FrameNode** first);


#endif

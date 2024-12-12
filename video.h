#ifndef VIDEOH
#define VIDEOH

#include "linkedList.h"
#include <stdio.h>

void saveVideo(FrameNode* curr, char* filePath);
FrameNode* loadVideo(char* filePath);

#endif

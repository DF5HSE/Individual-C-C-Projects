#pragma once
#include "bmp.h"

int insert_stego( char *InBMPFileName, char *OutBMPFileName, char *fileNameKey,
                  char *fileNameMsg, char *error );
int extract_stego( char *InBMPFileName, char *fileNameKey, char *fileNameMsg, char *error );

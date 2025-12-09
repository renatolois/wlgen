/*
    program performance probably won't increase with threads,
    maybe it will get worse because threads with locks would
    improve processing, but surreptitiously decrease output
    which is the main limiting factor of the program's
    performance, otherwise it is fully optimized
*/

#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int bruteChars(const long long wl_size, const char* alph, long long outputBuffer_len) {
  if(alph == NULL) return -1;
  const long long alph_size = strlen(alph);

  const char** buffer = malloc(sizeof(char*) * wl_size);
  if(buffer == NULL) {
    printf("failed to allocate memory\n");
    return -1;
  }
  for(int i=0; i< wl_size; i++) {
    buffer[i] = alph;
  }

  long long pos = -1;

  char* outputBuffer = (char*) malloc(sizeof(char) * (wl_size + 1) * outputBuffer_len);
  if(outputBuffer == NULL) {
    printf("failed to allocate memory\n");
    return -1;
  }
  long long int count = 0;
  while(true) {
    
    for(int i=0; i<wl_size; i++) {
      outputBuffer[i + (count * (wl_size + 1))] = *buffer[i];  
    }
    outputBuffer[wl_size + (count * (wl_size + 1))] = '\n';
    count++;
    if(count == outputBuffer_len) {
      fwrite(outputBuffer, wl_size + 1, outputBuffer_len, stdout);
      count = 0;
    }
    
    buffer[0] = alph + ((buffer[0] - alph + 1) % alph_size);
    if(buffer[0] == alph) {
      pos = 1;
      while(pos < wl_size) {
        buffer[pos] = alph + ((buffer[pos] - alph + 1) % alph_size);
        if(buffer[pos] != alph) break; // if buffer[pos] haven't carried
        pos++;
      } 
    }

    if( pos == wl_size) break;
  }

  if(count > 0) {
    fwrite(outputBuffer, wl_size + 1, count, stdout);
  }
  fflush(stdout);

  return 0;
}

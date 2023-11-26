#include "ErrorHandler.h"

static char *error_message;
static char *error_identifyer;

extern void SetErrorIndentfyer(char *errid){
    error_identifyer = errid;
}

extern void SetErrorMessage(char *errmsg){
    error_message = errmsg;
}

extern void malloc_verify(void *ptr){
    if (ptr == NULL) { error_message = MSG_MALLOC_ERROR; RAISE_ERROR(); }
}

extern void SDL_ptr_verify(void *ptr){
    
    if (ptr == NULL) { error_message = (char*)SDL_GetError(); RAISE_ERROR(); }
}

extern void SDL_verify(int err_c){
    if (err_c < 0) { error_message = (char*)SDL_GetError(); RAISE_ERROR(); }
}

extern void RAISE_ERROR(){
    printf("ID: %s\nMess: %s\n", error_identifyer, error_message);
    exit(1);        //Warning! Error handler will not clean up after the program!
}
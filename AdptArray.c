
//
// Created by Beni on 3/17/23.

#include "AdptArray.h"
#include <string.h>
#include <stdlib.h>


typedef struct AdptArray_ { ;
    int Arr_Current_Size;
    PElement *ptrArr;
    COPY_FUNC copyFunc_S;
    DEL_FUNC delFunc_S;
    PRINT_FUNC printFunc_S;
} AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_F, DEL_FUNC delFunc_F, PRINT_FUNC printFunc_F) {
    PAdptArray pAdpArr = (PAdptArray) malloc(sizeof(AdptArray));
    if (pAdpArr == NULL) {
        return NULL;
    }
    pAdpArr->Arr_Current_Size = 0;
    pAdpArr->ptrArr = NULL;
    pAdpArr->copyFunc_S = copyFunc_F;
    pAdpArr->delFunc_S = delFunc_F;
    pAdpArr->printFunc_S = printFunc_F;
    return pAdpArr;
}

void DeleteAdptArray(PAdptArray pAdpArr) {
    if (pAdpArr == NULL)
        return;
    for (int i = 0; i < pAdpArr->Arr_Current_Size; ++i) {
        if (pAdpArr->ptrArr[i] != NULL)
        pAdpArr->delFunc_S((pAdpArr->ptrArr[i]));
    }
    free(pAdpArr->ptrArr);
    free(pAdpArr);

}

Result SetAdptArrayAt(PAdptArray pAdpArr, int i, PElement ptrArr_F) {
    if (pAdpArr == NULL || i < 0) {
        return FAIL;
    }
    PElement *newPElement;
    // Check if the index is out of bounds
    if (i >= pAdpArr->Arr_Current_Size) {
        // Allocate memory for the new array
        newPElement = (PElement *) calloc((i + 1), sizeof(PElement));
        if (newPElement == NULL) {
            return FAIL;
        }
        // Copy the old elements to the new array
        for (int j = 0; j < pAdpArr->Arr_Current_Size; j++) {
            newPElement[j] = pAdpArr->ptrArr[j];
        }
        //free the prev array
        free(pAdpArr->ptrArr);
        // Update Array Size
        pAdpArr->Arr_Current_Size = i + 1;
        // Update the pointer to the new array
        pAdpArr->ptrArr = newPElement;
    }
    // Delete Previous Elem
    if (pAdpArr->ptrArr[i] != NULL) {
        pAdpArr->delFunc_S((pAdpArr->ptrArr[i]));
    }
    //copy the new element to the new array
    pAdpArr->ptrArr[i] = pAdpArr->copyFunc_S(ptrArr_F);
    return SUCCESS;

}

PElement GetAdptArrayAt(PAdptArray pAdpArr, int pos) {
    if (pAdpArr == NULL || pos < 0 || pos >= pAdpArr->Arr_Current_Size || pAdpArr->ptrArr[pos] == NULL) {
        return NULL;
    }
    PElement copyElement = pAdpArr->copyFunc_S(pAdpArr->ptrArr[pos]);
    return copyElement;
}

int GetAdptArraySize(PAdptArray pAdpArr) {
    if (pAdpArr == NULL || pAdpArr->ptrArr == NULL) {
        return -1;
    }
    return pAdpArr->Arr_Current_Size;
}


void PrintDB(PAdptArray pAdpArr) {
    for (int i = 0; i < pAdpArr->Arr_Current_Size; i++) {
        // check if the element is not NULL
        if (pAdpArr->ptrArr[i] != NULL) {
            pAdpArr->printFunc_S(pAdpArr->ptrArr[i]);
        }
    }
}
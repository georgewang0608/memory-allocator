/**
 * UW CSE 351 Spring 2016 Lab 5
 *
 * Extra credit: implementing mm_realloc
 *
 * This requires mm_malloc and mm_free to be working correctly, so
 * don't start on this until you finish mm.c.
 */
#include "mm.c"

// Extra credit.
void* mm_realloc(void* ptr, size_t size) {
  // Write your code here ...
  block_info* current_block;
  void* temp;
  // size_t temp_tag;
  size_t block_size;
  size_t req_size;

  size += WORD_SIZE;
  if (size <= MIN_BLOCK_SIZE) {
    // Make sure we allocate enough space for a block_info in case we
    // free this block (when we free this block, we'll need to use the
    // next pointer, the prev pointer, and the boundary tag).
    req_size = MIN_BLOCK_SIZE;
  } else {
    // Round up for correct alignment
    req_size = ALIGNMENT * ((size + ALIGNMENT - 1) / ALIGNMENT);
  }
  if(ptr == NULL) {
    return mm_malloc(size);
  } else if(size == 0) {
    mm_free(ptr);
    return NULL;
  } else {
    current_block = (block_info*)UNSCALED_POINTER_SUB(ptr, WORD_SIZE);
    block_size = SIZE(current_block -> size_and_tags);
    mm_free(ptr);
    temp = mm_malloc(size);
    if (req_size <= block_size) {
      char* ctemp = (char*)temp;
      char* ccurr = (char*)ptr;
      for(int i = 0; i < req_size - WORD_SIZE; i++ ) {
	ctemp[i] = ccurr[i];
      }
      return (void*)temp;
    } else {
      char* ctemp = (char*)temp;
      char* ccurr = (char*)ptr;
      for(int i = 0; i < block_size - WORD_SIZE; i++ ) {
      ctemp[i] = ccurr[i];
      }
      //(temp -> size_and_tags) = (current_block -> size_and_tags);
      //*current_block = *temp;
      //(temp -> size_and_tags) = temp_tag;
      //mm_free((void*)UNSCALED_POINTER_ADD(temp, WORD_SIZE));
      //mm_free(ptr);
    }
  }
  return (void*)temp;
}

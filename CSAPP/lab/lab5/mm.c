 #include <stdio.h>
 #include <stdlib.h>
 #include <assert.h>
 #include <unistd.h>
 #include <string.h>
 
 #include "mm.h"
 #include "memlib.h"
 
 team_t team = {
    /* Team name */
    "SA25011049",
    /* First member's full name */
    "Li Yuzhe",
    /* First member's email address */
    "lyz1810@mail.ustc.edu.cn",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};
 
 #define ALIGNMENT 8
 #define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~0x7)
 
 #define WSIZE 4       
 #define DSIZE 8       
 #define CHUNKSIZE (1<<12) 

 #define MIN_BLK_SIZE 24 
 
 #define MAX(x, y) ((x) > (y) ? (x) : (y))
 #define MIN(x, y) ((x) < (y) ? (x) : (y))
 
 #define PACK(size, alloc) ((size) | (alloc))
 
 #define GET(p) (*(unsigned int *)(p))
 #define PUT(p, val) (*(unsigned int *)(p) = (val))
 
 #define GET_PTR(p) ((char *)(*(unsigned long *)(p)))
 #define SET_PTR(p, ptr) (*(unsigned long *)(p) = (unsigned long)(ptr))
 
 #define GET_SIZE(p) (GET(p) & ~0x7)
 #define GET_ALLOC(p) (GET(p) & 0x1)
 
 #define HDRP(bp) ((char *)(bp) - WSIZE)
 #define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)
 
 #define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
 #define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))
 
 #define PRED_PTR_ADDR(bp) ((char *)(bp))
 #define SUCC_PTR_ADDR(bp) ((char *)(bp) + DSIZE)
 
 #define GET_PRED(bp) (GET_PTR(PRED_PTR_ADDR(bp)))
 #define GET_SUCC(bp) (GET_PTR(SUCC_PTR_ADDR(bp)))
 
 #define SET_PRED(bp, ptr) (SET_PTR(PRED_PTR_ADDR(bp), ptr))
 #define SET_SUCC(bp, ptr) (SET_PTR(SUCC_PTR_ADDR(bp), ptr))

 #define SEG_LEN 15

 static char *heap_listp = 0;
 static void **segregated_free_lists = 0; 
 static void *extend_heap(size_t words);
 static void *coalesce(void *bp);
 static void *find_fit(size_t asize);
 static void *place(void *bp, size_t asize);
 static void insert_free_block(void *bp);
 static void delete_free_block(void *bp);
 static int get_index(size_t size);
 
 /*
  * mm_init - 初始化分配器
  */
 int mm_init(void)
 {
     // 1. 分配分离链表头指针数组 (SEG_LEN * 8 bytes)
     if ((segregated_free_lists = mem_sbrk(SEG_LEN * sizeof(void *))) == (void *)-1)
         return -1;
 
     // 初始化链表头为 NULL
     for (int i = 0; i < SEG_LEN; i++) {
         segregated_free_lists[i] = NULL;
     }
 
     // 2. 创建初始堆 (4个字: Padding, Prol H, Prol F, Epil H)
     if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void *)-1)
         return -1;
 
     PUT(heap_listp, 0);                            /* Alignment padding */
     PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1)); /* Prologue header */
     PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1)); /* Prologue footer */
     PUT(heap_listp + (3 * WSIZE), PACK(0, 1));     /* Epilogue header */
     heap_listp += (2 * WSIZE);
 
     // 3. 扩展堆
     if (extend_heap(CHUNKSIZE) == NULL)
         return -1;
 
     return 0;
 }
 
 /*
  * mm_malloc - 分配块
  */
 void *mm_malloc(size_t size)
 {
     size_t asize;      
     size_t extendsize; 
     char *bp;
 
     if (size == 0) return NULL;
     if (size <= DSIZE + 8)
         asize = MIN_BLK_SIZE;
     else
         asize = DSIZE * ((size + (DSIZE) + (DSIZE - 1)) / DSIZE);
 
     if ((bp = find_fit(asize)) != NULL) {
         return place(bp, asize);
     }
     extendsize = MAX(asize, CHUNKSIZE);
     if ((bp = extend_heap(extendsize)) == NULL)
         return NULL;
 
     return place(bp, asize);
 }
 
 /*
  * mm_free - 释放块
  */
 void mm_free(void *ptr)
 {
     if (ptr == NULL) return;
 
     size_t size = GET_SIZE(HDRP(ptr));
 
     PUT(HDRP(ptr), PACK(size, 0));
     PUT(FTRP(ptr), PACK(size, 0));
 
     coalesce(ptr);
 }
 
 /*
  * mm_realloc - 重新分配
  */
 void *mm_realloc(void *ptr, size_t size)
 {
     if (ptr == NULL) return mm_malloc(size);
     if (size == 0) {
         mm_free(ptr);
         return NULL;
     }
 
     void *newptr;
     size_t copySize;
     size_t oldSize = GET_SIZE(HDRP(ptr));
     size_t asize;
 
     if (size <= DSIZE + 8)
         asize = MIN_BLK_SIZE;
     else
         asize = DSIZE * ((size + (DSIZE) + (DSIZE - 1)) / DSIZE);
 
     if (oldSize == asize) return ptr;
     newptr = mm_malloc(size);
     if (newptr == NULL) return NULL;
 
     copySize = oldSize - DSIZE; 
     if (size < copySize) copySize = size;
     
     memcpy(newptr, ptr, copySize);
     mm_free(ptr);
     return newptr;
 }
 /*
  * extend_heap - 扩展堆
  */
 static void *extend_heap(size_t size)
 {
     char *bp;
     size_t asize;
     asize = ALIGN(size);
     
     if ((long)(bp = mem_sbrk(asize)) == -1)
         return NULL;
     PUT(HDRP(bp), PACK(asize, 0));         
     PUT(FTRP(bp), PACK(asize, 0));         
     PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); 
     return coalesce(bp);
 }
 
 /*
  * coalesce - 合并空闲块
  */
 static void *coalesce(void *bp)
 {
     size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
     size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
     size_t size = GET_SIZE(HDRP(bp));
 
     if (prev_alloc && next_alloc) {            /* Case 1 */
         insert_free_block(bp);
         return bp;
     }
 
     else if (prev_alloc && !next_alloc) {      /* Case 2 */
         void *next_bp = NEXT_BLKP(bp);
         delete_free_block(next_bp); 
         
         size += GET_SIZE(HDRP(next_bp));
         PUT(HDRP(bp), PACK(size, 0));
         PUT(FTRP(bp), PACK(size, 0));
         
         insert_free_block(bp);
     }
 
     else if (!prev_alloc && next_alloc) {      /* Case 3 */
         void *prev_bp = PREV_BLKP(bp);
         delete_free_block(prev_bp); 
         
         size += GET_SIZE(HDRP(prev_bp));
         PUT(FTRP(bp), PACK(size, 0));
         PUT(HDRP(prev_bp), PACK(size, 0));
         
         bp = prev_bp;
         insert_free_block(bp);
     }
 
     else {                                     /* Case 4 */
         void *prev_bp = PREV_BLKP(bp);
         void *next_bp = NEXT_BLKP(bp);
         
         delete_free_block(prev_bp);
         delete_free_block(next_bp);
         
         size += GET_SIZE(HDRP(prev_bp)) + GET_SIZE(HDRP(next_bp));
         PUT(HDRP(prev_bp), PACK(size, 0));
         PUT(FTRP(next_bp), PACK(size, 0));
         
         bp = prev_bp;
         insert_free_block(bp);
     }
     return bp;
 }
 
 /*
  * place - 分割空闲块
  */
 static void *place(void *bp, size_t asize)
 {
     size_t csize = GET_SIZE(HDRP(bp));
     size_t remainder = csize - asize;
     delete_free_block(bp);
     if (remainder >= MIN_BLK_SIZE) {
         
         if (asize > 64) {
              PUT(HDRP(bp), PACK(remainder, 0));
              PUT(FTRP(bp), PACK(remainder, 0));
              insert_free_block(bp); 
              
              void *next_bp = NEXT_BLKP(bp);
              PUT(HDRP(next_bp), PACK(asize, 1));
              PUT(FTRP(next_bp), PACK(asize, 1));
              return next_bp;
         } else {
             PUT(HDRP(bp), PACK(asize, 1));
             PUT(FTRP(bp), PACK(asize, 1));
             
             void *next_bp = NEXT_BLKP(bp);
             PUT(HDRP(next_bp), PACK(remainder, 0));
             PUT(FTRP(next_bp), PACK(remainder, 0));
             insert_free_block(next_bp); 
             return bp;
         }
     } else {
         PUT(HDRP(bp), PACK(csize, 1));
         PUT(FTRP(bp), PACK(csize, 1));
         return bp;
     }
 }
 
 /*********************************************************
  * 链表操作 (适配 64位)
  ********************************************************/
 
 /*
  * get_index - 计算大小类索引
  */
 static int get_index(size_t size)
 {
     int list_num = 0;
     if (size <= 24) return 0;
     
     size = size >> 5; 
     while (size > 0 && list_num < SEG_LEN - 1) {
         size >>= 1;
         list_num++;
     }
     return list_num;
 }
 
 /*
  * insert_free_block - 按地址顺序插入
  */
 static void insert_free_block(void *bp)
 {
     int index = get_index(GET_SIZE(HDRP(bp)));
     void *search_ptr = segregated_free_lists[index];
     void *prev_ptr = NULL;
     while (search_ptr != NULL && search_ptr < bp) {
         prev_ptr = search_ptr;
         search_ptr = GET_SUCC(search_ptr);
     }
     SET_SUCC(bp, search_ptr);
     SET_PRED(bp, prev_ptr);
 
     if (prev_ptr != NULL) {
         SET_SUCC(prev_ptr, bp);
     } else {
         segregated_free_lists[index] = bp;
     }
 
     if (search_ptr != NULL) {
         SET_PRED(search_ptr, bp);
     }
 }
 
 /*
  * delete_free_block - 从链表删除
  */
 static void delete_free_block(void *bp)
 {
     int index = get_index(GET_SIZE(HDRP(bp)));
     void *prev_ptr = GET_PRED(bp);
     void *succ_ptr = GET_SUCC(bp);
 
     if (prev_ptr == NULL) {
         segregated_free_lists[index] = succ_ptr;
     } else {
         SET_SUCC(prev_ptr, succ_ptr);
     }
 
     if (succ_ptr != NULL) {
         SET_PRED(succ_ptr, prev_ptr);
     }
     
     SET_SUCC(bp, NULL);
     SET_PRED(bp, NULL);
 }
 
 /*
  * find_fit - 首次适配
  */
 static void *find_fit(size_t asize)
 {
     int index = get_index(asize);
     void *bp;
 
     for (int i = index; i < SEG_LEN; i++) {
         bp = segregated_free_lists[i];
         while (bp != NULL) {
             if (GET_SIZE(HDRP(bp)) >= asize) {
                 return bp;
             }
             bp = GET_SUCC(bp);
         }
     }
     return NULL;
 }
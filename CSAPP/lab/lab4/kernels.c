/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include "defs.h"
 
 /* 
  * Please fill in the following team struct 
  */
 team_t team = {
     "OptimizationTeam",   /* Team name */
 
     "Student Name",       /* First member full name */
     "student@univ.edu",   /* First member email address */
 
     "",                   /* Second member full name (leave blank if none) */
     ""                    /* Second member email addr (leave blank if none) */
 };
 
 /***************
  * ROTATE KERNEL
  ***************/
 
 /******************************************************
  * Your different versions of the rotate kernel go here
  ******************************************************/
 
 /* 
  * naive_rotate - The naive baseline version of rotate 
  */
 char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
 void naive_rotate(int dim, pixel *src, pixel *dst) 
 {
     int i, j;
 
     for (i = 0; i < dim; i++)
     for (j = 0; j < dim; j++)
         dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
 }
 
 /* 
  * rotate - Your current working version of rotate
  * IMPORTANT: This is the version you will be graded on
  * 
  * Optimization: Blocking (Tiling)
  * Block size 16 or 32 is usually optimal for L1 Cache.
  * We use 16x16 blocks here combined with loop unrolling.
  */
 char rotate_descr[] = "rotate: Blocked 16x16 implementation";
 void rotate(int dim, pixel *src, pixel *dst) 
 {
     int i, j, ii, jj;
     int bsize = 16; // Block size
 
     for (i = 0; i < dim; i += bsize) {
         for (j = 0; j < dim; j += bsize) {
             // Processing a small block
             // Adding boundary check (ii < dim) just in case dim is not multiple of 16
             for (ii = i; ii < i + bsize && ii < dim; ii++) {
                 for (jj = j; jj < j + bsize && jj < dim; jj++) {
                     dst[RIDX(dim-1-jj, ii, dim)] = src[RIDX(ii, jj, dim)];
                 }
             }
         }
     }
 }


 
 /*********************************************************************
  * register_rotate_functions - Register all of your different versions
  *     of the rotate kernel with the driver by calling the
  *     add_rotate_function() for each test function. When you run the
  *     driver program, it will test and report the performance of each
  *     registered test function.  
  *********************************************************************/
 
 void register_rotate_functions() 
 {
     add_rotate_function(&naive_rotate, naive_rotate_descr);   
     add_rotate_function(&rotate, rotate_descr);   
     /* ... Register additional test functions here */
 }
 
 
 /***************
  * SMOOTH KERNEL
  **************/
 
 /***************************************************************
  * Various typedefs and helper functions for the smooth function
  * You may modify these any way you like.
  **************************************************************/
 
 /* A struct used to compute averaged pixel value */
 typedef struct {
     int red;
     int green;
     int blue;
     int num;
 } pixel_sum;
 
 /* Compute min and max of two integers, respectively */
 static int min(int a, int b) { return (a < b ? a : b); }
 static int max(int a, int b) { return (a > b ? a : b); }
 
 /* 
  * initialize_pixel_sum - Initializes all fields of sum to 0 
  */
 static void initialize_pixel_sum(pixel_sum *sum) 
 {
     sum->red = sum->green = sum->blue = 0;
     sum->num = 0;
     return;
 }
 
 /* 
  * accumulate_sum - Accumulates field values of p in corresponding 
  * fields of sum 
  */
 static void accumulate_sum(pixel_sum *sum, pixel p) 
 {
     sum->red += (int) p.red;
     sum->green += (int) p.green;
     sum->blue += (int) p.blue;
     sum->num++;
     return;
 }
 
 /* 
  * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
  */
 static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
 {
     current_pixel->red = (unsigned short) (sum.red/sum.num);
     current_pixel->green = (unsigned short) (sum.green/sum.num);
     current_pixel->blue = (unsigned short) (sum.blue/sum.num);
     return;
 }
 
 /* 
  * avg - Returns averaged pixel value at (i,j) 
  */
 static pixel avg(int dim, int i, int j, pixel *src) 
 {
     int ii, jj;
     pixel_sum sum;
     pixel current_pixel;
 
     initialize_pixel_sum(&sum);
     for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
     for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
         accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
 
     assign_sum_to_pixel(&current_pixel, sum);
     return current_pixel;
 }
 
 /******************************************************
  * Your different versions of the smooth kernel go here
  ******************************************************/
 
 /*
  * naive_smooth - The naive baseline version of smooth 
  */
 char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
 void naive_smooth(int dim, pixel *src, pixel *dst) 
 {
     int i, j;
 
     for (i = 0; i < dim; i++)
     for (j = 0; j < dim; j++)
         dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
 }
 
 /*
  * smooth - Your current working version of smooth. 
  * IMPORTANT: This is the version you will be graded on
  * 
  * Optimization: Removed function calls, separated body from boundaries.
  */
 char smooth_descr[] = "smooth: Optimized with boundary separation";
 void smooth(int dim, pixel *src, pixel *dst) 
 {
     int i, j;
     int dim0 = dim;
     int dim1 = dim - 1;
     int dim2 = dim - 2;
     
     // 1. Handle the main body (Inner square)
     // No boundary checks needed here, always 9 neighbors.
     for (i = 1; i < dim1; i++) {
         for (j = 1; j < dim1; j++) {
             int r = 0, g = 0, b = 0;
             int idx;
             
             // Row i-1
             idx = RIDX(i-1, j-1, dim);
             r += src[idx].red; g += src[idx].green; b += src[idx].blue;
             r += src[idx+1].red; g += src[idx+1].green; b += src[idx+1].blue;
             r += src[idx+2].red; g += src[idx+2].green; b += src[idx+2].blue;
             
             // Row i
             idx = RIDX(i, j-1, dim);
             r += src[idx].red; g += src[idx].green; b += src[idx].blue;
             r += src[idx+1].red; g += src[idx+1].green; b += src[idx+1].blue;
             r += src[idx+2].red; g += src[idx+2].green; b += src[idx+2].blue;
             
             // Row i+1
             idx = RIDX(i+1, j-1, dim);
             r += src[idx].red; g += src[idx].green; b += src[idx].blue;
             r += src[idx+1].red; g += src[idx+1].green; b += src[idx+1].blue;
             r += src[idx+2].red; g += src[idx+2].green; b += src[idx+2].blue;
             
             dst[RIDX(i, j, dim)].red = (unsigned short)(r / 9);
             dst[RIDX(i, j, dim)].green = (unsigned short)(g / 9);
             dst[RIDX(i, j, dim)].blue = (unsigned short)(b / 9);
         }
     }
 
     // 2. Handle 4 Corners
     
     // Top-Left (0,0) -> 4 neighbors
     dst[0].red = (src[0].red + src[1].red + src[dim].red + src[dim+1].red) >> 2;
     dst[0].green = (src[0].green + src[1].green + src[dim].green + src[dim+1].green) >> 2;
     dst[0].blue = (src[0].blue + src[1].blue + src[dim].blue + src[dim+1].blue) >> 2;
 
     // Top-Right (0, dim-1) -> 4 neighbors
     i = 0; j = dim1;
     dst[RIDX(i, j, dim)].red = (src[RIDX(0, dim2, dim)].red + src[RIDX(0, dim1, dim)].red + 
                                 src[RIDX(1, dim2, dim)].red + src[RIDX(1, dim1, dim)].red) >> 2;
     dst[RIDX(i, j, dim)].green = (src[RIDX(0, dim2, dim)].green + src[RIDX(0, dim1, dim)].green + 
                                   src[RIDX(1, dim2, dim)].green + src[RIDX(1, dim1, dim)].green) >> 2;
     dst[RIDX(i, j, dim)].blue = (src[RIDX(0, dim2, dim)].blue + src[RIDX(0, dim1, dim)].blue + 
                                  src[RIDX(1, dim2, dim)].blue + src[RIDX(1, dim1, dim)].blue) >> 2;
 
     // Bottom-Left (dim-1, 0) -> 4 neighbors
     i = dim1; j = 0;
     dst[RIDX(i, j, dim)].red = (src[RIDX(dim2, 0, dim)].red + src[RIDX(dim2, 1, dim)].red + 
                                 src[RIDX(dim1, 0, dim)].red + src[RIDX(dim1, 1, dim)].red) >> 2;
     dst[RIDX(i, j, dim)].green = (src[RIDX(dim2, 0, dim)].green + src[RIDX(dim2, 1, dim)].green + 
                                   src[RIDX(dim1, 0, dim)].green + src[RIDX(dim1, 1, dim)].green) >> 2;
     dst[RIDX(i, j, dim)].blue = (src[RIDX(dim2, 0, dim)].blue + src[RIDX(dim2, 1, dim)].blue + 
                                  src[RIDX(dim1, 0, dim)].blue + src[RIDX(dim1, 1, dim)].blue) >> 2;
 
     // Bottom-Right (dim-1, dim-1) -> 4 neighbors
     i = dim1; j = dim1;
     dst[RIDX(i, j, dim)].red = (src[RIDX(dim2, dim2, dim)].red + src[RIDX(dim2, dim1, dim)].red + 
                                 src[RIDX(dim1, dim2, dim)].red + src[RIDX(dim1, dim1, dim)].red) >> 2;
     dst[RIDX(i, j, dim)].green = (src[RIDX(dim2, dim2, dim)].green + src[RIDX(dim2, dim1, dim)].green + 
                                   src[RIDX(dim1, dim2, dim)].green + src[RIDX(dim1, dim1, dim)].green) >> 2;
     dst[RIDX(i, j, dim)].blue = (src[RIDX(dim2, dim2, dim)].blue + src[RIDX(dim2, dim1, dim)].blue + 
                                  src[RIDX(dim1, dim2, dim)].blue + src[RIDX(dim1, dim1, dim)].blue) >> 2;
 
     // 3. Handle 4 Edges (Top, Bottom, Left, Right) - 6 neighbors each
     
     // Top Edge (Row 0, cols 1 to dim-2)
     for (j = 1; j < dim1; j++) {
         dst[j].red = (src[j-1].red + src[j].red + src[j+1].red + 
                       src[dim+j-1].red + src[dim+j].red + src[dim+j+1].red) / 6;
         dst[j].green = (src[j-1].green + src[j].green + src[j+1].green + 
                         src[dim+j-1].green + src[dim+j].green + src[dim+j+1].green) / 6;
         dst[j].blue = (src[j-1].blue + src[j].blue + src[j+1].blue + 
                        src[dim+j-1].blue + src[dim+j].blue + src[dim+j+1].blue) / 6;
     }
 
     // Bottom Edge (Row dim-1, cols 1 to dim-2)
     for (j = 1; j < dim1; j++) {
         int idx = RIDX(dim1, j, dim);
         int idx_up = RIDX(dim2, j, dim);
         dst[idx].red = (src[idx_up-1].red + src[idx_up].red + src[idx_up+1].red + 
                         src[idx-1].red + src[idx].red + src[idx+1].red) / 6;
         dst[idx].green = (src[idx_up-1].green + src[idx_up].green + src[idx_up+1].green + 
                           src[idx-1].green + src[idx].green + src[idx+1].green) / 6;
         dst[idx].blue = (src[idx_up-1].blue + src[idx_up].blue + src[idx_up+1].blue + 
                          src[idx-1].blue + src[idx].blue + src[idx+1].blue) / 6;
     }
 
     // Left Edge (Col 0, rows 1 to dim-2)
     for (i = 1; i < dim1; i++) {
         int idx = RIDX(i, 0, dim);
         dst[idx].red = (src[idx-dim].red + src[idx-dim+1].red + 
                         src[idx].red + src[idx+1].red + 
                         src[idx+dim].red + src[idx+dim+1].red) / 6;
         dst[idx].green = (src[idx-dim].green + src[idx-dim+1].green + 
                           src[idx].green + src[idx+1].green + 
                           src[idx+dim].green + src[idx+dim+1].green) / 6;
         dst[idx].blue = (src[idx-dim].blue + src[idx-dim+1].blue + 
                          src[idx].blue + src[idx+1].blue + 
                          src[idx+dim].blue + src[idx+dim+1].blue) / 6;
     }
 
     // Right Edge (Col dim-1, rows 1 to dim-2)
     for (i = 1; i < dim1; i++) {
         int idx = RIDX(i, dim1, dim);
         dst[idx].red = (src[idx-dim-1].red + src[idx-dim].red + 
                         src[idx-1].red + src[idx].red + 
                         src[idx+dim-1].red + src[idx+dim].red) / 6;
         dst[idx].green = (src[idx-dim-1].green + src[idx-dim].green + 
                           src[idx-1].green + src[idx].green + 
                           src[idx+dim-1].green + src[idx+dim].green) / 6;
         dst[idx].blue = (src[idx-dim-1].blue + src[idx-dim].blue + 
                          src[idx-1].blue + src[idx].blue + 
                          src[idx+dim-1].blue + src[idx+dim].blue) / 6;
     }
 }
 
 
 /********************************************************************* 
  * register_smooth_functions - Register all of your different versions
  *     of the smooth kernel with the driver by calling the
  *     add_smooth_function() for each test function.  When you run the
  *     driver program, it will test and report the performance of each
  *     registered test function.  
  *********************************************************************/
 
 void register_smooth_functions() {
     add_smooth_function(&smooth, smooth_descr);
     add_smooth_function(&naive_smooth, naive_smooth_descr);
     /* ... Register additional test functions here */
 }
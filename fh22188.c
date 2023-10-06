#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>

struct matrix
{
    int numrow;
    int numcol;
    int *elements;
};
typedef struct matrix Matrix;

/*
Print an image to the console. 
image: an array stores the flattened image stored in row major order.
Height: the height of the image.
Width: the width of the image.
*/
void image2char(int image[], int Height, int Width){
    
}


/*
Read a matrix from file. Don't change it!
filename: the file that contains the matrix.
return: a matrix structure containing the matrix.
*/
Matrix read_matrix(char *filename)
{
    FILE *f = fopen(filename, "rb");
    // read int variables to the file.
    int numrow = getw(f);
    int numcol = getw(f);
    Matrix M = {numrow, numcol, calloc(numrow * numcol, sizeof(int))};

    for (int i = 0; i < M.numrow; i++)
    {
        for (int j = 0; j < M.numcol; j++)
        {
            M.elements[i*numcol + j] = getc(f);
        }
    }

    fclose(f);
    return M;
}

/*
Retrieve an element from a matrix.
M: the matrix.
i,j: the row and column of the element.
return: the element at row i and column j.
*/

/*int idx(Matrix M, int i, int j){
    return (i) * M.numcol + (j);
}*/

int get_elem(Matrix M, int i, int j){
    return M.elements[M.numcol *i +j ];
}

/*
Assign value to an element in a matrix.
M: the matrix.
i,j: the row and column of the element.
value: the value to be assigned.
*/
void set_elem(Matrix M, int i, int j, int value){
    M.elements[M.numcol * i + j] = value;
}


/*
Compute the pairwise squared distance of the i-th row of M1 and the j-th row of M2.
M1: the first matrix.
M2: the second matrix.
return: a matrix D where D_ij is the squared distance between the i-th row of M1 and the j-th row of M2.
*/
void pairwise_dist2(Matrix M1, Matrix M2, Matrix D){
    for(int i = 0; i < M1.numrow; i++ ){  //iterates over the rows of the first matrix
        for(int j = 0; j < M2.numrow; j++ ){ //iterates over the rows of the second matrix
            int value = 0; // sets value to 0
            for ( int k = 0; k < 784; k++ ){
                value += pow( get_elem(M1,i,k)-get_elem(M2,j,k) , 2 ); // computes dist2(a,b)
            }set_elem(D, i, j, value); //sets each value of dij to the appropriate value
        } 
    }
}



/*
Find the index of the minimum element in an array. 
a: the array.
len: the length of the array.
return: the index of the minimum element in the array.
example: [1,2,3,4,5] -> 0
         [5,4,3,2,1] -> 4
*/
int find_min_index(int a[], int len){
    int min =  0; // picks an inital value for the min
    for (int i = 0; i < len; i++){
        if( a[i] < a[min]){ // compares the value of min to each element of the array
            min = i;  // if it is smaller it changes the minimum value
        }
    }return min;
}



/*
Find the indices of 5 minimum elements in an array.
a: the array.
len: the length of the array.
return: an array of 5 integers containing the indices of the 5 minimum elements in a.
example: [1,2,33,4,5,23,6] -> [0,1,3,4,6]
*/
void minimum5(int a[], int len, int indices[]){
    for( int i = 0; i < 5; i++){ // repeats the for instructions 5 times
        indices[i] = find_min_index(a, len); // sets each element of indices to the positon of the  5 lowest elements of the input array
        //int idx = i;
        a[indices[i]] = INT_MAX; // this ensures the element will be skipped in the next run of the loop 
    }
}



void main(){
    // 10% for submitting the correct code.
    Matrix X = read_matrix("./X.matrix");
    printf("N: %d, M: %d\n", X.numrow, (int) sqrt(X.numcol));   

    Matrix T = read_matrix("./T.matrix");
    printf("L: %d\n", T.numrow);

    Matrix Y = read_matrix("./Y.matrix");
    int s = 0;
    for (int i = 0; i < Y.numrow; i++) {
        if(Y.elements[i*Y.numcol + 0] == 1)
            s++;
    }
    printf("Number of 1 in the training set: %d\n", s);

    //TODO: construct the matrix D, where D_ij is the squared distance between the i-th row of T and the j-th row of X.
    // 40% of the total score.
    // 15% for the helper functions.
    // 25% for the pairwise_dist2 function.

    //constructs matrix D AND initalizes it with the set values
    Matrix D;
        D.numrow = 100;  
        D.numcol = 1987; 
        D.elements = malloc(198700 * sizeof(int));

    pairwise_dist2(T,X,D); //populates D matrix
    
    for(int i=0; i< T.numrow; i++){ // replace 0 with T.numrow.
        printf("The %d-th testing image:\n", i);
        //TODO: visualise the i-th testing image, optional. 

        //TODO: find the indices of the 5 smallest elements in the i-th row of D.
        // 15% of the total score.
        
        
        int indices[5] = {}; //creates an array with length 5
        int *Dij = malloc(D.numcol * sizeof(int)); //creates an empty array as minimumu 5 input is an array and not a matrix (D) which gave me an error

        minimum5(Dij, D.numcol, indices);

        int i = 0; 
        int labels[5] = {}; // creates an array with length 5
        for(int k = 0; k < 5; k++){ //repeats for alll rows of D
            labels[k] = Y.elements[indices[k]]; //Assigns thevaylueof Yindices[k],0 to the k-th element in labels
            if (labels[k] == 1){
                i++; //stores the number of 1's in labels
            }
        }

        printf("The %d-th testing image is classified as", i);
        //TODO: print out your prediction.
        // 15% of the total score.


        if ( i >= 3){ //condition for prediction
            printf(" 1 ");
        }else{
            printf(" not 1 ");
        }

        printf("\n");
        printf("----------------------------------------\n");

        free(Dij);
    }

    // did you free the memory that allocated in your program?
    // - 5% for every missing free.
    free(X.elements);
    free(T.elements);
    free(Y.elements);
    free(D.elements);
}
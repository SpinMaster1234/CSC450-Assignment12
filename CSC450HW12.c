#include <stdlib.h>
#include <stdio.h>

unsigned int bitsToInt(char * bits);

int main(){
    FILE * inputStream, * outputStream;
    inputStream = fopen("darthvador.bmp", "rb");
    outputStream = fopen("mirrored.bmp", "wb");

    char intBuf[4];

    //read the width, height and size from header;
    int sizePos, heightPos, widthPos;
    sizePos = 2;
    heightPos = 22;
    widthPos = 18;
    char * image;
    unsigned int size, height, width;

    //move the file pointer to the pos
    fseek(inputStream, sizePos, SEEK_SET);
    //read 4 bytes out into buf;
    fread(intBuf, 4, 1, inputStream);
    size = bitsToInt(intBuf);

    fseek(inputStream, heightPos, SEEK_SET);
    fread(intBuf, 4, 1, inputStream);
    height = bitsToInt(intBuf);

    fseek(inputStream, widthPos, SEEK_SET);
    fread(intBuf, 4, 1, inputStream);
    width = bitsToInt(intBuf);

    printf("File size is %d bits\n", size);
    printf("File width is %d bits\n", width);
    printf("File height is %d bits\n", height);

    image=malloc(3 * 4200);
    fseek(inputStream, 0, SEEK_SET);
    fread(image,54, 1,inputStream);
    fwrite(image,54,1,outputStream);

    char * row;
    row=malloc(3 * width);

    int pos = 54;
    int x;
    int y;

    for(y=0,y<height; y++){
        fread(row,3,width,inputStream);
        for(x=0;x<width;x++){

            int i;
            for(i=0;i<3;i++){
                int from=x*3+i;
                int to=(width-x-1)*3+i;
                image[to]=row[from];
            }

        }
        fwrite(image,3,width,outputStream);
    }

    fclose(inputStream);
    fclose(outputStream);

    return 0;
}


unsigned int bitsToInt(char * bits){ //argument is 8 bit * 4 array

    return (unsigned char)bits[0] | ((unsigned char)bits[1] << 8) | ((unsigned char)bits[2] << 16) | ((unsigned char)bits[3] << 24);
}
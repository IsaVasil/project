#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data{
    int red;
    int green;
    int blue;
}data1;

typedef struct PPM_Image_Buffer{
     data1* data;
    int rown,coln;
}PPM_Image_Buffer;


int read_ppm_colorbitmap(char* filename,PPM_Image_Buffer* buff){
FILE* f;
if((f=fopen(filename,"r"))==NULL){
    printf("Error could not open file");
    exit(-1);
}
fseek(f,3,SEEK_SET);
fscanf(f,"%d",&buff->coln);
fscanf(f,"%d",&buff->rown);
int sizeofpicture = buff->coln*buff->rown;
buff->data=malloc(sizeof(int)*3*sizeofpicture);

if(buff->data!=NULL){
    printf("no created data");
}
int row=buff->rown;
int colon=buff->coln;
int position=0;
while(row!=0){
    ++position;
    row/=10;
}
while(colon!=0){
    ++position;
    colon/=10;
}
fseek(f,8+position,SEEK_SET);
for(int i =0;i<sizeofpicture;i++){
fscanf(f,"%d",&(((buff->data)+i)->red));
fscanf(f,"%d",&(((buff->data)+i)->green));
fscanf(f,"%d",&(((buff->data)+i)->blue));
}
fclose(f);
}

int write_ppm_color_bitmap(char *filename,PPM_Image_Buffer* buff){
FILE* f;
if((f=fopen(filename,"w+"))==NULL){
    printf("Error could not open file");
    exit(-1);
}
int sizeofpicture=buff->coln*buff->rown;
fputs("p3\n",f);
fprintf(f,"%d %d\n",buff->coln,buff->rown);
fputs("255\n",f);
for(int i=0;i<sizeofpicture;i++){
    fprintf(f,"%d",((buff->data)+i)->red);
    fprintf(f,"%d",((buff->data)+i)->red);
    fprintf(f,"%d",((buff->data)+i)->red);
}
fclose(f);
}
void filter_color_component(PPM_Image_Buffer* buf,unsigned int rgb_mask){
    int sizeofpicture= buf->coln*buf->rown;
    for(int i =0; i<sizeofpicture;i++){
    if((rgb_mask & (1<<0))==0){
        ((buf->data)+i)->red=0;
    }
    if((rgb_mask & (1<<1))==0){
        ((buf->data)+i)->green=0;
    }
    if((rgb_mask & (1<<2))==0){
        ((buf->data)+i)->blue=0;
    }
    }
}
void convert_to_grayscale(PPM_Image_Buffer* buff){
    int sizeofpicture = buff->coln *buff ->rown;
    int i=0;
    do{
        i++;
        (buff->data+i)->red=(buff->data+i)->red*0.3+(buff->data+i)->green*0.59+(buff->data+i)->blue*0.11;
        (buff->data+i)->green=(buff->data+i)->red*0.3+(buff->data+i)->green*0.59+(buff->data+i)->blue*0.11;
        (buff->data+i)->red=(buff->data+i)->red*0.3+(buff->data+i)->green*0.59+(buff->data+i)->blue*0.11;
        if(((buff->data+i)->red!=(buff->data+i)->green)||((buff->data+i)->red!=(buff->data+i)->green)||((buff->data+i)->red!=(buff->data+i)->green)){
        --i;
    
    }}while(i<sizeofpicture);
    
}

int main(int argc,char *argv[]){
PPM_Image_Buffer* image =malloc(sizeof(PPM_Image_Buffer));
read_ppm_colorbitmap(argv[1],image);
//int opt,g;
for(int i=0;i<argc;i++){
    if(((strcmp(argv[i], "-f"))==0)&&(i+1)<argc){
        if((strcmp(argv[i+1],"r"))==0){
            filter_color_component(image,1);
        }
        else if((strcmp(argv[i+1],"g"))==0){
            filter_color_component(image,2);
        }
        else if(((strcmp(argv[i+1],"rg"))==0) || ((strcmp(argv[i+1],"gr"))==0) ){
            filter_color_component(image,3);
        }
        else if((strcmp(argv[i+1],"b"))==0){
            filter_color_component(image,4);
        }
        else if(((strcmp(argv[i+1],"rb"))==0) || ((strcmp(argv[i+1],"br"))==0)){
            filter_color_component(image,5);
        }
        else if(((strcmp(argv[i+1],"bg"))==0) || ((strcmp(argv[i+1],"gb"))==0)){
            filter_color_component(image,6);
        }
        else if(((strcmp(argv[i+1],"rgb"))==0) || ((strcmp(argv[i+1],"rbg"))==0) ||((strcmp(argv[i+1],"bgr"))==0) ||((strcmp(argv[i+1],"brg"))==0) || ((strcmp(argv[i+1],"gbr"))==0)|| ((strcmp(argv[i+1],"grb"))==0)){
            filter_color_component(image,7);
        }
        else{
            printf("invalid operation");
        }
    }
}

    return 0;
}
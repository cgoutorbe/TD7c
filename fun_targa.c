#include <stdlib.h>
#include <stdio.h>
#include "fun_targa.h"
#include "mem_targa.h"



#define TAILLE_MAX


int readImage(image_desc *pDesc,targa_header *pHeader,char * fName){
	
	char filename[] = "ensta_Tattoo_nb.tga";
	char text[18];
	FILE *fileImage = NULL;
	printf("hello3\n"); 
	
	fileImage =fopen("ensta_Tatoo_nb.tga","r");
	printf("hello4 %d \n",sizeof(*pHeader));
	fread(pHeader,sizeof(*pHeader),1, fileImage);
	//fread(text,18,1,fileImage);

	
	uint16_t width = pHeader->width;
	uint16_t height = pHeader->height;
        printf("width: %d\n",width);
        printf("height: %d\n",height);	
	mallocImage(pDesc,width,height);
	printf("hello\n");	
	for(int i=0;i<(width*height);i++){

		      	
	//	printf("%d\n",i);	
		fread(&(pDesc->pBlue[i]),sizeof(uint8_t),1,fileImage);
		fread(&(pDesc->pGreen[i]),sizeof(uint8_t),1,fileImage);
		fread(&(pDesc->pRed[i]),sizeof(uint8_t),1,fileImage);

	}
	fclose(fileImage);
	writeImage(*pDesc,*pHeader,fName);
	return 0;
}

int mallocImage(image_desc *pDesc, uint16_t width, uint16_t height){

	pDesc->pRed = malloc(sizeof(uint8_t)*width*height);
        pDesc->pBlue = malloc(sizeof(uint8_t)*width*height);
        pDesc->pGreen = malloc(sizeof(uint8_t)*width*height);
	//printf("malloc créé  -> %d\n",sizeof(uint8_t)*width*height);
	return 0;
}

int writeImage(image_desc desc, targa_header head, char* fName){
	FILE *nouvelleImage = NULL;
	nouvelleImage = fopen("nouvelleImage.tga","wb");
	fwrite(&head,sizeof(head),1,nouvelleImage);
	printf("%d\n",head.height*head.width);
	for(int i =0;i<head.height*head.width;i++){

	//printf("%d\n",i);

	fwrite(&(desc.pBlue[i]),sizeof(uint8_t),1,nouvelleImage);
	fwrite(&(desc.pGreen[i]),sizeof(uint8_t),1,nouvelleImage);
	fwrite(&(desc.pRed[i]),sizeof(uint8_t),1,nouvelleImage);



	}

	printf("nouvelle IMAGE créée\n");
	freeImage(&desc);
	fclose(nouvelleImage);
	return 0;

}

void freeImage(image_desc *pdesc){

	free(pdesc->pBlue);
	free(pdesc->pRed);
	free(pdesc->pGreen);
}


void main(){
	printf("Salut Charlie\n");
	image_desc  Desc;
	image_desc *pDesc; 
	pDesc = &Desc;

	char fName;
	char *pfName;
	pfName= &fName;
	
	
	targa_header  Header;
	targa_header *pHeader;
	pHeader = &Header;
	printf("hello2\n");	
	readImage(pDesc,pHeader,pfName);
	
}




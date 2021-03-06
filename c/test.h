#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Vector
{
	float x;
	float y;
	float z;
};

struct Vector *add(struct Vector v1, struct Vector v2){
	struct Vector *temp = malloc(sizeof *temp);
	temp->x = v1.x + v2.x;
	temp->y = v1.y + v2.y;
	temp->z = v1.z + v2.z;
	return temp;
}

struct Vector *sub(struct Vector v1, struct Vector v2){
	struct Vector *temp = malloc(sizeof *temp);
	temp->x = v1.x - v2.x;
	temp->y = v1.y - v2.y;
	temp->z = v1.z - v2.z;
	return temp;
}

struct Vector *mul(struct Vector v1, struct Vector v2){
	struct Vector *temp = malloc(sizeof *temp);
	temp->x = v1.x * v2.x;
	temp->y = v1.y * v2.y;
	temp->z = v1.z * v2.z;
	return temp;
}

float magnitude(struct Vector v1){
	float mag = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
	// printf("%f \n", mag);
	return mag;
}

struct Vector *normalize(struct Vector v1){
	float mag = magnitude(v1);
	struct Vector *temp = malloc(sizeof *temp);
	temp->x = v1.x/mag;
	temp->y = v1.y/mag;
	temp->z = v1.z/mag;
	return temp;
}

void print(struct Vector *v1){
	printf("%f, %f, %f\n", v1->x, v1->y, v1->z);
}

struct Vector *from_hex(char * hex_color){
	char* x = malloc(2);
	strncpy(x, hex_color+1, 2);
	char* y = malloc(2);
	strncpy(y, hex_color+3, 2);
	char* z = malloc(2);
	strncpy(z, hex_color+5, 2);

	float x1 = strtol(x, (char **)NULL, 16)/255.0;
	float y1 = strtol(y, (char **)NULL, 16)/255.0;
	float z1 = strtol(z, (char **)NULL, 16)/255.0;
	free(x);
	free(y);
	free(z);

	struct Vector *temp = malloc(sizeof *temp);
	temp->x = x1;
	temp->y = y1;
	temp->z = z1;

	return temp;
}
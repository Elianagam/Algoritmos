#include "bloom_filter.h"
#include <stdlib.h>
#define TAM_VECTOR 4115226 //Un numero arbitrario. Lo podemos cambiar luego.

struct bloom_filter {
	size_t* arreglo1; 
	hash_func_t funcion_hash1;
	size_t* arreglo2;
	hash_func_t funcion_hash2;
	size_t* arreglo3; 
	hash_func_t funcion_hash3;
};

size_t minimo(size_t a, size_t b, size_t c) {
	size_t menor;
	if (a < b) menor = a; 
	else menor = b;
	
	if (menor < c) return menor;
	return c;
}
	
	
bloom_filter_t* bloom_filter_crear(hash_func_t funcion1, hash_func_t funcion2, hash_func_t funcion3) {
	bloom_filter_t* filtro = malloc(sizeof(bloom_filter_t));
	if (filtro == NULL) return NULL;

	//Calloc. Asi todos los elementos son iniciados con 0.
	filtro->arreglo1 = calloc(TAM_VECTOR,sizeof(size_t));
	if (filtro->arreglo1 == NULL) {
		free(filtro);
		return NULL;
	}

	filtro->arreglo2 = calloc(TAM_VECTOR,sizeof(size_t));
	if (filtro->arreglo2 == NULL) {
		free(filtro->arreglo1);
		free(filtro);
		return NULL;
	}
	filtro->arreglo3 = calloc(TAM_VECTOR,sizeof(size_t));
	filtro->arreglo3 = calloc(TAM_VECTOR,sizeof(size_t));
	if (filtro->arreglo3 == NULL) {
		free(filtro->arreglo2);
		free(filtro->arreglo1);
		free(filtro);
		return NULL;
	}
	filtro->tam = MAXIMO;
	filtro->funcion_hash1 = funcion1;
	filtro->funcion_hash2 = funcion2;
	filtro->funcion_hash3 = funcion3;
	
	return filtro;
}

bool bloom_filter_cargar(bloom_filter_t* filtro, const char* clave) {
	if (filtro == NULL || clave == NULL) return false;
	size_t pos2 = filtro->funcion_hash2(clave, TAM_VECTOR);
	filtro->areglo[pos1]++;
	size_t pos2 = filtro->funcion_hash2(clave, TAM_VECTOR);
	filtro->arreglo[pos2]++;
	size_t pos3 = filtro->funcion_hash3(clave, TAM_VECTOR);
	filtro->arreglo[pos3]++;
	return true;
}
/********** PROPONGO QUE GUARDE UN TWEET CON SU CANTIDAD CORRESPONDIENTE,
******* SI EL TWWET YA ESTA LE SUMA 1 A LA CANTIDAD*************
*/

struct tt_nodo{
	char* tweet;
	size_t cant;
}typedef tt_nodo_t;

tt_nodo_t* crear_nodo(const char* clave){
	tt_nodo_t* nodo = malloc(sizeof(tt_nodo_t));
	if (!nodo) return NULL;
	nodo->tweet = clave;
	nodo->cant = 1;
	return nodo;
}

bool bloom_filter_cargar(bloom_filter_t* const char* clave) {
	if (filtro == NULL || clave == NULL) return false;
	
	size_t pos1 = filtro->funcion_hash1(clave, TAM_VECTOR);
	if (filtro->arreglo[pos1] != 0 &&filtro->arreglo[pos1]->tweet = clave) filtro->arreglo[pos1]->cant++;
	else{
		tt_nodo_t* nodo = crear_nodo(clave);
		filtro->arreglo[pos1] = nodo;
	}
	
	size_t pos2 = filtro->funcion_hash2(clave, TAM_VECTOR);
	if (filtro->arreglo[pos2] != 0 && filtro->arreglo[pos2]->tweet = clave) filtro->arreglo[pos1]->cant++;
	else{
		tt_nodo_t* nodo = crear_nodo(clave);
		filtro->arreglo[pos2] = nodo;
	}

	size_t pos3 = filtro->funcion_hash3(clave, TAM_VECTOR);
	if (filtro->arreglo[pos3] != 0 && filtro->arreglo[pos2]->tweet = clave) filtro->arreglo[pos1]->cant++;
	else{
		tt_nodo_t* nodo = crear_nodo(clave);
		filtro->arreglo[pos3] = nodo;
	}
	return true;
}

//*****************************************************************

size_t bloom_filter_obtener(bloom_filter_t* filtro, const char* clave) {
	if (filtro == NULL || clave == NULL) return 0;
	size_t pos1 = filtro->funcion_hash1(clave, TAM_VECTOR);
	size_t cant1 = filtro->arreglo1[pos1];
	size_t pos2 = filtro->funcion_hash1(clave, TAM_VECTOR);
	size_t cant2 = filtro->arreglo2[pos2];
	size_t pos3 = filtro->funcion_hash1(clave, TAM_VECTOR);
	size_t cant3 = filtro->arreglo1[pos3];
	return minimo(cant1, cant2, cant3);
}

void bloom_filter_destruir(bloom_filter_t* filtro) {
	free(filtro->arreglo1);
	free(filtro->arreglo2);
	free(filtro->arreglo3);
	
	free(filtro);
}
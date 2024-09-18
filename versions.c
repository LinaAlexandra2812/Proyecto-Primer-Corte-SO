/**
 * @file
 * @brief Implementacion del API de gestion de versiones
 * @author Erwin Meza Vega <emezav@unicauca.edu.co>
 * @copyright MIT License
*/

#include "versions.h"

/**
 * @brief Crea una version en memoria del archivo
 * Valida si el archivo especificado existe y crea su hash
 * @param filename Nombre del archivo
 * @param hash Hash del contenido del archivo
 * @param comment Comentario
 * @param result Nueva version en memoria
 *
 * @return Resultado de la operacion
 */
return_code create_version(char * filename, char * comment, file_version * result);

/**
 * @brief Función para inicializar el sistema de versionado
 * Crea el directorio .versions y el archivo versions.db si no existen.
 */
void init_versioning_system();

/**
 * @brief Obtiene el hash de un archivo.
 * @param filename Nombre del archivo a obtener el hash
 * @param hash Buffer para almacenar el hash (HASH_SIZE)
 * @return Referencia al buffer, NULL si ocurre error
 */
char *get_file_hash(char * filename, char * hash);

/**
 * @brief Verifica si existe una version para un archivo
 *
 * @param filename Nombre del archivo
 * @param hash Hash del contenido
 *
 * @return 1 si la version existe, 0 en caso contrario.
 */
int version_exists(char * filename, char * hash);

/**
 * @brief Copia un archivo
 *
 * @param source Archivo fuente
 * @param destination Destino
 *
 * @return
 */
int copy(char * source, char * destination);

/**
* @brief Almacena un archivo en el repositorio
*
* @param filename Nombre del archivo
* @param hash Hash del archivo: nombre del archivo en el repositorio
*
* @return
*/
int store_file(char * filename, char * hash);

/**
* @brief Almacena un archivo en el repositorio
*
* @param hash Hash del archivo: nombre del archivo en el repositorio
* @param filename Nombre del archivo
*
* @return
*/
int retrieve_file(char * hash, char * filename);

/**
 * @brief Adiciona una nueva version de un archivo.
 *
 * @param filename Nombre del archivo.
 * @param comment Comentario de la version.
 * @param hash Hash del contenido.
 *
 * @return 1 en caso de exito, 0 en caso de error.
 */
int add_new_version(file_version * v);


return_code create_version(char * filename, char * comment, file_version * result){
	struct stat s;

	//Verifica si el archivo existe y es regular
	if(stat(filename, &s) < 0 || !S_ISREG(s.st_mode)){
		perror("El archivo no existe o no es un archivo regular");
		return VERSION_ERROR;
	}

	//Obtener el hash del archivo
	if(!get_file_hash(filename, result->hash)){
		return VERSION_ERROR;
	}

	//Llenar la estructura de la versión
	strncpy(result->filename, filename, PATH_MAX);
	strncpy(result->comment, comment, COMMENT_SIZE);

	return VERSION_CREATED;
}

return_code add(char * filename, char * comment) {

	file_version v;

	// 1. Crea la nueva version en memoria
	// Si la operacion falla, retorna VERSION_ERROR
	// create_version(filename, comment, &v)

	// 2. Verifica si ya existe una version con el mismo hash
	// Retorna VERSION_ALREADY_EXISTS si ya existe
	//version_exists(filename, v.hash)

	// 3. Almacena el archivo en el repositorio.
	// El nombre del archivo dentro del repositorio es su hash (sin extension)
	// Retorna VERSION_ERROR si la operacion falla
	//store_file(filename, v.hash)

	// 4. Agrega un nuevo registro al archivo versions.db
	// Si no puede adicionar el registro, se debe borrar el archivo almacenado en el paso anterior
	// Si la operacion falla, retorna VERSION_ERROR
	//add_new_version(&v)

	// Si la operacion es exitosa, retorna VERSION_ADDED
	return VERSION_ERROR;
}

void init_versioning_system(){
	struct stat st = {0};

	//Verifica si el directorio existe
	if(stat(VERSIONS_DIR, &st)==-1){
		if(mkdir(VERSIONS_DIR, 0700) != 0){
			perror("Error al crear el directorio .versions");
			exit(EXIT_FAILURE);
		}
		printf("Directorio '.versions' creado.\n");
	}
	FILE *db = fopen(VERSIONS_DB_PATH, "a");
	if(!db){
		perror("Error al crear el archivo versions.db");
		exit(EXIT_FAILURE);
	}
	fclose(db);
	printf("Archivo 'veriosn.db' creado\n");
}

int add_new_version(file_version * v) {
	FILE * fp;

	// Adiciona un nuevo registro (estructura) al archivo versions.db
	return 0;
}


void list(char * filename) {
	//Abre el la base de datos de versiones (versions.db)
	//Muestra los registros cuyo nombre coincide con filename.
	//Si filename es NULL, muestra todos los registros.
	FILE * fp;
	file_version r;
	int cont;
	fp = fopen(".versions/versions.db", "r");

	if(fp == NULL){
		return;
	}

	cont = 1;
	//Leer hasta fin de archivo
	while(!feof(fp)){
		//Realizar una lectura y validar
		if (fread(&r, sizeof(file_version), 1 , fp) != 1){
			break;
		}

		//Si el registro corresponde al archivo buscado, imprimir 
		//Comparación entre cadenas: strcmp
		if (r.filename == filename){
			printf("%d, %s, %s\n", cont, r.hash, r.comment);
			cont = cont + 1;
		}
	}

	fclose(fp);
}

char *get_file_hash(char * filename, char * hash) {
	char *comando;
	FILE * fp;

	struct stat s;

	//Verificar que el archivo existe y que se puede obtener el hash
	if (stat(filename, &s) < 0 || !S_ISREG(s.st_mode)) {
		perror("stat");
		return NULL;
	}

	sha256_hash_file_hex(filename, hash);

	return hash;

}

int copy(char * source, char * destination) {
	// Copia el contenido de source a destination (se debe usar open-read-write-close, o fopen-fread-fwrite-fclose)
}

int version_exists(char * filename, char * hash) {

	// Verifica si en la bd existe un registro que coincide con filename y hash
	return 1;
}

int get(char * filename, int version) {
	//1. Abre la BD y busca el registro r que coincide con filename y version
	//retrieve_file(r.hash, r.filename)

	FILE *fp;
	file_version r;
	int cont;

	//Abrir el archivo ".versions/versions.db"
	fp = fopen(".versions/versions.db", "r");

	if(fp == NULL){
		return;
	}

	cont = 1;

	//Leer hasta fin de archivo
	while (!feof(fp)){
		//Realizar una lectura y validar
		if (fread(&r, sizeof(file_version), 1, fp) != 1){
			break;
		}

		//Buscar el archivo y la version solicitada
		if(r.filename == filename){
			if (cont == version){
				//Copiar el archivo
				copy(r.hash, r.filename); //Preguntar
				break;
			} else {
				//Buscar la siguiente version
				cont = cont + 1;
			}
		}
	}

	fclose(fp);
}


int store_file(char * filename, char * hash) {
	char dst_filename[PATH_MAX];
	snprintf(dst_filename, PATH_MAX, "%s/%s", VERSIONS_DIR, hash);
	return copy(filename, dst_filename);
}

int retrieve_file(char * hash, char * filename) {
	char src_filename[PATH_MAX];
	snprintf(src_filename, PATH_MAX, "%s/%s", VERSIONS_DIR, hash);
	return copy(src_filename, filename);
}


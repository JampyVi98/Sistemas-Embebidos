
#include"matriz_entrenamiento.h" //Llamar matriz de entrenamiento

//float datos_prueba[5] = {5, 3.5, 1.3, 0.3, 1}; //datos de prueba tag 1
float datos_prueba[5] = {5, 2.3, 3.3, 1, 2}; //datos de prueba tag 2
//float datos_prueba[5] = {6.3, 2.5, 5, 1.9, 3}; //datos de prueba tag 3
float aux; //variable auxiliar
int resp, cont_tag = 0, k_vecinos = 3; //respuesta, contador, número de vecinos usados para la relación
void setup() {
  Serial.begin(9600);
  resp = knn(3, 3, 120, 5); //Llamar al método
  Serial.print("Los datos de prueba pertenecen a una etiqueta: ");
  Serial.println(resp);
  if (resp == 1)
    Serial.println("Por lo tanto se trata de una flor tipo Iris-setosa");
  if (resp == 2)
    Serial.println("Por lo tanto se trata de una flor tipo Iris-versicolor");
  if (resp == 3)
    Serial.println("Por lo tanto se trata de una flor tipo Iris-virginica");
  if (resp == datos_prueba[4]) //comparación de  la respuesta con la etiqueta real de los datos
    Serial.println("La prediccion es correcta");
}

void loop() {
}

int knn(int k, int tags, int filas, int columnas) {
  float sumatoria = 0, distancia = 0;
  float mat_k[3][k];
  /*mat_k
    |1|2|3|4|5| -> numero de vecinos
    |0|0|0|0|0| -> distancias
    |3|3|3|2|2| -> asignacion de vecino por etiqueta
  */
  int mat_t[2][tags];
  /*mat_t
    |1|2|3| -> etiquetas en la base de datos
    |0|2|3| -> conteo de etiquetas en cad vecino, la suma debe ser igual a k
  */
  for (int i = 0; i < k; i++) { //moverse en columnas
    mat_k[0][i] = i + 1.0; //enceramos
    mat_k[1][i] = 0;
    mat_k[2][i] = 3000.0 + i;

    /*
       | 1  | 2  | 3  | 4  | 5  |
       | 0  | 0  | 0  | 0  | 0  |
       |3000|3001|3002|3003|3004|
    */
  }

  for (int i = 0; i < tags; i++) { //moverse en columnas
    mat_t[0][i] = i + 1; //enceramos
    mat_t[1][i] = 0;
    /*
       |1|2|3|
       |0|0|0|
    */
  }
  /*PASOS PARA KNN
     Leer cada fila de la matriz de entrenamiento
     Distancia entre la fila de la matriz con la nueca instancia
     Ordenar la matriz mat_k(de menor a mayor)
     Contar las etiquetas en la matriz k y asignar en matriz tags
     Elegir tag con mayor coincidencias
     Retornar resultado
  */

  for (int i = 0; i < filas; i++) { //Lee filas
    sumatoria = 0; //Encera variable sumatoria
    for (int j = 0; j < columnas - 1; j++) { //Lee columnas
      sumatoria = sumatoria + pow(matriz[i][j] - datos_prueba[j], 2); //Calcula sumatoria de potencias
    }
    distancia = sqrt(sumatoria); //Halla distancia
    //Comparación de datos
    if (distancia < mat_k[2][k - 1]) {
      mat_k[2][k - 1] = distancia;
      mat_k[1][k - 1] = matriz[i][columnas - 1];
      //Sorter
      for (int x = 0; x < k; x++) {
        for (int z = x + 1; z < k; z++) {
          if (mat_k[2][x] > mat_k[2][z]) {
            //Distancia
            aux = mat_k[2][x];
            mat_k[2][x] = mat_k[2][z];
            mat_k[2][z] = aux;
            //Tag
            aux = mat_k[1][x];
            mat_k[1][x] = mat_k[1][z];
            mat_k[1][z] = aux;
          } //end if
        }
      } //end sorter
    } //end comparación
  }
  //IMPRIMIR mat_k
  Serial.println("MATRIZ DE K-VECINOS");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < k; j++) {
      Serial.print(mat_k[i][j]);
      Serial.print(" ");
    }
    Serial.println(" ");
  }

  //contar cuantos vecinos hay por etiqueta
  for (int i = 0; i < k; i++) { //moverse en columnas
    if (mat_k[1][i] == 1.0) {
      mat_t[1][0]++;
    } else if (mat_k[1][i] == 2.0) {
      mat_t[1][1]++;
    } else {
      mat_t[1][2]++;
    }
  }
  Serial.println(" ");

  //IMPRIMIR mat_t
  Serial.println("MATRIZ DE TAGS");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < tags; j++) {
      Serial.print(mat_t[i][j]);
      Serial.print(" ");
    }
    Serial.println(" ");
  }

  Serial.println(" ");
  //RESULTADO
  for (int i = 0; i < tags; i++) {
    if (mat_t[1][i] >= tags / 2)
      return i + 1;
  }
}

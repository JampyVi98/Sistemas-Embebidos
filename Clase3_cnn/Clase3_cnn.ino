#include"matriz_entrenamiento.h" //Llamar matriz de entrenamiento

char respuesta; //Dato de retorno
void setup() {
  Serial.begin(9600);
  respuesta = cnn(3, 3, 120, 5); //Llamar al método de algoritmo CNN
}

void loop() {
}

char cnn(int k, int tags, int filas, int columnas) {
  float sum1, sum2, sum3, sumatoria = 0; //Variables de sumatoria
  int cont1 = 0, cont2 = 0, cont3 = 0, drain = 0, source = 0; //Variables de conteo
  /*
     centroides -> promedio
                    promedio por columna y por etiqueta
                    almaceno vectores
                    knn entre vectores y matriz de entrenamiento

  */

  float centroid[tags][columnas]; //Matriz de centroides
  for (int i = 0; i < tags; i++) {
    for (int j = 0; j < columnas; j++) {
      centroid[i][j] = 0; //Encerar matriz de centroides hasta la penúltima columna
      if (j == 4)
        centroid[i][j] = i + 1; //Última columna con valor de cada etiqueta(1,2,3...)
    }
  }

  float dist[filas][tags + 1]; //Matriz de distancias
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j <= tags; j++) {
      dist[i][j] = 0; //Encerar matriz de distancias
    }
  }
  for (int j = 0; j < columnas - 1; j++) { //Correr en columnas hasta la penúltima
    //ENCERAR CONTADORES
    cont1 = 0;
    cont2 = 0;
    cont3 = 0;
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    for (int i = 0; i < filas; i++) { //Correr en filas
      if (matriz[i][4] == 1) { //Condición caso 1
        cont1++; //Suma contador
        sum1 = sum1 + matriz[i][j]; //Se suman los valores de la misma fila hasta la penúltima columna
        centroid[0][j] = sum1 / cont1; //Se obtiene el promedio y se almacena en una posició de la matriz de centroides
      }
      if (matriz[i][4] == 2) { //Condición caso 2
        cont2++; //Suma contador
        sum2 = sum2 + matriz[i][j]; //Se suman los valores de la misma fila hasta la penúltima columna
        centroid[1][j] = sum2 / cont2; //Se obtiene el promedio y se almacena en una posició de la matriz de centroides
      }
      if (matriz[i][4] == 3) { //Condición caso 3
        cont3++; //Suma contador
        sum3 = sum3 + matriz[i][j]; //Se suman los valores de la misma fila hasta la penúltima columna
        centroid[2][j] = sum3 / cont3; //Se obtiene el promedio y se almacena en una posició de la matriz de centroides
      }
    }
  }
//IMPRIMIR MATRIZ DE CENTROIDES
  Serial.println("MATRIZ DE CENTROIDES");
  for (int i = 0; i < tags; i++) {
    for (int j = 0; j < columnas; j++) {
      Serial.print(centroid[i][j], 4);
      Serial.print(' ');
    }
    Serial.println(' ');
  }

  for (int i = 0; i < filas; i++) { //Correr en filas
    sumatoria = 0; //Encera variable sumatoria
    for (int j = 0; j < columnas - 1; j++) { //Correr en columnas hasta la penúltima
      sumatoria = sumatoria + pow(matriz[i][j] - centroid[0][j], 2); //Calcula sumatoria de potencias
    }
    dist[i][0] = sqrt(sumatoria); //Halla distancia y se almacena en una posición de la matriz de distancias
    sumatoria = 0; //Encera variable sumatoria
    for (int j = 0; j < columnas - 1; j++) { //Lee columnas
      sumatoria = sumatoria + pow(matriz[i][j] - centroid[1][j], 2); //Calcula sumatoria de potencias
    }
    dist[i][1] = sqrt(sumatoria); //Halla distancia y se almacena en una posición de la matriz de distancias
    sumatoria = 0; //Encera variable sumatoria
    for (int j = 0; j < columnas - 1; j++) { //Lee columnas
      sumatoria = sumatoria + pow(matriz[i][j] - centroid[2][j], 2); //Calcula sumatoria de potencias
    }
    dist[i][2] = sqrt(sumatoria); //Halla distancia y se almacena en una posición de la matriz de distancias
  }

  for (int i = 0; i < filas; i++) { //Correr en filas
    for (int j = 0; j < tags; j++) { //Correr en columnas
      for (int k = j + 1; k < tags; k++) { //Correr en una posición superior a j
        for (int l = k + 1; l < tags; l++) { //Correr en una posición superior a k
          //HALLAR NÚMERO MENOR EN LA FILA
          if (dist[i][j] < dist[i][k]) { 
            if (dist[i][j] < dist[i][l]) {
              dist[i][tags] = 1; //Asigna la etiqueta en la posición final de la matriz de distancias según el número menor
            }
          }   else if (dist[i][k] < dist[i][l]) {
            dist[i][tags] = 2; //Asigna la etiqueta en la posición final de la matriz de distancias según el número menor
          } else {
            dist[i][tags] = 3; //Asigna la etiqueta en la posición final de la matriz de distancias según el número menor
          }
        }
      }
    }
  }

  Serial.println(" ");
  //COMPARAR ETIQUETAS E IMPRIMIR SU DESTINO(DRAIN/SOURCE)
  Serial.println("MATRIZ DE COMPARACIÓN D/S");
  for (int i = 0; i < filas; i++) { //Lee filas
    for (int j = 0; j < columnas; j++) { //Lee columnas
      if (j < columnas - 1) {
        Serial.print(matriz[i][j], 1); //Imprime los datos de la matriz de entrenamiento a excepción de la etiqueta
        Serial.print(" | "); //Imprimir separador
      } else if (matriz[i][j] == dist[i][tags]) { //Compara entre la etiqueta real y la etiqueta obtenida
        Serial.print("D"); //Si el algoritmo acierta los datos van al drain
        drain++;
      } else {
        Serial.print("S"); //Si el algoritmo falla los datos van al source y se sigue trabajando con ellos
        source++;
      }
    }
    Serial.println(" ");
  }
  Serial.println(" ");
  //IMPRIMIR RESULTADOS
  Serial.println("----------RESULTADOS----------");
  Serial.print("Datos en DRAIN: ");
  Serial.println(drain); //Número de datos en drain
  Serial.print("Datos en SOURCE: ");
  Serial.println(source); //Número de datos en source
  Serial.println("------------------------------");
  return 0;
}

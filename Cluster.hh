/** @file Cluster.hh
    @brief Especificación de la clase Cluster 
*/

#ifndef CLUSTER_HH
#define CLUSTER_HH

#include "Procesador.hh"
#include "BinTree.hh"
#include <queue>

/** @class Cluster
    @brief Representa la información y las operaciones dentro de los procesadores del Cluster

      Sus operaciones son las modificadoras del própio Cluster, y modificadoras de los própios procesadores dentro del Cluster,
      la de lectura (única que produce un nuevo Cluster) y finalmente las de escritura, la que imprime un Procesador del Cluster,
      la que imprime la estructura de este y finalmente la que imprime todo el Cluster
*/

class Cluster {

   // Decripción: contiene un conjunto de Procesadores y las operaciones sobre ellos

private:

   /* Un Cluster se representa mediante su estructura de procesadores, que tendrá
     forma arborescente mediante sus identificadores y finalmente un diccionario que
     relacionará cada identificador de procesador con el própio procesador */


   /** @brief Estructura de procesadores mediante sus identificadores */
    BinTree<string> a_string;

   /** @brief Diccionario con identificadores y procesadores */
    map<string, Procesador> mp;

   
   /** @brief Función Auxiliar que se usa para leer recursivamente el cluster en preorden */
    void leer_preorden(BinTree<string>& a, map<string, Procesador>& m);

   /** @brief Función Auxiliar usada para imprimir la estructura del cluster */
    void estructura_recursiva(const BinTree<string>& a) const;

   /** @brief Función Auxiliar usada de forma recursiva para la función modificar_cluster */
    bool poner_subarbol(string id_p, const BinTree<string>& a_o, BinTree<string>& a);

    /*
    Invariante de la representación:
    - a_string NO vacío
    - mp NO vacío
    */

public:

    //Constructora

   /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un cluster.
      \pre \em cierto
      \post el resultado es un cluster vacio.
   */

    Cluster();

    //Modificadoras

   /** @brief Modificadora del Cluster.

      \pre PI NO vacío
      \post Se ha sustituido una parte del PI por un subárbol 
      con raíz en el procesador dueño del atributo identificador = id.
      Si el Procesador con pid = id no existe, tiene procesos pendientes
      o tiene procesadores auxiliares se imprime un mensaje de error
      en el canal estándar de salida y no se cumple la primera parte del post.
   */

    void modificar_cluster(string id);

   /** @brief Modificadora de la memoria de todos los procesadores del Cluster.

      \pre \em cierto
      \post Se aplica la modificadora de la clase Procesador
      "compactar_memoria_processador" a todos los procesadores del Cluster
   */    

    void compactar_memoria_c();

   /** @brief Modificadora para añadir un Proceso a algún Procesador del Cluster.

      \pre proc NO es vacío
      \post El Procesador del PI con ident. = id ahora ya contiene el proceso.
      no obstante, si NO existe el Procesador en el Cluster, el Procesador
      ya contien proc o no se puede colocar el proceso entonces imprime 
      mensaje de error en el canal estándar de salida y no cumple la primera parte
      de la post.
   */

    void poner_proceso_a_procesador(string id,const Proceso& proc);

   /** @brief Modificadora para eliminar un Proceso de algún Procesador del Cluster.

      \pre \em cierto
      \post El Procesador del PI con identificador id ya NO contiene el proceso con identificador id_p;
      aún así, si el proceso no existe o el procesador no existe imprime mensaje de error en el canal
      de salida estándar y no cumple la primera parte del post.
   */

    void eliminar_proceso_procesador(string id, int id_proc);

    /** @brief Modificadora para enviar un Proceso al Procesador más ideal del Cluster.

      \pre PI No es Vacío
      \post Devuelve cierto si el PI ahora tiene el proceso.
      cabe mencionar que si un proceso se puede colocar en más de un procesador, se elige el que disponga
      de un hueco más ajustado respecto a tal proceso. En caso de empate entre varios
      procesadores, se designa el que quede con más memoria libre. 
      Si persiste el empate, se escoge el más cercano a la raíz del árbol de procesadores y si todavía es
      necesario desempatar, el de más a la izquierda. De lo contrario
      devuelve falso si no se ha podido meter el proceso en el PI.
   */

    bool enviar_proceso_se_ha_puesto(Proceso& proc);

   /** @brief Modificadora para compactar la memoria de uno de los procesadores del Cluster.

      \pre \em cierto
      \post El Procesador con idnt. = id tiene todos los procesos
      trasladados hacia el inicio de la memoria del
      procesador sin espacios entre ellos y sin solaparse.
      si no existe el Procesador entonces se imprime un
      mensaje de error en el canal estándar de salida y
      ya no se cumple la primera parte de la post.
   */

    void compactar_memoria_procesador(string id_p);

   /** @brief Modificadora para adelantar el tiempo estimado de todos los Procesos que hay en el cluster.

      \pre 0 < t
      \post Todos los procesos activos en el Cluster se adelantan t unidades de tiempo.
      si un Proceso llega a 0, éste se elimina.
   */
    
    void adelantar_tiempo(int t);

    //Lectura i Escriptura

   /** @brief Operación de Lectura de un Cluster vacío

      \pre  El canal estándar de entrada contiene un número par de procesadores , 
      que representa un árbol binario en preorden, donde '*' representa un árbol vacío.
      \post El PI es el Cluster tomado del canal estándar de entrada.
   */

    void leer();

   /** @brief Operación de Escritura

      \pre \em cierto
      \post Se han escrito por el canal estándar de salida todos los Procesadores
      del parámetro implícito en orden creciente de su identificador.
   */

    void escribir();

   /** @brief Operación de escritura de la estructura del Cluster.

      \pre \em cierto
      \post La Estructura del Cluster se imprime en el canal estándar de Salida
      siguiendo el ejemplo del enunciado de la práctica.
   */

    void imprimir_estructura() const;

   /** @brief Operación de escritura de un Procesador del Cluster

      \pre \em cierto
      \post Imprime Procesador con id = id_p en el canal estándar de salida.
      si no existe un Procesador con este identificador, entonces
      imprime mensaje de error en el canal estándar de salida y no se
      cumple la primera parte de la post
   */

    void imprimir_procesador(string id_p);
};
#endif
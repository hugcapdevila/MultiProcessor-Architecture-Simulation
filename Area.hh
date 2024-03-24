/** @file Area.hh
    @brief Especificación de la clase Area 
*/

#ifndef AREA_HH
#define AREA_HH

#include "Cluster.hh"
#include "Proceso.hh"
#include <queue>
#include <string>
#include <map>

/** @class Area
    @brief Representa la información y las operaciones asociadas a una Area de procesos pendientes.

    Sus operaciones son las modificadoras de poner y quitar prioridad junto con las de poner un proceso en el Area de espera y enviar n procesos
    al Cluster. Finalmente contamos con las operaciones de escritura y lectura del Area además de la escritura de una prioridad concreta de esta.
*/

class Area {

// Descripción: contiene la estructura y las operaciones de una Area de procesos pendientes.

private:

    /* Una Area de procesos pendientes se representa mediante un diccionario,
    donde la llave es la prioridad y el valor asociado es una struct con la
    cola de procesos pendientes de la prioridad y dos enteros que úsados para
    saber el número de procesos aceptados y rechazados al ser enviados al Cluster*/

    /** @brief Struct usada dentro del diccionario para guardar una cola de procesos junto los procesos aceptados y rechazados */
    struct que_ar {
        int n_not = 0; // número de procesos rechazados
        int n_acc = 0; // número de procesos aceptados
        queue<Proceso> que;
    };

    /** @brief Diccionario con llave id de prioridad y que_ar asociada a ella. Nos ordena directamente las prioridades,
    motivo por el cuál nos simplifica muchísimo el código */
    map<string, que_ar> l_prio;

    /* si existe un proceso pendiente entonces l_prio NO esta vacia */

    /** @brief Función privada para saber si hay un Proceso con identificador = id dentro de una prioridad */
    bool hay_uno_igual(queue<Proceso>& aux, int id);

public:

    //Constructora

   /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar una area.
      \pre \em cierto
      \post el resultado es una Area de procesos pendientes vacía
   */
    Area();

    //Modificadoras

   /** @brief Modificadora para añadir un Proceso al PI.

      \pre \em cierto
      \post El Proceso pasa a estar en el Area de espera dentro de la cola con identificador = prio,
       si no existe esta cola o ya tenía ese mismo proceso dentro, entonces,
       imprime mensaje de error en el canal estándar de salida.
   */

    void poner_proceso(Proceso& prc, string prio);

   /** @brief Modificadora para añadir una prioridad al PI. 

      \pre \em cierto
      \post Se ha añadido una nueva que_ar al parámetro implícito, l_prio esta ordenada crecientemente,
       si la prioridad ya existía imprime un mensaje de error por el canal estándar de salida.
   */

    void poner_prioridad(string s);

   /** @brief Modificadora para eliminar una prioridad al PI.

      \pre \em cierto
      \post El parámetro implícito ya no contiene esta prioridad con identificador sl,
       si no existe prioridad con el identificador s o esta tiene procesos pendientes,
       se imprime un mensaje de error en el canal estándar de salida.
   */

    void eliminar_prioridad(string s);

    /** @brief Modificadora para enviar n procesos al cluster que provienen del PI.

      \pre \em cierto
      \post El Cluster al que se envian ahora contiene todos los procesos que se han
      podido colocar, todos los que no han podido vuelven al PI como procesos nuevos,
      además actualizamos el n_acc y el n_not en función de la información que nos
      devuelven las funciones del Cluster.
   */  

    void enviar_procesos(int n, Cluster& c);

    //Lectura i Escriptura

    /** @brief Operación de Escritura de una prioridad

      \pre \em cierto
      \post Se imprime los procesos pendientes en el canal estándar
       de salida de la prioridad con identificador = id, 
       en orden decreciente de antigüedad, en añadido, escribe el número de procesos
       de la prioridad colocados en el cluster y el número de éstos rechazados.
       Si no existe esta prioridad imprime mensaje de error 
       en el canal estándar de salida y no se cumple la primera parte de la post.
   */

    void imprimir_prioridad(string id) const;

    /** @brief Operación de Lectura de una Area. 

      \pre Hay preparadas en el canal estándar de entrada tantas strings como prioridades
      vayamos a poner en el Area.
      \post El parámetro implícito pasa a tener todas las prioridades entradas en el canal
      estándar de entrada.
   */

    void leer();

   /** @brief Operación de Escritura del Area

      \pre \em cierto
      \post Imprime por el canal estándar de salida
       todas las prioridades de la lista siguiendo el criterio
       de la función "imprimir_prioridad"
   */
    void escribir() const;

};

#endif
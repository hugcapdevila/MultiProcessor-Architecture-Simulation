/** @file Procesador.hh
    @brief Especificación de la classe Procesador
*/

#ifndef PROCESADOR_HH
#define PROCESADOR_HH

#include "Proceso.hh"
#include <map>
#include <set>
#include <string>

/** @class Procesador
    @brief Representa el conjunto de características y
    operaciones de los Procesadores.

    Sus operaciones son las modificadoras de procesos (poner o quitar), las de compactar su memória
    interna y las de progresar el tiempo de sus procesos, las consultoras que se dividen en dos subgrupos:
    las consultoras de los própios atributos, tenemos la consultora del identificador y la de memória libre mientras
    que por otra parte tenemos las consultoras del estado del Procesador durante el código como la
    consultora del tamaño de un hueco dado un iterador, la de si está compactada su memória, la consultora que
    determina si existe algun Proceso en el Procesador y finalmente una que observa si hay algun Proceso con id = id
    y la que concluye si se puede poner un Proceso de tamaño esp en el PI.

*/

class Procesador {

    //Descripción: contiene la estructura de memória y las operaciones de un Procesador

private:

    /* Un Procesador se representa mediante su estructura de memória formada con 3 diccionarios,
    su identificador, su espacio disponible en la memória y finalmente la memória libre
    que tiene el Procesador teniendo en cuenta todos los procesos que tenga en ella.
    */

    /** @brief Espacio disponible TOTAL de la memória (constante una vez leído)*/
    int espacio_disponible;

    /** @brief Memória disponble del Procesador para poner nuevos procesos*/
    int memoria_libre;

    /** @brief String que representa el identificador del Procesador */
    string id;

    /** @brief Diccionario que representa el id de la clase Proceso con la posición inicial de este tal que así: map<id Proceso, posición inicial> */
    map<int, int> m1;

    /** @brief Diccionario que representa la posición inicial con la pròpia clase Proceso tal que así: map<Posición Inicial, Proceso> */
    map<int, Proceso> m2;

    /** @brief Diccionario que representa el tamaño del hueco disponible con la posición inicial de este/estos (puede haber +1)
    tal que así: map<Tamaño hueco, Posición incial de los huecos> */
    map<int, set<int> > m3;

    /*
    Invariante de la representación:
    - 0 < espacio_disponible
    - 0 < memoria_libre
    - id solo contiene números i letras
    */

public:
    //Constructoras

   /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un procesador.
      \pre \em cierto
      \post El resultado es un Procesador vacío
   */
    Procesador();

    /** @brief Creadora con atributos 

      \pre \em cierto
      \post El resultado es un Procesador con los atributos leídos.
   */

    Procesador(const string id_p, const int memoria);

    //Modificadoras

    /** @brief Modificadora para añadir un Proceso al Procesador.

      \pre el PI no tiene el proceso 'proc' y este puede ponerse (se comprueba en el Cluster).
      \post el PI ahora contiene el Proceso 'proc'.
   */

    void poner_proceso(const Proceso& proc, map<int, set<int> >::iterator& espit);

    /** @brief Modificadora para eliminar un Proceso del Procesador .

      \pre el PI guarda el Proceso 'proc' (se comprueba en el Cluster).
      \post el PI ya NO contiene el Proceso 'proc'
   */

    void eliminar_proceso(int id_proc);

    /** @brief Modificadora para compactar la memória del PI

      \pre el PI NO tiene todos los procesos compactados
      \post El PI ahora tiene todos los procesos juntados empezando al principio para que esten en posiciones consecutivas.
  */

    void compactar_memoria();

    /** @brief Modificadora del tiempo estimado de todos los Procesos del PI

      \pre 0 < t
      \post Todos los procesos activos en el PI se adelantan t unidades de tiempo,
      si un Proceso llega a 0, éste se elimina.
   */

    void progresar_tiempo(int t);

    //Consultores

    /** @brief Consultora del identificador del PI.

      \pre \em cierto
      \post Devuelve el id del PI
   */

    string consultar_id() const;

    /** @brief Consultora del hueco apuntado por espit.

      \pre espit apunta a un elemento de m3
      \post Devuelve el hueco del PI que es apuntado por espit.
   */

    int consultar_hueco(map<int, set<int> >::iterator& espit) const;

    /** @brief Consultora del atributo "memoria libre" del PI.

      \pre \em cierto
      \post Devuelve la cantidad de memória libre que queda en el PI.
   */

    int consultar_memoria_libre() const;

    /** @brief Consultora para determinar si el PI tiene la memória compactada.

      \pre \em cierto
      \post Devuelve true si este efectivamente tiene la memória compactada,
      de lo contrario retorna false.
   */

    bool is_compactado() const;

    /** @brief Consultora de si existe un proceso con identificador = id.

      \pre \em cierto
      \post Devuelve true si este efectivamente existe,
      de lo contrario retorna false.
   */

    bool existe(int id) const;

    /** @brief Consultora de si PI tiene algún Proceso en ejecución.

      \pre \em cierto
      \post Devuelve true si el PI posee algún Proceso,
      de lo contrario retorna false.
   */

    bool contiene_procesos() const;

    /** @brief Consultora de si se puede poner un Proceso con tamaño = esp en el PI.

      \pre \em cierto
      \post Devuelve true si se puede poner el proceso en el Procesador,
      además en el iterador it tenemos la posición donde este se tiene que colocar,
      de lo contrario retorna false y espit apunta a m3.end().
   */

    bool se_puede_colocar(int esp, map<int, set<int> >::iterator& espit);

    //Lectura i Escriptura

    /** @brief Operación de Lectura.

      \pre hay preparados en el canal estándar de entrada una string
      con sólo números y letras ademas de (un número entero > 0) o '*'
      \post el parámetro implícito pasa a tener los atributos leídos
       del canal estándar de entrada, la función devuelve false si la entrada
       es '*' de lo contrario devuelve true
   */

    bool leer();

    /** @brief Operación de Escriptura. 

      \pre \em cierto
      \post Se han escrito los procesos del procesador en orden creciente
      desde la primera posición de memoria (incluida) en el canal estándar
      de salida. Por cada proceso se escriben sus atributos,
      sin embargo, el tiempo que se escribe , es el restante para que éste finalice
   */

    void escribir() const;

};
#endif
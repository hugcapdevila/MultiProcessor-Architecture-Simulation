/** @file Proceso.hh
    @brief Especificación de la clase Proceso 
*/

#ifndef PROCESO_HH
#define PROCESO_HH


#include <iostream>
using namespace std;

/** @class Proceso
    @brief Representa la información y las operaciones asociadas a un Proceso

    Sus operaciones son la modificadora de tiempo_estimado usada para actualizar el tiempo restante para que termine el Proceso,
    seguidamente tenemos las consultoras de memoria_ocupada, del id y del tiempo_estimado y finalmente las operaciones
    de Escritura y Lectura estándar.

*/

class Proceso {

  // Descripción: contiene la información y las operaciones asociadas a un Proceso.

private:

    /* Un Proceso se representa mediante 3 atributos, todos enteros. Uno para la memoria que ocupa
    de un Procesador (constante una vez leída), a continuación tenemos
    el identificador y finalmente el tiempo estimado para que este termine.
    */

/** @brief Indica la memória que ocupa */
    int memoria_ocupada;

    /** @brief Indica el identificador del Proceso */
    int id;
    
    /** @brief Indica el tiempo estimado para que finalize el Proceso */
    int tiempo_estimado;

    /*
    Invariante de la representación:
    - 0 <= id
    - 0 < memoria_ocupada
    - 0 < tiempo_estimado (para la lectura solo) cuando usamos la función "avanzar_tiempo" puede dar menor o igual que 0
    */

    public:

    //Constructoras

    /** @brief Constructora por defecto. 

      Se ejecuta automáticamente al declarar un  Proceso.
      \pre \em cierto
      \post El resultado es un proceso vacío
   */

    Proceso();

    /** @brief Constructora de un Proceso con atributos.

      \pre \em cierto
      \post el resultado es un Proceso con id = ident, memoria_ocupada = mem_ocupada y tiempo_estimado = t_est
   */

    Proceso(int ident, int mem_ocupada, int t_est);

   //Modificadora

    /** @brief Modificadora del atributo tiempo_estimado.

      \pre 0 < t
      \post el parametro implicíto tiene tiempo_estimado -= t, retorna true
      en caso de que tiempo estimado <= 0, false de lo contrario.
   */
    
    bool avanzar_tiempo_se_ha_borrado(int t);

   //Consultoras

    /** @brief Consultora del atributo del PI "identificador".

      \pre \em cierto
      \post Devuelve id del PI.
   */

    int consultar_id() const;

    /** @brief Consultora del atributo del PI "memoria_ocupada"

      \pre \em cierto
      \post Devuelve memoria_ocupada del PI.
   */

    int consultar_mem_ocpd() const;

    /** @brief Consultora del atributo del PI "tiempo_estimado"

      \pre \em cierto
      \post Devuelve tiempo_estimado del PI
    */

    int consultar_tiempo() const;

   //Lectura i Escritura

    /** @brief Operación de  Lectura de un Proceso. 

      \pre Hay preparados en el canal de entrada 3 enteros no negativos.
      \post Se han escrito los atributos del P.I 
    */  

    void leer();

    /** @brief Operación de Escritura
    
      \pre \em cierto
      \post Imprime por el canal de salida estandar los atributos
      del Proceso en el siguiente orden: id - memoria_ocupada - tiempo_estimado.
   */

    void escribir() const;

};

#endif
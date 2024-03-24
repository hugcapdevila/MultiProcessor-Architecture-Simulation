/** @mainpage Simulación del rendimiento de procesadores interconectados

En esta práctica queremos simular el funcionamiento de una arquitectura multiprocesador, donde
cada procesador trabaja exclusivamente con su propia memoria y puede ejecutar más
de un proceso simultáneamente. El proyecto será implementado a través de distintas clases
como: \em Cluster, \em  Procesador \em Proceso, \em   Area.

*/

/** @file program.cc
    @brief Programa principal para la práctica \em simulación \em del \em rendimiento \em de \em procesadores \em interconectados  */

#include "Cluster.hh"
#include "Procesador.hh"
#include "Proceso.hh"
#include "Area.hh"

/** @brief Función para interpretar los comandos

    \pre cierto
    \post Ejecuta la función principal de la simulación donde
    probaremos todos los comandos enumerados en el enunciado de la práctica

    \em Leyenda
    id_p => identificador Procesador
    id_proc => identificador Proceso
    id_prio => identificador Prioridad
*/

int main() {
    Cluster c;
    c.leer();
    Area a;
    a.leer();
    string comando;
    cin >> comando;
    while (comando != "fin") {
        if (comando == "configurar_cluster" or comando == "cc") {
            cout << "#" << comando << endl;
            c.leer();
        }
        else if (comando == "modificar_cluster" or comando == "mc") {
            string id_p;
            cin >> id_p;
            cout << "#" << comando << " " << id_p << endl;
            c.modificar_cluster(id_p);
        }
        else if (comando == "alta_prioridad" or comando == "ap") {
            string id_prio;
            cin >> id_prio;
            cout << "#" << comando << " " << id_prio << endl;
            a.poner_prioridad(id_prio);
        }
        else if (comando == "baja_prioridad" or comando == "bp") {
            string id_prio;
            cin >> id_prio;
            cout << "#" << comando << " " << id_prio << endl;
            a.eliminar_prioridad(id_prio);
        }
        else if (comando == "alta_proceso_procesador" or comando == "app") {
            string id_p;
            cin >> id_p;
            int id_proc;
            cin >> id_proc;
            int mem_ocpd;
            cin >> mem_ocpd;
            int t_est;
            cin >> t_est;
            cout << "#" << comando << " " << id_p << " " << id_proc << endl;
            Proceso aux(id_proc, mem_ocpd, t_est);
            c.poner_proceso_a_procesador(id_p, aux);
        }
        else if (comando == "alta_proceso_espera" or comando == "ape") {
            string id_prio;
            cin >> id_prio;
            int id_proc;
            cin >> id_proc;
            int mem_ocpd;
            cin >> mem_ocpd;
            int t_est;
            cin >> t_est;
            cout << "#" << comando << " " << id_prio << " " << id_proc << endl;
            Proceso aux(id_proc, mem_ocpd, t_est);
            a.poner_proceso(aux, id_prio);
        }
        else if (comando == "baja_proceso_procesador" or comando == "bpp") {
            string id_p;
            cin >> id_p;
            int id_proc;
            cin >> id_proc;
            cout << "#" << comando << " " << id_p << " " << id_proc << endl;
            c.eliminar_proceso_procesador(id_p, id_proc);
        }
        else if (comando == "enviar_procesos_cluster" or comando == "epc") {
            int n;
            cin >> n;
            cout << "#" << comando << " " << n << endl;
            a.enviar_procesos(n, c);
        } 
        else if (comando == "avanzar_tiempo" or comando == "at") {
            int t;
            cin >> t;
            cout << "#" << comando << " " << t << endl;
            c.adelantar_tiempo(t);
        }
        else if (comando == "imprimir_prioridad" or comando == "ipri") {
            string id_prio;
            cin >> id_prio;
            cout << "#" << comando << " " << id_prio << endl;
            a.imprimir_prioridad(id_prio);
        }
        else if (comando == "imprimir_area_espera" or comando == "iae") {
            cout << "#" << comando << endl;
            a.escribir();
        }
        else if (comando == "imprimir_procesador" or comando == "ipro") {
            string id_p;
            cin >> id_p;
            cout << "#" << comando << " " << id_p << endl;
            c.imprimir_procesador(id_p);
        }
        else if (comando == "imprimir_estructura_cluster" or comando == "iec") {
            cout << "#" << comando << endl;
            c.imprimir_estructura();
        }
        else if (comando == "imprimir_procesadores_cluster" or comando == "ipc") {
            cout << "#" << comando << endl;
            c.escribir();
        }
        else if (comando == "compactar_memoria_procesador" or comando == "cmp") {
            string id_p;
            cin >> id_p;
            cout << "#" << comando << " " << id_p << endl;
            c.compactar_memoria_procesador(id_p);
        }
        else if (comando == "compactar_memoria_cluster" or comando == "cmc") {
            cout << "#" << comando << endl;
            c.compactar_memoria_c();
        }
        cin >> comando;
    }
}
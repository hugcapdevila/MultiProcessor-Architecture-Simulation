/** @file Proceso.cc
    @brief Código de la clase Proceso
*/

#include "Proceso.hh"

Proceso::Proceso() {
    id = 0;
    memoria_ocupada = 0;
    tiempo_estimado = 0;
}

Proceso::Proceso(int ident, int mem_ocupada, int t_est) {
    id = ident;
    memoria_ocupada = mem_ocupada;
    tiempo_estimado = t_est;
}

bool Proceso::avanzar_tiempo_se_ha_borrado(int t) {
    if (tiempo_estimado > t) {
        tiempo_estimado -= t;
        return false;
    }
    else return true;
}

int Proceso::consultar_id() const {
    return id;
}

int Proceso::consultar_mem_ocpd() const {
    return memoria_ocupada;
}

int Proceso::consultar_tiempo() const {
    return tiempo_estimado;
}

void Proceso::leer() {
    cin >> id >> memoria_ocupada >> tiempo_estimado;
}

void Proceso::escribir() const {
    cout << id << " " << memoria_ocupada << " " << tiempo_estimado << endl;
}

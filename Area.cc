/** @file Area.cc
    @brief Código de la clase Area
*/

#include "Area.hh"

bool Area::hay_uno_igual(queue<Proceso>& aux, int id) {
    while (not aux.empty()) {
        if (aux.front().consultar_id() == id) return true;
        aux.pop();
    }
    return false;
}

Area::Area() {
    l_prio = map<string, que_ar>();
}

void Area::poner_proceso(Proceso& prc, string prio) {
    map<string, que_ar>::iterator it;
    it = l_prio.find(prio);
    if (it == l_prio.end()) cout << "error: no existe prioridad" << endl;
    else {
        queue<Proceso> aux = (*it).second.que;
        int auxid = prc.consultar_id();
        if (hay_uno_igual(aux, auxid)) cout << "error: ya existe proceso" << endl;
        else {
            (*it).second.que.push(prc);
        }
    }
}

void Area::poner_prioridad(string s) {
    map<string, que_ar>::iterator it;
    it = l_prio.find(s);
    if (it != l_prio.end()) cout << "error: ya existe prioridad" << endl;
    else {
        que_ar aux;
        l_prio.insert(make_pair(s, aux));
    }
}

void Area::eliminar_prioridad(string s) {
    map<string, que_ar>::iterator it;
    it = l_prio.find(s);
    if (it != l_prio.end()) {
        if (not (*it).second.que.empty()) cout << "error: prioridad con procesos" << endl;
        else it = l_prio.erase(it);
    }
    else cout << "error: no existe prioridad" << endl;
}

void Area::enviar_procesos(int n, Cluster& c) {
    int i = 0;
    map<string, que_ar>::iterator it = l_prio.begin();
    while (i < n and it != l_prio.end()) {
        if (not (*it).second.que.empty()) {
            int max = (*it).second.que.size();
            int j = 0;
            while (j < max and i < n) {
                if (c.enviar_proceso_se_ha_puesto((*it).second.que.front())) {
                    ++(*it).second.n_acc;
                    ++i;
                }
                else {
                    ++(*it).second.n_not;
                    (*it).second.que.push((*it).second.que.front());
                }
                (*it).second.que.pop();
                ++j;
            }
        }
        ++it;
    }
}

void Area::imprimir_prioridad(string id) const {
    map<string, que_ar>::const_iterator it = l_prio.find(id);
    if (it == l_prio.end()) cout << "error: no existe prioridad" <<  endl;
    else {
        queue<Proceso> aux = (*it).second.que;
        while (not aux.empty()) {
            aux.front().escribir();
            aux.pop();
        }
        cout << (*it).second.n_acc << " " << (*it).second.n_not << endl;
    }
}

void Area::leer() {
    //Solo leeremos prioridades
    int n_prio;
    cin >> n_prio;
    string prioridad;
    for (int i = 0; i < n_prio; ++i) {
        cin >> prioridad;
        l_prio[prioridad];
    }
}

void Area::escribir() const {
    map<string, que_ar>::const_iterator it = l_prio.begin();
    while (it != l_prio.end()) {
        cout << (*it).first << endl;
        queue<Proceso> aux = (*it).second.que;
        while (not aux.empty()) {
            aux.front().escribir();
            aux.pop();
        }
        cout << (*it).second.n_acc << " " << (*it).second.n_not << endl;
        ++it;
    }
}
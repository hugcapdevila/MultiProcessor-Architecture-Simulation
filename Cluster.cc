/** @file Cluster.cc
    @brief Código de la clase Cluster
*/

#include "Cluster.hh"

void Cluster::leer_preorden(BinTree<string>& a, map<string, Procesador>& m) {
    Procesador auxp;
    if (auxp.leer()) {
        string aux = auxp.consultar_id();
        BinTree<string> left;
        BinTree<string> right;

        leer_preorden(left, m);
        leer_preorden(right, m);

        a = BinTree<string>(aux, left, right);
        m.insert(make_pair(aux, auxp));
    }
}

void Cluster::estructura_recursiva(const BinTree<string> &a) const {
    if (a.empty()) cout << " ";
    else {
        cout << "(" << a.value();
        estructura_recursiva(a.left());
        estructura_recursiva(a.right());
        cout << ")";  
    }
}
 
bool Cluster::poner_subarbol(string id_p, const BinTree<string>& a_o, BinTree<string>& a) {
    if (not a_o.empty()) {
        if (a_o.value() == id_p) {
            if (not a_o.left().empty() or not a_o.right().empty()) {
                return false;
            }
            else {
                mp.erase(mp.find(id_p)); /* Borramos aquí el procesador del qual empezamos a modificar,
                debido a si en el nuevo subcluster nos ponen un procesador con el mismo id (no rompe las normas del enunciado) */
                leer_preorden(a, mp);
            } 
        }
        else {
            BinTree<string> left;
            BinTree<string> right;

            if (not poner_subarbol(id_p, a_o.left(), left)) return false;
            if (not poner_subarbol(id_p, a_o.right(), right)) return false;

            a = BinTree<string>(a_o.value(), left, right);
        }
    }
    return true;
}

Cluster::Cluster() {
    a_string = BinTree<string>();
    mp = map<string, Procesador>();
}

void Cluster::modificar_cluster(string id) {
    map<string, Procesador>::iterator it = mp.find(id);
    // Error 1
    if (it == mp.end()) {
        cout << "error: no existe procesador" << endl;
        /*Leemos el árbol aunque sepamos que no vamos a necesitarlo 
        para evitar cualquier error indeseado, además de tambien por
        precisión al enunciado de la práctica que estipula que 
        se leera un árbol en esta función*/
        BinTree<string> useless;
        map<string, Procesador> m_useless;
        leer_preorden(useless, m_useless);
    }
    // Error 2
    else if ((*it).second.contiene_procesos()) {
        cout << "error: procesador con procesos" << endl;
        /*Leemos el árbol aunque sepamos que no vamos a necesitarlo 
        para evitar cualquier error indeseado, además de tambien por
        precisión al enunciado de la práctica que estipula que 
        se leera un árbol en esta función*/
        BinTree<string> useless;
        map<string, Procesador> m_useless;
        leer_preorden(useless, m_useless);
    }
    // Error 3 -> recorremos el árbol del PI en postorden para encontrar nuestro procesador
    else {
        BinTree<string> aux;
        if (not poner_subarbol(id, a_string, aux)) {
            cout << "error: procesador con auxiliares" << endl;
        }
        else {
            a_string = aux; 
        }
    }
}


void Cluster::compactar_memoria_c() {
    map<string, Procesador>::iterator it = mp.begin();
    while (it != mp.end()) {
        if (not (*it).second.is_compactado()) {
            (*it).second.compactar_memoria();
        }
        ++it;
    }
}

void Cluster::poner_proceso_a_procesador(string id, const Proceso& proc) {
    // Error 1 -> Procesador no está en el cluster
    map<string, Procesador>::iterator it = mp.find(id); //it apunta al Procesador en el que tenemos que poner el Proceso
    map<int, set<int> >::iterator espit;
    if (it == mp.end()) cout << "error: no existe procesador" << endl;

    // Error 2 -> Procesador ya contiene un Proceso con el mismo id
    else if ((*it).second.existe(proc.consultar_id())) cout << "error: ya existe proceso" << endl;

    //Error 3 -> Proceso no se puede colocar en Procesador // espit = m3.end();
    else if (not (*it).second.se_puede_colocar(proc.consultar_mem_ocpd(), espit)) cout << "error: no cabe proceso" << endl;

    //En este caso Sí que lo podemos poner, espit apunta a la posición de m3 en el que hay un espacio disponible
    else {
        (*it).second.poner_proceso(proc, espit);
    }
    
}

void Cluster::eliminar_proceso_procesador(string id, int id_proc) {
    //Error 1 No existe Procesador en el Cluster
    map<string, Procesador>::iterator it = mp.find(id);
    if (it == mp.end()) cout << "error: no existe procesador" << endl;
    else {
        (*it).second.eliminar_proceso(id_proc);
    }
}

bool Cluster::enviar_proceso_se_ha_puesto(Proceso& proc) {
    string proc_ideal = "**";
    int hueco_ajustado_actual = 0;
    bool first = true;
    //Recorremos el árbol en anchura siguiendo el ejemplo de los apuntes.
    queue <BinTree<string> > c;
    c.push(a_string);
    while(not c.empty()){
        map<int, set<int> >::iterator espit;
        BinTree<string> aux(c.front());
        //En esta parte del código buscamos el procesador óptimo para el proceso a poner siguiendo los criterios del enunciado de la práctica
        if (mp[aux.value()].se_puede_colocar(proc.consultar_mem_ocpd(), espit) and not mp[aux.value()].existe(proc.consultar_id())) {
            if (first) {
                proc_ideal = aux.value();
                hueco_ajustado_actual = mp[aux.value()].consultar_hueco(espit);
                first = false;
            }
            else {
                if (hueco_ajustado_actual > mp[aux.value()].consultar_hueco(espit)) {
                    hueco_ajustado_actual = mp[aux.value()].consultar_hueco(espit);
                    proc_ideal = aux.value();
                } 
                else if (hueco_ajustado_actual == mp[aux.value()].consultar_hueco(espit)) {
                    if (mp[proc_ideal].consultar_memoria_libre() < mp[aux.value()].consultar_memoria_libre()) {
                        proc_ideal = aux.value();
                    }
                }
            }
        }
        if (not aux.left().empty()) c.push(aux.left());
        if (not aux.right().empty()) c.push(aux.right());
        c.pop();
    }
    if (proc_ideal == "**") return false; //Significa que no se ha podido poner en ningún Procesador del Cluster
    else {
        poner_proceso_a_procesador(proc_ideal, proc);
        return true;
    }
}

void Cluster::compactar_memoria_procesador(string id_p) {
    map<string, Procesador>::iterator it = mp.find(id_p);
    if (it == mp.end()) cout << "error: no existe procesador" << endl;
    else {
        if (not (*it).second.is_compactado()) {
            (*it).second.compactar_memoria();
        }
    }
}

void Cluster::adelantar_tiempo(int t) {
    map<string, Procesador>::iterator it = mp.begin();
    while (it != mp.end()) {
        (*it).second.progresar_tiempo(t);
        ++it;
    }
}

void Cluster::leer() {
    mp.clear();
    leer_preorden(a_string, mp);
}

void Cluster::escribir() {
    map<string, Procesador>::iterator it = mp.begin();
    while (it != mp.end()) {
        cout << (*it).first << endl;
        (*it).second.escribir();
        ++it;
    }
}

void Cluster::imprimir_estructura() const {
    estructura_recursiva(a_string);
    cout << endl;
}

void Cluster::imprimir_procesador(string id_p) {
    map<string, Procesador>::iterator it = mp.find(id_p);
    if (it == mp.end()) cout << "error: no existe procesador" << endl;
    else {
        (*it).second.escribir();
    }
}
/** @file Pocesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

Procesador::Procesador() {
    espacio_disponible = 0;
    memoria_libre = 0;
    id = "**";
    //compactado = true;
    m1 = map<int, int>();
    m2 = map<int, Proceso>();
    m3 = map<int, set<int> >();
}

Procesador::Procesador(const string id_p, const int memoria) {
    id = id_p;
    //compactado = true;
    espacio_disponible = memoria;
    memoria_libre = memoria;
    m3[espacio_disponible].insert(0);
}

void Procesador::poner_proceso(const Proceso& proc, map<int, set<int> >::iterator& espit) {
    //Pre : Proceso se puede poner
    //espit apunta a m3.lower_bound(proc.consultar_mem_ocpd())
    int posi = (*(*espit).second.begin());
    m2[posi] = proc;
    m1[proc.consultar_id()] = posi;
    (*espit).second.erase((*espit).second.begin());

    //Miramos el hueco que hemos dejado
    int hueco = (*espit).first - proc.consultar_mem_ocpd();
    //Si poniendo el proceso queda aún un hueco, lo tenemos que poner
    if (hueco != 0) m3[hueco].insert(posi + proc.consultar_mem_ocpd());
    if ((*espit).second.empty()) espit = m3.erase(espit);

    /* Si el procesador ya estaba compactado previamente, al añadir un Proceso seguirá estando-lo,
    no obstante, si previamente no lo estaba cabe la posibilidad que ahora si que lo esté */
    
    //compactado = esta_compactado();

    memoria_libre -= proc.consultar_mem_ocpd();
}

void Procesador::eliminar_proceso(int id_proc) {
    map<int,int>::iterator it_id = m1.find(id_proc);
    if (it_id == m1.end()) cout << "error: no existe proceso" << endl;
    else {
        map<int, Proceso>::iterator it_m2 = m2.find((*it_id).second);
        m1.erase(it_id); //eliminem proces de m1 un cop ja tenim agafada la posició
        int espacio = (*it_m2).second.consultar_mem_ocpd(); //Miramos el espacio que deja el Proceso
        int posi = (*it_m2).first;
        it_m2 = m2.erase(it_m2);
        memoria_libre += espacio;
        int space_right;
        //Estamos buscando el número de huecos libres siguientes al proceso
        if (it_m2 != m2.end()) space_right = (*it_m2).first - (posi+espacio);
        else space_right = espacio_disponible - (posi + espacio);
        //si space_right es igual a 0, significa que no tiene espacios a su derecha
        if (space_right > 0) {

            /* Aquí estamos eliminando el space_right de m3 porque este espacio
            va a pasar a ser o bien 1. el espacio dejado por el proceso + space right
            o en caso de que por la izquierda también haya un espacio entonces tendremos
            que juntar los 3 espacios*/

            map<int,set<int> >::iterator it_m3 = m3.find(space_right);
            (*it_m3).second.erase(posi+espacio);
            if ((*it_m3).second.empty()) it_m3 = m3.erase(it_m3);
            espacio += space_right;
        }

        int space_left = posi;
        int proc_left = 0;
        //Algoritmo Similiar al anterior
        if (it_m2 != m2.begin()) {
            --it_m2;
            proc_left =  (*it_m2).first + (*it_m2).second.consultar_mem_ocpd();
            space_left = posi - proc_left;
        }
        if (space_left > 0) {
            map<int,set<int> >::iterator it_space = m3.find(space_left);
            (*it_space).second.erase(proc_left);
            //se elimina el hueco, si no existen mas huecos de ese tamaño
            if ((*it_space).second.empty()) m3.erase(it_space);
            //se actualiza la posicion
            posi = proc_left;
            espacio += space_left;
    }
    m3[espacio].insert(posi);

    /* Caso similar al de añadir proceso pero ahora podemos pasar de compactado a no compactado
    y también el caso inverso así que tenemos hacer la comprobación*/

    //compactado = esta_compactado();

    }
}

void Procesador::compactar_memoria() {
//Pre: Memória No está compactada

/* Primera parte de la instrucción, vamos a compactar todos los
Procesos situados en m2, cambiando su posición inicial y de paso
también aprovecharemos para modificar m1 */

    map<int, Proceso>::iterator it_m2 = m2.begin();
    int posi_siguiente = 0; 
    while (it_m2 != m2.end()) {
        int posi_actual = posi_siguiente;
        posi_siguiente += (*it_m2).second.consultar_mem_ocpd();
        if ((*it_m2).first != posi_actual) {
            m1[(*it_m2).second.consultar_id()] = posi_actual;
            m2.insert(make_pair(posi_actual, (*it_m2).second));
            it_m2 = m2.erase(it_m2);
        }
        else ++it_m2;
    }

    /* Finalmente debemos actualizar m3 apropiadamente, primero buscamos el hueco que quedará a la derecha,
    usando posi_siguiente que contiene la primera posición libre */

    map<int, set<int> > auxs;
    auxs[memoria_libre].insert(posi_siguiente);
    m3 = auxs;
}

void Procesador::progresar_tiempo(int t) {
    map<int, Proceso>::iterator it = m2.begin();
    while (it != m2.end()) {
        if ((*it).second.avanzar_tiempo_se_ha_borrado(t)) {
            int id = (*it).second.consultar_id();
            ++it;
            //Para que no quede desreferenciado el iterador
            eliminar_proceso(id);
        }
        else ++it;
    }
}

string Procesador::consultar_id() const {
    return id;
}

int Procesador::consultar_hueco(map<int, set<int> >::iterator& espit) const {
    //espit apunta a un elemento de m3.
    return (*espit).first;
}

 int Procesador::consultar_memoria_libre() const {
    return memoria_libre;
}

bool Procesador::is_compactado() const {
    if (m3.size() == 0 or m2.empty()) return true;
    if (m3.size() == 1) {
        map<int, Proceso>::const_iterator it = m2.end();
        --it;
        //Miramos si hay un hueco entre posición final del último proceso y el final de la memória, si no lo hay NO está compactado
        if ((*it).first + (*it).second.consultar_mem_ocpd() == espacio_disponible) return false;
        else {
            if ((*m3.begin()).second.size() == 1) return true;
            else return false;
        }
    }
    else return false;
}

bool Procesador::existe(int id) const {
    return m1.find(id) != m1.end();
}

bool Procesador::contiene_procesos() const {
    return (not m1.empty());
}

bool Procesador::se_puede_colocar(int esp, map<int, set<int> >::iterator& espit) {
    espit = m3.lower_bound(esp);
    return (espit != m3.end());
}

bool Procesador::leer() {
    cin >> id;
    if (id != "*") {
        cin >> espacio_disponible;
        memoria_libre = espacio_disponible;
        //Reiniciamos la memòria en caso de que leamos un procesador previamente con atributos no vacios
        m1 = map<int, int>();
        m2 = map<int, Proceso>();
        m3 = map<int, set<int> >();
        set<int> aux;
        aux.insert(0);
        m3.insert(make_pair(espacio_disponible, aux));
        return true;
    }
    else return false;
}

void Procesador::escribir() const {
    map<int, Proceso>::const_iterator it = m2.begin();
    while (it != m2.end()) {
        cout << (*it).first << " ";
        (*it).second.escribir();
        ++it;
    }
}
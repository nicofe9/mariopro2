#ifndef FINDER_HH
#define FINDER_HH

#include <map>
#include <set>
#include "geometry.hh"

template <typename T>
class Finder {
 private:
    std::map<std::pair<int, int>, const T*> objects_; 

 public:
    Finder() {}         // constructor por defecto

    void add(const T *t) {
        auto r = t->get_rect();             //obtenim el rectangle de l'objecte
        objects_[{r.left, r.top}] = t;      //afegim l'objecte al mapa amb la seva posició com a clau
    }

    void update(const T *t) {
        remove(t);                  // eliminem l'objecte antic
        add(t);           // afegim l'objecte nou
    }

    void remove(const T *t) {
        auto r = t->get_rect();         // obtenim el rectangle de l'objecte
        objects_.erase({r.left, r.top});    // eliminem l'objecte del mapa amb la seva posició com a clau
    }

    std::set<const T *> query(pro2::Rect rect) const {
        std::set<const T *> result;             // conjunt per emmagatzemar els objectes que compleixin la condició
        for (const auto& [key, obj] : objects_) {       // recorrem tots els objectes del mapa
            auto r = obj->get_rect();       // obtenim el rectangle de l'objecte
            if (!(r.right < rect.left or r.left > rect.right or r.bottom < rect.top or r.top > rect.bottom)) {  // comprovem si l'objecte està dins del rectangle
                result.insert(obj); // si l'objecte està dins del rectangle, l'afegim al conjunt
            }
        }
        return result;
    }
};

#endif
#ifndef FINDER_HH
#define FINDER_HH

#include <map>
#include <set>
#include "geometry.hh"

template <typename T>
class Finder {
 private:
    // Usamos un map indexado por la esquina superior izquierda del rectángulo
    std::map<std::pair<int, int>, const T*> objects_;

 public:
    Finder() {}

    void add(const T *t) {
        auto r = t->get_rect();
        objects_[{r.left, r.top}] = t;
    }

    void update(const T *t) {
        // Para actualizar, eliminamos y volvemos a añadir
        remove(t);
        add(t);
    }

    void remove(const T *t) {
        auto r = t->get_rect();
        objects_.erase({r.left, r.top});
    }

    std::set<const T *> query(pro2::Rect rect) const {
        std::set<const T *> result;
        // Buscamos todos los objetos cuyo rectángulo intersecta con rect
        for (const auto& [key, obj] : objects_) {
            auto r = obj->get_rect();
            if (!(r.right < rect.left or r.left > rect.right or r.bottom < rect.top or r.top > rect.bottom)) {
                result.insert(obj);
            }
        }
        return result;
    }
};

#endif
#include "List.hpp"

template <class DATO>
class Queue : public List<DATO> {
public:
    using List<DATO>::isEmpty;
    using List<DATO>::cons;
    using List<DATO>::pop;
    using List<DATO>::map;
};

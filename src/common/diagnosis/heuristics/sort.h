#ifndef __DIAGNOSIS_HEURISTICS_SORT_H__
#define __DIAGNOSIS_HEURISTICS_SORT_H__

#include "diagnosis/heuristics/heuristic.h"

namespace diagnosis {
namespace heuristics {
class t_sort : public t_heuristic_filter {
public:
    virtual void operator () (const structs::t_spectra & spectra,
                              t_rank_element * ret,
                              const structs::t_spectra_filter * filter=NULL) const;

    virtual std::ostream & print (std::ostream & out) const;
};
}
}
#endif
#ifndef __CANDIDATE_H_edf867e97cb99b12f0025a979426b18b2db6b361__
#define __CANDIDATE_H_edf867e97cb99b12f0025a979426b18b2db6b361__

#include "types.h"
#include "utils/boost.h"

#include <iostream>
#include <set>

#define CANDIDATE_NORMAL_PREFIX ""
#define CANDIDATE_NORMAL_SUFFIX " 0"
#define CANDIDATE_NORMAL_SEP " "
#define CANDIDATE_PRETTY_PREFIX "{c"
#define CANDIDATE_PRETTY_SUFFIX "}"
#define CANDIDATE_PRETTY_SEP ", c"
#define CANDIDATE_LATEX_PREFIX "\\{c_{"
#define CANDIDATE_LATEX_SUFFIX "}\\}"
#define CANDIDATE_LATEX_SEP "}, c_{"

namespace diagnostic {
class t_candidate :
        public std::set<t_component_id> {
    public:
    inline t_candidate () {}

    /**
     * \brief Creates a candidate using va_args. The list must be terminated with a 0.
     */
    t_candidate (int c, ...);

    template <class InputIterator>
    t_candidate (InputIterator first, InputIterator last,
                 const key_compare & comp=key_compare(),
                 const allocator_type & alloc=allocator_type()) :
        set<t_component_id> (first, last, comp, alloc) {}

    inline virtual ~t_candidate () {}


    virtual std::istream & read (std::istream & in);

    virtual std::ostream & generic_write (std::ostream & out,
                                          std::string prefix,
                                          std::string suffix,
                                          std::string separator) const;

    virtual inline std::ostream & write (std::ostream & out) const {
        return generic_write(out,
                             CANDIDATE_NORMAL_PREFIX,
                             CANDIDATE_NORMAL_SUFFIX,
                             CANDIDATE_NORMAL_SEP);
    }

    virtual inline std::ostream & pretty_write (std::ostream & out) const {
        return generic_write(out,
                             CANDIDATE_PRETTY_PREFIX,
                             CANDIDATE_PRETTY_SUFFIX,
                             CANDIDATE_PRETTY_SEP);
    }

    virtual inline std::ostream & latex_write (std::ostream & out) const {
        return generic_write(out,
                             CANDIDATE_LATEX_PREFIX,
                             CANDIDATE_LATEX_SUFFIX,
                             CANDIDATE_LATEX_SEP);
    }

};
}

namespace std {
using diagnostic::t_candidate;
istream & operator >> (istream & in,
                       t_candidate & candidate);
ostream & operator << (ostream & out,
                       const t_candidate & candidate);
}
#endif

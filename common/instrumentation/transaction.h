#ifndef __COMMON_INSTRUMENTATION_TRANSACTION_H__
#define __COMMON_INSTRUMENTATION_TRANSACTION_H__

#include "types.h"

#include "instrumentation/construct.h"
#include "instrumentation/observation.h"

#include "instrumentation/probe.h"
#include "instrumentation/oracle.h"

#include <list>

class t_transaction_construct: public t_construct {
public:
  DEFINE_BOOST_SHARED_PTRS(t_transaction_construct);
};

struct t_transaction_observation: public t_observation_window {

public:
  DEFINE_BOOST_SHARED_PTRS(t_transaction_observation);
  
  typedef std::list<t_ptr> t_transactions;
  typedef std::list<t_oracle_observation::t_ptr> t_oracles;
  typedef std::list<t_probe_observation::t_ptr> t_probes;

  t_transactions transactions;
  t_oracles oracles;
  t_probes probes;

  inline t_transaction_observation(t_time_interval time,
                                   t_construct_id c_id): t_observation_window(time, c_id) {}
  
  inline t_transaction_observation(t_time_interval time_start,
                                   t_construct_id c_id_start,
                                   t_time_interval time_end,
                                   t_construct_id c_id_end): t_observation_window(time_start, c_id_start, time_end, c_id_end) {}
  
  virtual void observation(const t_transaction_observation::t_ptr & obs);
  virtual void observation(const t_oracle_observation::t_ptr & obs);
  virtual void observation(const t_probe_observation::t_ptr & obs);
  
  virtual size_t size() const;
};

#endif

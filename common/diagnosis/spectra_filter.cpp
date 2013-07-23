#include "spectra_filter.h"
#include "utils/iostream.h"

namespace diagnosis {

t_spectra_filter::t_spectra_filter(){
  filtered_component_count = 0;
  filtered_transaction_count = 0;
}

t_transaction_id t_spectra_filter::next_transaction(t_transaction_id transaction) const {
  if(transaction >= f_transaction.size())
    return transaction + 1;
  else
    return f_transaction[transaction];
}

t_component_id t_spectra_filter::next_component(t_component_id component) const {
  if(component >= f_component.size())
    return component + 1;
  else
    return f_component[component];
}

t_component_id t_spectra_filter::get_last_component() const {
  return f_component.size()?(f_component.size() - 1):0UL;
}

t_transaction_id t_spectra_filter::get_last_transaction() const {
  return f_transaction.size()?(f_transaction.size() - 1):0UL;
}

t_component_id t_spectra_filter::get_filtered_component_count() const {
  return filtered_component_count;
}

t_transaction_id t_spectra_filter::get_filtered_transaction_count() const {
  return filtered_transaction_count;
}

bool t_spectra_filter::is_component(t_component_id component) const {
  assert(component > 0);
  if(component >= f_component.size())
    return false;
  return f_component[component - 1] != component;
}

bool t_spectra_filter::is_transaction(t_transaction_id transaction) const {
  assert(transaction > 0);
  if(transaction >= f_transaction.size())
    return false;
  return f_transaction[transaction - 1] != transaction;
}

void t_spectra_filter::filter_all_components_but(const t_candidate & candidate) {

  if(candidate.size() > 0 &&
     *candidate.rbegin() >= f_component.size())
    resize_components(*candidate.rbegin());

  t_candidate::reverse_iterator it = candidate.rbegin();
  t_component_id next = f_component.size();
  t_id next_pos = f_component.size();

  for(;it != candidate.rend(); it++) {
    t_component_id current = *it;
    for(;next_pos > *it; next_pos--)
      f_component[next_pos - 1] = next;

    if(f_component[current - 1] == current)
      next = current;
  }

  for(;next_pos > 0; next_pos--)
    f_component[next_pos - 1] = next;
}

void t_spectra_filter::filter_component(t_component_id component) {
  assert(component > 0);

  if(is_component(component))
    return;

  filtered_component_count++;

  if(component >= f_component.size())
    resize_components(component);

  t_component_id next = f_component[component];
  t_component_id i = component;
  while(i--)
    if(f_component[i] == component)
      f_component[i] = next;
}

void t_spectra_filter::filter_transaction(t_transaction_id transaction) {
  assert(transaction > 0);
  if(is_transaction(transaction))
    return;

  filtered_transaction_count++;

  if(transaction >= f_transaction.size())
    resize_transactions(transaction);

  t_transaction_id next = f_transaction[transaction];
  t_transaction_id i = transaction;
  while(i--)
    if(f_transaction[i] == transaction)
      f_transaction[i] = next;
}

void t_spectra_filter::resize_components(t_component_id size) {
  t_count old_size = f_component.size();
  f_component.resize(size + 1);

  while(old_size++ < f_component.size())
    f_component[old_size - 1] = old_size;
}

void t_spectra_filter::resize_transactions(t_transaction_id size) {
  t_count old_size = f_transaction.size();
  f_transaction.resize(size + 1);

  while(old_size++ < f_transaction.size())
    f_transaction[old_size - 1] = old_size;
}
}

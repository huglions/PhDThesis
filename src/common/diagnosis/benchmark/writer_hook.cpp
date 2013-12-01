#include "writer_hook.h"

#include <boost/filesystem.hpp>
#include <fstream>

#define FILE_ITERATIONS ".num_iterations.txt"
#define FILE_SYSTEMS "num_systems.txt"

namespace diagnosis {
namespace benchmark {
t_writer_hook::t_writer_hook (std::string d) : root_dir(d) {
    boost::filesystem::create_directories(root_dir);


    iterations = 0;
    systems = 0;
}

void t_writer_hook::init_system (const randomizers::t_system & system) {
    systems = read_counter(FILE_SYSTEMS) + 1;
    t_basic_benchmark_hook::init_system(system);
}

void t_writer_hook::init (const structs::t_spectra & spectra,
                          const structs::t_candidate & correct) {
    t_path iteration_counter = boost::lexical_cast<std::string> (get_system_count()) + FILE_ITERATIONS;


    iterations = read_counter(iteration_counter) + 1;
    t_basic_benchmark_hook::init(spectra, correct);
}

void t_writer_hook::cleanup () {
    t_path iteration_counter = boost::lexical_cast<std::string> (get_system_count()) + FILE_ITERATIONS;


    assert(get_iteration_count() > 0);
    assert(get_iteration_count() - read_counter(iteration_counter) <= 1);
    assert(get_system_count() - read_counter(FILE_SYSTEMS) <= 1);

    write_counter(iteration_counter, get_iteration_count());
    write_counter(FILE_SYSTEMS, get_system_count());
    t_basic_benchmark_hook::cleanup();
}

bool t_writer_hook::open_system_file (const t_path & rel_path, std::ofstream & f, bool append) const {
    t_path fname;


    fname += boost::lexical_cast<std::string> (get_system_count()) + ".";
    fname += rel_path;

    return open_file(fname, f, append);
}

bool t_writer_hook::open_iteration_file (const t_path & rel_path, std::ofstream & f, bool append) const {
    t_path fname;


    fname += boost::lexical_cast<std::string> (get_system_count()) + ".";
    fname += boost::lexical_cast<std::string> (get_iteration_count()) + ".";
    fname += rel_path;

    return open_file(fname, f, append);
}

bool t_writer_hook::open_file (const t_path & rel_path, std::ofstream & f, bool append) const {
    t_path fname(get_root_dir());


    fname /= rel_path;

    bool new_file = !boost::filesystem::exists(fname);

    if (f.is_open())
        f.close();

    f.open(fname.c_str(), std::ofstream::out | (append ? std::ofstream::app : (std::ios_base::openmode) 0));
    f.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    return new_file;
}

void t_writer_hook::write_counter (const t_path & rel_path, t_count iterations) const {
    boost::filesystem::path fname(root_dir);


    fname /= rel_path;

    std::ofstream f(fname.c_str());
    f.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    f << iterations;
}

t_count t_writer_hook::read_counter (const t_path & rel_path) const {
    boost::filesystem::path f_iterations(root_dir);


    f_iterations /= rel_path;

    std::ifstream f(f_iterations.c_str());
    t_count iterations = 0;

    f >> iterations;

    return iterations;
}

const t_writer_hook::t_path & t_writer_hook::get_root_dir () const {
    return root_dir;
}

t_count t_writer_hook::get_iteration_count () const {
    return iterations;
}

t_count t_writer_hook::get_system_count () const {
    return systems;
}
}
}
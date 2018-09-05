#include <iostream>
#include <fstream>
#include <filesystem>
#include <cassert>

#include <iostream>

auto main(int argc, char** argv) -> int
{
    auto path = std::filesystem::path{"/etc"};
    path = path / "passwd";
    std::cout << path << '\n'
              << path.stem() << '\n'
              << path.filename() << '\n'
              << path.relative_path() << '\n'
              << path.root_path() << '\n'
              << path.parent_path() << '\n'
              // etc..
              << std::endl;

    auto pgm = std::filesystem::path{*argv};
    std::cout << pgm << '\n'
        << std::filesystem::absolute(pgm)  
        << std::endl;
    assert(std::filesystem::exists(pgm));
    assert(std::filesystem::is_regular_file(pgm));
    assert(not std::filesystem::is_empty(pgm));
    // etc..

    // annoying:
    //std::filesystem::copy_file(pgm, pgm + ".new"); FAIL: no operator+
    std::filesystem::copy_file(pgm, pgm.native() + ".new");
    auto new_dir = std::filesystem::absolute(pgm).parent_path() / "ding_dong";
    std::filesystem::create_directories(new_dir);
    auto new_file1 = new_dir / "the_wicked_bitch";
    auto new_file2 = new_dir / "is_dead";
    std::ofstream o1(new_file1);
    std::ofstream o2(new_file2);

    for(auto& itr : std::filesystem::directory_iterator(new_dir))
        std::cout << itr << std::endl;

    std::filesystem::remove_all(new_dir);

    return 0;
}


#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
//#include <span>
#include <string>
#include <boost/process.hpp>
#include <range/v3/all.hpp>
// TODO add to range-v3/include/range/v3/view.hpp
#include <range/v3/view/remove.hpp>
namespace bp = boost::process;
using namespace ranges;
using namespace std::literals;

int main(int argc, char *argv[]) {
  // Go into a safer C++20 world
  // std::span args { argv + 1, argc - 1};
  for (auto i = 1; i < argc; ++i) {
    auto file = std::ifstream { argv[i] };
    auto constexpr subdirectory = "CV";
    std::filesystem::create_directory(subdirectory);
    std::filesystem::current_path(subdirectory);
    for (const auto & line : getlines_view { file } | views::tail) {
      auto url = line
        | views::remove('\r') | views::split(',')
        | views::slice(8, 9) | views::transform(to<std::string>());
      auto resume_url = *url.begin() + "/resume/download";
      std::cout << "Handling " << line << std::endl;
      resume_url = std::regex_replace(resume_url, std::regex { "/profiles/" },
                                      "/candidate/");

      bp::system(bp::search_path("curl"),
                 "--remote-name", "--remote-header-name", "--user-agent",
                 "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:70.0) Gecko/20100101 Firefox/70.0",
                 resume_url);
    }
  }
}

/** \file

    Download the résumés listed in some CSV files coming from Talemetry

    Each file has a header and each row describes a candidate.

    In each file, the only thing we look at are the URL pointing to the
    descriptions of the candidates.

    \author Ronan Keryell
*/
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <span>
#include <string>

#include <boost/process.hpp>
#include <range/v3/all.hpp>

const std::regex url_syntax { R"delim((https://[\w|./-]+))delim" };
const std::regex profiles { "/profiles/" };

int main(int argc, char *argv[]) {
  // Skip the first argument which is actually the program name
  for (auto const &a :
         std::span { argv + 1, static_cast<std::size_t>(argc - 1)}) {
    // Open each file from the names passed as argument
    auto file = std::ifstream { a };

    // Create a local subdirectory and work into it
    auto constexpr subdirectory = "CV";
    std::filesystem::create_directory(subdirectory);
    std::filesystem::current_path(subdirectory);

    // Explicit the type here since we construct a std::string
    // from a std::sub_match
    for (const std::string url : ranges::getlines_view { file }
           | ranges::views::transform([] (auto &&line) {
                           return line | ranges::views::tokenize(url_syntax, 1);
                                      })
           | ranges::views::join /* Get a range instead of range of ranges */) {
      std::cout << "Handling URL " << url << std::endl;
      // Rewrite the candidate URL into the candidate résumé URL
      auto resume_url = std::regex_replace(url + "/resume/download", profiles,
                                           "/candidate/");
      // Use curl to do the real fetching, to handle HTTP protocol
      boost::process::system(bp::search_path("curl"),
                             // Use the name advertized by the server
                             // to store the file
                             "--remote-name", "--remote-header-name",
                             // Talemetry impose some browsers... :-(
                             // Just lie by imitating some other one
                             "--user-agent",
                             "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:70.0)"
                             " Gecko/20100101 Firefox/70.0",
                             resume_url);
    }
  }
}

#include <iostream>
#include <unistd.h>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

int main (int argc, char *argv[]) {
  fs::path SHELL{getenv("SHELL")}, HOME{getenv("HOME")};
  if (SHELL.stem() == "zsh") {
    system("termux-open ");
    return 0;
  } else {
    cout << "[*] Installing Oh-my-zsh..." << endl;
    fs::create_directories(HOME / ".config/zsh"); 
   // system("git clone https://github.com/robbyrussell/oh-my-zsh.git --depth 1 $HOME/.config/zsh/.oh-my-zsh;");
  }
  return 0;
}

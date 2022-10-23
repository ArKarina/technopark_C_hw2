run: build
  ./build/app

format:
  clang-format --dry-run --Werror src/*.cpp

tidy: cmake
  clang-tidy -p build src/*.cpp

build: cmake
  ninja -Cbuild

cmake:
  cmake -Bbuild -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

app:
  cd build && ./app

tests:
  cd build && cd test && ./run_tests
clean:
  rm -r build
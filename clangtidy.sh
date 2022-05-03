clang-tidy src/* \
-p "build/CMakeFiles" \
-header-filter=".*" \
-checks="-*,modernize-*,cppcoreguidelines-*,readability-*,-modernize-use-trailing-return-type,-*-magic-numbers"

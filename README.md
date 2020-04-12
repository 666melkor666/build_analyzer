# build_analyzer
Inspired by the [ClangBuildAnalyzer](https://github.com/aras-p/ClangBuildAnalyzer) project.  
Allows to collect and analyze C++ builds using clang `-ftime-trace` feature.

# building
Clone the project.
```
clone the project.
cd <source_dir>
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
cmake --build ./
```

# using analyzer
Analyzer consists of two parts:
1. c++ part which analyzes `time-trace` files.
2. python script (analyze.py) which prints the collected statistics.

## step 1 - gathering statistics from `time-trace` files.
During this step each `time-trace` file is analyzed and a statistic for each requested event is collected.  
At the end full statistics is written to the `<output_dir>` separately for each type of event.  
run `./build_analyzer --timeTraceFilesPath=<path_to_time_trace_files> --outputDir=<output_dir> --all`  
`--timeTraceFilesPath` specifies the path to the build directory which contains `time-trace` json files.  
`--outputDir` specifies the path where the result statistics should be written.  
`--all` specifies which type of events should be collected. By default no events are collected. 
User is able to specify either `all` or a set of specific events to be analyzed. See `./build_analyzer --help` for more details.

## step 2 - print the collected statistics.
To print the collected statistics run `analyze.py` script:  
`python3 analyze.py --outputDir <output_dir> --maxLength 5`  
Possible output:
```
ParseClass:

Total time: 0:04:33.552767 Average time: 0:00:00.287950 Count: 950 clang::ASTContext
Total time: 0:03:35.248318 Average time: 0:00:00.206177 Count: 1044 clang::SourceManager
Total time: 0:02:37.473290 Average time: 0:00:00.299379 Count: 526 clang::Preprocessor
Total time: 0:02:23.116212 Average time: 0:00:00.042267 Count: 3386 llvm::BumpPtrAllocatorImpl
Total time: 0:02:12.931039 Average time: 0:00:00.005334 Count: 24921 llvm::format_provider


Frontend:

Total time: 7:13:22.584624 Average time: 0:00:02.936486 Count: 8855 

OptModule:

Total time: 0:02:00.445287 Average time: 0:01:00.222644 Count: 2 /home/melkor/programming/sources/llvm-project/clang/lib/Sema/SemaDeclAttr.cpp
Total time: 0:01:32.139615 Average time: 0:00:46.069808 Count: 2 /home/melkor/programming/sources/llvm-project/clang/lib/ASTMatchers/Dynamic/Registry.cpp
Total time: 0:01:13.983111 Average time: 0:00:36.991556 Count: 2 /home/melkor/programming/sources/llvm-project/llvm/lib/Target/X86/X86ISelLowering.cpp
Total time: 0:01:08.119059 Average time: 0:00:34.059530 Count: 2 /home/melkor/programming/sources/llvm-project/llvm/tools/llvm-readobj/ELFDumper.cpp
Total time: 0:01:03.514846 Average time: 0:00:31.757423 Count: 2 /home/melkor/programming/sources/llvm-project/clang/lib/Sema/SemaExpr.cpp


OptFunction:

Total time: 0:00:37.470540 Average time: 0:00:04.163393 Count: 9 clang::interp::Function::dump(llvm::raw_ostream&) const
Total time: 0:00:27.430528 Average time: 0:00:03.428816 Count: 8 clang::clangd::CanonicalIncludes::addSystemHeadersMapping(clang::LangOptions const&)
Total time: 0:00:27.253432 Average time: 0:00:02.477585 Count: 11 ArmMveAliasValid(unsigned int, llvm::StringRef)
Total time: 0:00:24.960640 Average time: 0:00:00.035863 Count: 696 main
Total time: 0:00:21.538194 Average time: 0:00:00.008500 Count: 2534 llvm::ErrorList::join(llvm::Error, llvm::Error)


InstantiateClass:

Total time: 0:01:03.099650 Average time: 0:00:00.018635 Count: 3386 llvm::SmallVector<std::pair<void *, unsigned long>, 0>
Total time: 0:01:01.866759 Average time: 0:00:00.018271 Count: 3386 llvm::SmallVectorImpl<std::pair<void *, unsigned long> >
Total time: 0:00:58.404575 Average time: 0:00:00.017249 Count: 3386 llvm::is_trivially_copyable<std::pair<void *, unsigned long> >
Total time: 0:00:54.874844 Average time: 0:00:00.017482 Count: 3139 std::unique_ptr<llvm::FileError, std::default_delete<llvm::FileError> >
Total time: 0:00:53.522427 Average time: 0:00:00.017051 Count: 3139 std::unique_ptr<llvm::ErrorInfoBase, std::default_delete<llvm::ErrorInfoBase> >


Source:

Total time: 0:36:56.089673 Average time: 0:00:02.506889 Count: 884 /home/melkor/programming/sources/llvm-project/clang/include/clang/AST/ASTContext.h
Total time: 0:23:13.701081 Average time: 0:00:03.501762 Count: 398 /home/melkor/programming/sources/llvm-project/clang/include/clang/Frontend/FrontendAction.h
Total time: 0:23:07.883098 Average time: 0:00:03.344297 Count: 415 /home/melkor/programming/sources/llvm-project/clang/include/clang/Frontend/ASTUnit.h
Total time: 0:21:42.325112 Average time: 0:00:03.763945 Count: 346 /home/melkor/programming/sources/llvm-project/clang/include/clang/Tooling/Tooling.h
Total time: 0:20:39.980650 Average time: 0:00:00.348799 Count: 3555 /home/melkor/programming/sources/llvm-project/llvm/include/llvm/ADT/ArrayRef.h


ParseTemplate:

Total time: 0:01:45.623932 Average time: 0:00:00.001583 Count: 66729 <unknown>
Total time: 0:00:44.070348 Average time: 0:00:00.011963 Count: 3684 _M_extract_float
Total time: 0:00:30.173514 Average time: 0:00:00.009816 Count: 3074 _M_get_insert_hint_equal_pos
Total time: 0:00:25.872245 Average time: 0:00:00.007023 Count: 3684 _M_extract_int
Total time: 0:00:22.144608 Average time: 0:00:00.002079 Count: 10653 do_get


CodeGen Function:

Total time: 0:00:06.663796 Average time: 0:00:00.019657 Count: 339 clang::ast_matchers::internal::matcher_hasBitWidth0Matcher::matches
Total time: 0:00:00.902466 Average time: 0:00:00.002631 Count: 343 clang::ast_matchers::internal::HasDeclarationMatcher<clang::QualType, clang::ast_matchers::internal::Matcher<clang::Decl> >::matchesSpecialized
Total time: 0:00:00.859751 Average time: 0:00:00.008429 Count: 102 main
Total time: 0:00:00.843905 Average time: 0:00:00.000905 Count: 932 std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::operator=
Total time: 0:00:00.827823 Average time: 0:00:00.003196 Count: 259 std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string


Backend:

Total time: 3:34:49.503103 Average time: 0:00:02.765394 Count: 4661 

InstantiateFunction:

Total time: 0:01:06.935676 Average time: 0:00:00.173408 Count: 386 llvm::AnalysisManager<llvm::Function>::getResultImpl
Total time: 0:01:00.229639 Average time: 0:00:00.166841 Count: 361 llvm::AnalysisManager<llvm::Function>::getResult<llvm::TargetLibraryAnalysis>
Total time: 0:00:51.816930 Average time: 0:00:00.016507 Count: 3139 std::vector<std::unique_ptr<llvm::ErrorInfoBase, std::default_delete<llvm::ErrorInfoBase> >, std::allocator<std::unique_ptr<llvm::ErrorInfoBase, std::default_delete<llvm::ErrorInfoBase> > > >::push_back
Total time: 0:00:51.414327 Average time: 0:00:00.016379 Count: 3139 std::vector<std::unique_ptr<llvm::ErrorInfoBase, std::default_delete<llvm::ErrorInfoBase> >, std::allocator<std::unique_ptr<llvm::ErrorInfoBase, std::default_delete<llvm::ErrorInfoBase> > > >::emplace_back<std::unique_ptr<llvm::ErrorInfoBase, std::default_delete<llvm::ErrorInfoBase> > >
Total time: 0:00:48.642931 Average time: 0:00:00.014559 Count: 3341 std::tie<const unsigned long, const bool>
```

## Comparison with ClangBuildAnalyzer

## TODO

#include "analyze/build_analyzer.h"
#include "file_system/json_file_finder.h"
#include "file_system/file_reader.h"
#include "parser/parser.h"
#include "config.h"

#include <chrono>
#include <iostream>
#include <exception>

namespace
{
bool shouldShowHelp(int argc, char const** argv)
{
	if(argc == 1)
		return true;

	for(int i = 1; i < argc; ++i)
	{
		if(0 == strcmp(argv[i], "--help"))
			return true;
	}

	return false;
}
} // namespace unnamed

int main(int argc, char const** argv)
{
	if(shouldShowHelp(argc, argv))
	{
		build_analyzer::printHelp(std::cout);

		return 0;
	}

	build_analyzer::Config config;
    try
    {
        config = build_analyzer::parse(argv, argc);
    }
    catch(std::exception const& error)
    {
        std::cerr << "Error while parsing command line arguments: "
                  << error.what();

        return 1;
    }

    std::cout << config.timeTraceFilesPath << std::endl;

    build_analyzer::file_system::JsonFileFinder finder{config.timeTraceFilesPath};

    build_analyzer::file_system::FileReader reader;
    build_analyzer::analyze::BuildAnalyzer analyzer{config};

    std::size_t processedFiles = 0;

    auto start = std::chrono::high_resolution_clock::now();
    std::size_t processedBytes = 0;
    while(auto file = finder.next())
    {
        auto content = reader.read(*file);

        processedBytes += content.size();

        try
        {
            build_analyzer::parser::Parser parser{content, *file};

            while(auto event = parser.next())
                analyzer.add(std::move(*event));
        }
        catch(std::exception const& error)
        {
            std::cerr << "Error: " << error.what() << std::endl;
        }

        ++processedFiles;
        if(processedFiles % 100 == 0)
        {
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Files processed: " << processedFiles << std::endl;
            std::cout << "Average processing time: "
                      << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1e9 / processedFiles
                      << " seconds per file" << std::endl;
            std::cout << "Processed data: " << processedBytes / (1024.0 * 1024 * 1024) << " Gb" << std::endl;
        }
    }

    analyzer.print(config.outputDir);

    return 0;
}

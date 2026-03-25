## C++ Toolset

Welcome to the C++ Toolset. This repository features two standalone C++ applications/libraries designed to showcase system-level file manipulation, third-party API integration, and modern, functional C++ template metaprogramming.

### Table of Contents

1.  [Component 1: Filer (AI Document Organizer)](https://www.google.com/search?q=%23component-1-filer-ai-document-organizer)
2.  [Component 2: Simple Utilities](https://www.google.com/search?q=%23component-2-simple-utilities)
3.  [Prerequisites](https://www.google.com/search?q=%23prerequisites)
4.  [Getting Started & Build Instructions](https://www.google.com/search?q=%23getting-started--build-instructions)

-----

### Component 1: Filer (AI Document Organizer)

`filer.cpp` is an automated background service that acts as a smart directory watcher. It monitors a designated folder for new scanned documents, extracts their text, and uses a local Large Language Model (LLM) to intelligently rename and categorize the files.

#### Key Features:

  * **Directory Polling:** Continuously watches the `./unprocessed_scans` directory every 5 seconds for new files.
  * **OCR Integration:** Automatically invokes the Tesseract OCR command-line tool to extract text from incoming images or PDFs.
  * **Local AI Processing:** Truncates the extracted text and sends it to a local Ollama instance (`http://localhost:11434/api/generate`) using the `mistral` model by default.
  * **Intelligent JSON Parsing:** Forces the LLM to output a valid JSON object containing a `category` and `filename`.
  * **Automated Archiving:** Safely renames the file (preserving the original extension) and moves it to a dynamically created subdirectory inside `./Scanned_Archive`, with built-in collision prevention to avoid overwriting existing files.

-----

### Component 2: Simple Utilities

`simple.cpp` provides a lightweight toolkit of modern C++ templates designed to bring functional programming concepts and boilerplate reduction to standard C++ workflows.

#### Included Utilities:

  * **`print`**: A variadic template function that easily prints multiple arguments of varying types to standard output.
  * **`for_range`**: A functional wrapper for iterating over a range and applying a lambda or function to each step.
  * **`benchmark`**: A high-resolution timer that executes a provided closure and outputs its execution time in milliseconds.
  * **`with_resource`**: A try-catch wrapper that enforces setup and teardown routines around an action, ensuring resources are cleaned up even if an exception is thrown.
  * **`memoize`**: A powerful wrapper that caches the results of computationally expensive function calls in a `std::map` to improve subsequent retrieval speeds.
  * **`secure_run`**: An exception-handling wrapper that safely executes actions and outputs standard error messages without crashing the program.
  * **`map_vec`**: A functional array mapping tool that transforms elements of a `std::vector` into a new vector using a provided transformation function.
  * **`evaluate`**: A helper function utilizing a custom `Comparison` enum to logically evaluate two integers.

-----

### Prerequisites

To compile and run these files, you will need the following dependencies:

**For `filer.cpp`:**

  * A modern C++ compiler supporting C++17 (for `std::filesystem`).
  * **libcurl**: Required for making HTTP requests to the AI endpoint.
  * **nlohmann/json**: A C++ JSON library for parsing LLM requests and responses.
  * **Tesseract OCR**: Must be installed on your system and accessible via your environment `PATH`.
  * **Ollama**: A local instance of Ollama running the `mistral` model (or update the `AI_MODEL` constant to your preferred local model).

**For `simple.cpp`:**

  * A standard C++17 compatible compiler (no external libraries required).

-----

### Getting Started & Build Instructions

1.  **Clone the repository:**
    Ensure you have downloaded both `filer.cpp` and `simple.cpp`.

2.  **Building the Filer tool:**
    Because `filer.cpp` relies on external libraries, you will need to link them during compilation.

    ```bash
    g++ -std=c++17 filer.cpp -o filer_app -lcurl
    ```

    *Note: Make sure `nlohmann/json.hpp` is available in your include path.*

3.  **Running the Filer:**
    Ensure Ollama is running (`ollama serve`), then execute the compiled program:

    ```bash
    ./filer_app
    ```

    The program will automatically generate the `./unprocessed_scans` and `./Scanned_Archive` directories upon startup. Drop scanned files into the `unprocessed_scans` directory to watch the magic happen.

4.  **Using the Utilities:**
    Include `simple.cpp` (or split it into a `.hpp` header file) in your own C++ applications to leverage its functional templates.

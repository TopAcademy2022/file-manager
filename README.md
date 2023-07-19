# file-manager

File manager training project

## How build project

    1. Clone this repository;
    2. Make sure you have the Boost c++ library version 1.45.0 or higher;
    3. Change the path to the built Boost library in file-manager/CMakeList.txt (line 30):
        Replace "path/to/build/boost" in command "set (BOOST_LIBRARYDIR "path/to/build/boost")" 
		with the path to the **built** Boost library (where the .lib files are);
    4. Using cmake to build the project. Example: 
        create a folder to build the project (build);
        go to "build" folder;
        run "cmake .." in "build" folder;
        run "cmake --build ." in "build" folder;

## Contributing

    Please read the contribution guidelines before starting work on a pull request.

## Summary of the contributing guidelines

    1. One pull request per issue;
	2. The branch is called the title of your issue. 
		For example, your issue is "Create sort button in file", then the name of your branch is "create-sort-button-file".
    3. Choose the main as base branch;
    4. Include tests and documentation;
    5. Your changes contain 1 commit;
    6. The commit text is the title of the closed issue and add the phrase "Closed #X", where X is the issue number;
    7. Follow the coding style guide.

# file-manager

File manager training project

## How build project

    1. Clone this repository;
    2. Make sure you have the Boost c++ library version 1.45.0 or higher;
		If you want cmake to download the Boost library itself, 
		change the "set (FIRST_BOOST_INSTALL OFF)" flag to ON on the 36 line.
    3. If you don't want cmake to download the Boost library - сhange the path 
		to the Boost library in file-manager/CMakeList.txt (line 39 and 40):
        Replace "./library/boost_1_80_0" to the Boost library;
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

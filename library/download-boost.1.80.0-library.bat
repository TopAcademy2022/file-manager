:: Remarks Print all information on console
@echo ON

:: Remarks Source file location
set source='https://sourceforge.net/projects/boost/files/boost/1.80.0/boost_1_80_0.zip/download'

:: Remarks File name
set fileName='boost_1_80_0.zip'

:: Remarks Directory for extracting Boost library
set extractedFolderPath='../library'

:: Remarks Download the file
powershell -Command "(New-Object Net.WebClient).DownloadFile(%source%, %fileName%)"

:: Remarks Extract library
powershell Expand-Archive %fileName% -DestinationPath %extractedFolderPath%
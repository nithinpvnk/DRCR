* compile.bat - devenv CommPrototype.sln /rebuild debug

* run.bat - 
	:run.bat
	cd Debug
	start WPF.exe
	start MsgServer.exe
	cd..

* "ServerRoot" is the folder where uploaded files are saved.
* "Downloads" is the folder where downloaded files are saved.

* My code works for single client - server.
* My code works only for file uploads.

Code Flow :
===========
CheckIN:
--------
* Press "Select File" button to browse a file/files.

* Press "Upload" button after selecting the file/files.

* then server files are displayed for selection of dependencies.

* Select file/files as dependencies for the upload files.

Extract:
--------
* After checkin, server files are automatically displayed or press "Get Files" button to display the server files.

* check "Dependencies" check box to download the selected file/files with dependency.
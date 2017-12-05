Datasafe
SJSU CMPE 130 Section 01 Group 15

Datasafe is developed for Windows Environment. It makes use of open source crypto++ library for AES implementation (A build of the library is included). To compile, link the cryptlib.lib static library to the datasafe.cpp source file. A simple way to do this would be to use Microsoft's Visual Studio 2017 Command Prompt, included in Microsoft's Build Tools for Visual Studio 2017(https://www.visualstudio.com/downloads/#build-tools-for-visual-studio-2017) Navigate to the \datasafe directory in the VS Command Prompt and type "cl datasafe.cpp /link cryptlib.lib" (without quotations), and hit enter. An executable is also included in the repository for convenience.


ANTI-VIRUS NOTE
Windows Defender and some other anti-virus softwares may target datasafe as a false positive for a trojan. I have reported the false positive to Microsoft and have virus scanned the executable to be safe. If your anti-virus gives you trouble you may have to make an exception for the executable or directory where the executable is located in your anti-virus software.
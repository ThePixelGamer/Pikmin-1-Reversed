# Microsoft Developer Studio Project File - Name="sysCore" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=sysCore - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sysCore.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sysCore.mak" CFG="sysCore - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sysCore - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Debug"
# PROP Intermediate_Dir "../Debug/SysCoreObj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SYSCORE_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SYSCORE_EXPORTS" /Fr /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib wsock32.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /fullbuild
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "sysCore - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "ATX SOURCE FILES"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\Atx\AtxCommandStream.cpp
# End Source File
# Begin Source File

SOURCE=.\Atx\AtxDirectRouter.cpp
# End Source File
# Begin Source File

SOURCE=.\Atx\AtxFileStream.cpp
# End Source File
# Begin Source File

SOURCE=.\Atx\AtxRouter.cpp
# End Source File
# Begin Source File

SOURCE=.\Atx\AtxStream.cpp
# End Source File
# End Group
# Begin Group "GEOMETRY SOURCE FILES"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Geometry\Matrix3f.cpp
# End Source File
# Begin Source File

SOURCE=.\Geometry\Matrix4f.cpp
# End Source File
# Begin Source File

SOURCE=.\Geometry\SRT.cpp
# End Source File
# Begin Source File

SOURCE=.\Geometry\Vector2f.cpp
# End Source File
# Begin Source File

SOURCE=.\Geometry\Vector3f.cpp
# End Source File
# End Group
# Begin Group "NETWORK SOURCE FILES"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Networking\TcpStream.cpp
# End Source File
# Begin Source File

SOURCE=.\Networking\WSocket.cpp
# End Source File
# End Group
# Begin Group "STREAM SOURCE FILES"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Stream\BufferedStream.cpp
# End Source File
# Begin Source File

SOURCE=.\Stream\CmdStream.cpp
# End Source File
# Begin Source File

SOURCE=.\Stream\DebugStream.cpp
# End Source File
# Begin Source File

SOURCE=.\Stream\FileIO.cpp
# End Source File
# Begin Source File

SOURCE=.\Stream\RamStream.cpp
# End Source File
# Begin Source File

SOURCE=.\Stream\RandomAccessStream.cpp
# End Source File
# Begin Source File

SOURCE=.\Stream\Stream.cpp
# End Source File
# End Group
# Begin Group "MODEL SOURCE FILES"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Model_File\Envelope.cpp
# End Source File
# Begin Source File

SOURCE=.\Model_File\VtxMatrix.cpp
# End Source File
# End Group
# Begin Group "TEXTURE SOURCE FILES"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Texturing\TexImg.cpp
# End Source File
# Begin Source File

SOURCE=.\Texturing\Texture.cpp
# End Source File
# End Group
# Begin Group "UI SOURCE FILES"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\UI\ComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\EditBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\OptionBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\RectArea.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\ToolWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\UIFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\UIMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\UIWindow.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\AgeServer.cpp
# End Source File
# Begin Source File

SOURCE=.\AnimData.cpp
# End Source File
# Begin Source File

SOURCE=.\AyuHeap.cpp
# End Source File
# Begin Source File

SOURCE=.\AyuStack.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseApp.cpp
# End Source File
# Begin Source File

SOURCE=.\CacheInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Colour.cpp
# End Source File
# Begin Source File

SOURCE=.\ControllerManager.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxObject.cpp
# End Source File
# Begin Source File

SOURCE=.\Graphics.cpp
# End Source File
# Begin Source File

SOURCE=.\ID32.cpp
# End Source File
# Begin Source File

SOURCE=.\IDelegate.cpp
# End Source File
# Begin Source File

SOURCE=.\Module.cpp
# End Source File
# Begin Source File

SOURCE=.\Nodes.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\System\StdSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\String.cpp
# End Source File
# Begin Source File

SOURCE=.\sysCore.cpp
# End Source File
# Begin Source File

SOURCE=.\System\System.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "ATX HEADER FILES"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\Atx\AtxCommandStream.h
# End Source File
# Begin Source File

SOURCE=.\Atx\AtxDirectRouter.h
# End Source File
# Begin Source File

SOURCE=.\Atx\AtxFileStream.h
# End Source File
# Begin Source File

SOURCE=.\Atx\AtxRouter.h
# End Source File
# Begin Source File

SOURCE=.\Atx\AtxStream.h
# End Source File
# End Group
# Begin Group "GEOMETRY HEADER FILES"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Geometry\Matrix3f.h
# End Source File
# Begin Source File

SOURCE=.\Geometry\Matrix4f.h
# End Source File
# Begin Source File

SOURCE=.\Geometry\SRT.h
# End Source File
# Begin Source File

SOURCE=.\Geometry\Vector2f.h
# End Source File
# Begin Source File

SOURCE=.\Geometry\Vector3f.h
# End Source File
# End Group
# Begin Group "NETWORK HEADER FILES"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Networking\TcpStream.h
# End Source File
# Begin Source File

SOURCE=.\Networking\WSocket.h
# End Source File
# End Group
# Begin Group "STREAM HEADER FILES"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Stream\BufferedStream.h
# End Source File
# Begin Source File

SOURCE=.\Stream\CmdStream.h
# End Source File
# Begin Source File

SOURCE=.\Stream\FileIO.h
# End Source File
# Begin Source File

SOURCE=.\Stream\RamStream.h
# End Source File
# Begin Source File

SOURCE=.\Stream\RandomAccessStream.h
# End Source File
# Begin Source File

SOURCE=.\Stream\Stream.h
# End Source File
# End Group
# Begin Group "MODEL HEADER FILES"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Model_File\Envelope.h
# End Source File
# Begin Source File

SOURCE=.\Model_File\VtxMatrix.h
# End Source File
# End Group
# Begin Group "TEXTURE HEADER FILES"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Texturing\TexImg.h
# End Source File
# Begin Source File

SOURCE=.\Texturing\Texture.h
# End Source File
# End Group
# Begin Group "UI HEADER FILES"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UI\ComboBox.h
# End Source File
# Begin Source File

SOURCE=.\UI\EditBox.h
# End Source File
# Begin Source File

SOURCE=.\UI\OptionBox.h
# End Source File
# Begin Source File

SOURCE=.\UI\RectArea.h
# End Source File
# Begin Source File

SOURCE=.\UI\ToolWindow.h
# End Source File
# Begin Source File

SOURCE=.\UI\UIFrame.h
# End Source File
# Begin Source File

SOURCE=.\UI\UIMgr.h
# End Source File
# Begin Source File

SOURCE=.\UI\UIWindow.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\AgeServer.h
# End Source File
# Begin Source File

SOURCE=.\AnimData.h
# End Source File
# Begin Source File

SOURCE=.\AyuHeap.h
# End Source File
# Begin Source File

SOURCE=.\AyuStack.h
# End Source File
# Begin Source File

SOURCE=.\BaseApp.h
# End Source File
# Begin Source File

SOURCE=.\CacheInfo.h
# End Source File
# Begin Source File

SOURCE=.\Colour.h
# End Source File
# Begin Source File

SOURCE=.\ControllerManager.h
# End Source File
# Begin Source File

SOURCE=.\Stream\DebugStream.h
# End Source File
# Begin Source File

SOURCE=.\GfxObject.h
# End Source File
# Begin Source File

SOURCE=.\Graphics.h
# End Source File
# Begin Source File

SOURCE=.\ID32.h
# End Source File
# Begin Source File

SOURCE=.\IDelegate.h
# End Source File
# Begin Source File

SOURCE=.\Module.h
# End Source File
# Begin Source File

SOURCE=.\Nodes.h
# End Source File
# Begin Source File

SOURCE=.\ObjInfo.h
# End Source File
# Begin Source File

SOURCE=.\System\StdSystem.h
# End Source File
# Begin Source File

SOURCE=.\String.h
# End Source File
# Begin Source File

SOURCE=.\sysCore.h
# End Source File
# Begin Source File

SOURCE=.\System\System.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project

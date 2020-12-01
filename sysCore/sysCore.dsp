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
# ADD CPP /nologo /MDd /W3 /Gm /Gi /GX /ZI /Od /I "include/" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SYSCORE_EXPORTS" /Fr /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib wsock32.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /fullbuild
# SUBTRACT LINK32 /pdb:none /debug /pdbtype:<none>
# Begin Target

# Name "sysCore - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Anim"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Anim\AnimData.cpp
# End Source File
# End Group
# Begin Group "App"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\App\BaseApp.cpp
# End Source File
# Begin Source File

SOURCE=.\source\App\GameApp.cpp
# End Source File
# End Group
# Begin Group "Atx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Atx\AtxCommandStream.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Atx\AtxDirectRouter.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Atx\AtxFileStream.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Atx\AtxStream.cpp
# End Source File
# End Group
# Begin Group "Ayu"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Ayu\AyuHeap.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Ayu\AyuStack.cpp
# End Source File
# End Group
# Begin Group "Controller"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Controller\ControllerManager.cpp
# End Source File
# End Group
# Begin Group "Graphics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Graphics\Graphics.cpp
# End Source File
# End Group
# Begin Group "Math"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Math\BoundBox.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Math\Matrix3f.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Math\Matrix4f.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Math\Plane.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Math\Quat.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Math\SRT.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Math\Vector2f.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Math\Vector3f.cpp
# End Source File
# End Group
# Begin Group "Model"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Model\DispList.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Model\Envelope.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Model\Mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Model\MtxGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Model\VtxMatrix.cpp
# End Source File
# End Group
# Begin Group "Module"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Module\Module.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Module\ModuleMgr.cpp
# End Source File
# End Group
# Begin Group "Networking"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Networking\TcpStream.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Networking\WSocket.cpp
# End Source File
# End Group
# Begin Group "Nodes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Nodes\ANode.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Nodes\CoreNode.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Nodes\EditNode.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Nodes\FaceNode.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Nodes\MemInfoNode.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Nodes\Node.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Nodes\NodeMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Nodes\SRTNode.cpp
# End Source File
# End Group
# Begin Group "Object"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Object\AnimobjInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Object\DlobjInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Object\GfxObject.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Object\GfxobjInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Object\TexobjInfo.cpp
# End Source File
# End Group
# Begin Group "Stream"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Stream\BufferedStream.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Stream\CmdStream.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Stream\DebugStream.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Stream\FileIO.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Stream\RamStream.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Stream\RandomAccessStream.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Stream\Stream.cpp
# End Source File
# End Group
# Begin Group "System"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\System\StdSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\source\System\System.cpp
# End Source File
# End Group
# Begin Group "Texture"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Texture\TexImg.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Texture\Texture.cpp
# End Source File
# End Group
# Begin Group "UI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\UI\AppWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\source\UI\ComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\source\UI\EditBox.cpp
# End Source File
# Begin Source File

SOURCE=.\source\UI\OptionBox.cpp
# End Source File
# Begin Source File

SOURCE=.\source\UI\RectArea.cpp
# End Source File
# Begin Source File

SOURCE=.\source\UI\ToolWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\source\UI\UIFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\source\UI\UIMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\source\UI\UIWindow.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\source\_String.cpp
# End Source File
# Begin Source File

SOURCE=.\source\AgeServer.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Object\BinobjInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CacheInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Colour.cpp
# End Source File
# Begin Source File

SOURCE=.\source\DataChunk.cpp
# End Source File
# Begin Source File

SOURCE=.\source\ID32.cpp
# End Source File
# Begin Source File

SOURCE=.\source\sysCore.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Anim No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\Anim\AnimData.h
# End Source File
# End Group
# Begin Group "App No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\App\BaseApp.h
# End Source File
# Begin Source File

SOURCE=.\include\App\GameApp.h
# End Source File
# End Group
# Begin Group "Atx No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\Atx\AtxCommandStream.h
# End Source File
# Begin Source File

SOURCE=.\include\Atx\AtxDirectRouter.h
# End Source File
# Begin Source File

SOURCE=.\include\Atx\AtxFileStream.h
# End Source File
# Begin Source File

SOURCE=.\include\Atx\AtxRouter.h
# End Source File
# Begin Source File

SOURCE=.\include\Atx\AtxStream.h
# End Source File
# End Group
# Begin Group "Ayu No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\Ayu\AyuHeap.h
# End Source File
# Begin Source File

SOURCE=.\include\Ayu\AyuStack.h
# End Source File
# End Group
# Begin Group "Controller No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\Controller\ControllerManager.h
# End Source File
# End Group
# Begin Group "Graphics No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\Graphics\Graphics.h
# End Source File
# End Group
# Begin Group "Math No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\Math\BoundBox.h
# End Source File
# Begin Source File

SOURCE=.\include\Math\Matrix3f.h
# End Source File
# Begin Source File

SOURCE=.\include\Math\Matrix4f.h
# End Source File
# Begin Source File

SOURCE=.\include\Math\Plane.h
# End Source File
# Begin Source File

SOURCE=.\include\Math\Quat.h
# End Source File
# Begin Source File

SOURCE=.\include\Math\SRT.h
# End Source File
# Begin Source File

SOURCE=.\include\Math\Vector2f.h
# End Source File
# Begin Source File

SOURCE=.\include\Math\Vector3f.h
# End Source File
# End Group
# Begin Group "Model No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\Model\DispList.h
# End Source File
# Begin Source File

SOURCE=.\include\Model\Envelope.h
# End Source File
# Begin Source File

SOURCE=.\source\Model\Joint.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Model\Joint.h
# End Source File
# Begin Source File

SOURCE=.\include\Model\Mesh.h
# End Source File
# Begin Source File

SOURCE=.\include\Model\MtxGroup.h
# End Source File
# Begin Source File

SOURCE=.\include\Model\VtxMatrix.h
# End Source File
# End Group
# Begin Group "Module No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\Module\Module.h
# End Source File
# Begin Source File

SOURCE=.\include\Module\ModuleMgr.h
# End Source File
# End Group
# Begin Group "Networking No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\Networking\TcpStream.h
# End Source File
# Begin Source File

SOURCE=.\include\Networking\WSocket.h
# End Source File
# End Group
# Begin Group "Nodes No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\Nodes\ANode.h
# End Source File
# Begin Source File

SOURCE=.\include\Nodes\CoreNode.h
# End Source File
# Begin Source File

SOURCE=.\include\Nodes\EditNode.h
# End Source File
# Begin Source File

SOURCE=.\include\Nodes\FaceNode.h
# End Source File
# Begin Source File

SOURCE=.\include\Nodes\MemInfoNode.h
# End Source File
# Begin Source File

SOURCE=.\include\Nodes\Node.h
# End Source File
# Begin Source File

SOURCE=.\include\Nodes\NodeMgr.h
# End Source File
# Begin Source File

SOURCE=.\include\Nodes\SRTNode.h
# End Source File
# End Group
# Begin Group "Object No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\Object\AnimobjInfo.h
# End Source File
# Begin Source File

SOURCE=.\include\Object\DlobjInfo.h
# End Source File
# Begin Source File

SOURCE=.\include\Object\GfxObject.h
# End Source File
# Begin Source File

SOURCE=.\include\Object\GfxobjInfo.h
# End Source File
# Begin Source File

SOURCE=.\include\Object\TexobjInfo.h
# End Source File
# End Group
# Begin Group "Stream No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\Stream\BufferedStream.h
# End Source File
# Begin Source File

SOURCE=.\include\Stream\CmdStream.h
# End Source File
# Begin Source File

SOURCE=.\include\Stream\DebugStream.h
# End Source File
# Begin Source File

SOURCE=.\include\Stream\FileIO.h
# End Source File
# Begin Source File

SOURCE=.\include\Stream\RamStream.h
# End Source File
# Begin Source File

SOURCE=.\include\Stream\RandomAccessStream.h
# End Source File
# Begin Source File

SOURCE=.\include\Stream\Stream.h
# End Source File
# End Group
# Begin Group "System No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\System\StdSystem.h
# End Source File
# Begin Source File

SOURCE=.\include\System\System.h
# End Source File
# End Group
# Begin Group "Texture No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\Texture\TexImg.h
# End Source File
# Begin Source File

SOURCE=.\include\Texture\Texture.h
# End Source File
# End Group
# Begin Group "UI No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\UI\AppWindow.h
# End Source File
# Begin Source File

SOURCE=.\include\UI\ComboBox.h
# End Source File
# Begin Source File

SOURCE=.\include\UI\EditBox.h
# End Source File
# Begin Source File

SOURCE=.\include\UI\OptionBox.h
# End Source File
# Begin Source File

SOURCE=.\include\UI\RectArea.h
# End Source File
# Begin Source File

SOURCE=.\include\UI\ToolWindow.h
# End Source File
# Begin Source File

SOURCE=.\include\UI\UIFrame.h
# End Source File
# Begin Source File

SOURCE=.\include\UI\UIMgr.h
# End Source File
# Begin Source File

SOURCE=.\include\UI\UIWindow.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\include\_String.h
# End Source File
# Begin Source File

SOURCE=.\include\AgeServer.h
# End Source File
# Begin Source File

SOURCE=.\include\Object\BinobjInfo.h
# End Source File
# Begin Source File

SOURCE=.\include\CacheInfo.h
# End Source File
# Begin Source File

SOURCE=.\include\Colour.h
# End Source File
# Begin Source File

SOURCE=.\include\DataChunk.h
# End Source File
# Begin Source File

SOURCE=.\include\ID32.h
# End Source File
# Begin Source File

SOURCE=.\include\IDelegate.h
# End Source File
# Begin Source File

SOURCE=.\include\sysCore.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project

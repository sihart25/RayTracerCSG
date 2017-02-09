# Microsoft Developer Studio Project File - Name="RayTracerCSG" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=RayTracerCSG - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RayTracerCSG.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RayTracerCSG.mak" CFG="RayTracerCSG - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RayTracerCSG - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "RayTracerCSG - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "RayTracerCSG"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RayTracerCSG - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "RayTracerCSG - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "RayTracerCSG - Win32 Release"
# Name "RayTracerCSG - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\Source\Camera.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Colour.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Composite.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Control.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Cylinder.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Difference.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Disc.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Display.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Group.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Intersection.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Intersects.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Light.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Main.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Material.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Matrix.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Mesh.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Object.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Plane.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Primitive.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Ray.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Reader.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Scene.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Screen.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Shape.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Sphere.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Transform.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Transformation.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Triangle.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Union.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Vectors.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Writer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Source\Camera.h
# End Source File
# Begin Source File

SOURCE=..\Source\Colour.h
# End Source File
# Begin Source File

SOURCE=..\Source\Composite.h
# End Source File
# Begin Source File

SOURCE=..\Source\Constants.h
# End Source File
# Begin Source File

SOURCE=..\Source\Control.h
# End Source File
# Begin Source File

SOURCE=..\Source\Cylinder.h
# End Source File
# Begin Source File

SOURCE=..\Source\Difference.h
# End Source File
# Begin Source File

SOURCE=..\Source\Disc.h
# End Source File
# Begin Source File

SOURCE=..\Source\Display.h
# End Source File
# Begin Source File

SOURCE=..\Source\Group.h
# End Source File
# Begin Source File

SOURCE=..\Source\Intersection.h
# End Source File
# Begin Source File

SOURCE=..\Source\Intersects.h
# End Source File
# Begin Source File

SOURCE=..\Source\Light.h
# End Source File
# Begin Source File

SOURCE=..\Source\Material.h
# End Source File
# Begin Source File

SOURCE=..\Source\Matrix.h
# End Source File
# Begin Source File

SOURCE=..\Source\Mesh.h
# End Source File
# Begin Source File

SOURCE=..\Source\Object.h
# End Source File
# Begin Source File

SOURCE=..\Source\Plane.h
# End Source File
# Begin Source File

SOURCE=..\Source\Primitive.h
# End Source File
# Begin Source File

SOURCE=..\Source\Ray.h
# End Source File
# Begin Source File

SOURCE=..\Source\Reader.h
# End Source File
# Begin Source File

SOURCE=..\Source\Scene.h
# End Source File
# Begin Source File

SOURCE=..\Source\Screen.h
# End Source File
# Begin Source File

SOURCE=..\Source\Shape.h
# End Source File
# Begin Source File

SOURCE=..\Source\Sphere.h
# End Source File
# Begin Source File

SOURCE=..\Source\Transform.h
# End Source File
# Begin Source File

SOURCE=..\Source\Transformation.h
# End Source File
# Begin Source File

SOURCE=..\Source\Triangle.h
# End Source File
# Begin Source File

SOURCE=..\Source\Union.h
# End Source File
# Begin Source File

SOURCE=..\Source\Vectors.h
# End Source File
# Begin Source File

SOURCE=..\Source\Writer.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project

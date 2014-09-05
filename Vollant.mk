##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=Vollant
ConfigurationName      :=Release
WorkspacePath          := "C:\Projects\Vollant"
ProjectPath            := "C:\Projects\Vollant"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=xvix
Date                   :=08/19/14
CodeLitePath           :="C:\Program Files\CodeLite"
LinkerName             :=C:\MinGW-4.8.1\bin\g++.exe 
SharedObjectLinkerName :=C:\MinGW-4.8.1\bin\g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)SFML_STATIC $(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Vollant.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           :=
RcCompilerName         :=C:\MinGW-4.8.1\bin\windres.exe 
LinkOptions            :=  -mwindows 
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)C:/SFML-2.0/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)sfml-main $(LibrarySwitch)sfml-audio-s $(LibrarySwitch)sfml-graphics-s $(LibrarySwitch)sfml-window-s $(LibrarySwitch)sfml-system-s 
ArLibs                 :=  "libsfml-main" "libsfml-audio-s" "libsfml-graphics-s" "libsfml-window-s" "libsfml-system-s" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)C:/SFML-2.0/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:\MinGW-4.8.1\bin\ar.exe rcu
CXX      := C:\MinGW-4.8.1\bin\g++.exe 
CC       := C:\MinGW-4.8.1\bin\gcc.exe 
CXXFLAGS :=  -O2 -Wall -std=gnu++0x -mwindows $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:\MinGW-4.8.1\bin\as.exe 


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
UNIT_TEST_PP_SRC_DIR:=C:\UnitTest++-1.3
Objects0=$(IntermediateDirectory)/src_Game.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_TextureManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_GameObject.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Player.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Bird.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_resource.rc$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Release"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_Game.cpp$(ObjectSuffix): src/Game.cpp $(IntermediateDirectory)/src_Game.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Projects/Vollant/src/Game.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Game.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Game.cpp$(DependSuffix): src/Game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Game.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Game.cpp$(DependSuffix) -MM "src/Game.cpp"

$(IntermediateDirectory)/src_Game.cpp$(PreprocessSuffix): src/Game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Game.cpp$(PreprocessSuffix) "src/Game.cpp"

$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix): src/main.cpp $(IntermediateDirectory)/src_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Projects/Vollant/src/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.cpp$(DependSuffix): src/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main.cpp$(DependSuffix) -MM "src/main.cpp"

$(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix): src/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix) "src/main.cpp"

$(IntermediateDirectory)/src_TextureManager.cpp$(ObjectSuffix): src/TextureManager.cpp $(IntermediateDirectory)/src_TextureManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Projects/Vollant/src/TextureManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_TextureManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_TextureManager.cpp$(DependSuffix): src/TextureManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_TextureManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_TextureManager.cpp$(DependSuffix) -MM "src/TextureManager.cpp"

$(IntermediateDirectory)/src_TextureManager.cpp$(PreprocessSuffix): src/TextureManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_TextureManager.cpp$(PreprocessSuffix) "src/TextureManager.cpp"

$(IntermediateDirectory)/src_GameObject.cpp$(ObjectSuffix): src/GameObject.cpp $(IntermediateDirectory)/src_GameObject.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Projects/Vollant/src/GameObject.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_GameObject.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_GameObject.cpp$(DependSuffix): src/GameObject.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_GameObject.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_GameObject.cpp$(DependSuffix) -MM "src/GameObject.cpp"

$(IntermediateDirectory)/src_GameObject.cpp$(PreprocessSuffix): src/GameObject.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_GameObject.cpp$(PreprocessSuffix) "src/GameObject.cpp"

$(IntermediateDirectory)/src_Player.cpp$(ObjectSuffix): src/Player.cpp $(IntermediateDirectory)/src_Player.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Projects/Vollant/src/Player.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Player.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Player.cpp$(DependSuffix): src/Player.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Player.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Player.cpp$(DependSuffix) -MM "src/Player.cpp"

$(IntermediateDirectory)/src_Player.cpp$(PreprocessSuffix): src/Player.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Player.cpp$(PreprocessSuffix) "src/Player.cpp"

$(IntermediateDirectory)/src_Bird.cpp$(ObjectSuffix): src/Bird.cpp $(IntermediateDirectory)/src_Bird.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Projects/Vollant/src/Bird.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Bird.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Bird.cpp$(DependSuffix): src/Bird.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Bird.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Bird.cpp$(DependSuffix) -MM "src/Bird.cpp"

$(IntermediateDirectory)/src_Bird.cpp$(PreprocessSuffix): src/Bird.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Bird.cpp$(PreprocessSuffix) "src/Bird.cpp"

$(IntermediateDirectory)/src_resource.rc$(ObjectSuffix): src/resource.rc
	$(RcCompilerName) -i "C:/Projects/Vollant/src/resource.rc" $(RcCmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/src_resource.rc$(ObjectSuffix) $(RcIncludePath)

-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/src_Game.cpp$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Game.cpp$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Game.cpp$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_main.cpp$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_main.cpp$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_TextureManager.cpp$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_TextureManager.cpp$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_TextureManager.cpp$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_GameObject.cpp$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_GameObject.cpp$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_GameObject.cpp$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_Player.cpp$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Player.cpp$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Player.cpp$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_Bird.cpp$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Bird.cpp$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Bird.cpp$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/resource.rc$(ObjectSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile).exe
	$(RM) ".build-release/Vollant"



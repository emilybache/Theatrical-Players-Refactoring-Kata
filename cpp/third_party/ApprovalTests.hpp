// Approval Tests version v.4.0.0
// More information at: https://github.com/approvals/ApprovalTests.cpp
#include <stdexcept>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <memory>
#include <vector>
#include <functional>
#include <iostream>
#include <stdlib.h>
#include <numeric>
#include <stack>
#include <exception>
#include <map>
#include <ostream>
 // ******************** From: Blocker.h
#ifndef APPROVALTESTS_CPP_BLOCKER_H
#define APPROVALTESTS_CPP_BLOCKER_H

class Blocker
{
public:
    virtual ~Blocker() = default;
    virtual bool isBlockingOnThisMachine() const = 0;
};

#endif 

 // ******************** From: Macros.h
#ifndef APPROVALTESTS_CPP_MACROS_H
#define APPROVALTESTS_CPP_MACROS_H



#define APPROVAL_TESTS_MACROS_STATIC(type, name, defaultValue) \
static type &name(type *value = NULL) { \
    static type *staticValue; \
    if (value != NULL) \
    { \
        staticValue = value; \
    } \
    if (staticValue == NULL) \
    { \
        staticValue = defaultValue; \
    } \
    if ( staticValue == nullptr ) \
    { \
        const char* helpMessage = "The variable in " #name "() is not initialised"; \
        throw std::runtime_error( helpMessage ); \
    } \
    return *staticValue; \
}




#define APPROVAL_TESTS_UNUSED(expr) do { (void)(expr); } while (0)



#endif 

 // ******************** From: StringUtils.h


#ifndef APPROVALTESTS_CPP_STRINGUTILS_H
#define APPROVALTESTS_CPP_STRINGUTILS_H


class StringUtils
{
public:
    static std::string replaceAll(std::string inText, const std::string& find, const std::string& replaceWith) {
        size_t start_pos = 0;
        while ((start_pos = inText.find(find, start_pos)) != std::string::npos) {
            inText.replace(start_pos, find.length(), replaceWith);
            start_pos += replaceWith.length(); 
        }
        return inText;
    }

    static bool contains(std::string inText, const std::string& find)
    {
        return inText.find(find, 0) != std::string::npos;
    }

    static std::string toLower(std::string inText)
    {
        std::string copy(inText);
        std::transform(inText.begin(), inText.end(), copy.begin(),
          [](char c){ return static_cast<char>(::tolower(c)); });
        return copy;
    }
    
    static bool endsWith(std::string value, std::string ending)
    {
        if (ending.size() > value.size())
        {
            return false;
        }
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    template<typename T>
    static std::string toString(const T& contents)
    {
        std::stringstream s;
        s << contents;
        return s.str();
    }

};
#endif 

 // ******************** From: ApprovalWriter.h
#ifndef APPROVALTESTS_CPP_APPROVALWRITER_H
#define APPROVALTESTS_CPP_APPROVALWRITER_H

class ApprovalWriter
{
public:
    virtual std::string getFileExtensionWithDot() = 0;
    virtual void write(std::string path) = 0;
    virtual void cleanUpReceived(std::string receivedPath) = 0;
};

#endif 

 // ******************** From: StringWriter.h
#ifndef APPROVALTESTS_CPP_STRINGWRITER_H
#define APPROVALTESTS_CPP_STRINGWRITER_H


class StringWriter : public ApprovalWriter
{
private:
    std::string s;
    std::string ext;

public:
    StringWriter( std::string contents, std::string fileExtensionWithDot = ".txt" )
        : s( contents ), ext( fileExtensionWithDot ) {}

    std::string getFileExtensionWithDot() override
    {
        return ext;
    }

    void write( std::string path ) override
    {
        std::ofstream out( path.c_str(), std::ofstream::out );
        if ( ! out)
        {
            throw std::runtime_error("Unable to write file: " + path);
        }
        this->Write( out );
        out.close();
    }

    void Write( std::ostream &out )
    {
        out << s << "\n";
    }

    virtual void cleanUpReceived(std::string receivedPath) override {
        remove(receivedPath.c_str());
    }


};
#endif

 // ******************** From: FileUtils.h




#ifndef APPROVALTESTS_CPP_FILEUTILS_H
#define APPROVALTESTS_CPP_FILEUTILS_H


class FileUtils {
public:
    static bool fileExists(std::string path)
    {
        struct stat info;
        return stat( path.c_str(), &info ) == 0;
    }

    static int fileSize(std::string path) {
        struct stat statbuf;
        int stat_ok = stat(path.c_str(), &statbuf);

        if (stat_ok == -1) {
            return -1;
        }

        return int(statbuf.st_size);
    }

    static void ensureFileExists(std::string fullFilePath) {
        if (!fileExists(fullFilePath)) {
            StringWriter s("", "");
            s.write(fullFilePath);
        }
    }

    static std::string getExtensionWithDot(std::string filePath) {
        std::size_t found = filePath.find_last_of(".");
        return filePath.substr(found);
    }

    static void writeToFile(std::string filePath, std::string content)
    {
        std::ofstream out(filePath.c_str(), std::ios::binary | std::ofstream::out);
        out << content;
    }
};

#endif 

 // ******************** From: WinMinGWUtils.h
#ifndef APPROVALTESTS_CPP_WINMINGWUTILS_H
#define APPROVALTESTS_CPP_WINMINGWUTILS_H

// <SingleHpp unalterable>

#if (defined(__MINGW32__) || defined(__MINGW64__))
#define APPROVAL_TESTS_MINGW
#endif

#ifdef APPROVAL_TESTS_MINGW
#ifdef __cplusplus
extern "C" {
#endif

#include <sec_api/stdlib_s.h> /* errno_t, size_t */

errno_t getenv_s(
    size_t     *ret_required_buf_size,
    char       *buf,
    size_t      buf_size_in_bytes,
    const char *name
);

#ifdef __cplusplus
}
#endif

#endif // APPROVAL_TESTS_MINGW

// </SingleHpp>

#endif 

 // ******************** From: SystemUtils.h
#ifndef APPROVALTESTS_CPP_SYSTEMUTILS_H
#define APPROVALTESTS_CPP_SYSTEMUTILS_H

// <SingleHpp unalterable>
#ifdef _WIN32
    // ReSharper disable once CppUnusedIncludeDirective
    #include <io.h>
    #include <windows.h>
    #include <direct.h>
#else
    // ReSharper disable once CppUnusedIncludeDirective
    #include <unistd.h>
#endif
// </SingleHpp>



class SystemUtils
{
public:
    static bool isWindowsOs()
    {
#ifdef _WIN32
        return true;
#else
        return false;
#endif

    }
    
    static bool isCygwin()
    {
#ifdef __CYGWIN__
        return true;
#else
        return false;
#endif
    }

    static std::string getDirectorySeparator()
    {
        return isWindowsOs() ? "\\" : "/";
    }

    
    static std::string checkFilenameCase(const std::string& fullPath)
    {
        if (!isWindowsOs() || !FileUtils::fileExists(fullPath))
        {
            return fullPath;
        }
#ifdef _WIN32

        WIN32_FIND_DATAA findFileData;
        HANDLE hFind = FindFirstFileA(fullPath.c_str(), &findFileData);

        if (hFind != INVALID_HANDLE_VALUE)
        {
            const std::string fixedFilename = findFileData.cFileName;
            const std::string fixedPath = 
                StringUtils::replaceAll( fullPath, StringUtils::toLower(fixedFilename), fixedFilename );
            FindClose(hFind);
            return fixedPath;
        }


#endif
        return fullPath;

    }

    static std::string safeGetEnvForWindows(char const *name)
    {
        APPROVAL_TESTS_UNUSED(name);
#ifdef _WIN32
        
        
        

        size_t size;
        getenv_s(&size, nullptr, 0, name);

        if (size != 0)
        {
            std::string result;
            result.resize(size);
            getenv_s(&size, &*result.begin(), size, name);
            result.pop_back();
            return result;
        }
#endif
        return std::string();
    }

    static std::string safeGetEnvForNonWindows(char const *name)
    {
        APPROVAL_TESTS_UNUSED(name);
        char* p = nullptr;
#ifndef _WIN32
        p = getenv(name);
#endif
        return (p != nullptr) ? p : std::string();
    }

    
    static std::string safeGetEnv(char const *name)
    {
        return isWindowsOs() ? safeGetEnvForWindows(name) : safeGetEnvForNonWindows(name);
    }
    
    static std::string getMachineName()
    {
        auto name = safeGetEnv("COMPUTERNAME");
        if ( ! name.empty())
        {
            return name;
        }

        name = safeGetEnv("HOSTNAME");
        if ( ! name.empty())
        {
            return name;
        }

        return "Unknown Computer";
    }

    static void makeDirectoryForWindows(std::string directory)
    {
        APPROVAL_TESTS_UNUSED(directory);
#ifdef _WIN32
        int nError = _mkdir(directory.c_str());
        if (nError != 0)
        {
            std::string helpMessage = std::string("Unable to create directory: ") + directory;
            throw std::runtime_error( helpMessage );
        }
#endif
    }

    static void makeDirectoryForNonWindows(std::string directory)
    {
        APPROVAL_TESTS_UNUSED(directory);
#ifndef _WIN32
        mode_t nMode = 0733; 
        int nError = mkdir(directory.c_str(),nMode);
        if (nError != 0)
        {
            std::string helpMessage = std::string("Unable to create directory: ") + directory;
            throw std::runtime_error( helpMessage );
        }
#endif
    }

    static void makeDirectory(std::string directory)
    {
        makeDirectoryForWindows(directory);
        makeDirectoryForNonWindows(directory);
    }

    static void ensureDirectoryExists(std::string fullFilePath)
    {
        if (!FileUtils::fileExists(fullFilePath))
        {
            makeDirectory(fullFilePath);
        }
    }
};
#endif

 // ******************** From: MachineBlocker.h
#ifndef APPROVALTESTS_CPP_MACHINEBLOCKER_H
#define APPROVALTESTS_CPP_MACHINEBLOCKER_H



class MachineBlocker : public Blocker
{
private:
    std::string machineName;
    bool block;

    MachineBlocker() = delete;

public:
    MachineBlocker( const std::string& machineName, bool block ) : machineName(machineName), block(block)
    {
    }

    static MachineBlocker onMachineNamed( const std::string& machineName )
    {
        return MachineBlocker(machineName, true);
    }

    static MachineBlocker onMachinesNotNamed( const std::string& machineName )
    {
        return MachineBlocker(machineName, false);
    }

    virtual bool isBlockingOnThisMachine() const override
    {
        const auto isMachine = (SystemUtils::getMachineName() == machineName);
        return isMachine == block;
    }
};


#endif 

 // ******************** From: FileUtilsSystemSpecific.h
#ifndef APPROVALTESTS_CPP_FILEUTILSSYSTEMSPECIFIC_H
#define APPROVALTESTS_CPP_FILEUTILSSYSTEMSPECIFIC_H


class FileUtilsSystemSpecific
{
public:
    static std::string getCommandLineForCopy(std::string source, std::string destination, bool isWindows)
    {
        if (isWindows) {
            return std::string("copy /Y ") + "\"" + source + "\" \"" + destination + "\"";
        } else {
            return std::string("cp ") + "\"" + source + "\" \"" + destination + "\"";
        }
    }

    static void copyFile( std::string source, std::string destination )
    {
        system( getCommandLineForCopy(source, destination, SystemUtils::isWindowsOs()).c_str() );
    }
};
#endif

 // ******************** From: Reporter.h
#ifndef APPROVALTESTS_CPP_REPORTER_H
#define APPROVALTESTS_CPP_REPORTER_H



class Reporter {
public:
    virtual ~Reporter() = default;
    virtual bool report(std::string received, std::string approved) const = 0;
};

#endif

 // ******************** From: AutoApproveReporter.h
#ifndef APPROVALTESTS_CPP_AUTOAPPROVEREPORTER_H
#define APPROVALTESTS_CPP_AUTOAPPROVEREPORTER_H


class AutoApproveReporter : public Reporter
{
public:
    bool report(std::string received, std::string approved) const override
    {
        std::cout << "file " << approved << " automatically approved - next run should succeed\n";
        FileUtilsSystemSpecific::copyFile( received, approved );
        return true;
    }
};

#endif

 // ******************** From: GoogleCustomizationsFactory.h
#ifndef APPROVALTESTS_CPP_GOOGLECUSTOMIZATIONSFACTORY_H
#define APPROVALTESTS_CPP_GOOGLECUSTOMIZATIONSFACTORY_H



class GoogleCustomizationsFactory
{
public:
    using Comparator = std::function<bool(const std::string&, const std::string&)>;
private:
    using ComparatorContainer = std::vector< Comparator >;
    APPROVAL_TESTS_MACROS_STATIC(ComparatorContainer, comparatorContainer, GoogleCustomizationsFactory::createContainer())

    static ComparatorContainer* createContainer()
    {
        auto container = new ComparatorContainer;

        auto exactNameMatching = [](std::string testFileNameWithExtension, std::string testCaseName)
        {
            return StringUtils::contains(testFileNameWithExtension, testCaseName + ".");
        };
        container->push_back( exactNameMatching );
        return container;
    }

public:
    static ComparatorContainer getEquivalencyChecks()
    {
        return comparatorContainer();
    }

    static bool addTestCaseNameRedundancyCheck(Comparator comparator)
    {
        comparatorContainer().push_back(comparator);
        return true;
    }
    

};

#endif 

 // ******************** From: ExistingFile.h
#ifndef APPROVALTESTS_CPP_EXISTINGFILE_H
#define APPROVALTESTS_CPP_EXISTINGFILE_H



class ExistingFile : public ApprovalWriter{
    std::string filePath;
public:
    ExistingFile(std::string filePath) : filePath(filePath){}
    virtual std::string getFileExtensionWithDot() override {
        return FileUtils::getExtensionWithDot(filePath);
    }
    virtual void write(std::string ) override {
        
    }
    virtual void cleanUpReceived(std::string ) override {
        
    }
};
#endif

 // ******************** From: CommandLauncher.h
#ifndef APPROVALTESTS_CPP_COMMANDLAUNCHER_H
#define APPROVALTESTS_CPP_COMMANDLAUNCHER_H



class CommandLauncher
{
public:
    virtual ~CommandLauncher() {}
    virtual bool launch(std::vector<std::string> argv) = 0;
};

#endif  

 // ******************** From: CommandReporter.h
#ifndef APPROVALTESTS_CPP_COMMANDREPORTER_H
#define APPROVALTESTS_CPP_COMMANDREPORTER_H



class CommandReporter : public Reporter {
private:
    std::string cmd;
    CommandLauncher *l;

protected:
    CommandReporter(std::string command, CommandLauncher *launcher)
            : cmd(command), l(launcher) {
    }

public:
    bool report(std::string received, std::string approved) const override {
        FileUtils::ensureFileExists(approved);
        return l->launch(getFullCommand(received, approved));
    }

    std::vector<std::string> getFullCommand(const std::string &received, const std::string &approved) const
    {
        std::vector<std::string> fullCommand;
        fullCommand.push_back(cmd);
        fullCommand.push_back(received);
        fullCommand.push_back(approved);
        return fullCommand;
    }
};
#endif 

 // ******************** From: SystemLauncher.h

#ifndef APPROVALTESTS_CPP_SYSTEMLAUNCHER_H
#define APPROVALTESTS_CPP_SYSTEMLAUNCHER_H


typedef std::vector<std::string> (*ConvertArgumentsFunctionPointer)(std::vector<std::string>);

class SystemLauncher : public CommandLauncher
{
private:
    ConvertArgumentsFunctionPointer convertArgumentsForSystemLaunching;
public:
    SystemLauncher() : SystemLauncher(doNothing)
    {
    }

    explicit SystemLauncher(std::vector<std::string> (*pointer)(std::vector<std::string>)) : convertArgumentsForSystemLaunching(pointer) 
    {
    }

    
    void setConvertArgumentsForSystemLaunchingFunction(ConvertArgumentsFunctionPointer function)
    {
        convertArgumentsForSystemLaunching = function;
    }

    bool exists(const std::string& command)
    {
        bool foundByWhich = false;
        if (!SystemUtils::isWindowsOs()) {
            std::string which = "which " + command + " > /dev/null 2>&1";
            int result = system(which.c_str());
            foundByWhich = (result == 0);
        }
        return  foundByWhich || FileUtils::fileExists(command);

    }

    static std::vector<std::string> doNothing(std::vector<std::string> argv)
    {
        return argv;
    }

    bool launch(std::vector<std::string> argv) override
    {
        if (!exists(argv.front()))
        {
            return false;
        }

        argv = convertArgumentsForSystemLaunching(argv);

        std::string command = std::accumulate(argv.begin(), argv.end(), std::string(""), [](std::string a, std::string b) {return a + " " + "\"" + b + "\""; });
        std::string launch = SystemUtils::isWindowsOs() ? ("start \"\" " +  command) :  (command + " &");
        system(launch.c_str());
        return true;
    }
};

#endif 

 // ******************** From: DiffInfo.h
#ifndef APPROVALTESTS_CPP_DIFFINFO_H
#define APPROVALTESTS_CPP_DIFFINFO_H


enum class Type { TEXT, IMAGE, TEXT_AND_IMAGE };



struct DiffInfo
{
    DiffInfo(std::string program, Type type) :
        program(program),
        arguments("%s %s"),
        type(type)
    {
    }
    DiffInfo(std::string program, std::string arguments, Type type) :
        program(program),
        arguments(arguments),
        type(type)
    {
    }
    std::string program;
    std::string arguments;
    Type type;

    std::string getProgramForOs() const
    {
        std::string result = program;
        if (result.rfind("{ProgramFiles}", 0) == 0)
        {
            const std::vector<const char*> envVars =
            {
                "ProgramFiles",
                "ProgramW6432",
                "ProgramFiles(x86)"
            };

            for(const auto& envVar : envVars)
            {
                std::string envVarValue = SystemUtils::safeGetEnv(envVar);
                if (envVarValue.empty())
                {
                    continue;
                }
                envVarValue += '\\';

                auto result1 = StringUtils::replaceAll(result, "{ProgramFiles}", envVarValue);
                if (FileUtils::fileExists(result1))
                {
                    return result1;
                }
            }
        }
        return result;
    }
};


#endif 

 // ******************** From: DiffPrograms.h
#ifndef APPROVALTESTS_CPP_DIFFPROGRAMS_H
#define APPROVALTESTS_CPP_DIFFPROGRAMS_H



#define APPROVAL_TESTS_MACROS_ENTRY(name, defaultValue) \
        static DiffInfo name() { return defaultValue; }


namespace DiffPrograms {


    namespace Mac {
        APPROVAL_TESTS_MACROS_ENTRY(DIFF_MERGE,
              DiffInfo("/Applications/DiffMerge.app/Contents/MacOS/DiffMerge", "%s %s -nosplash", Type::TEXT))

        APPROVAL_TESTS_MACROS_ENTRY(BEYOND_COMPARE, DiffInfo("/Applications/Beyond Compare.app/Contents/MacOS/bcomp", Type::TEXT))

        APPROVAL_TESTS_MACROS_ENTRY(KALEIDOSCOPE, DiffInfo("/Applications/Kaleidoscope.app/Contents/MacOS/ksdiff", Type::TEXT_AND_IMAGE))

        APPROVAL_TESTS_MACROS_ENTRY(KDIFF3, DiffInfo("/Applications/kdiff3.app/Contents/MacOS/kdiff3", "%s %s -m", Type::TEXT))

        APPROVAL_TESTS_MACROS_ENTRY(P4MERGE, DiffInfo("/Applications/p4merge.app/Contents/MacOS/p4merge", Type::TEXT_AND_IMAGE))

        APPROVAL_TESTS_MACROS_ENTRY(TK_DIFF, DiffInfo("/Applications/TkDiff.app/Contents/MacOS/tkdiff", Type::TEXT))

        APPROVAL_TESTS_MACROS_ENTRY(VS_CODE, DiffInfo("/Applications/Visual Studio Code.app/Contents/Resources/app/bin/code", "-d %s %s", Type::TEXT))
    }
    namespace Linux {
        
        APPROVAL_TESTS_MACROS_ENTRY(KDIFF3, DiffInfo("kdiff3", Type::TEXT))

        APPROVAL_TESTS_MACROS_ENTRY(MELD, DiffInfo("meld", Type::TEXT))
    }
    namespace Windows {
        APPROVAL_TESTS_MACROS_ENTRY(BEYOND_COMPARE_3, DiffInfo("{ProgramFiles}Beyond Compare 3\\BCompare.exe", Type::TEXT_AND_IMAGE))

        APPROVAL_TESTS_MACROS_ENTRY(BEYOND_COMPARE_4, DiffInfo("{ProgramFiles}Beyond Compare 4\\BCompare.exe", Type::TEXT_AND_IMAGE))

        APPROVAL_TESTS_MACROS_ENTRY(TORTOISE_IMAGE_DIFF,
              DiffInfo("{ProgramFiles}TortoiseSVN\\bin\\TortoiseIDiff.exe", "/left:%s /right:%s", Type::IMAGE))

        APPROVAL_TESTS_MACROS_ENTRY(TORTOISE_TEXT_DIFF, DiffInfo("{ProgramFiles}TortoiseSVN\\bin\\TortoiseMerge.exe", Type::TEXT))

        APPROVAL_TESTS_MACROS_ENTRY(WIN_MERGE_REPORTER, DiffInfo("{ProgramFiles}WinMerge\\WinMergeU.exe", Type::TEXT_AND_IMAGE))

        APPROVAL_TESTS_MACROS_ENTRY(ARAXIS_MERGE, DiffInfo("{ProgramFiles}Araxis\\Araxis Merge\\Compare.exe", Type::TEXT_AND_IMAGE))

        APPROVAL_TESTS_MACROS_ENTRY(CODE_COMPARE, DiffInfo("{ProgramFiles}Devart\\Code Compare\\CodeCompare.exe", Type::TEXT))

        APPROVAL_TESTS_MACROS_ENTRY(KDIFF3, DiffInfo("{ProgramFiles}KDiff3\\kdiff3.exe", Type::TEXT))
        APPROVAL_TESTS_MACROS_ENTRY(VS_CODE, DiffInfo("{ProgramFiles}Microsoft VS Code\\Code.exe", "-d %s %s", Type::TEXT))

    }
}

#endif 

 // ******************** From: GenericDiffReporter.h
#ifndef APPROVALTESTS_CPP_GENERICDIFFREPORTER_H
#define APPROVALTESTS_CPP_GENERICDIFFREPORTER_H


class GenericDiffReporter : public CommandReporter {
private:
    SystemLauncher launcher;
public:
    GenericDiffReporter(const std::string& program) : CommandReporter(program, &launcher)
    {
        checkForCygwin();
    }
    GenericDiffReporter(const DiffInfo& info) : CommandReporter(info.getProgramForOs().c_str(), &launcher)
    {
        checkForCygwin();
    }

    void checkForCygwin()
    {
        if ( SystemUtils::isCygwin())
        {
            launcher.setConvertArgumentsForSystemLaunchingFunction(convertForCygwin);
        }
    }

    static std::vector<std::string> convertForCygwin(std::vector<std::string> argv)
    {
        if (! SystemUtils::isCygwin())
        {
            return argv;
        }
        std::vector<std::string> copy = argv;
        for( size_t i = 0; i != argv.size(); ++i )
        {
            if ( i == 0)
            {
                copy[i] = "$(cygpath '"  + argv[i] + "')";
            }
            else
            {
                copy[i] = "$(cygpath -aw '"  + argv[i] + "')";
            }
        }
        return copy;
    }
};

#endif 

 // ******************** From: FirstWorkingReporter.h
#ifndef APPROVALTESTS_CPP_FIRSTWORKINGREPORTER_H
#define APPROVALTESTS_CPP_FIRSTWORKINGREPORTER_H


class FirstWorkingReporter : public Reporter
{
private:
    std::vector< std::unique_ptr<Reporter> > reporters;
public:
    
    FirstWorkingReporter(std::vector<Reporter*> theReporters)
    {
        for(auto r : theReporters)
        {
            reporters.push_back(std::unique_ptr<Reporter>(r));
        }
    }

    bool report(std::string received, std::string approved) const override
    {
        for(auto& r : reporters)
        {
            if (r->report(received, approved))
            {
                return true;
            }
        }
        return false;
    }
};

#endif 

 // ******************** From: LinuxReporters.h
#ifndef APPROVALTESTS_CPP_LINUXREPORTERS_H
#define APPROVALTESTS_CPP_LINUXREPORTERS_H


namespace Linux
{
    class KDiff3Reporter : public GenericDiffReporter {
    public:
        KDiff3Reporter() : GenericDiffReporter(DiffPrograms::Linux::KDIFF3()) {};
    };

    class MeldReporter : public GenericDiffReporter {
    public:
        MeldReporter() : GenericDiffReporter(DiffPrograms::Linux::MELD()) {};
    };

    class LinuxDiffReporter : public FirstWorkingReporter
    {
    public:
        LinuxDiffReporter() : FirstWorkingReporter(
                {
                        
                        new MeldReporter(),
                        new KDiff3Reporter()
                        
                }
        )
        {
        }
    };

}

#endif 

 // ******************** From: MacReporters.h
#ifndef APPROVALTESTS_CPP_MACREPORTERS_H
#define APPROVALTESTS_CPP_MACREPORTERS_H


namespace Mac {
    class DiffMergeReporter : public GenericDiffReporter {
    public:
        DiffMergeReporter() : GenericDiffReporter(DiffPrograms::Mac::DIFF_MERGE()) {}
    };

    class VisualStudioCodeReporter : public GenericDiffReporter {
    public:
        VisualStudioCodeReporter() : GenericDiffReporter(DiffPrograms::Mac::VS_CODE()) {}
    };

    class BeyondCompareReporter : public GenericDiffReporter {
    public:
        BeyondCompareReporter() : GenericDiffReporter(DiffPrograms::Mac::BEYOND_COMPARE()) {}
    };

    class KaleidoscopeReporter : public GenericDiffReporter {
    public:
        KaleidoscopeReporter() : GenericDiffReporter(DiffPrograms::Mac::KALEIDOSCOPE()) {}
    };

    class KDiff3Reporter : public GenericDiffReporter {
    public:
        KDiff3Reporter() : GenericDiffReporter(DiffPrograms::Mac::KDIFF3()) {}
    };

    class P4MergeReporter : public GenericDiffReporter {
    public:
        P4MergeReporter() : GenericDiffReporter(DiffPrograms::Mac::P4MERGE()) {}
    };

    class TkDiffReporter : public GenericDiffReporter {
    public:
        TkDiffReporter() : GenericDiffReporter(DiffPrograms::Mac::TK_DIFF()) {}
    };

    class MacDiffReporter : public FirstWorkingReporter {
    public:
        MacDiffReporter() : FirstWorkingReporter(
                {
                        
                        new BeyondCompareReporter(),
                        new DiffMergeReporter(),
                        new KaleidoscopeReporter(),
                        new P4MergeReporter(),
                        new KDiff3Reporter(),
                        new TkDiffReporter(),
                        new VisualStudioCodeReporter()
                        
                }
        ) {
        }
    };
}

#endif 

 // ******************** From: WindowsReporters.h
#ifndef APPROVALTESTS_CPP_WINDOWSREPORTERS_H
#define APPROVALTESTS_CPP_WINDOWSREPORTERS_H


namespace Windows {
    class BeyondCompare3Reporter : public GenericDiffReporter {
    public:
        BeyondCompare3Reporter() : GenericDiffReporter(DiffPrograms::Windows::BEYOND_COMPARE_3()) {};
    };

  class VisualStudioCodeReporter : public GenericDiffReporter {
    public:
      VisualStudioCodeReporter() : GenericDiffReporter(DiffPrograms::Windows::VS_CODE()) {};
    };

    class BeyondCompare4Reporter : public GenericDiffReporter {
    public:
        BeyondCompare4Reporter() : GenericDiffReporter(DiffPrograms::Windows::BEYOND_COMPARE_4()) {};
    };

    class BeyondCompareReporter : public FirstWorkingReporter {
    public:
        BeyondCompareReporter() : FirstWorkingReporter({new BeyondCompare4Reporter(), new BeyondCompare3Reporter()}) {
        }
    };

    class TortoiseImageDiffReporter : public GenericDiffReporter {
    public:
        TortoiseImageDiffReporter() : GenericDiffReporter(DiffPrograms::Windows::TORTOISE_IMAGE_DIFF()) {};
    };

    class TortoiseTextDiffReporter : public GenericDiffReporter {
    public:
        TortoiseTextDiffReporter() : GenericDiffReporter(DiffPrograms::Windows::TORTOISE_TEXT_DIFF()) {};
    };

    class TortoiseDiffReporter : public FirstWorkingReporter {
    public:
        TortoiseDiffReporter() : FirstWorkingReporter(
                {new TortoiseTextDiffReporter(), new TortoiseImageDiffReporter()}) {
        }
    };

    class WinMergeReporter : public GenericDiffReporter {
    public:
        WinMergeReporter() : GenericDiffReporter(DiffPrograms::Windows::WIN_MERGE_REPORTER()) {};
    };

    class AraxisMergeReporter : public GenericDiffReporter {
    public:
        AraxisMergeReporter() : GenericDiffReporter(DiffPrograms::Windows::ARAXIS_MERGE()) {};
    };

    class CodeCompareReporter : public GenericDiffReporter {
    public:
        CodeCompareReporter() : GenericDiffReporter(DiffPrograms::Windows::CODE_COMPARE()) {};
    };

    class KDiff3Reporter : public GenericDiffReporter {
    public:
        KDiff3Reporter() : GenericDiffReporter(DiffPrograms::Windows::KDIFF3()) {};
    };

    class WindowsDiffReporter : public FirstWorkingReporter {
    public:
        WindowsDiffReporter() : FirstWorkingReporter(
                {
                        
                        new TortoiseDiffReporter(),
                        new BeyondCompareReporter(),
                        new WinMergeReporter(),
                        new AraxisMergeReporter(),
                        new CodeCompareReporter(),
                        new KDiff3Reporter(),
                        new VisualStudioCodeReporter(),
                        
                }
        ) {
        }
    };
}

#endif 

 // ******************** From: DiffReporter.h
#ifndef APPROVALTESTS_CPP_DIFFREPORTER_H
#define APPROVALTESTS_CPP_DIFFREPORTER_H


class DiffReporter : public FirstWorkingReporter
{
public:
    DiffReporter() : FirstWorkingReporter(
            {
                    new Mac::MacDiffReporter(),
                    new Linux::LinuxDiffReporter(),
                    new Windows::WindowsDiffReporter()
            }
    )
    {
    }
};

#endif 

 // ******************** From: DefaultReporterFactory.h
#ifndef APPROVALTESTS_CPP_DEFAULTREPORTERFACTORY_H
#define APPROVALTESTS_CPP_DEFAULTREPORTERFACTORY_H




class DefaultReporterFactory
{
private:
    using ReporterContainer = std::vector< std::shared_ptr<Reporter> >;
    APPROVAL_TESTS_MACROS_STATIC(ReporterContainer, defaultReporterContainer, DefaultReporterFactory::createReporterContainer())
    
    static ReporterContainer* createReporterContainer()
    {
        auto container = new ReporterContainer; 
        container->push_back( std::make_shared<DiffReporter>());
        return container;
    }

public:
    static std::shared_ptr<Reporter> getDefaultReporter()
    {
        return defaultReporterContainer().at(0);
    }
    
    static void setDefaultReporter( const std::shared_ptr<Reporter>& reporter)
    {
        defaultReporterContainer().at(0) = reporter;
    }

};

#endif 

 // ******************** From: DefaultReporterDisposer.h
#ifndef APPROVALTESTS_CPP_DEFAULTREPORTERDISPOSER_H
#define APPROVALTESTS_CPP_DEFAULTREPORTERDISPOSER_H



class DefaultReporterDisposer
{
private:
    std::shared_ptr<Reporter> previous_result;
public:
    explicit DefaultReporterDisposer(const std::shared_ptr<Reporter>& reporter)
    {
        previous_result = DefaultReporterFactory::getDefaultReporter();
        DefaultReporterFactory::setDefaultReporter(reporter);
    }

    ~DefaultReporterDisposer()
    {
        DefaultReporterFactory::setDefaultReporter(previous_result);
    }
};

#endif 

 // ******************** From: DefaultReporter.h
#ifndef APPROVALTESTS_CPP_DEFAULTREPORTER_H
#define APPROVALTESTS_CPP_DEFAULTREPORTER_H



class DefaultReporter : public Reporter
{
public:
    virtual bool report(std::string received, std::string approved) const override
    {
        return DefaultReporterFactory::getDefaultReporter()->report(received, approved);
    }
};

#endif 

 // ******************** From: ApprovalNamer.h
#ifndef APPROVALTESTS_CPP_APPROVALNAMER_H
#define APPROVALTESTS_CPP_APPROVALNAMER_H


using std::string;

class ApprovalNamer
{
public:
    virtual ~ApprovalNamer() = default;
    virtual string getApprovedFile(string extensionWithDot) = 0;
    virtual string getReceivedFile(string extensionWithDot) = 0;

};

#endif

 // ******************** From: ApprovalTestNamer.h
#ifndef APPROVALTESTS_CPP_APPROVALTESTNAMER_H
#define APPROVALTESTS_CPP_APPROVALTESTNAMER_H


using std::string;

class TestName {
public:
    const string& getFileName() const {
        return fileName;
    }

    void setFileName(const string &file) {
        fileName = SystemUtils::checkFilenameCase(file);
    }

    std::vector<string> sections;
private:
    string fileName;
};

class TestConfiguration {
public:
    std::string subdirectory;
};

class ApprovalTestNamer : public ApprovalNamer {
private:
public:
    ApprovalTestNamer() {
    }

    std::string getTestName() const {
        std::stringstream ext;
        auto test = getCurrentTest();
        for (size_t i = 0; i < test.sections.size(); i++) {
            if (0 < i) {
                ext << ".";
            }
            ext << test.sections[i];
        }

        return convertToFileName(ext.str());
    }

    static bool isForbidden(char c)
    {
        static std::string forbiddenChars("\\/:?\"<>|' ");
        return std::string::npos != forbiddenChars.find(c);
    }

    static string convertToFileName(const string& fileName)
    {
        std::stringstream result;
        for (auto ch : fileName)
        {
            if (!isForbidden(ch))
            {
                result << ch;
            }
            else
            {
                result << "_";
            }
        }
        return result.str();
    }

// <SingleHpp unalterable>
    static TestName &getCurrentTest()
    {
        try
        {
            return currentTest();
        }
        catch( const std::runtime_error& )
        {
            std::string lineBreak = "************************************************************************************n";
            std::string lineBuffer = "*                                                                                  *n";
            std::string helpMessage =
                "nn" + lineBreak + lineBuffer + 
R"(* Welcome to Approval Tests.
* 
* You have forgotten to configure your test framework for Approval Tests.
* 
* To do this in Catch, add the following to your main.cpp:
* 
*     #define APPROVALS_CATCH
*     #include "ApprovalTests.hpp"
* 
* To do this in Google Test, add the following to your main.cpp:
* 
*     #define APPROVALS_GOOGLETEST
*     #include "ApprovalTests.hpp"
* 
* To do this in doctest, add the following to your main.cpp:
* 
*     #define APPROVALS_DOCTEST
*     #include "ApprovalTests.hpp"
* 
* For more information, please visit:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/GettingStarted.md
)" +
                    lineBuffer + lineBreak + 'n';
            throw std::runtime_error( helpMessage );
        }
    }
// </SingleHpp>


    
    string getFileName() {
        return getSourceFileName();
    }


    std::string getSourceFileName() const {
        auto file = getCurrentTest().getFileName();
        auto start = file.rfind(SystemUtils::getDirectorySeparator()) + 1;
        auto end = file.rfind(".");
        auto fileName = file.substr(start, end - start);
        return convertToFileName(fileName);
    }

    string getDirectory() {
        auto file = getCurrentTest().getFileName();
        auto end = file.rfind(SystemUtils::getDirectorySeparator()) + 1;
        auto directory = file.substr(0, end);
        if ( ! testConfiguration().subdirectory.empty() )
        {
            directory += testConfiguration().subdirectory + SystemUtils::getDirectorySeparator(); 
            SystemUtils::ensureDirectoryExists(directory);
        }
        return directory;
    }

    APPROVAL_TESTS_MACROS_STATIC(TestName, currentTest, NULL)
    APPROVAL_TESTS_MACROS_STATIC(TestConfiguration, testConfiguration, new TestConfiguration)

    virtual string getApprovedFile(string extensionWithDot) {

        return getFullFileName(".approved", extensionWithDot);
    }

    virtual string getReceivedFile(string extensionWithDot) {

        return getFullFileName(".received", extensionWithDot);
    }

    std::string getOutputFileBaseName() const {
        return getSourceFileName() + "." + getTestName();
    }

    std::string getFullFileName(string approved, string extensionWithDot) {
        std::stringstream ext;
        ext << getDirectory() << getOutputFileBaseName() << approved << extensionWithDot;
        return ext.str();
    }
};

#endif

 // ******************** From: SubdirectoryDisposer.h
#ifndef APPROVALTESTS_CPP_SUBDIRECTORYDISPOSER_H
#define APPROVALTESTS_CPP_SUBDIRECTORYDISPOSER_H




class SubdirectoryDisposer
{
private:
    std::string previous_result;
public:
    explicit SubdirectoryDisposer(std::string subdirectory)
    {
        previous_result = ApprovalTestNamer::testConfiguration().subdirectory;
        ApprovalTestNamer::testConfiguration().subdirectory = subdirectory;
    }

    ~SubdirectoryDisposer()
    {
        ApprovalTestNamer::testConfiguration().subdirectory = previous_result;
    }
};

#endif 

 // ******************** From: ExistingFileNamer.h
#ifndef APPROVALTESTS_CPP_EXISTINGFILENAMER_H
#define APPROVALTESTS_CPP_EXISTINGFILENAMER_H


class ExistingFileNamer: public ApprovalNamer{
    ApprovalTestNamer namer;
    std::string filePath;
public:
    ExistingFileNamer(std::string filePath): filePath(filePath){

    }
    virtual string getApprovedFile(string extensionWithDot) {
        return namer.getApprovedFile(extensionWithDot);
    }
    virtual string getReceivedFile(string ) {
        return filePath;
    }

};

#endif 

 // ******************** From: DefaultFrontLoadedReporter.h
#ifndef APPROVALTESTS_CPP_DEFAULTFRONTLOADEDREPORTER_H
#define APPROVALTESTS_CPP_DEFAULTFRONTLOADEDREPORTER_H



class DefaultFrontLoadedReporter : public Reporter
{
public:
    virtual bool report(std::string , std::string ) const override
    {
        return false;
    }
};

#endif 

 // ******************** From: FrontLoadedReporterFactory.h
#ifndef APPROVALTESTS_CPP_FRONTLOADEDREPORTERFACTORY_H
#define APPROVALTESTS_CPP_FRONTLOADEDREPORTERFACTORY_H




class FrontLoadedReporterFactory
{
    using ReporterContainer = std::vector< std::shared_ptr<Reporter> >;
    APPROVAL_TESTS_MACROS_STATIC(ReporterContainer, frontLoadedReporterContainer, FrontLoadedReporterFactory::createReporterContainer())

    static ReporterContainer* createReporterContainer()
    {
        auto container = new ReporterContainer;
        container->push_back( std::make_shared<DefaultFrontLoadedReporter>());
        return container;
    }

public:
    static std::shared_ptr<Reporter> getFrontLoadedReporter()
    {
        return frontLoadedReporterContainer().at(0);
    }

    static void setFrontLoadedReporter( const std::shared_ptr<Reporter>& reporter)
    {
        frontLoadedReporterContainer().at(0) = reporter;
    }
};

#endif 

 // ******************** From: FrontLoadedReporterDisposer.h
#ifndef APPROVALTESTS_CPP_FRONTLOADEDREPORTERDISPOSER_H
#define APPROVALTESTS_CPP_FRONTLOADEDREPORTERDISPOSER_H



class FrontLoadedReporterDisposer
{
private:
    std::shared_ptr<Reporter> previous_result;
public:
    explicit FrontLoadedReporterDisposer(const std::shared_ptr<Reporter>& reporter)
    {
        previous_result = FrontLoadedReporterFactory::getFrontLoadedReporter();
        FrontLoadedReporterFactory::setFrontLoadedReporter(reporter);
    }

    ~FrontLoadedReporterDisposer()
    {
        FrontLoadedReporterFactory::setFrontLoadedReporter(previous_result);
    }

};


#endif 

 // ******************** From: ApprovalComparator.h
#ifndef APPROVALTESTS_CPP_APPROVALCOMPARATOR_H
#define APPROVALTESTS_CPP_APPROVALCOMPARATOR_H


class ApprovalComparator
{
public:
    virtual ~ApprovalComparator() = default;

    virtual bool contentsAreEquivalent(std::string receivedPath,
                                       std::string approvedPath) const = 0;
};

#endif 

 // ******************** From: TextFileComparator.h
#ifndef APPROVALTESTS_CPP_TEXTFILECOMPARATOR_H
#define APPROVALTESTS_CPP_TEXTFILECOMPARATOR_H


class TextFileComparator : public ApprovalComparator
{
public:
    static std::ifstream::int_type getNextRelevantCharacter(std::ifstream& astream)
    {
        auto ch = astream.get();
        if (ch == '\r')
        {
            return astream.get();
        }
        else
        {
            return ch;
        }
    }

    virtual bool contentsAreEquivalent(std::string receivedPath,
                                       std::string approvedPath) const
    {
        std::ifstream astream(approvedPath.c_str(),
                              std::ios::binary | std::ifstream::in);
        std::ifstream rstream(receivedPath.c_str(),
                              std::ios::binary | std::ifstream::in);

        while (astream.good() && rstream.good()) {
            int a = getNextRelevantCharacter(astream);
            int r = getNextRelevantCharacter(rstream);

            if (a != r) {
                return false;
            }
        }
        return true;
    }
};
#endif 

 // ******************** From: ApprovalException.h
#ifndef APPROVALTESTS_CPP_APPROVALEXCEPTION_H
#define APPROVALTESTS_CPP_APPROVALEXCEPTION_H


class ApprovalException : public std::exception
{
private:
    std::string message;
public:
    ApprovalException( const std::string& msg ) : message( msg ) {}

    virtual const char *what() const throw()
    {
        return message.c_str();
    }
};

class ApprovalMismatchException : public ApprovalException
{
private:
    std::string format( const std::string &received, const std::string &approved )
    {
        std::stringstream s;
        s << "Failed Approval: \n"
          << "Received does not match approved \n"
          << "Received : \"" << received << "\" \n"
          << "Approved : \"" << approved << "\"";
        return s.str();
    }
public:
    ApprovalMismatchException( std::string received, std::string approved )
        : ApprovalException( format( received, approved ) )
    {
    }
};

class ApprovalMissingException : public ApprovalException
{
private:
    std::string format( const std::string &file )
    {
        std::stringstream s;
        s << "Failed Approval: \n"
          << "Approval File Not Found \n"
          << "File: \"" << file << '"';
        return s.str();
    }
public:
    ApprovalMissingException( std::string , std::string approved )
        : ApprovalException( format( approved ) )
    {
    }
};

#endif

 // ******************** From: FileApprover.h
#ifndef APPROVALTESTS_CPP_FILEAPPROVER_H
#define APPROVALTESTS_CPP_FILEAPPROVER_H


class FileApprover {
private:
    using ComparatorContainer = std::map< std::string, std::shared_ptr<ApprovalComparator> >;
    APPROVAL_TESTS_MACROS_STATIC(ComparatorContainer, comparators, new ComparatorContainer())

public:
    FileApprover() {};

    ~FileApprover() {};

    static void registerComparator(std::string extensionWithDot, std::shared_ptr<ApprovalComparator> comparator)
    {
        comparators()[extensionWithDot] = comparator;
    }

    static std::shared_ptr<ApprovalComparator> getComparatorForFile(string receivedPath) {
        const std::string fileExtension = FileUtils::getExtensionWithDot(receivedPath);
        auto iterator = comparators().find(fileExtension);
        if (iterator != comparators().end()) {
            return iterator->second;
        }
        return std::make_shared<TextFileComparator>();
    }

    
    static void verify(std::string receivedPath,
                       std::string approvedPath,
                       const ApprovalComparator& comparator) {
        if (!FileUtils::fileExists(approvedPath)) {
            throw ApprovalMissingException(receivedPath, approvedPath);
        }

        if (!FileUtils::fileExists(receivedPath)) {
            throw ApprovalMissingException(approvedPath, receivedPath);
        }

        if (!comparator.contentsAreEquivalent(receivedPath, approvedPath)) {
            throw ApprovalMismatchException(receivedPath, approvedPath);
        }
    }

    static void verify(std::string receivedPath,
                       std::string approvedPath) {
        verify(receivedPath, approvedPath, *getComparatorForFile(receivedPath));
    }

    static void verify(ApprovalNamer& n, ApprovalWriter& s, const Reporter& r) {
        std::string approvedPath = n.getApprovedFile(s.getFileExtensionWithDot());
        std::string receivedPath = n.getReceivedFile(s.getFileExtensionWithDot());
        s.write(receivedPath);
        try
        {
            verify(receivedPath, approvedPath);
            s.cleanUpReceived(receivedPath);
        }
        catch (const ApprovalException&) {
            reportAfterTryingFrontLoadedReporter(receivedPath, approvedPath, r);
            throw;
        }
    }

    static void
    reportAfterTryingFrontLoadedReporter(const string &receivedPath, const string &approvedPath, const Reporter &r)
    {
        auto tryFirst = FrontLoadedReporterFactory::getFrontLoadedReporter();
        if (!tryFirst->report(receivedPath, approvedPath))
        {
            r.report(receivedPath, approvedPath);
        }
    }


};

#endif

 // ******************** From: Approvals.h
#ifndef APPROVALTESTS_CPP_APPROVALS_H
#define APPROVALTESTS_CPP_APPROVALS_H


class Approvals {
private:
    Approvals() {}

    ~Approvals() {}

public:
    static std::shared_ptr<ApprovalNamer> getDefaultNamer()
    {
        return std::make_shared<ApprovalTestNamer>();
    }

    static void verify(std::string contents, const Reporter &reporter = DefaultReporter()) {
        StringWriter writer(contents);
        ApprovalTestNamer namer;
        FileApprover::verify(namer, writer, reporter);
    }

    template<typename T>
    static void verify(const T& contents, const Reporter &reporter = DefaultReporter()) {
        verify(StringUtils::toString(contents), reporter);
    }

    template<typename T>
    static void verify(const T& contents,
                       std::function<void(const T&, std::ostream &)> converter,
                       const Reporter &reporter = DefaultReporter())
    {
        std::stringstream s;
        converter(contents, s);
        verify(s.str(), reporter);
    }

    static void verifyExceptionMessage(
        std::function<void(void)> functionThatThrows,
        const Reporter &reporter = DefaultReporter())
    {
        std::string message = "*** no exception thrown ***";
        try
        {
            functionThatThrows();
        }
        catch(const std::exception& e)
        {
            message = e.what();
        }
        Approvals::verify(message, reporter);
    }
    
    template<typename Iterator>
    static void verifyAll(std::string header,
                          const Iterator &start, const Iterator &finish,
                          std::function<void(typename Iterator::value_type, std::ostream &)> converter,
                          const Reporter &reporter = DefaultReporter()) {
        std::stringstream s;
        if (!header.empty()) {
            s << header << "\n\n\n";
        }
        for (auto it = start; it != finish; ++it) {
            converter(*it, s);
            s << '\n';
        }
        verify(s.str(), reporter);
    }

    template<typename Container>
    static void verifyAll(std::string header,
                          const Container &list,
                          std::function<void(typename Container::value_type, std::ostream &)> converter,
                          const Reporter &reporter = DefaultReporter()) {
        verifyAll<typename Container::const_iterator>(header, list.begin(), list.end(), converter, reporter);
    }

    template<typename T>
    static void verifyAll(std::string header,
                          const std::vector<T> &list,
                          const Reporter &reporter = DefaultReporter()) {
        int i = 0;
        verifyAll<std::vector<T>>(header, list, [&](T e, std::ostream &s) { s << "[" << i++ << "] = " << e; },
                                  reporter);
    }

    template<typename T>
    static void verifyAll(const std::vector<T> &list,
                          const Reporter &reporter = DefaultReporter()) {
        verifyAll<T>("", list, reporter);
    }

    static void verifyExistingFile(const std::string filePath, const Reporter &reporter = DefaultReporter()) {
        ExistingFile writer(filePath);
        ExistingFileNamer namer(filePath);
        FileApprover::verify(namer, writer, reporter);
    }
    
    static SubdirectoryDisposer useApprovalsSubdirectory(std::string subdirectory = "approval_tests")
    {
        return SubdirectoryDisposer(subdirectory);
    }

    static DefaultReporterDisposer useAsDefaultReporter(const std::shared_ptr<Reporter>& reporter)
    {
        return DefaultReporterDisposer(reporter);
    }

    static FrontLoadedReporterDisposer useAsFrontLoadedReporter(const std::shared_ptr<Reporter>& reporter)
    {
        return FrontLoadedReporterDisposer(reporter);
    }

};

#endif

 // ******************** From: Catch2Approvals.h

#ifndef APPROVALTESTS_CPP_CATCH2APPROVALS_H
#define APPROVALTESTS_CPP_CATCH2APPROVALS_H


// <SingleHpp unalterable>
#ifdef APPROVALS_CATCH
#define CATCH_CONFIG_MAIN

#include <Catch.hpp>

struct Catch2ApprovalListener : Catch::TestEventListenerBase {
    using TestEventListenerBase::TestEventListenerBase;
    TestName currentTest;

    Catch2ApprovalListener(Catch::ReporterConfig const &_config) : Catch::TestEventListenerBase(_config) {}

    virtual void testCaseStarting(Catch::TestCaseInfo const &testInfo) override {

        currentTest.setFileName(testInfo.lineInfo.file);
        ApprovalTestNamer::currentTest(&currentTest);
    }

    virtual void testCaseEnded(Catch::TestCaseStats const &/*testCaseStats*/) override {
        while (!currentTest.sections.empty()) {
            currentTest.sections.pop_back();
        }
    }

    virtual void sectionStarting(Catch::SectionInfo const &sectionInfo) override {
        currentTest.sections.push_back(sectionInfo.name);
    }

    virtual void sectionEnded(Catch::SectionStats const &/*sectionStats*/) override {
        currentTest.sections.pop_back();
    }
};
CATCH_REGISTER_LISTENER(Catch2ApprovalListener)

#endif
#ifdef TEST_COMMIT_REVERT_CATCH

struct Catch2TestCommitRevert : Catch::TestEventListenerBase {
    using TestEventListenerBase::TestEventListenerBase;
    virtual void  testRunEnded( Catch::TestRunStats const& testRunStats )override{
        bool commit = testRunStats.totals.testCases.allOk();
        std::string message = "r ";
        if (commit) {
            std::cout << "git add -A n";
            std::cout << "git commit -m " << message;
        } else
        {
            std::cout << "git clean -fd n";
            std::cout << "git reset --hard HEAD n";
        }
    }
};
CATCH_REGISTER_LISTENER(Catch2TestCommitRevert)
#endif
// </SingleHpp>
#endif 

 // ******************** From: CombinationApprovals.h
#ifndef APPROVALTESTS_CPP_COMBINATIONAPPROVALS_H
#define APPROVALTESTS_CPP_COMBINATIONAPPROVALS_H


class Empty
{
public:
    template< typename Other>
    bool operator!=(const Other &) const {
        return true;
    }

    bool operator!=(const Empty &) const {
        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, const Empty&) {
        os << "This should never be written - see Empty\n";
        return os;
    }

};

class CombinationApprovals
{
public:
    CombinationApprovals() = delete;
    ~CombinationApprovals() = delete;

    template <
        typename Function,
        typename Container1,
        typename Container2,
        typename Container3,
        typename Container4,
        typename Container5,
        typename Container6,
        typename Container7,
        typename Container8,
        typename Container9,
        
        typename std::enable_if<! std::is_base_of<Reporter, Container9>::value, int>::type = 0>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Container2& inputs2,
        const Container3& inputs3,
        const Container4& inputs4,
        const Container5& inputs5,
        const Container6& inputs6,
        const Container7& inputs7,
        const Container8& inputs8,
        const Container9& inputs9,
        const Reporter& reporter = DefaultReporter())
    {
        Empty empty;
        std::stringstream s;
        for (auto input1 : inputs1)
        {
            for (auto input2 : inputs2)
            {
                for (auto input3 : inputs3)
                {
                    for (auto input4 : inputs4)
                    {
                        for (auto input5 : inputs5)
                        {
                            for (auto input6 : inputs6)
                            {
                                for (auto input7 : inputs7)
                                {
                                    for (auto input8 : inputs8)
                                    {
                                        for (auto input9 : inputs9)
                                        {
                                            s << "(" << input1;
                                            if (empty != input2) { s << ", " << input2; }
                                            if (empty != input3) { s << ", " << input3; }
                                            if (empty != input4) { s << ", " << input4; }
                                            if (empty != input5) { s << ", " << input5; }
                                            if (empty != input6) { s << ", " << input6; }
                                            if (empty != input7) { s << ", " << input7; }
                                            if (empty != input8) { s << ", " << input8; }
                                            if (empty != input9) { s << ", " << input9; }
                                            s << ") => " << converter(input1, input2, input3, input4, input5,
                                                                      input6, input7, input8, input9) << '\n';
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        Approvals::verify(s.str(), reporter);
    }

    template <
        typename Function,
        typename Container1,
        typename Container2,
        typename Container3,
        typename Container4,
        typename Container5,
        typename Container6,
        typename Container7,
        typename Container8,
        
        typename std::enable_if<! std::is_base_of<Reporter, Container8>::value, int>::type = 0>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Container2& inputs2,
        const Container3& inputs3,
        const Container4& inputs4,
        const Container5& inputs5,
        const Container6& inputs6,
        const Container7& inputs7,
        const Container8& inputs8,
        const Reporter& reporter = DefaultReporter())
    {
        verifyAllCombinations(
            [&](typename Container1::value_type i1,
                typename Container2::value_type i2,
                typename Container3::value_type i3,
                typename Container4::value_type i4,
                typename Container5::value_type i5,
                typename Container6::value_type i6,
                typename Container7::value_type i7,
                typename Container8::value_type i8,
                Empty){return converter(i1, i2, i3, i4, i5, i6, i7, i8);},
            inputs1,
            inputs2,
            inputs3,
            inputs4,
            inputs5,
            inputs6,
            inputs7,
            inputs8,
            empty(),
            reporter);
    }

    template <
        typename Function,
        typename Container1,
        typename Container2,
        typename Container3,
        typename Container4,
        typename Container5,
        typename Container6,
        typename Container7,
        
        typename std::enable_if<! std::is_base_of<Reporter, Container7>::value, int>::type = 0>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Container2& inputs2,
        const Container3& inputs3,
        const Container4& inputs4,
        const Container5& inputs5,
        const Container6& inputs6,
        const Container7& inputs7,
        const Reporter& reporter = DefaultReporter())
    {
        verifyAllCombinations(
            [&](typename Container1::value_type i1,
                typename Container2::value_type i2,
                typename Container3::value_type i3,
                typename Container4::value_type i4,
                typename Container5::value_type i5,
                typename Container6::value_type i6,
                typename Container7::value_type i7,
                Empty){return converter(i1, i2, i3, i4, i5, i6, i7);},
            inputs1,
            inputs2,
            inputs3,
            inputs4,
            inputs5,
            inputs6,
            inputs7,
            empty(),
            reporter);
    }

    template <
        typename Function,
        typename Container1,
        typename Container2,
        typename Container3,
        typename Container4,
        typename Container5,
        typename Container6,
        
        typename std::enable_if<! std::is_base_of<Reporter, Container6>::value, int>::type = 0>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Container2& inputs2,
        const Container3& inputs3,
        const Container4& inputs4,
        const Container5& inputs5,
        const Container6& inputs6,
        const Reporter& reporter = DefaultReporter())
    {
        verifyAllCombinations(
            [&](typename Container1::value_type i1,
                typename Container2::value_type i2,
                typename Container3::value_type i3,
                typename Container4::value_type i4,
                typename Container5::value_type i5,
                typename Container6::value_type i6,
                Empty){return converter(i1, i2, i3, i4, i5, i6);},
            inputs1,
            inputs2,
            inputs3,
            inputs4,
            inputs5,
            inputs6,
            empty(),
            reporter);
    }

    template <
        typename Function,
        typename Container1,
        typename Container2,
        typename Container3,
        typename Container4,
        typename Container5,
        
        typename std::enable_if<! std::is_base_of<Reporter, Container5>::value, int>::type = 0>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Container2& inputs2,
        const Container3& inputs3,
        const Container4& inputs4,
        const Container5& inputs5,
        const Reporter& reporter = DefaultReporter())
    {
        verifyAllCombinations(
            [&](typename Container1::value_type i1,
                typename Container2::value_type i2,
                typename Container3::value_type i3,
                typename Container4::value_type i4,
                typename Container5::value_type i5,
                Empty){return converter(i1, i2, i3, i4, i5);},
            inputs1,
            inputs2,
            inputs3,
            inputs4,
            inputs5,
            empty(),
            reporter);
    }

    template <
        typename Function,
        typename Container1,
        typename Container2,
        typename Container3,
        typename Container4,
        
        typename std::enable_if<! std::is_base_of<Reporter, Container4>::value, int>::type = 0>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Container2& inputs2,
        const Container3& inputs3,
        const Container4& inputs4,
        const Reporter& reporter = DefaultReporter())
    {
        verifyAllCombinations(
            [&](typename Container1::value_type i1,
                typename Container2::value_type i2,
                typename Container3::value_type i3,
                typename Container4::value_type i4,
                Empty){return converter(i1, i2, i3, i4);},
            inputs1,
            inputs2,
            inputs3,
            inputs4,
            empty(),
            reporter);
    }

    template <
        typename Function,
        typename Container1,
        typename Container2,
        typename Container3,
        
        typename std::enable_if<! std::is_base_of<Reporter, Container3>::value, int>::type = 0>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Container2& inputs2,
        const Container3& inputs3,
        const Reporter& reporter = DefaultReporter())
    {
        verifyAllCombinations(
            [&](typename Container1::value_type i1,
                typename Container2::value_type i2,
                typename Container3::value_type i3,
                Empty){return converter(i1, i2, i3);},
            inputs1,
            inputs2,
            inputs3,
            empty(),
            reporter);
    }

    template <
        typename Function,
        typename Container1,
        typename Container2,
        
        typename std::enable_if<! std::is_base_of<Reporter, Container2>::value, int>::type = 0>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Container2& inputs2,
        const Reporter& reporter = DefaultReporter())
    {
        verifyAllCombinations(
            [&](typename Container1::value_type i1,
                typename Container2::value_type i2,
                Empty){return converter(i1, i2);},
            inputs1,
            inputs2,
            empty(),
            reporter);
    }

    template <
        typename Function,
        typename Container1,
        
        typename std::enable_if<! std::is_base_of<Reporter, Container1>::value, int>::type = 0>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Reporter& reporter = DefaultReporter())
    {
        verifyAllCombinations(
            [&](typename Container1::value_type i1,
                Empty){return converter(i1);},
            inputs1,
            empty(),
            reporter);
    }

    
    
    
    using EmptyContainer = std::vector<Empty>;
    static EmptyContainer empty()
    {
        return EmptyContainer{Empty()};
    }
};

#endif

 // ******************** From: GoogleTestApprovals.h
#ifndef APPROVALTESTS_CPP_GOOGLTESTAPPPROVALS_H
#define APPROVALTESTS_CPP_GOOGLTESTAPPPROVALS_H


#ifdef APPROVALS_GOOGLETEST_EXISTING_MAIN
#define APPROVALS_GOOGLETEST
#endif

#ifdef APPROVALS_GOOGLETEST

// <SingleHpp unalterable>
#include "gtest/gtest.h"


class GoogleTestListener : public ::testing::EmptyTestEventListener
{
    TestName currentTest;
public:
    bool isDuplicate(std::string testFileNameWithExtension, std::string testCaseName)
    {
        for( auto check : GoogleCustomizationsFactory::getEquivalencyChecks())
        {
            if (check(testFileNameWithExtension, testCaseName))
            {
                return true;
            }
        }
        return false;
    }

    virtual void OnTestStart(const ::testing::TestInfo& testInfo) override
    {
        currentTest.setFileName(testInfo.file());
        currentTest.sections = {};
        if (! isDuplicate(currentTest.getFileName(), testInfo.test_case_name()))
        {
            currentTest.sections.push_back(testInfo.test_case_name());
        }
        if (! std::string(testInfo.name()).empty())
        {
            currentTest.sections.push_back(testInfo.name());
        }
        
        ApprovalTestNamer::currentTest(&currentTest);
    }
};

inline void initializeApprovalTestsForGoogleTests() {
    auto& listeners = testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new GoogleTestListener);
}

#ifndef APPROVALS_GOOGLETEST_EXISTING_MAIN
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    initializeApprovalTestsForGoogleTests();
    return RUN_ALL_TESTS();
}
#endif //APPROVALS_GOOGLETEST_EXISTING_MAIN

// </SingleHpp>
#endif
#endif 

 // ******************** From: DocTestApprovals.h
#ifndef APPROVALTESTS_CPP_DOCTESTAPPROVALS_H
#define APPROVALTESTS_CPP_DOCTESTAPPROVALS_H


// <SingleHpp unalterable>
#ifdef APPROVALS_DOCTEST

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest.h>

// anonymous namespace to prevent compiler -Wsubobject-linkage warnings
// This is OK as this code is only compiled on main()
namespace {
    struct AbstractReporter : doctest::IReporter {
        virtual void report_query(const doctest::QueryData&) {}
        // called when the whole test run starts
        virtual void test_run_start() {}

        // called when the whole test run ends (caching a pointer to the input doesn't make sense here)
        virtual void test_run_end(const doctest::TestRunStats &) {}

        // called when a test case is started (safe to cache a pointer to the input)
        virtual void test_case_start(const doctest::TestCaseData &) {}

        // called when a test case has ended
        virtual void test_case_end(const doctest::CurrentTestCaseStats &) {}

        // called when an exception is thrown from the test case (or it crashes)
        virtual void test_case_exception(const doctest::TestCaseException &) {}

        // called whenever a subcase is entered (don't cache pointers to the input)
        virtual void subcase_start(const doctest::SubcaseSignature &) {}

        // called whenever a subcase is exited (don't cache pointers to the input)
        virtual void subcase_end() {}

        // called for each assert (don't cache pointers to the input)
        virtual void log_assert(const doctest::AssertData &) {}

        // called for each message (don't cache pointers to the input)
        virtual void log_message(const doctest::MessageData &) {}

        // called when a test case is skipped either because it doesn't pass the filters, has a skip decorator
        // or isn't in the execution range (between first and last) (safe to cache a pointer to the input)
        virtual void test_case_skipped(const doctest::TestCaseData &) {}


    };

    struct DocTestApprovalListener : AbstractReporter {
        TestName currentTest;

        // constructor has to accept the ContextOptions by ref as a single argument
        DocTestApprovalListener(const doctest::ContextOptions & /*in*/) {
        }

        void test_case_start(const doctest::TestCaseData &testInfo) override {

            currentTest.sections.push_back(testInfo.m_name);
            currentTest.setFileName(testInfo.m_file);
            ApprovalTestNamer::currentTest(&currentTest);
        }

        void test_case_end(const doctest::CurrentTestCaseStats & /*in*/) override {

            while (!currentTest.sections.empty()) {
                currentTest.sections.pop_back();
            }
        }

        void subcase_start(const doctest::SubcaseSignature &signature) override {

            currentTest.sections.push_back(signature.m_name);
        }

        void subcase_end() override {

            currentTest.sections.pop_back();
        }
    };
}

REGISTER_LISTENER("approvals", 0, DocTestApprovalListener);


#endif // APPROVALS_DOCTEST
// </SingleHpp>
#endif 

 // ******************** From: GoogleConfiguration.h
#ifndef APPROVALTESTS_CPP_GOOGLECONFIGURATION_H
#define APPROVALTESTS_CPP_GOOGLECONFIGURATION_H


class GoogleConfiguration
{
public:
    static bool addTestCaseNameRedundancyCheck(GoogleCustomizationsFactory::Comparator comparator)
    {
        return GoogleCustomizationsFactory::addTestCaseNameRedundancyCheck(comparator);
    }

    static bool addIgnorableTestCaseNameSuffix(std::string suffix)
    {
        return addTestCaseNameRedundancyCheck( createIgnorableTestCaseNameSuffixCheck(suffix) );
    }

    static GoogleCustomizationsFactory::Comparator createIgnorableTestCaseNameSuffixCheck( const std::string& suffix )
    {
        return [suffix](std::string testFileNameWithExtension, std::string testCaseName)
        {
            if (testCaseName.length() <= suffix.length() || !StringUtils::endsWith(testCaseName, suffix))
            {
                return false;
            }

            auto withoutSuffix = testCaseName.substr(0, testCaseName.length() - suffix.length());
            auto withFileExtension = withoutSuffix + ".";
            return StringUtils::contains(testFileNameWithExtension, withFileExtension);
        };
    }
};

#endif 

 // ******************** From: OkraApprovals.h
#ifndef APPROVALTESTS_CPP_OKRAAPPPROVALS_H
#define APPROVALTESTS_CPP_OKRAAPPPROVALS_H

#ifdef APPROVALS_OKRA

// <SingleHpp unalterable>
#include "Okra.h"


struct OkraApprovalListener : public okra::IListener
{
 TestName currentTest;

public:
 void OnStart(const okra::TestInfo &testInfo) override
 {
  currentTest.fileName = testInfo.file_path;
  currentTest.sections = {testInfo.name};
  ApprovalTestNamer::currentTest(&currentTest);
 }

 void OnEnd(const okra::TestInfo &testInfo, std::chrono::high_resolution_clock::duration duration) override {
 }
 void OnFail(const std::string &message) override {
 }
};

OKRA_REGISTER_LISTENER(OkraApprovalListener);
// </SingleHpp>
#endif
#endif 

 // ******************** From: AutoApproveIfMissingReporter.h
#ifndef APPROVALTESTS_CPP_AUTOAPPROVEIFMISSINGREPORTER_H
#define APPROVALTESTS_CPP_AUTOAPPROVEIFMISSINGREPORTER_H


class AutoApproveIfMissingReporter : public Reporter
{
public:
    bool report(std::string received, std::string approved) const override
    {
        if (FileUtils::fileExists(approved))
        {
            return false;
        }

        return AutoApproveReporter().report(received, approved);
    }
};

#endif 

 // ******************** From: BlockingReporter.h
#ifndef APPROVALTESTS_CPP_BLOCKINGREPORTER_H
#define APPROVALTESTS_CPP_BLOCKINGREPORTER_H



class BlockingReporter : public Reporter
{
private:
    std::shared_ptr<Blocker> blocker;

    BlockingReporter() = delete;

public:
    BlockingReporter( std::shared_ptr<Blocker> blocker ) : blocker(blocker)
    {
    }

    static std::shared_ptr<BlockingReporter> onMachineNamed( const std::string& machineName )
    {
        auto machineBlocker = std::make_shared<MachineBlocker>( MachineBlocker::onMachineNamed(machineName) );
        return std::make_shared<BlockingReporter>(machineBlocker);
    }

    static std::shared_ptr<BlockingReporter> onMachinesNotNamed( const std::string& machineName )
    {
        auto machineBlocker = std::make_shared<MachineBlocker>( MachineBlocker::onMachinesNotNamed(machineName) );
        return std::make_shared<BlockingReporter>(machineBlocker);
    }

    virtual bool report(std::string , std::string ) const override
    {
        return blocker->isBlockingOnThisMachine();
    }
};

#endif 

 // ******************** From: ClipboardReporter.h
#ifndef APPROVALTESTS_CPP_COMMANDLINEREPORTER_H
#define APPROVALTESTS_CPP_COMMANDLINEREPORTER_H




class ClipboardReporter : public Reporter {
public:
    static std::string getCommandLineFor(std::string received, std::string approved, bool isWindows)
    {
        if (isWindows) {
            return std::string("move /Y ") + "\"" + received + "\" \"" + approved + "\"";
        } else {
            return std::string("mv ") + "\"" + received + "\" \"" + approved + "\"";
        }
    }

    virtual bool report(std::string received, std::string approved) const override
    {
        copyToClipboard(getCommandLineFor(received, approved, SystemUtils::isWindowsOs()));
        return true;
    }

    static void copyToClipboard(const std::string& newClipboard) {
        

        const std::string clipboardCommand = SystemUtils::isWindowsOs() ? "clip" : "pbclip";
        auto cmd = std::string("echo ") + newClipboard + " | " + clipboardCommand;
        system(cmd.c_str());
    }
};

#endif 

 // ******************** From: CombinationReporter.h
#ifndef APPROVALTESTS_CPP_COMBINATIONREPORTER_H
#define APPROVALTESTS_CPP_COMBINATIONREPORTER_H


class CombinationReporter : public Reporter
{
private:
    std::vector< std::unique_ptr<Reporter> > reporters;
public:
    
    CombinationReporter(std::vector<Reporter*> theReporters)
    {
        for(auto r : theReporters)
        {
            reporters.push_back(std::unique_ptr<Reporter>(r));
        }
    }

    bool report(std::string received, std::string approved) const override
    {
        bool result = false;
        for(auto& r : reporters)
        {
            result |= r->report(received, approved);
        }
        return result;
    }
};

#endif 

 // ******************** From: QuietReporter.h
#ifndef APPROVALTESTS_CPP_QUIETREPORTER_H
#define APPROVALTESTS_CPP_QUIETREPORTER_H



class QuietReporter : public Reporter
{
public:
    bool report(std::string , std::string ) const override
    {
        return true;
    }
};

#endif 


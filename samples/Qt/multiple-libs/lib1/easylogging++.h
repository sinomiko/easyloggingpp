///////////////////////////////////////////////////////////////////////////////////
//                                                                               //
//   easylogging++.h - Core of EasyLogging++                                     //
//                                                                               //
//   EasyLogging++ v8.07                                                         //
//   Cross platform logging made easy for C++ applications                       //
//   Author Majid Khan <mkhan3189@gmail.com>                                     //
//   http://www.icplusplus.com/tools/easylogging                                 //
//   https://github.com/mkhan3189/EasyLoggingPP                                  //
//                                                                               //
//   Copyright (c) 2012-2013 Majid Khan                                          //
//                                                                               //
//   This software is provided 'as-is', without any express or implied           //
//   warranty. In no event will the authors be held liable for any damages       //
//   arising from the use of this software.                                      //
//                                                                               //
//   Permission is granted to anyone to use this software for any purpose,       //
//   including commercial applications, and to alter it and redistribute         //
//   it freely, subject to the following restrictions:                           //
//                                                                               //
//   1. The origin of this software must not be misrepresented; you must         //
//      not claim that you wrote the original software. If you use this          //
//      software in a product, an acknowledgment in the product documentation    //
//      would be appreciated but is not required.                                //
//                                                                               //
//   2. Altered source versions must be plainly marked as such, and must         //
//      not be misrepresented as being the original software.                    //
//                                                                               //
//   3. This notice may not be removed or altered from any source                //
//      distribution                                                             //
//                                                                               //
//                                                                               //
///////////////////////////////////////////////////////////////////////////////////

#ifndef EASYLOGGINGPP_H
#define EASYLOGGINGPP_H
//
// Log location macros
//
#if !defined(__FILE__)
#   define __FILE__ ""
#endif // !defined(__FILE__)
#if !defined(__LINE__)
#   define __LINE__ 0
#endif // !defined(__LINE__)
// Appropriate function macro
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#   define __func__ __FUNCSIG__
#elif defined(__GNUC__) && (__GNUC__ >= 2)
#   define __func__ __PRETTY_FUNCTION__
#else
#   if !defined(__func__)
#      define __func__ ""
#   endif // !defined(__func__)
#endif // defined(_MSC_VER) && (_MSC_VER >= 1020)
//
// Compiler evaluation
//
// GNU
#if defined(__GNUC__)
#   if defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define _CXX0X 1
#   endif // defined(__GXX_EXPERIMENTAL_CXX0X__)
#endif // defined(__GNUC__)
// VC++ (http://msdn.microsoft.com/en-us/library/vstudio/hh567368.aspx)
#if defined(_MSC_VER)
#   if (_MSC_VER == 1600)
#      define _CXX0X 1
#   elif (_MSC_VER == 1700)
#      define _CXX11 1
#   endif // (_MSC_VER == 1600)
#endif // defined(_MSC_VER)
#if defined(QT_CORE_LIB)
#   if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#      define _ELPP_QT_5 1
#   else
#      define _ELPP_QT_5 0
#   endif // (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#endif // defined(QT_CORE_LIB)
//
// High-level log evaluation
//
#if (!defined(_DISABLE_LOGS))
#   define _ENABLE_EASYLOGGING 1
#else
#   define _ENABLE_EASYLOGGING 0
#endif // (!defined(_DISABLE_LOGS))
//
// OS evaluation
//
// Windows
#if defined(_WIN32) || defined(_WIN64)
#   define _ELPP_OS_WINDOWS 1
#else
#   define _ELPP_OS_WINDOWS 0
#endif // defined(_WIN32) || defined(_WIN64)
// Linux
#if (defined(__linux) || defined(__linux__))
#   define _ELPP_OS_LINUX 1
#else
#   define _ELPP_OS_LINUX 0
#endif // (defined(__linux) || defined(__linux__))
// Mac
#if defined(__APPLE__)
#   define _ELPP_OS_MAC 1
#else
#   define _ELPP_OS_MAC 0
#endif // defined(__APPLE__)
// Unix
#define _ELPP_OS_UNIX ((_ELPP_OS_LINUX || _ELPP_OS_MAC) && (!_ELPP_OS_WINDOWS))
// Assembly
#if (defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))) ||     \
    (defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64)))
#   define _ELPP_ASSEMBLY_SUPPORTED 1
#else
#   define _ELPP_ASSEMBLY_SUPPORTED 0
#endif
#if (!defined(_DISABLE_ELPP_ASSERT))
#   if (defined(_STOP_ON_FIRST_ELPP_ASSERTION))
#      define __EASYLOGGINGPP_ASSERT(expr, msg) if (!(expr)) { std::cerr << "EASYLOGGING++ ASSERTION FAILED [" #expr << "] with message \"" << msg << "\"" << std::endl; exit(1); }
#   else
#      define __EASYLOGGINGPP_ASSERT(expr, msg) if (!(expr)) { std::cerr << "EASYLOGGING++ ASSERTION FAILED [" #expr << "] with message \"" << msg << "\"" << std::endl; }
#   endif // (defined(_STOP_ON_FIRST_ELPP_ASSERTION))
#else
#   define __EASYLOGGINGPP_ASSERT(x, y)
#endif // (!defined(_DISABLE_ELPP_ASSERT))
#define __EASYLOGGINGPP_SUPPRESS_UNSED(x) (void)x;
#if _ELPP_OS_UNIX
// Log file permissions for unix-based systems
#   define _LOG_PERMS S_IRUSR | S_IWUSR | S_IXUSR | S_IWGRP | S_IRGRP | S_IXGRP | S_IWOTH | S_IXOTH
#endif // _ELPP_OS_UNIX
#if (!defined(_DISABLE_MUTEX) && (_ENABLE_EASYLOGGING))
#   define _ELPP_ENABLE_MUTEX 1
#else
#   define _ELPP_ENABLE_MUTEX 0
#endif // (!defined(_DISABLE_MUTEX) && (_ENABLE_EASYLOGGING))
#define _ELPP_DEBUG_LOG       (!defined(_DISABLE_DEBUG_LOGS) && (_ENABLE_EASYLOGGING) && ((defined(_DEBUG)) || (!defined(NDEBUG))))
#define _ELPP_INFO_LOG        (!defined(_DISABLE_INFO_LOGS) && (_ENABLE_EASYLOGGING))
#define _ELPP_WARNING_LOG     (!defined(_DISABLE_WARNING_LOGS) && (_ENABLE_EASYLOGGING))
#define _ELPP_ERROR_LOG       (!defined(_DISABLE_ERROR_LOGS) && (_ENABLE_EASYLOGGING))
#define _ELPP_FATAL_LOG       (!defined(_DISABLE_FATAL_LOGS) && (_ENABLE_EASYLOGGING))
#define _ELPP_VERBOSE_LOG     (!defined(_DISABLE_VERBOSE_LOGS) && (_ENABLE_EASYLOGGING))
#define _ELPP_QA_LOG          (defined(_QUALITY_ASSURANCE) && (_ENABLE_EASYLOGGING))
#define _ELPP_TRACE_LOG       (!defined(_DISABLE_TRACE_LOGS) && (_ENABLE_EASYLOGGING))
#define _ELPP_NO_COPY(className) private: className(const className&); className& operator=(const className&);
#define _ELPP_NO_INITIALIZATION(className) private: className(void); _ELPP_NO_COPY(className)
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cwchar>
#if _ELPP_OS_UNIX
#   include <sys/stat.h>
#   include <sys/time.h>
#   if (_ELPP_ENABLE_MUTEX)
#      if (_ELPP_ASSEMBLY_SUPPORTED)
#         include <sched.h>
#      else
#         include <pthread.h>
#      endif // (_ELPP_ASSEMBLY_SUPPORTED)
#   endif // (_ELPP_ENABLE_MUTEX)
#elif _ELPP_OS_WINDOWS
#   include <cerrno>
#   include <direct.h>
#   include <Windows.h>
#endif // _ELPP_OS_UNIX
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#if defined(_ELPP_STL_LOGGING)
// For logging STL based templates
#   include <list>
#   include <utility>
#   include <queue>
#   include <deque>
#   include <set>
#   include <bitset>
#   include <stack>
#endif // defined(_ELPP_STL_LOGGING)
#if defined(QT_CORE_LIB) && defined(_ELPP_QT_LOGGING)
// For logging Qt based classes & templates
#   include <QString>
#   include <QVector>
#   include <QList>
#   include <QPair>
#   include <QMap>
#   include <QQueue>
#   include <QSet>
#   include <QLinkedList>
#   include <QHash>
#   include <QMultiHash>
#   include <QStack>
#endif // defined(QT_CORE_LIB) && defined(_ELPP_QT_LOGGING)
namespace easyloggingpp {

struct Level {
    _ELPP_NO_INITIALIZATION(Level)
    public:
        enum {
        ELPP_ALL = 0, ELPP_DEBUG = 1, ELPP_INFO = 2, ELPP_WARNING = 4, ELPP_ERROR = 8,
                ELPP_FATAL = 16, ELPP_VERBOSE = 32, ELPP_QA = 64, ELPP_TRACE = 128
    };
};

struct ConfigurationType {
    _ELPP_NO_INITIALIZATION(ConfigurationType)
    public:
        enum {
        ELPP_Enabled = 0, ELPP_ToFile = 1, ELPP_ToStandardOutput = 2, ELPP_Format = 4, ELPP_Filename = 8,
                ELPP_MillisecondsWidth = 16, ELPP_PerformanceTracking = 32
    };
};

namespace internal {
struct Aspect {
    _ELPP_NO_INITIALIZATION(Aspect)
    public:
        enum {
        Normal = 0, Conditional = 1, Interval = 2
    };
};

class Constants {
    _ELPP_NO_COPY(Constants)
    public:
        explicit Constants (void) :
      //
      // Log level name outputs
      //
      LOG_INFO_LEVEL_VALUE   ("INFO") ,
        LOG_DEBUG_LEVEL_VALUE  ("DEBUG"),
        LOG_WARNING_LEVEL_VALUE("WARN"),
        LOG_ERROR_LEVEL_VALUE  ("ERROR"),
        LOG_FATAL_LEVEL_VALUE  ("FATAL"),
        LOG_VERBOSE_LEVEL_VALUE("VER"),
        LOG_QA_LEVEL_VALUE     ("QA"),
        LOG_TRACE_LEVEL_VALUE  ("TRACE"),
        //
        // Format specifiers
        //
        APP_NAME_FORMAT_SPECIFIER      ("%app"),
        LOGGER_ID_FORMAT_SPECIFIER     ("%logger"),
        LEVEL_FORMAT_SPECIFIER         ("%level"),
        DATE_ONLY_FORMAT_SPECIFIER     ("%date"),
        TIME_ONLY_FORMAT_SPECIFIER     ("%time"),
        DATE_TIME_FORMAT_SPECIFIER     ("%datetime"),
        LOCATION_FORMAT_SPECIFIER      ("%loc"),
        FUNCTION_FORMAT_SPECIFIER      ("%func"),
        USER_FORMAT_SPECIFIER          ("%user"),
        HOST_FORMAT_SPECIFIER          ("%host"),
        LOG_MESSAGE_FORMAT_SPECIFIER   ("%log"),
        VERBOSE_LEVEL_FORMAT_SPECIFIER ("%vlevel"),
        //
        // Others
        //
        NULL_POINTER                  ("nullptr"),
        FORMAT_SPECIFIER_ESCAPE_CHAR  ('E'),
        MAX_LOG_PER_CONTAINER         (100),
        MAX_LOG_PER_COUNTER           (100000),
        DEFAULT_MILLISECOND_OFFSET    (1000),
        MAX_VERBOSE_LEVEL             (9),
        CURRENT_VERBOSE_LEVEL         (0),  // Set dynamically from registeredLoggers
    #if _ELPP_OS_UNIX
        PATH_SLASH                    ("/"),
    #elif _ELPP_OS_WINDOWS
        PATH_SLASH                    ("\\"),
    #endif // _ELPP_OS_UNIX
        DEFAULT_LOG_FILENAME          ("myeasylog.log")
    {
        // Trivial logger configuration - only to set format (difference: not using %logger)
        std::stringstream ss;
        ss << " * ALL:\n";
        ss << "    FORMAT               =  %datetime %level  %log\n";
        ss << "* DEBUG:\n";
        ss << "    FORMAT               =  %datetime %level [%user@%host] [%func] [%loc] %log\n";
        // INFO and WARNING uses is defined by ALL
        ss << "* ERROR:\n";
        ss << "    FORMAT               =  %datetime %level %log\n";
        ss << "* FATAL:\n";
        ss << "    FORMAT               =  %datetime %level %log\n";
        ss << "* QA:\n";
        ss << "    FORMAT               =  %datetime %level    %log\n";
        ss << "* VERBOSE:\n";
        ss << "    FORMAT               =  %datetime %level-%vlevel %log\n";
        ss << "* TRACE:\n";
        ss << "    FORMAT               =  %datetime %level [%func] [%loc] %log\n";
        DEFAULT_LOGGER_CONFIGURATION = ss.str();
    } // C'tor
    //
    // Log level name outputs
    //
    const std::string LOG_INFO_LEVEL_VALUE;
    const std::string LOG_DEBUG_LEVEL_VALUE;
    const std::string LOG_WARNING_LEVEL_VALUE;
    const std::string LOG_ERROR_LEVEL_VALUE;
    const std::string LOG_FATAL_LEVEL_VALUE;
    const std::string LOG_VERBOSE_LEVEL_VALUE;
    const std::string LOG_QA_LEVEL_VALUE;
    const std::string LOG_TRACE_LEVEL_VALUE;
    //
    // Format specifiers
    //
    const std::string APP_NAME_FORMAT_SPECIFIER;
    const std::string LOGGER_ID_FORMAT_SPECIFIER;
    const std::string LEVEL_FORMAT_SPECIFIER;
    const std::string DATE_ONLY_FORMAT_SPECIFIER;
    const std::string TIME_ONLY_FORMAT_SPECIFIER;
    const std::string DATE_TIME_FORMAT_SPECIFIER;
    const std::string LOCATION_FORMAT_SPECIFIER;
    const std::string FUNCTION_FORMAT_SPECIFIER;
    const std::string USER_FORMAT_SPECIFIER;
    const std::string HOST_FORMAT_SPECIFIER;
    const std::string LOG_MESSAGE_FORMAT_SPECIFIER;
    const std::string VERBOSE_LEVEL_FORMAT_SPECIFIER;
    //
    // Others
    //
    const std::string     NULL_POINTER;
    const char            FORMAT_SPECIFIER_ESCAPE_CHAR;
    const unsigned int    MAX_LOG_PER_CONTAINER;
    const unsigned int    MAX_LOG_PER_COUNTER;
    const unsigned int    DEFAULT_MILLISECOND_OFFSET;
    const int             MAX_VERBOSE_LEVEL;
    int                   CURRENT_VERBOSE_LEVEL;
    const std::string     PATH_SLASH;
    const std::string     DEFAULT_LOG_FILENAME;
    std::string           DEFAULT_LOGGER_CONFIGURATION;

    enum kFormatFlags { kDateOnly = 2,
                        kTimeOnly = 4,
                        kDateTime = 8,
                        kLoggerId = 16,
                        kLocation = 32,
                        kFunction = 64,
                        kUser = 128,
                        kHost = 256,
                        kLogMessage = 512,
                        kVerboseLevel = 1024,
                        kAppName = 2048
                      };
private:
}; // class Constants
namespace threading {
//
// To take care of shared resources in multi-threaded application
//
class Mutex {
public:
#if _ELPP_ASSEMBLY_SUPPORTED
#   if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
#      define _ELPP_MUTEX_LOCK_GNU_ASM(lf_, old_) "movl $1,%%eax\n"       \
    "\txchg %%eax,%0\n"   \
    "\tmovl %%eax,%1\n"   \
    "\t" : "=m" (lf_), "=m" (old_) : : "%eax", "memory"
#      define _ELPP_MUTEX_UNLOCK_GNU_ASM(lf_)     "movl $0,%%eax\n"                                \
    "\txchg %%eax,%0\n"                            \
    "\t" : "=m" (lf_) : : "%eax", "memory"
#   endif // defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
    explicit Mutex(void) : lockerFlag_(0) {
    }
#else
    explicit Mutex(void) {
#   if _ELPP_OS_UNIX
        pthread_mutex_init(&underlyingMutex_, NULL);
#   elif _ELPP_OS_WINDOWS
        InitializeCriticalSection(&underlyingMutex_);
#   endif // _ELPP_OS_UNIX
    }
    virtual ~Mutex(void) {
#   if _ELPP_OS_UNIX
        pthread_mutex_destroy(&underlyingMutex_);
#   elif _ELPP_OS_WINDOWS
        DeleteCriticalSection(&underlyingMutex_);
#   endif // _ELPP_OS_UNIX
    }
#endif // _ELPP_ASSEMBLY_SUPPORTED
    inline void lock(void) {
#if _ELPP_ASSEMBLY_SUPPORTED
        bool locked = false;
        while (!locked) {
            locked = tryLock();
            if (!locked) {
#   if _ELPP_OS_UNIX
                sched_yield();
#   elif _ELPP_OS_WINDOWS
                Sleep(0);
#   endif
            }
        }
#else
#   if _ELPP_OS_UNIX
        pthread_mutex_lock(&underlyingMutex_);
#   elif _ELPP_OS_WINDOWS
        EnterCriticalSection(&underlyingMutex_);
#   endif // _ELPP_OS_UNIX
#endif // _ELPP_ASSEMBLY_SUPPORTED
    }
    inline bool tryLock(void) {
#if _ELPP_ASSEMBLY_SUPPORTED
        int oldLock_;
#   if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
        asm volatile (_ELPP_MUTEX_LOCK_GNU_ASM(lockerFlag_, oldLock_));
#   elif defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
        int *ptrLock = &lockerFlag_;
        __asm {
            mov eax,1
                    mov ecx,ptrLock
                    xchg eax,[ecx]
                    mov oldLock_,eax
        }
#   endif // defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
        return (oldLock_ == 0);
#else
#   if _ELPP_OS_UNIX
        return (pthread_mutex_trylock(&underlyingMutex_) == 0) ? true : false;
#   elif _ELPP_OS_WINDOWS
        return TryEnterCriticalSection(&underlyingMutex_) ? true : false;
#   endif // _ELPP_OS_UNIX
#endif // _ELPP_ASSEMBLY_SUPPORTED
    }
    inline void unlock(void) {
#if _ELPP_ASSEMBLY_SUPPORTED
#   if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
        asm volatile (_ELPP_MUTEX_UNLOCK_GNU_ASM(lockerFlag_));
#   elif defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
        int *ptrLock = &lockerFlag_;
        __asm {
            mov eax,0
                    mov ecx,ptrLock
                    xchg eax,[ecx]
        }
#   endif // defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
#else
#   if _ELPP_OS_UNIX
        pthread_mutex_unlock(&underlyingMutex_);
#   elif _ELPP_OS_WINDOWS
        LeaveCriticalSection(&underlyingMutex_);
#   endif // _ELPP_OS_UNIX
#endif // _ELPP_ASSEMBLY_SUPPORTED
    }
private:
#if _ELPP_ASSEMBLY_SUPPORTED
    int lockerFlag_;
#else
#   if _ELPP_OS_UNIX
    pthread_mutex_t underlyingMutex_;
#   elif _ELPP_OS_WINDOWS
    CRITICAL_SECTION underlyingMutex_;
#   endif // _ELPP_OS_UNIX
#endif // _ELPP_ASSEMBLY_SUPPORTED
}; // class Mutex
class ScopedLock {
    _ELPP_NO_COPY(ScopedLock)
    public:
        explicit ScopedLock(void) {
        mutex_.lock();
    }
    virtual ~ScopedLock(void) {
        mutex_.unlock();
    }
private:
    Mutex mutex_;
}; // class ScopedLock
} // namespace threading
namespace utilities {
class StringUtilities {
    _ELPP_NO_INITIALIZATION(StringUtilities)
    public:
        static inline std::string trim(const std::string &str) {
        size_t s = str.find_first_not_of(" \n\r\t");
        size_t e = str.find_last_not_of(" \n\r\t");
        if ((s == std::string::npos) || (e == std::string::npos)) {
            return "";
        }
        else {
            return str.substr(s, e - s + 1);
        }
    }

    static inline bool startsWith(const std::string& str, const std::string& start) {
        return (str.length() >= start.length()) && (str.compare(0, start.length(), start) == 0);
    }

    static inline bool endsWith(const std::string& str, const std::string& end) {
        return (str.length() >= end.length()) && (str.compare(str.length() - end.length(), end.length(), end) == 0);
    }

    static inline std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string>& elems) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    static inline std::string replaceAll(const std::string& str, const std::string& replaceWhat, const std::string& replaceWith) {
        if (replaceWhat == replaceWith)
            return str;
        std::string result = str;
        size_t foundAt = -1;
        while ((foundAt = result.find(replaceWhat)) != std::string::npos) {
            result.replace(foundAt, replaceWhat.length(), replaceWith);
        }
        return result;
    }

    static inline std::string stripAllWhiteSpaces(const std::string& str) {
        std::string result = replaceAll(str, " ", "");
        result = replaceAll(result, "\n", "");
        result = replaceAll(result, "\r", "");
        result = replaceAll(result, "\t", "");
        return result;
    }

    static inline void tolower(std::string& str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    static inline unsigned int getLineCount(const std::string& str) {
        if (str == "") {
            return 0;
        }
        unsigned int count = std::count(str.begin(), str.end(), '\n');
        return ++count;
    }
};
#define ELPP_StringUtils internal::utilities::StringUtilities
class OSUtilities {
    _ELPP_NO_INITIALIZATION(OSUtilities)
    public:
        // Runs command on terminal and returns the output.
        // This is applicable only on linux and mac, for all other OS, an empty string is returned.
        static const std::string getBashOutput(const char* command_) {
        if (command_ == NULL) {
            return std::string();
        }
#if _ELPP_OS_UNIX
        FILE* proc = NULL;
        if ((proc = popen(command_, "r")) == NULL) {
            std::cerr << "\nUnable to run command [" << command_ << "]" << std::endl;
            return std::string();
        }
        char hBuff[4096];
        if (fgets(hBuff, sizeof(hBuff), proc) != NULL) {
            pclose(proc);
            if (hBuff[strlen(hBuff) - 1] == '\n') {
                hBuff[strlen(hBuff) - 1] = '\0';
            }
            return std::string(hBuff);
        }
        return std::string();
#else
        return std::string();
#endif // _ELPP_OS_UNIX
    }

    // Gets current username.
    static const std::string currentUser(void) {
#if _ELPP_OS_UNIX
        const char* username = getenv("USER");
#elif _ELPP_OS_WINDOWS
        char* username = NULL;
        size_t len;
        errno_t err = _dupenv_s(&username, &len, "USERNAME");
#endif // _ELPP_OS_UNIX
        if ((username == NULL) || (!strcmp(username, ""))) {
            // Try harder on unix-based systems
            return OSUtilities::getBashOutput("whoami");
        } else {
            return std::string(username);
        }
    }

    // Gets current host name or computer name.
    static const std::string currentHost(void) {
#if _ELPP_OS_UNIX
        const char* hostname = getenv("HOSTNAME");
#elif _ELPP_OS_WINDOWS
        char* hostname = NULL;
        size_t len;
        errno_t err = _dupenv_s(&hostname, &len, "COMPUTERNAME");
#endif // _ELPP_OS_UNIX
        if ((hostname == NULL) || ((strcmp(hostname, "") == 0))) {
            // Try harder on unix-based systems
            std::string hostnameStr = OSUtilities::getBashOutput("hostname");
            if (hostnameStr.empty()) {
                return std::string("unknown-host");
            } else {
                return hostnameStr;
            }
        } else {
            return std::string(hostname);
        }
    }

    // Determines whether or not provided path_ exist in current file system
    static inline bool pathExists(const char* path_) {
        if (path_ == NULL) {
            return false;
        }
#if _ELPP_OS_UNIX
        struct stat st;
        return (stat(path_, &st) == 0);
#elif _ELPP_OS_WINDOWS
        DWORD fileType = GetFileAttributesA(path_);
        if (fileType == INVALID_FILE_ATTRIBUTES) {
            return false;
        }
        return (fileType & FILE_ATTRIBUTE_DIRECTORY) == 0 ? false : true;
#endif // _ELPP_OS_UNIX
    }

    // Creates path as specified
    static bool createPath(const std::string& path_) {
        if (path_.empty()) {
            return false;
        }
        if (OSUtilities::pathExists(path_.c_str())) {
            return true;
        }
#if _ELPP_OS_UNIX
        const char* pathDelim_ = "/";
#elif _ELPP_OS_WINDOWS
        char pathDelim_[] = "\\";
#endif // _ELPP_OS_UNIX
        int status = -1;
        char* currPath_ = const_cast<char*>(path_.c_str());
        std::string buildingPath_;
        if (path_[0] == '/') {
            buildingPath_ = "/";
        }
#if _ELPP_OS_UNIX
        currPath_ = strtok(currPath_, pathDelim_);
#elif _ELPP_OS_WINDOWS
        // Use secure functions API
        char* nextTok_;
        currPath_ = strtok_s(currPath_, pathDelim_, &nextTok_);
#endif // _ELPP_OS_UNIX
        while (currPath_ != NULL) {
            buildingPath_.append(currPath_);
            buildingPath_.append(pathDelim_);
#if _ELPP_OS_UNIX
            status = mkdir(buildingPath_.c_str(), _LOG_PERMS);
            currPath_ = strtok(NULL, pathDelim_);
#elif _ELPP_OS_WINDOWS
            status = _mkdir(buildingPath_.c_str());
            currPath_ = strtok_s(NULL, pathDelim_, &nextTok_);
#endif // _ELPP_OS_UNIX
        }
        if (status == -1) {
            return false;
        }
        return true;
    }

    static std::string getPathFromFilename(const std::string& fullPath_, Constants* constants_) {
        if (fullPath_ == "" || fullPath_.find(constants_->PATH_SLASH) == std::string::npos) {
            return fullPath_;
        }
        size_t lastSlashAt = fullPath_.find_last_of(constants_->PATH_SLASH);
        if (lastSlashAt == 0) {
            return constants_->PATH_SLASH;
        }
        return fullPath_.substr(0, lastSlashAt + 1);
    }
}; // class OSUtilities
//
// Contains static functions related to log manipulation
//
class LogManipulator {
    _ELPP_NO_INITIALIZATION(LogManipulator)
    public:
        // Updates the formatSpecifier_ for currentFormat_ to value_ provided
        static void updateFormatValue(const std::string& formatSpecifier_,
                                      const std::string& value_, std::string& currentFormat_,
                                      internal::Constants* constants_) {
        size_t foundAt = -1;
        while ((foundAt = currentFormat_.find(formatSpecifier_, foundAt + 1)) != std::string::npos){
            if (currentFormat_[foundAt > 0 ? foundAt - 1 : 0] == constants_->FORMAT_SPECIFIER_ESCAPE_CHAR) {
                currentFormat_.erase(foundAt > 0 ? foundAt - 1 : 0, 1);
                ++foundAt;
            } else {
                currentFormat_ = currentFormat_.replace(foundAt, formatSpecifier_.size(), value_);
                return;
            }
        }
    }
}; // class LogManipulator
//
// Contains utility functions related to date/time
//
class DateUtilities {
    _ELPP_NO_INITIALIZATION(DateUtilities)
    public:
    #if _ELPP_OS_WINDOWS
        static void gettimeofday(struct timeval *tv) {
        if (tv != NULL) {
#   if defined(_MSC_EXTENSIONS)
            const unsigned __int64 delta_ = 11644473600000000Ui64;
#   else
            const unsigned __int64 delta_ = 11644473600000000ULL;
#   endif // defined(_MSC_EXTENSIONS)
            const double secOffSet = 0.000001;
            const unsigned long usecOffSet = 1000000;
            FILETIME fileTime_;
            GetSystemTimeAsFileTime(&fileTime_);
            unsigned __int64 present_ = 0;
            present_ |= fileTime_.dwHighDateTime;
            present_ = present_ << 32;
            present_ |= fileTime_.dwLowDateTime;
            present_ /= 10; // mic-sec
            // Subtract the difference
            present_ -= delta_;
            tv->tv_sec = static_cast<long>(present_ * secOffSet);
            tv->tv_usec = static_cast<long>(present_ % usecOffSet);
        }
    }
#endif // _ELPP_OS_WINDOWS
    // Gets current date and time with milliseconds.
    static std::string getDateTime(const std::string& bufferFormat_, unsigned int type_, internal::Constants* constants_, unsigned int milliSecondOffset_ = 1000) {
        long milliSeconds = 0;
        const int kDateBuffSize_ = 30;
        char dateBuffer_[kDateBuffSize_] = "";
        char dateBufferOut_[kDateBuffSize_] = "";
#if _ELPP_OS_UNIX
        bool hasTime_ = (type_ & constants_->kDateTime || type_ & constants_->kTimeOnly);
        timeval currTime;
        gettimeofday(&currTime, NULL);
        if (hasTime_) {
            milliSeconds = currTime.tv_usec / milliSecondOffset_ ;
        }
        struct tm * timeInfo = localtime(&currTime.tv_sec);
        strftime(dateBuffer_, sizeof(dateBuffer_), bufferFormat_.c_str(), timeInfo);
        if (hasTime_) {
            sprintf(dateBufferOut_, "%s.%03ld", dateBuffer_, milliSeconds);
        } else {
            sprintf(dateBufferOut_, "%s", dateBuffer_);
        }
#elif _ELPP_OS_WINDOWS
        const char* kTimeFormatLocal_ = "HH':'mm':'ss";
        const char* kDateFormatLocal_ = "dd/MM/yyyy";
        if ((type_ & constants_->kDateTime) || (type_ & constants_->kDateOnly)) {
            if (GetDateFormatA(LOCALE_USER_DEFAULT, 0, 0, kDateFormatLocal_, dateBuffer_, kDateBuffSize_) != 0) {
                sprintf_s(dateBufferOut_, "%s", dateBuffer_);
            }
        }
        if ((type_ & constants_->kDateTime) || (type_ & constants_->kTimeOnly)) {
            if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0, kTimeFormatLocal_, dateBuffer_, kDateBuffSize_) != 0) {
                milliSeconds = (long)(GetTickCount()) % milliSecondOffset_;
                if (type_ & constants_->kDateTime) {
                    sprintf_s(dateBufferOut_, "%s %s.%03ld", dateBufferOut_, dateBuffer_, milliSeconds);
                } else {
                    sprintf_s(dateBufferOut_, "%s.%03ld", dateBuffer_, milliSeconds);
                }
            }
        }
#endif // _ELPP_OS_UNIX
        return std::string(dateBufferOut_);
    }

    static std::string formatMilliSeconds(double milliSeconds_) {
        double result = milliSeconds_;
        std::string unit = "ms";
        std::stringstream stream_;
        if (result > 1000.0f) {
            result /= 1000; unit = "seconds";
            if (result > 60.0f) {
                result /= 60; unit = "minutes";
                if (result > 60.0f) {
                    result /= 60; unit = "hours";
                    if (result > 24.0f) {
                        result /= 24; unit = "days";
                    }
                }
            }
        }
        stream_ << result << " " << unit;
        return stream_.str();
    }

    static inline double getTimeDifference(const timeval& endTime_, const timeval& startTime_) {
        return static_cast<double>((((endTime_.tv_sec - startTime_.tv_sec) * 1000000) + (endTime_.tv_usec - startTime_.tv_usec)) / 1000);
    }
}; // class DateUtilities
} // namespace utilities

template<class Class, class Predicate>
class Registry {
public:
    explicit Registry(void) {
    }

    virtual ~Registry(void) {
        unregisterAll();
    }

    Registry(const Registry& other_) {
        if (this != &other_) {
            unregisterAll();
            for (unsigned int i = 0; i < other_.list_.size(); ++i) {
                Class* curr_ = other_.list_.at(i);
                if (curr_) {
                    list_.push_back(new Class(*curr_));
                }
            }
        }
    }

    Registry& operator=(const Registry& other_) {
        if (this == &other_) {
            return *this;
        }
        unregisterAll();
        for (unsigned int i = 0; i < other_.list_.size(); ++i) {
            Class* curr_ = other_.list_.at(i);
            if (curr_) {
                list_.push_back(new Class(*curr_));
            }
        }
        return *this;
    }

    bool operator!=(const Registry<Class, Predicate>& other_) {
        if (list_.size() != other_.list_.size()) {
            return true;
        }
        for (unsigned int i = 0; i < list_.size(); ++i) {
            if (list_.at(i) != other_.list_.at(i)) {
                return true;
            }
        }
        return false;
    }

    bool operator==(const Registry<Class, Predicate>& other_) {
        if (list_.size() != other_.list_.size()) {
            return false;
        }
        for (unsigned int i = 0; i < list_.size(); ++i) {
            if (list_.at(i) != other_.list_.at(i)) {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    Class* get(const T& t_) {
        Iterator iter = std::find_if(list_.begin(), list_.end(), Predicate(t_));
        if (iter != list_.end() && *iter != NULL) {
            return *iter;
        }
        return NULL;
    }

    template<typename T, typename T2>
    Class* get(const T& t_, const T2& t2_) {
        Iterator iter = std::find_if(list_.begin(), list_.end(), Predicate(t_, t2_));
        if (iter != list_.end() && *iter != NULL) {
            return *iter;
        }
        return NULL;
    }

    template<typename T2>
    inline bool exist(const T2& t_) {
        return (get(t_) != NULL);
    }

    inline size_t count(void) const {
        return list_.size();
    }

    inline bool empty(void) const {
        return list_.empty();
    }

    Class* at(unsigned int i) const {
        return list_.at(i);
    }

protected:
    typedef typename std::vector<Class*>::iterator Iterator;

    inline void registerNew(Class* c_) {
        list_.push_back(c_);
    }

    inline void unregisterAll(void) {
        if (!empty()) {
            std::for_each(list_.begin(), list_.end(), std::bind1st(std::mem_fun(&Registry::release), this));
            list_.clear();
        }
    }

    inline void unregister(Class* c_) {
        if (c_) {
            Iterator iter = list_.begin();
            for (; iter != list_.end(); ++iter) {
                if (c_ == *iter) {
                    break;
                }
            }
            if (iter != list_.end() && *iter != NULL) {
                list_.erase(iter);
                delete c_;
                c_ = NULL;
            }
        }
    }

    std::vector<Class*>& list(void) {
        return list_;
    }
private:
    inline void release(Class* c_) {
        if (c_) {
            delete c_;
            c_ = NULL;
        }
    }
    std::vector<Class*> list_;
}; // class Registry

template <typename T>
class SmartPointer {
public:
    explicit SmartPointer(void) :
        ptr_(0), referenceCounter_(0) {
        referenceCounter_ = new ReferenceCounter();
        referenceCounter_->increment();
    }

    SmartPointer(T* ptr_) :
        ptr_(ptr_), referenceCounter_(0) {
        referenceCounter_ = new ReferenceCounter();
        referenceCounter_->increment();
    }

    SmartPointer(const SmartPointer<T>& smartPointer_) :
        ptr_(smartPointer_.ptr_), referenceCounter_(smartPointer_.referenceCounter_) {
        referenceCounter_->increment();
    }

    SmartPointer<T>& operator=(const SmartPointer<T>& other_) {
        if (this != &other_)
        {
            validate();
            ptr_ = other_.ptr_;
            referenceCounter_ = other_.referenceCounter_;
            referenceCounter_->increment();
        }
        return *this;
    }

    virtual ~SmartPointer(void) {
        validate();
    }

    T& operator*(void) {
        return *ptr_;
    }

    T* operator->(void) {
        return ptr_;
    }

    T* pointer(void) {
        return ptr_;
    }

    class ReferenceCounter
    {
    public:
        explicit ReferenceCounter(void) : count_(0) {
        }

        ReferenceCounter& operator=(const ReferenceCounter& other_) {
            if (this != &other_) {
                count_ = other_.count_;
            }
            return *this;
        }

        void increment(void) {
            count_++;
        }

        int decrement(void) {
            return this == NULL ? 0 : --count_;
        }

    private:
        int count_;
    };
private:
    T* ptr_;
    ReferenceCounter* referenceCounter_;
    void validate(void) {
        if(referenceCounter_->decrement() == 0) {
            delete ptr_;
            ptr_ = NULL;
            delete referenceCounter_;
            referenceCounter_ = NULL;
        }
    }
};

class Configuration {
public:
    explicit Configuration(unsigned int level_, unsigned int type_, const std::string& value_) :
        level_(level_),
        type_(type_),
        value_(value_) {
    }

    unsigned int level(void) const {
        return level_;
    }

    unsigned int type(void) const {
        return type_;
    }
    std::string value(void) const {
        return value_;
    }

    void setValue(const std::string& value_) {
        this->value_ = value_;
    }

    class Predicate {
    public:
        explicit Predicate(unsigned int level_, unsigned int type_) :
            level_(level_),
            type_(type_) {
        }

        bool operator()(const Configuration* conf_) {
            return ((conf_ != NULL) && (conf_->level() == level_) && (conf_->type() == type_));
        }

    private:
        unsigned int level_;
        unsigned int type_;
    };
private:
    unsigned int level_;
    unsigned int type_;
    std::string value_;
};

} // namespace internal
class Configurations : public internal::Registry<internal::Configuration, internal::Configuration::Predicate> {
public:
    explicit Configurations(void) :
        isFromFile_(false) {
        setToDefault();
    }

    explicit Configurations(const std::string& configurationFile_, Configurations* base_ = NULL) :
        configurationFile_(configurationFile_),
        isFromFile_(false) {
        parseFromFile(configurationFile_, base_);
    }

    inline void setFromBase(Configurations* base_) {
        if (base_ == NULL || base_ == this) return;
        std::for_each(base_->list().begin(), base_->list().end(), std::bind1st(std::mem_fun(&Configurations::set), this));
    }

    void set(unsigned int level_, unsigned int configurationType_, const std::string& value_) {
        if (value_ == "") return; // ignore empty values
        if ((configurationType_ == ConfigurationType::ELPP_PerformanceTracking && level_ != Level::ELPP_ALL) ||
                (configurationType_ == ConfigurationType::ELPP_MillisecondsWidth && level_ != Level::ELPP_ALL)) {
            // configurationType_ not applicable for this level_
            return;
        }
        internal::Configuration* conf_ = get(level_, configurationType_);
        if (conf_ == NULL) {
            registerNew(new internal::Configuration(level_, configurationType_, value_));
        } else {
            // Configuration already there, just update the value!
            conf_->setValue(value_);
        }
        if (level_ == Level::ELPP_ALL) {
            setAll(configurationType_, value_, true);
        }
    }

    bool parseFromFile(const std::string& configurationFile_, Configurations* base_ = NULL) {
        setFromBase(base_);
        std::ifstream fileStream_(configurationFile_.c_str(), std::ifstream::in);
        __EASYLOGGINGPP_ASSERT(fileStream_.is_open(), "Unable to open configuration file for parsing.");
        bool parsedSuccessfully_ = false;
        std::string line = std::string();
        unsigned int currLevel = 0;
        while (fileStream_.good()) {
            std::getline(fileStream_, line);
            parsedSuccessfully_ = Parser::parseLine(line, currLevel, this);
            __EASYLOGGINGPP_ASSERT(parsedSuccessfully_, "Unable to parse configuration line: " << line);
        }
        isFromFile_ = true;
        return parsedSuccessfully_;
    }

    bool parseFromText(const std::string& configurationsString) {
        bool parsedSuccessfully_ = false;
        std::string line = std::string();
        unsigned int currLevel = 0;
        std::vector<std::string> lines;
        ELPP_StringUtils::split(configurationsString, '\n', lines);
        for (unsigned int i = 0; i < lines.size(); ++i) {
            line = lines.at(i);
            parsedSuccessfully_ = Parser::parseLine(line, currLevel, this);
            __EASYLOGGINGPP_ASSERT(parsedSuccessfully_, "Unable to parse configuration line: " << line);
        }
        isFromFile_ = false;
        return parsedSuccessfully_;
    }

    void setToDefault(void) {
        setAll(ConfigurationType::ELPP_Enabled, "true");
#if _ELPP_OS_UNIX
        setAll(ConfigurationType::ELPP_Filename, "/tmp/logs/myeasylog.log");
#elif _ELPP_OS_WINDOWS
        setAll(ConfigurationType::ELPP_Filename, "logs/myeasylog.log");
#endif // _ELPP_OS_UNIX
        setAll(ConfigurationType::ELPP_ToFile, "true");
        setAll(ConfigurationType::ELPP_ToStandardOutput, "true");
        setAll(ConfigurationType::ELPP_MillisecondsWidth, "3");
        setAll(ConfigurationType::ELPP_PerformanceTracking, "false");
        setAll(ConfigurationType::ELPP_Format, "%datetime %level  [%logger] %log");
        set(Level::ELPP_DEBUG, ConfigurationType::ELPP_Format, "%datetime %level [%logger] [%user@%host] [%func] [%loc] %log");
        // INFO and WARNING are set to default by Level::ALL
        set(Level::ELPP_ERROR, ConfigurationType::ELPP_Format, "%datetime %level [%logger] %log");
        set(Level::ELPP_FATAL, ConfigurationType::ELPP_Format, "%datetime %level [%logger] %log");
        set(Level::ELPP_VERBOSE, ConfigurationType::ELPP_Format, "%datetime %level-%vlevel [%logger] %log");
        set(Level::ELPP_QA, ConfigurationType::ELPP_Format, "%datetime %level    [%logger] %log");
        set(Level::ELPP_TRACE, ConfigurationType::ELPP_Format, "%datetime %level [%logger] [%func] [%loc] %log");
    }

    inline void setAll(unsigned int configurationType_, const std::string& value_, bool skipELPP_ALL = false) {
        if (!skipELPP_ALL) {
            set(Level::ELPP_ALL, configurationType_, value_);
        }
        for (unsigned int i = 1; i <= 128; i <<= 1) {
            set(i, configurationType_, value_);
        }
    }

    inline void clear(void) {
        unregisterAll();
    }

    std::string configurationFile(void) const {
        return configurationFile_;
    }

    class Parser {
        _ELPP_NO_INITIALIZATION(Parser)
        public:
            static void ignoreComments(std::string& line) {
            size_t foundAt = 0;
            size_t quotesStart = line.find("\"");
            size_t quotesEnd = std::string::npos;
            if (quotesStart != std::string::npos) {
                quotesEnd = line.find("\"", quotesStart + 1);
            }
            if ((foundAt = line.find("//")) != std::string::npos) {
                if (foundAt < quotesEnd) {
                    foundAt = line.find("//", quotesEnd + 1);
                }
                line = line.substr(0, foundAt);
            }
        }

        static inline bool isLevel(const std::string& line) {
            return ELPP_StringUtils::startsWith(line, "*");
        }

        static inline bool isConfig(const std::string& line) {
            size_t assignment = line.find('=');
            return line != "" &&
                    (line[0] >= 65 || line[0] <= 90 || line[0] >= 97 || line[0] <= 122) &&
                    (assignment != std::string::npos) &&
                    (line.size() > assignment);
        }

        static inline bool isComment(const std::string& line) {
            return ELPP_StringUtils::startsWith(line, "//");
        }

        static unsigned int levelFromString(const std::string& levelStr) {
            if (levelStr == "all")
                return Level::ELPP_ALL;
            if (levelStr == "debug")
                return Level::ELPP_DEBUG;
            if (levelStr == "info")
                return Level::ELPP_INFO;
            if (levelStr == "warning")
                return Level::ELPP_WARNING;
            if (levelStr == "error")
                return Level::ELPP_ERROR;
            if (levelStr == "fatal")
                return Level::ELPP_FATAL;
            if (levelStr == "qa")
                return Level::ELPP_QA;
            if (levelStr == "verbose")
                return Level::ELPP_VERBOSE;
            if (levelStr == "trace")
                return Level::ELPP_TRACE;
            return 1010;
        }
        static unsigned int configFromString(const std::string& configStr) {
            if (configStr == "enabled")
                return ConfigurationType::ELPP_Enabled;
            if (configStr == "to_file")
                return ConfigurationType::ELPP_ToFile;
            if (configStr == "to_standard_output")
                return ConfigurationType::ELPP_ToStandardOutput;
            if (configStr == "format")
                return ConfigurationType::ELPP_Format;
            if (configStr == "filename")
                return ConfigurationType::ELPP_Filename;
            if (configStr == "milliseconds_width")
                return ConfigurationType::ELPP_MillisecondsWidth;
            if (configStr == "performance_tracking")
                return ConfigurationType::ELPP_PerformanceTracking;
            return 1010;
        }
        static bool parseLine(std::string& line, unsigned int& currLevel, Configurations* conf) {
            std::string currLevelStr = std::string();
            unsigned int currConfig = 0;
            std::string currConfigStr = std::string();
            std::string currValue = std::string();
            if (isComment(line)) return true;
            ignoreComments(line);
            line = ELPP_StringUtils::trim(line);
            if (line == "") {
                // Comment ignored
                return true;
            }
            if (Parser::isLevel(line)) {
                currLevelStr = ELPP_StringUtils::stripAllWhiteSpaces(line);
                if (currLevelStr.size() <= 2) {
                    return true;
                }
                currLevelStr = currLevelStr.substr(1, currLevelStr.size() - 2);
                ELPP_StringUtils::tolower(currLevelStr);
                currLevel = Parser::levelFromString(currLevelStr);
                return true;
            }
            if (isConfig(line)) {
                size_t assignment = line.find('=');
                currConfigStr = line.substr(0, assignment);
                currConfigStr = ELPP_StringUtils::stripAllWhiteSpaces(currConfigStr);
                ELPP_StringUtils::tolower(currConfigStr);
                currConfig = Parser::configFromString(currConfigStr);
                currValue = line.substr(assignment + 1);
                currValue = ELPP_StringUtils::trim(currValue);
                size_t quotesStart = currValue.find("\"", 0);
                size_t quotesEnd = std::string::npos;
                if (quotesStart != std::string::npos) {
                    quotesEnd = currValue.find("\"", quotesStart + 1);
                }
                if (quotesStart != std::string::npos && quotesEnd != std::string::npos) {
                    // Quote provided - check and strip if valid
                    __EASYLOGGINGPP_ASSERT((quotesStart < quotesEnd), "Configuration error - No ending quote found in [" << currConfigStr << "]");
                    __EASYLOGGINGPP_ASSERT((quotesStart + 1 != quotesEnd), "Empty configuration value for [" << currConfigStr << "]");
                    if ((quotesStart != quotesEnd) && (quotesStart + 1 != quotesEnd)) {
                        // Explicit check in case if assertion is disabled
                        currValue = currValue.substr(quotesStart + 1, quotesEnd - 1);
                    }
                }
            }
            __EASYLOGGINGPP_ASSERT(currLevel != 1010, "Unrecognized severity level [" << currLevelStr << "]");
            __EASYLOGGINGPP_ASSERT(currConfig != 1010, "Unrecognized configuration [" << currConfigStr << "]");
            if (currLevel == 1010 || currConfig == 1010) {
                return false; // unrecognizable level or config
            }
            conf->set(currLevel, currConfig, currValue);
            return true;
        }
    }; // class Parser
private:
    std::string configurationFile_;
    bool isFromFile_;

    inline void set(internal::Configuration* conf_) {
        if (conf_ == NULL) return;
        set(conf_->level(), conf_->type(), conf_->value());
    }
}; // class Configurations

class Loggers;  // fwd declaration

namespace internal {
class TypedConfigurations {
public:
    explicit TypedConfigurations(const Configurations& configurations, internal::Constants* constants_) :
        constants_(constants_) {
        parse(configurations);
    }

    virtual ~TypedConfigurations(void) {
        deleteFileStreams();
    }
private:
    std::map<unsigned int, bool> enabledMap_;
    std::map<unsigned int, bool> toFileMap_;
    std::map<unsigned int, std::string> filenameMap_;
    std::map<unsigned int, bool> toStandardOutputMap_;
    std::map<unsigned int, std::string> logFormatMap_;
    std::map<unsigned int, std::string> dateFormatMap_;
    std::map<unsigned int, std::string> dateFormatSpecifierMap_;
    std::map<unsigned int, int> millisecondsLengthMap_;
    std::map<unsigned int, bool> performanceTrackingMap_;
    std::map<unsigned int, std::ofstream*> fileStreamMap_;
    std::map<unsigned int, unsigned int> formatFlagMap_;
    internal::Constants* constants_;
    friend class Writer;
    friend class easyloggingpp::Loggers;

    bool enabled(unsigned int level_) {
        std::map<unsigned int, bool>::iterator it = enabledMap_.find(level_);
        if (it == enabledMap_.end()) {
            return enabledMap_[Level::ELPP_ALL];
        }
        return it->second;
    }

    bool toFile(unsigned int level_) {
        std::map<unsigned int, bool>::iterator it = toFileMap_.find(level_);
        if (it == toFileMap_.end()) {
            return toFileMap_[Level::ELPP_ALL];
        }
        return it->second;
    }

    std::string& filename(unsigned int level_) {
        std::map<unsigned int, std::string>::iterator it = filenameMap_.find(level_);
        if (it == filenameMap_.end()) {
            return filenameMap_[Level::ELPP_ALL];
        }
        return it->second;
    }

    bool toStandardOutput(unsigned int level_) {
        std::map<unsigned int, bool>::iterator it = toStandardOutputMap_.find(level_);
        if (it == toStandardOutputMap_.end()) {
            return toStandardOutputMap_[Level::ELPP_ALL];
        }
        return it->second;
    }

    std::string& logFormat(unsigned int level_) {
        std::map<unsigned int, std::string>::iterator it = logFormatMap_.find(level_);
        if (it == logFormatMap_.end()) {
            return logFormatMap_[Level::ELPP_ALL];
        }
        return it->second;
    }

    std::string& dateFormat(unsigned int level_) {
        std::map<unsigned int, std::string>::iterator it = dateFormatMap_.find(level_);
        if (it == dateFormatMap_.end()) {
            return dateFormatMap_[Level::ELPP_ALL];
        }
        return it->second;
    }

    std::string& dateFormatSpecifier(unsigned int level_) {
        std::map<unsigned int, std::string>::iterator it = dateFormatSpecifierMap_.find(level_);
        if (it == dateFormatSpecifierMap_.end()) {
            return dateFormatSpecifierMap_[Level::ELPP_ALL];
        }
        return it->second;
    }

    int millisecondsLength(unsigned int level_ = Level::ELPP_ALL) {
        __EASYLOGGINGPP_SUPPRESS_UNSED(level_);
        return millisecondsLengthMap_[Level::ELPP_ALL];
    }

    bool performanceTracking(unsigned int level_ = Level::ELPP_ALL) {
        __EASYLOGGINGPP_SUPPRESS_UNSED(level_);
        return performanceTrackingMap_[Level::ELPP_ALL];
    }

    std::ofstream* fileStream(unsigned int level_) {
        std::map<unsigned int, std::ofstream*>::iterator it = fileStreamMap_.find(level_);
        if (it == fileStreamMap_.end()) {
            return fileStreamMap_[Level::ELPP_ALL];
        }
        return it->second;
    }

    int formatFlag(unsigned int level_) {
        std::map<unsigned int, unsigned int>::iterator it = formatFlagMap_.find(level_);
        if (it == formatFlagMap_.end()) {
            return formatFlagMap_[Level::ELPP_ALL];
        }
        return it->second;
    }

    void parse(const Configurations& configurations_) {
        for (size_t i = 0; i < configurations_.count(); ++i) {
            Configuration* conf = configurations_.at(i);
            switch (conf->type()) {
            case ConfigurationType::ELPP_Enabled:
                setValue(conf->level(), getBool(conf->value()), enabledMap_);
                break;
            case ConfigurationType::ELPP_ToFile:
                setValue(conf->level(), getBool(conf->value()), toFileMap_);
                break;
            case ConfigurationType::ELPP_Filename:
                insertFilename(conf->level(), conf->value());
                break;
            case ConfigurationType::ELPP_ToStandardOutput:
                setValue(conf->level(), getBool(conf->value()), toStandardOutputMap_);
                break;
            case ConfigurationType::ELPP_Format:
                determineFormats(conf->level(), conf->value());
                break;
            case ConfigurationType::ELPP_MillisecondsWidth:
                if (conf->level() == Level::ELPP_ALL) {
                    int origVal = getInt(conf->value());
                    int msl_;
#if _ELPP_OS_UNIX
                    switch (origVal) {
                    case 3:
                        msl_ = 1000;
                        break;
                    case 4:
                        msl_ = 100;
                        break;
                    case 5:
                        msl_ = 10;
                        break;
                    case 6:
                        msl_ = 1;
                        break;
                    default:
                        msl_ = constants_->DEFAULT_MILLISECOND_OFFSET;
                    }
#elif _ELPP_OS_WINDOWS
                    msl_ = 1000;
#endif // _ELPP_OS_UNIX
                    setValue(conf->level(), msl_, millisecondsLengthMap_);
                }
                break;
            case ConfigurationType::ELPP_PerformanceTracking:
                if (conf->level() == Level::ELPP_ALL) {
                    setValue(conf->level(), getBool(conf->value()), performanceTrackingMap_);
                }
                break;
            }
        }
    }

    void determineFormats(unsigned int level_, const std::string& originalFormat) {
        unsigned int formatSpec = 0x0;
        if (originalFormat.find(constants_->APP_NAME_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kAppName;
        }
        if (originalFormat.find(constants_->LOGGER_ID_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kLoggerId;
        }
        if (originalFormat.find(constants_->LOCATION_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kLocation;
        }
        if (originalFormat.find(constants_->FUNCTION_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kFunction;
        }
        if (originalFormat.find(constants_->USER_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kUser;
        }
        if (originalFormat.find(constants_->HOST_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kHost;
        }
        if (originalFormat.find(constants_->LOG_MESSAGE_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kLogMessage;
        }
        if (originalFormat.find(constants_->VERBOSE_LEVEL_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kVerboseLevel;
        }
        if (originalFormat.find(constants_->DATE_TIME_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kDateTime;
            setValue(level_, constants_->DATE_TIME_FORMAT_SPECIFIER, dateFormatSpecifierMap_);
        } else if (originalFormat.find(constants_->DATE_ONLY_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kDateOnly;
            setValue(level_, constants_->DATE_ONLY_FORMAT_SPECIFIER, dateFormatSpecifierMap_);
        } else if (originalFormat.find(constants_->TIME_ONLY_FORMAT_SPECIFIER) != std::string::npos) {
            formatSpec |= constants_->kTimeOnly;
            setValue(level_, constants_->TIME_ONLY_FORMAT_SPECIFIER, dateFormatSpecifierMap_);
        }
#if _ELPP_OS_UNIX
        const std::string kTimeFormatLocal_ = "%H:%M:%S";
        const std::string kDateFormatLocal_ = "%d/%m/%Y";
        std::string dateFormat;

        if (formatSpec & constants_->kDateOnly) {
            dateFormat = kDateFormatLocal_;
        } else if (formatSpec & constants_->kTimeOnly) {
            dateFormat = kTimeFormatLocal_;
        } else {
            std::stringstream ss;
            ss << kDateFormatLocal_ << " " << kTimeFormatLocal_;
            dateFormat = ss.str();
        }
        setValue(level_, dateFormat, dateFormatMap_);
#endif // _ELPP_OS_UNIX
        setValue(level_, formatSpec, formatFlagMap_);
        // Update %level
        std::string origFormatCopy = originalFormat;
        switch (level_) {
        case Level::ELPP_DEBUG:
            utilities::LogManipulator::updateFormatValue(constants_->LEVEL_FORMAT_SPECIFIER,
                                                         constants_->LOG_DEBUG_LEVEL_VALUE, origFormatCopy, constants_);
            break;
        case Level::ELPP_INFO:
            utilities::LogManipulator::updateFormatValue(constants_->LEVEL_FORMAT_SPECIFIER,
                                                         constants_->LOG_INFO_LEVEL_VALUE, origFormatCopy, constants_);
            break;
        case Level::ELPP_WARNING:
            utilities::LogManipulator::updateFormatValue(constants_->LEVEL_FORMAT_SPECIFIER,
                                                         constants_->LOG_WARNING_LEVEL_VALUE, origFormatCopy, constants_);
            break;
        case Level::ELPP_ERROR:
            utilities::LogManipulator::updateFormatValue(constants_->LEVEL_FORMAT_SPECIFIER,
                                                         constants_->LOG_ERROR_LEVEL_VALUE, origFormatCopy, constants_);
            break;
        case Level::ELPP_FATAL:
            utilities::LogManipulator::updateFormatValue(constants_->LEVEL_FORMAT_SPECIFIER,
                                                         constants_->LOG_FATAL_LEVEL_VALUE, origFormatCopy, constants_);
            break;
        case Level::ELPP_VERBOSE:
            utilities::LogManipulator::updateFormatValue(constants_->LEVEL_FORMAT_SPECIFIER,
                                                         constants_->LOG_VERBOSE_LEVEL_VALUE, origFormatCopy, constants_);
            break;
        case Level::ELPP_QA:
            utilities::LogManipulator::updateFormatValue(constants_->LEVEL_FORMAT_SPECIFIER,
                                                         constants_->LOG_QA_LEVEL_VALUE, origFormatCopy, constants_);
            break;
        case Level::ELPP_TRACE:
            utilities::LogManipulator::updateFormatValue(constants_->LEVEL_FORMAT_SPECIFIER,
                                                         constants_->LOG_TRACE_LEVEL_VALUE, origFormatCopy, constants_);
            break;
        }
        setValue(level_, origFormatCopy + "\n", logFormatMap_);
    }

    void deleteFileStreams(void) {
        for (std::map<unsigned int, std::ofstream*>::iterator it = fileStreamMap_.begin();
             it != fileStreamMap_.end(); ++it) {
            if (it->second) {
                if (it->second->is_open()) {
                    it->second->close();
                }
                delete it->second;
                it->second = NULL;
            }
        }
        fileStreamMap_.clear();
    }

    // This is different since we need unique values
    void insertFilename(unsigned int level_, const std::string& fname_) {
        std::string fnameFull = fname_;
        if (utilities::StringUtilities::endsWith(fnameFull, constants_->PATH_SLASH)) {
            fnameFull.append(constants_->DEFAULT_LOG_FILENAME);
        }
        std::string path_ = utilities::OSUtilities::getPathFromFilename(fnameFull, constants_);
        if (path_.size() < fnameFull.size()) {
            // Contains path - create it if it does not already exist
            utilities::OSUtilities::createPath(path_);
        }
        if (filenameMap_.size() == 0) {
            filenameMap_.insert(std::pair<unsigned int, std::string>(Level::ELPP_ALL, fnameFull));
            std::ofstream *fsAll = newFileStream(fnameFull);
            if (fsAll != NULL) {
                fileStreamMap_.insert(std::pair<unsigned int, std::ofstream*>(Level::ELPP_ALL, fsAll));
            }
            return;
        }
        for (std::map<unsigned int, std::string>::iterator it = filenameMap_.begin(); it != filenameMap_.end(); ++it) {
            if (it->second == fnameFull) {
                return;
            }
        }
        filenameMap_.insert(std::pair<unsigned int, std::string>(level_, fnameFull));
        // Just before we proceed and create new file stream we check for existing one on same level,
        // if we have existing one, we first delete it to prevent memory leak.
        std::ofstream *fs = fileStreamMap_[level_];
        if (fs != NULL) {
            delete fs;
            fs = NULL;
        }
        fileStreamMap_.erase(level_);
        fs = newFileStream(fnameFull);
        if (fs != NULL) {
            fileStreamMap_.insert(std::pair<unsigned int, std::ofstream*>(level_, fs));
        }
    }

    template <typename T>
    void setValue(unsigned int level_, const T& value_, std::map<unsigned int, T>& map_, bool skipELPP_ALL = false) {
        if (map_.size() == 0 && !skipELPP_ALL) {
            map_.insert(std::pair<unsigned int, T>(Level::ELPP_ALL, value_));
            return;
        }
        typedef typename std::map<unsigned int, T>::iterator Iterator;
        for (Iterator it = map_.begin(); it != map_.end(); ++it) {
            if (it->second == value_) {
                return;
            }
        }
        Iterator it = map_.find(level_);
        if (it == map_.end()) {
            map_.insert(std::pair<unsigned int, T>(level_, value_));
        } else {
            map_[level_] = value_;
        }
    }

    std::ofstream* newFileStream(const std::string& filename) {
#if defined(_ALWAYS_CLEAN_LOGS)
        std::ofstream *fs = new std::ofstream(filename.c_str(), std::ofstream::out);
#else
        std::ofstream *fs = new std::ofstream(filename.c_str(), std::ofstream::out | std::ofstream::app);
#endif // defined(_ALWAYS_CLEAN_LOGS)
        if (fs->is_open()) {
            fs->flush();
        } else {
            delete fs;
            fs = NULL;
            std::cerr << "Bad file [" << filename << "]" << std::endl;
        }
        return fs;
    }

    int getInt(const std::string& confValue_) {
        bool valid = true;
        std::string trimmedVal = utilities::StringUtilities::trim(confValue_);
        if (trimmedVal.size() == 0) {
            valid = false;
            __EASYLOGGINGPP_SUPPRESS_UNSED(valid);
            __EASYLOGGINGPP_ASSERT(valid, "Configuration value not a valid integer " << trimmedVal);
        }
        for (size_t i = 0; i < trimmedVal.size(); ++i) {
            if (trimmedVal[i] < 48 || trimmedVal[i] > 57) {
                valid = false;
                break;
            }
        }
        __EASYLOGGINGPP_SUPPRESS_UNSED(valid);
        __EASYLOGGINGPP_ASSERT(valid, "Configuration value not a valid integer " << trimmedVal);
        return atoi(confValue_.c_str());
    }

    inline bool getBool(const std::string& confValue_) {
        std::string trimmedVal = utilities::StringUtilities::trim(confValue_);
        return (trimmedVal == "1" || trimmedVal == "true" || trimmedVal == "TRUE");
    }
};
class Writer;  // fwd declaration
} // namespace internal
class Logger {
public:
    explicit Logger(const std::string& uniqueIdentifier_, internal::Constants* constants_) :
        id_(uniqueIdentifier_),
        constants_(constants_),
        typedConfigurations_(NULL),
        stream_(new std::stringstream()){
        Configurations defaultConfs;
        configure(defaultConfs);
        userConfigurations_ = defaultConfs;
        defaultConfs.clear();
    }

    explicit Logger(const std::string& uniqueIdentifier_, internal::Constants* constants_, const Configurations& configurations) :
        id_(uniqueIdentifier_),
        constants_(constants_),
        typedConfigurations_(NULL),
        stream_(new std::stringstream()){
        configure(configurations);
    }

    virtual ~Logger(void) {
        if (typedConfigurations_) {
            delete typedConfigurations_;
            typedConfigurations_ = NULL;
        }
        if (stream_) {
            delete stream_;
            stream_ = NULL;
        }
    }

    inline std::string id(void) const {
        return id_;
    }

    void configure(const Configurations& configurations_) {
        if (this->userConfigurations_ != configurations_) {
            this->userConfigurations_ = configurations_;
        }
        if (typedConfigurations_) {
            delete typedConfigurations_;
            typedConfigurations_ = NULL;
        }
        typedConfigurations_ = new internal::TypedConfigurations(configurations_, constants_);
        configured_ = true;
    }

    inline void reconfigure(void) {
        configure(this->userConfigurations_);
    }

    inline std::string applicationName(void) const {
        return applicationName_;
    }

    inline void setApplicationName(const std::string& applicationName_) {
        this->applicationName_ = applicationName_;
    }

    inline Configurations& configurations(void) {
        return userConfigurations_;
    }

    inline bool configured(void) const {
        return configured_;
    }

    class Predicate {
    public:
        explicit Predicate(const std::string& id_) :
            id_(id_) {
        }
        inline bool operator()(const Logger* logger_) {
            return ((logger_ != NULL) && (logger_->id() == id_));
        }
    private:
        std::string id_;
    };
private:
    std::string id_;
    internal::Constants* constants_;
    Configurations userConfigurations_;
    internal::TypedConfigurations* typedConfigurations_;
    std::stringstream* stream_;
    std::string applicationName_;
    bool configured_;
    friend class internal::Writer;
    friend class Loggers;

    Logger(void);

    std::stringstream* stream(void) {
        return stream_;
    }
};
namespace internal {
class LogCounter {
    _ELPP_NO_COPY(LogCounter)
    public:
        explicit LogCounter(Constants* constants_) :
      file_(""),
        line_(0),
        position_(1),
        constants_(constants_) {
    }

    explicit LogCounter(const char* file_,
                        unsigned long int line_,
                        Constants* constants_) :
        file_(file_),
        line_(line_),
        position_(1),
        constants_(constants_) {
    }

    virtual ~LogCounter(void) {
    }

    inline void resetLocation(const char* file_,
                              unsigned long int line_) {
        this->file_ = file_;
        this->line_ = line_;
    }

    inline void reset(unsigned int n_) {
        if (position_ >= constants_->MAX_LOG_PER_COUNTER) {
            position_ = (n_ >= 1 ? constants_->MAX_LOG_PER_COUNTER % n_ : 0);
        }
        ++position_;
    }

    inline const char* file(void) const {
        return file_;
    }

    inline unsigned long int line(void) const {
        return line_;
    }

    inline unsigned int position(void) const {
        return position_;
    }

    inline std::string toString(void) const {
        std::stringstream ss;
        ss << position_;
        return ss.str();
    }

    class Predicate {
    public:
        explicit Predicate(const char* file_, unsigned long int line_)
            : file_(file_),
              line_(line_) {
        }
        inline bool operator()(const LogCounter* counter_) {
            return ((counter_ != NULL) &&
                    (counter_->file_ == file_) &&
                    (counter_->line_ == line_));
        }

    private:
        const char* file_;
        unsigned long int line_;
    };
private:
    const char* file_;
    unsigned long int line_;
    unsigned int position_;
    Constants* constants_;
}; // class LogCounter

class RegisteredCounters : public Registry<LogCounter, LogCounter::Predicate>  {
public:
    bool validate(const char* file_, unsigned long int line_, unsigned int n_, Constants* constants_) {
        bool result_ = false;
        LogCounter* counter_ = get(file_, line_);
        if (counter_ == NULL) {
            registerNew(counter_ = new LogCounter(file_, line_, constants_));
        }
        if (n_ >= 1 && counter_->position() != 0 && counter_->position() % n_ == 0) {
            result_ = true;
        }
        counter_->reset(n_);
        return result_;
    }
}; // class RegisteredCounters

class RegisteredLoggers : public internal::Registry<Logger, Logger::Predicate> {
public:
    RegisteredLoggers(void) :
        constants_(new internal::Constants()),
        username_(utilities::OSUtilities::currentUser()),
        hostname_(utilities::OSUtilities::currentHost()),
        counters_(new internal::RegisteredCounters()) {
        Configurations conf;
        conf.parseFromText(constants_->DEFAULT_LOGGER_CONFIGURATION);
        registerNew(new Logger("trivial", constants_, conf));
        registerNew(new Logger("business", constants_));
        registerNew(new Logger("security", constants_));
        Configurations confPerformance;
        confPerformance.setAll(ConfigurationType::ELPP_PerformanceTracking, "true");
        registerNew(new Logger("performance", constants_, confPerformance));
    }

    virtual ~RegisteredLoggers(void) {
        if (constants_) {
            delete constants_;
            constants_ = NULL;
        }
        if (counters_) {
            delete counters_;
            counters_ = NULL;
        }
    }

    internal::Constants* constants(void) const {
        return constants_;
    }

    RegisteredCounters* counters(void) {
        return counters_;
    }

    bool validateCounter(const char* file_, unsigned long int line_, unsigned int n_) {
        return counters_->validate(file_, line_, n_, constants_);
    }
private:
    internal::Constants* constants_;
    std::string username_;
    std::string hostname_;
    internal::threading::Mutex mutex_;
    RegisteredCounters* counters_;
    friend class Writer;
    friend class easyloggingpp::Loggers;

    inline std::string& username(void) {
        return username_;
    }

    inline std::string& hostname(void) {
        return hostname_;
    }

    Logger* get(const std::string& id_) {
        Logger* logger_ = internal::Registry<Logger, Logger::Predicate>::get(id_);
        if (logger_ == NULL) {
            logger_ = new Logger(id_, constants_);
            registerNew(logger_);
        }
        return logger_;
    }

    inline void unregister(Logger*& logger_) {
        internal::Registry<Logger, Logger::Predicate>::unregister(logger_);
    }

    inline void acquireLock(void) {
        mutex_.lock();
    }

    inline void releaseLock(void) {
        mutex_.unlock();
    }

    void setApplicationArguments(int argc, char** argv) {
        while (argc-- > 0) {
            // Look for --v=X argument
            if ((strlen(argv[argc]) >= 5) && (argv[argc][0] == '-') && (argv[argc][1] == '-') &&
                    (argv[argc][2] == 'v') && (argv[argc][3] == '=') && (isdigit(argv[argc][4]))) {
                // Current argument is --v=X
                // where X is a digit between 0-9
                constants_->CURRENT_VERBOSE_LEVEL = atoi(argv[argc] + 4);
            }
            // Look for -v argument
            else if ((strlen(argv[argc]) == 2) && (argv[argc][0] == '-') && (argv[argc][1] == 'v')) {
                constants_->CURRENT_VERBOSE_LEVEL = constants_->MAX_VERBOSE_LEVEL;
            }
            // Look for --verbose argument
            else if ((strlen(argv[argc]) == 9) && (argv[argc][0] == '-') && (argv[argc][1] == '-') &&
                     (argv[argc][2] == 'v') && (argv[argc][3] == 'e') && (argv[argc][4] == 'r') &&
                     (argv[argc][5] == 'b') && (argv[argc][6] == 'o') && (argv[argc][7] == 's') &&
                     (argv[argc][8] == 'e')) {
                constants_->CURRENT_VERBOSE_LEVEL = constants_->MAX_VERBOSE_LEVEL;
            }
        }
    }

    inline void setApplicationArguments(int argc, const char** argv) {
        setApplicationArguments(argc, const_cast<char**>(argv));
    }
};

extern internal::SmartPointer<RegisteredLoggers> registeredLoggers;
#if defined(_ELPP_STL_LOGGING)
namespace workarounds {
// There is workaround needed to loop through some stl containers. In order to do that, we need iterable containers
// of same type and provide iterator interface and pass it on to writeIterator().
// Remember, this is passed by value in constructor so that we dont change original queue.
// This operation is as expensive as O(class_.size()) or O(kContainerMaxLog) which ever is smaller.

//
// Abstract IterableContainer template that provides interface for iterable classes of type T
//
template <typename T, typename Container>
class IterableContainer {
public:
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;
    IterableContainer(void){}
    iterator begin(void) { return getContainer().begin(); }
    iterator end(void) { return getContainer().end(); }
    const_iterator begin(void) const { return getContainer().begin(); }
    const_iterator end(void) const { return getContainer().end(); }
private:
    virtual Container& getContainer(void) = 0;
};

//
// Implements IterableContainer and provides iterable std::priority_queue class
//
template<typename T, typename Container = std::vector<T>, typename Comparator = std::less<typename Container::value_type> >
class IterablePriorityQueue : public IterableContainer<T, Container>, public std::priority_queue<T, Container, Comparator> {
public:
    explicit IterablePriorityQueue(std::priority_queue<T, Container, Comparator> queue_) {
        unsigned int count_ = 0;
        while (++count_ < registeredLoggers->constants()->MAX_LOG_PER_CONTAINER && !queue_.empty()) {
            this->push(queue_.top());
            queue_.pop();
        }
    }
private:
    inline Container& getContainer(void) {
        return this->c;
    }
};

//
// Implements IterableContainer and provides iterable std::queue class
//
template<typename T, typename Container = std::deque<T> >
class IterableQueue : public IterableContainer<T, Container>, public std::queue<T, Container> {
public:
    explicit IterableQueue(std::queue<T, Container> queue_) {
        unsigned int count_ = 0;
        while (++count_ < registeredLoggers->constants()->MAX_LOG_PER_CONTAINER && !queue_.empty()) {
            this->push(queue_.front());
            queue_.pop();
        }
    }
private:
    inline Container& getContainer(void) {
        return this->c;
    }
};

//
// Implements IterableContainer and provides iterable std::stack class
//
template<typename T, typename Container = std::deque<T> >
class IterableStack : public IterableContainer<T, Container>, public std::stack<T, Container> {
public:
    explicit IterableStack(std::stack<T, Container> stack_) {
        unsigned int count_ = 0;
        while (++count_ < registeredLoggers->constants()->MAX_LOG_PER_CONTAINER && !stack_.empty()) {
            this->push(stack_.top());
            stack_.pop();
        }
    }
private:
    inline Container& getContainer(void) {
        return this->c;
    }
};
} // namespace workarounds
#endif //defined(_ELPP_STL_LOGGING)

#define _ELPP_STREAM(l) (*(l->stream()))

class Writer {
public:
    explicit Writer(const std::string& loggerId_,
                    unsigned int aspect_,
                    unsigned int severity_,
                    const char* func_,
                    const char* file_,
                    const unsigned long int line_,
                    bool condition_ = true,
                    int verboseLevel_ = 0,
                    int counter_ = 0) :
        aspect_(aspect_),
        severity_(severity_),
        func_(func_),
        file_(file_),
        line_(line_),
        condition_(condition_),
        verboseLevel_(verboseLevel_),
        counter_(counter_),
        proceed_(true),
        constants_(registeredLoggers->constants()) {
        logger_ = registeredLoggers->get(loggerId_);
        if (!logger_->configured()) {
            __EASYLOGGINGPP_ASSERT(logger_->configured(), "Logger [" << loggerId_ << "] has not been configured!");
            registeredLoggers->unregister(logger_);
            logger_ = NULL; // unregister() should do this - but isnt
            proceed_ = false;
        }
        if (proceed_) {
            proceed_ = logger_->typedConfigurations_->enabled(severity_) && (_ENABLE_EASYLOGGING);
            if (proceed_) {
                if (severity_ == Level::ELPP_DEBUG) {
#if (!_ELPP_DEBUG_LOG)
                    proceed_ = false;
#endif
                } else if (severity_ == Level::ELPP_INFO) {
#if (!_ELPP_INFO_LOG)
                    proceed_ = false;
#endif
                } else if (severity_ == Level::ELPP_WARNING) {
#if (!_ELPP_WARNING_LOG)
                    proceed_ = false;
#endif
                } else if (severity_ == Level::ELPP_ERROR) {
#if (!_ELPP_ERROR_LOG)
                    proceed_ = false;
#endif
                } else if (severity_ == Level::ELPP_FATAL) {
#if (!_ELPP_FATAL_LOG)
                    proceed_ = false;
#endif
                } else if (severity_ == Level::ELPP_QA) {
#if (!_ELPP_QA_LOG)
                    proceed_ = false;
#endif
                } else if (severity_ == Level::ELPP_VERBOSE) {
#if (!_ELPP_VERBOSE_LOG)
                    proceed_ = false;
#endif
                } else if (severity_ == Level::ELPP_TRACE) {
#if (!_ELPP_TRACE_LOG)
                    proceed_ = false;
#endif
                }
            }
        }
        if (proceed_ && (severity_ == Level::ELPP_VERBOSE)) {
            proceed_ = (verboseLevel_ <= constants_->CURRENT_VERBOSE_LEVEL);
        }
        if (proceed_ && (aspect_ == Aspect::Conditional)) {
            proceed_ = condition_;
        }
#if _ELPP_ENABLE_MUTEX
        registeredLoggers->acquireLock();
#endif // _ELPP_ENABLE_MUTEX
    }

    virtual ~Writer(void) {
        if (proceed_) {
            buildAndWriteLine();
        }

#if _ELPP_ENABLE_MUTEX
        registeredLoggers->releaseLock();
#endif // _ELPP_ENABLE_MUTEX
    }

    inline Writer& operator<<(const std::string& log_) {
        if (!proceed_) { return *this; }
#if _ENABLE_EASYLOGGING
        _ELPP_STREAM(logger_) << log_;
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(char log_) {
#if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(bool log_) {
#if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(signed short log_) {
#if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(unsigned short log_) {
#if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(signed int log_) {
#if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(unsigned int log_) {
#if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(signed long log_) {
#if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(unsigned long log_) {
#if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(float log_) {
#if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(double log_) {
#if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(char* log_) {
#if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(const char* log_) {
#if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(const void* log_) {
#if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(long double log_) {
#if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_;
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(const std::wstring& log_) {
        if (!proceed_) { return *this; }
        return operator<<(log_.c_str());
    }
    inline Writer& operator<<(const wchar_t* log_) {
#if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        if (log_ == NULL) {
            _ELPP_STREAM(logger_) << constants_->NULL_POINTER;
            return *this;
        }
        size_t len_ = wcslen(log_) + 1;
        char* buff_ = (char*)malloc(len_ + 1);
#   if _ELPP_OS_UNIX
        std::wcstombs(buff_, log_, len_);
#   elif _ELPP_OS_WINDOWS
        size_t convCount_ = 0;
        mbstate_t mbState_;
        errno_t err;
        ::memset((void*)&mbState_, 0, sizeof(mbState_));
        err = wcsrtombs_s(&convCount_, buff_, len_, &log_, len_, &mbState_);
#   endif // _ELPP_OS_UNIX
        _ELPP_STREAM(logger_) << buff_;
        free(buff_);
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
#if defined(_ELPP_STL_LOGGING)
    template <typename T, typename Container>
    inline Writer& operator<<(const std::vector<T, Container>& vec_) {
        if (!proceed_) { return *this; }
        return writeIterator(vec_.begin(), vec_.end(), vec_.size());
    }
    template <typename T, typename Container>
    inline Writer& operator<<(const std::list<T, Container>& list_) {
        if (!proceed_) { return *this; }
        return writeIterator(list_.begin(), list_.end(), list_.size());
    }
    template <typename T, typename Container>
    inline Writer& operator<<(const std::deque<T, Container>& deque_) {
        if (!proceed_) { return *this; }
        return writeIterator(deque_.begin(), deque_.end(), deque_.size());
    }
    template <typename T, typename Container>
    inline Writer& operator<<(const std::queue<T, Container>& queue_) {
#   if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        workarounds::IterableQueue<T, Container> iterableQueue_ =
                static_cast<workarounds::IterableQueue<T, Container> >(queue_);
        return writeIterator(iterableQueue_.begin(), iterableQueue_.end(), iterableQueue_.size());
#   else
        return *this;
#   endif // _ENABLE_EASYLOGGING
    }
    template <typename T, typename Container>
    inline Writer& operator<<(const std::stack<T, Container>& stack_) {
#   if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        workarounds::IterableStack<T, Container> iterableStack_ =
                static_cast<workarounds::IterableStack<T, Container> >(stack_);
        return writeIterator(iterableStack_.begin(), iterableStack_.end(), iterableStack_.size());
#   else
        return *this;
#   endif // _ENABLE_EASYLOGGING
    }
    template <typename T, typename Container, typename Comparator>
    inline Writer& operator<<(const std::priority_queue<T, Container, Comparator>& priorityQueue_) {
#   if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        workarounds::IterablePriorityQueue<T, Container, Comparator> iterablePriorityQueue_ =
                static_cast<workarounds::IterablePriorityQueue<T, Container, Comparator> >(priorityQueue_);
        return writeIterator(iterablePriorityQueue_.begin(), iterablePriorityQueue_.end(), iterablePriorityQueue_.size());
#   else
        return *this;
#   endif // _ENABLE_EASYLOGGING
    }
    template <typename T, typename Comparator, typename Container>
    inline Writer& operator<<(const std::set<T, Comparator, Container>& set_) {
        if (!proceed_) { return *this; }
        return writeIterator(set_.begin(), set_.end(), set_.size());
    }
    template <typename T, typename Comparator, typename Container>
    inline Writer& operator<<(const std::multiset<T, Comparator, Comparator>& set_) {
        if (!proceed_) { return *this; }
        return writeIterator(set_.begin(), set_.end(), set_.size());
    }
    template <typename First, typename Second>
    inline Writer& operator<<(const std::pair<First, Second>& pair_) {
#   if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << "(";
        operator << (static_cast<First>(pair_.first));
        _ELPP_STREAM(logger_) << ", ";
        operator << (static_cast<Second>(pair_.second));
        _ELPP_STREAM(logger_) << ")";
#   endif // _ENABLE_EASYLOGGING
        return *this;
    }
    template <size_t Size>
    inline Writer& operator<<(const std::bitset<Size>& bitset_) {
#   if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << "[";
        _ELPP_STREAM(logger_) << bitset_.to_string();
        _ELPP_STREAM(logger_) << "]";
#   endif // _ENABLE_EASYLOGGING
        return *this;
    }
    template <typename K, typename V, typename Comparator, typename Container>
    inline Writer& operator<<(const std::map<K, V, Comparator, Container>& map_) {
        if (!proceed_) { return *this; }
        return writeIterator(map_.begin(), map_.end(), map_.size());
    }
    template <typename K, typename V, typename Comparator, typename Container>
    inline Writer& operator<<(const std::multimap<K, V, Comparator, Container>& map_) {
        if (!proceed_) { return *this; }
        return writeIterator(map_.begin(), map_.end(), map_.size());
    }
#endif // defined(_ELPP_STL_LOGGING)
#if defined(QT_CORE_LIB) && defined(_ELPP_QT_LOGGING)
    inline Writer& operator<<(const QString& log_) {
#   if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_.toStdString();
#   else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#   endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(QString* log_) {
        if (!proceed_) { return *this; }
        return writePointer(log_);
    }
    inline Writer& operator<<(const QStringRef& log_) {
        if (!proceed_) { return *this; }
        return operator<<(log_.toString());
    }
    inline Writer& operator<<(QStringRef* log_) {
        if (!proceed_) { return *this; }
        return writePointer(log_);
    }
    inline Writer& operator<<(qint64 log_) {
#   if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << QString::number(log_).toStdString();
#   else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#   endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(qint64* log_) {
        if (!proceed_) { return *this; }
        return writePointer(log_);
    }
    inline Writer& operator<<(quint64 log_) {
#   if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << QString::number(log_).toStdString();
#   else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#   endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(quint64* log_) {
        if (!proceed_) { return *this; }
        return writePointer(log_);
    }
    inline Writer& operator<<(QChar log_) {
#   if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_.toLatin1();
#   else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#   endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(QChar* log_) {
        if (!proceed_) { return *this; }
        return writePointer(log_);
    }
#   if (!_ELPP_QT_5)
    inline Writer& operator<<(QBool log_) {
#      if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << (bool(log_ != 0) ? "true" : "false");
#      else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#      endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(QBool* log_) {
        return writePointer(log_);
    }
#   endif // (!_ELPP_QT_5)
    inline Writer& operator<<(const QLatin1String& log_) {
#   if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << log_.latin1();
#   else
        __EASYLOGGINGPP_SUPPRESS_UNSED(log_);
#   endif // _ENABLE_EASYLOGGING
        return *this;
    }
    inline Writer& operator<<(QLatin1String* log_) {
        if (!proceed_) { return *this; }
        return writePointer(log_);
    }
    template <typename T>
    inline Writer& operator<<(const QList<T>& list_) {
        if (!proceed_) { return *this; }
        return writeIterator(list_.begin(), list_.end(), list_.size());
    }
    template <typename T>
    inline Writer& operator<<(const QVector<T>& vec_) {
        if (!proceed_) { return *this; }
        return writeIterator(vec_.begin(), vec_.end(), vec_.size());
    }
    template <typename T>
    inline Writer& operator<<(const QQueue<T>& queue_) {
        if (!proceed_) { return *this; }
        return writeIterator(queue_.begin(), queue_.end(), queue_.size());
    }
    template <typename T>
    inline Writer& operator<<(const QSet<T>& set_) {
        if (!proceed_) { return *this; }
        return writeIterator(set_.begin(), set_.end(), set_.size());
    }
    template <typename First, typename Second>
    inline Writer& operator<<(const QPair<First, Second>& pair_) {
#   if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << "(";
        operator << (static_cast<First>(pair_.first));
        _ELPP_STREAM(logger_) << ", ";
        operator << (static_cast<Second>(pair_.second));
        _ELPP_STREAM(logger_) << ")";
#   else
        __EASYLOGGINGPP_SUPPRESS_UNSED(pair_);
#   endif // _ENABLE_EASYLOGGING
        return *this;
    }
    template <typename K, typename V>
    inline Writer& operator<<(const QMap<K, V>& map_) {
#   if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << "[";
        QList<K> keys = map_.keys();
        typename QList<K>::const_iterator begin = keys.begin();
        typename QList<K>::const_iterator end = keys.end();
        int max_ = static_cast<int>(constants_->MAX_LOG_PER_CONTAINER); // to prevent warning
        for (int index_ = 0; begin != end && index_ < max_; ++index_, ++begin) {
            _ELPP_STREAM(logger_) << "(";
            operator << (static_cast<K>(*begin));
            _ELPP_STREAM(logger_) << ", ";
            operator << (static_cast<V>(map_.value(*begin)));
            _ELPP_STREAM(logger_) << ")";
            _ELPP_STREAM(logger_) << ((index_ < keys.size() -1) ? ", " : "");
        }
        if (begin != end) {
            _ELPP_STREAM(logger_) << " ...";
        }
        _ELPP_STREAM(logger_) << "]";
#   else
        __EASYLOGGINGPP_SUPPRESS_UNSED(map_);
#   endif // _ENABLE_EASYLOGGING
        return *this;
    }
    template <typename K, typename V>
    inline Writer& operator<<(const QMultiMap<K, V>& map_) {
        if (!proceed_) { return *this; }
        operator << (static_cast<QMap<K, V> >(map_));
        return *this;
    }
    template <typename K, typename V>
    inline Writer& operator<<(const QHash<K, V>& hash_) {
#   if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << "[";
        QList<K> keys = hash_.keys();
        typename QList<K>::const_iterator begin = keys.begin();
        typename QList<K>::const_iterator end = keys.end();
        int max_ = static_cast<int>(constants_->MAX_LOG_PER_CONTAINER); // prevent type warning
        for (int index_ = 0; begin != end && index_ < max_; ++index_, ++begin) {
            _ELPP_STREAM(logger_) << "(";
            operator << (static_cast<K>(*begin));
            _ELPP_STREAM(logger_) << ", ";
            operator << (static_cast<V>(hash_.value(*begin)));
            _ELPP_STREAM(logger_) << ")";
            _ELPP_STREAM(logger_) << ((index_ < keys.size() -1) ? ", " : "");
        }
        if (begin != end) {
            _ELPP_STREAM(logger_) << " ...";
        }
        _ELPP_STREAM(logger_) << "]";
#   else
        __EASYLOGGINGPP_SUPPRESS_UNSED(hash_);
#   endif // _ENABLE_EASYLOGGING
        return *this;
    }
    template <typename K, typename V>
    inline Writer& operator<<(const QMultiHash<K, V>& multiHash_) {
        if (!proceed_) { return *this; }
        operator << (static_cast<QHash<K, V> >(multiHash_));
        return *this;
    }
    template <typename T>
    inline Writer& operator<<(const QLinkedList<T>& linkedList_) {
        if (!proceed_) { return *this; }
        return writeIterator(linkedList_.begin(), linkedList_.end(), linkedList_.size());
    }
    template <typename T>
    inline Writer& operator<<(const QStack<T>& stack_) {
        if (!proceed_) { return *this; }
        return writeIterator(stack_.begin(), stack_.end(), stack_.size());
    }
#endif // defined(QT_CORE_LIB) && defined(_ELPP_QT_LOGGING)
    template <class Class>
    inline Writer& operator<<(const Class& class_) {
#if _ENABLE_EASYLOGGING
        if (!proceed_) { return *this; }
        _ELPP_STREAM(logger_) << class_;
#endif // _ENABLE_EASYLOGGING
        return *this;
    }
private:
    unsigned int aspect_;
    unsigned int severity_;
    const char* func_;
    const char* file_;
    const unsigned long int line_;
    bool condition_;
    int verboseLevel_;
    int counter_;
    Logger* logger_;
    std::stringstream tempss_;
    std::string currLine_;
    bool proceed_;
    easyloggingpp::internal::Constants* constants_;
    friend class Logger;

    template <typename Pointer>
    inline Writer& writePointer(const Pointer& pointer_) {
#if _ENABLE_EASYLOGGING
        return (pointer_ != NULL ? operator << (*pointer_) : operator << (constants_->NULL_POINTER));
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(pointer_);
        return *this;
#endif // _ENABLE_EASYLOGGING
    }

    template<class Iterator>
    inline Writer& writeIterator(Iterator begin_, Iterator end_, size_t size_) {
#if _ENABLE_EASYLOGGING
        _ELPP_STREAM(logger_) << "[";
        for (unsigned int i = 0; begin_ != end_ && i < constants_->MAX_LOG_PER_CONTAINER; ++i, ++begin_) {
            operator << (*begin_);
            _ELPP_STREAM(logger_) << ((i < size_ - 1) ? ", " : "");
        }
        if (begin_ != end_) {
            _ELPP_STREAM(logger_) << " ...";
        }
        _ELPP_STREAM(logger_) << "]";
#else
        __EASYLOGGINGPP_SUPPRESS_UNSED(begin_);
        __EASYLOGGINGPP_SUPPRESS_UNSED(end_);
        __EASYLOGGINGPP_SUPPRESS_UNSED(size_);
#endif // _ENABLE_EASYLOGGING
        return *this;
    }

    void buildAndWriteLine(void) {
        RegisteredLoggers* rl_ = registeredLoggers.pointer();
        TypedConfigurations* conf_ = logger_->typedConfigurations_;
        unsigned int f_ = conf_->formatFlag(severity_); // format spec
        currLine_ = conf_->logFormat(severity_);
        std::string dateFormat = conf_->dateFormat(severity_);
        std::string fs_; // format specifier
        std::string v_; // value
        // App name
        if (f_ & constants_->kAppName) {
            v_ = logger_->applicationName();
            fs_ = constants_->APP_NAME_FORMAT_SPECIFIER;
            easyloggingpp::internal::utilities::LogManipulator::updateFormatValue(fs_, v_, currLine_, constants_);
        }
        if (f_ & constants_->kLoggerId) {
            v_ = logger_->id();
            fs_ = constants_->LOGGER_ID_FORMAT_SPECIFIER;
            easyloggingpp::internal::utilities::LogManipulator::updateFormatValue(fs_, v_, currLine_, constants_);
        }
        // Date/Time
        if ((f_ & constants_->kDateOnly) || (f_ & constants_->kTimeOnly) || (f_ & constants_->kDateTime)) {
            v_ = easyloggingpp::internal::utilities::DateUtilities::getDateTime(dateFormat,
                                                                                f_, constants_, conf_->millisecondsLength(Level::ELPP_ALL));
            fs_ = conf_->dateFormatSpecifier(severity_);
            easyloggingpp::internal::utilities::LogManipulator::updateFormatValue(fs_, v_, currLine_, constants_);
        }
        // Function
        if (f_ & constants_->kFunction) {
            v_ = std::string(func_);
            fs_ = constants_->FUNCTION_FORMAT_SPECIFIER;
            easyloggingpp::internal::utilities::LogManipulator::updateFormatValue(fs_, v_, currLine_, constants_);
        }
        // Location
        if (f_ & constants_->kLocation) {
            tempss_ << file_ << ":" << line_;
            v_ = tempss_.str();
            fs_ = constants_->LOCATION_FORMAT_SPECIFIER;
            easyloggingpp::internal::utilities::LogManipulator::updateFormatValue(fs_, v_, currLine_, constants_);
            tempss_.str("");
        }
        // User
        if (f_ & constants_->kUser) {
            v_ = rl_->username();
            fs_ = constants_->USER_FORMAT_SPECIFIER;
            easyloggingpp::internal::utilities::LogManipulator::updateFormatValue(fs_, v_, currLine_, constants_);
        }
        // Host
        if (f_ & constants_->kHost) {
            v_ = rl_->hostname();
            fs_ = constants_->HOST_FORMAT_SPECIFIER;
            easyloggingpp::internal::utilities::LogManipulator::updateFormatValue(fs_, v_, currLine_, constants_);
        }
        // Verbose level
        if (severity_ == Level::ELPP_VERBOSE && f_ & constants_->kVerboseLevel) {
            tempss_ << verboseLevel_;
            fs_ = constants_->VERBOSE_LEVEL_FORMAT_SPECIFIER;
            easyloggingpp::internal::utilities::LogManipulator::updateFormatValue(fs_, tempss_.str(), currLine_, constants_);
        }
        // Log message
        if (f_ & constants_->kLogMessage) {
            fs_ = constants_->LOG_MESSAGE_FORMAT_SPECIFIER;
            easyloggingpp::internal::utilities::LogManipulator::updateFormatValue(fs_, logger_->stream()->str(), currLine_, constants_);
        }
        log();
    }
    void log(void) {
        if (logger_->stream_) {
            if (logger_->typedConfigurations_->toFile(severity_)) {
                std::ofstream* fstr = logger_->typedConfigurations_->fileStream(severity_);
                (*fstr) << currLine_;
                fstr->flush();
            }
            if (logger_->typedConfigurations_->toStandardOutput(severity_)) {
                std::cout << currLine_;
            }
            logger_->stream_->str("");
        }
    }
};
} // namespace internal

class VersionInfo {
    _ELPP_NO_INITIALIZATION(VersionInfo)
    public:
        // Minimal formatted displayable information
        static inline const std::string formattedInfo(void) {
        std::stringstream ss;
        ss << "EasyLogging++ v" << version() << " (" << releaseDate() << ")";
        ss << std::endl;
        ss << website();
        ss << std::endl;
        ss << copyright();
        return ss.str();
    }

    // Current version number
    static inline const std::string version(void) { return std::string("8.07"); }

    // Release date of current version
    static inline const std::string releaseDate(void) { return std::string("17-04-2013 0759hrs"); }

    // Original author and maintainer
    static inline const std::string author(void) { return std::string("Majid Khan <mkhan3189@gmail.com>"); }

    // Web link
    static inline const std::string website(void) { return std::string("http://icplusplus.com/tools/easylogging"); }

    // Link to source code
    static inline const std::string sourceCodeLink(void) { return std::string("https://github.com/mkhan3189/EasyLoggingPP"); }

    // Copyright information
    static inline const std::string copyright(void) { return std::string("Copyright (c) 2012 - 2013 Majid Khan"); }

    // Full licence
    static const std::string licence(void) {
        std::stringstream ss;
        ss << "   This software is provided 'as-is', without any express or implied" << std::endl;
        ss << "   warranty. In no event will the authors be held liable for any damages" << std::endl;
        ss << "   arising from the use of this software." << std::endl;
        ss << std::endl;
        ss << "   Permission is granted to anyone to use this software for any purpose," << std::endl;
        ss << "   including commercial applications, and to alter it and redistribute" << std::endl;
        ss << "   it freely, subject to the following restrictions:" << std::endl;
        ss << std::endl;
        ss << "   1. The origin of this software must not be misrepresented; you must" << std::endl;
        ss << "      not claim that you wrote the original software. If you use this" << std::endl;
        ss << "      software in a product, an acknowledgment in the product documentation" << std::endl;
        ss << "      would be appreciated but is not required." << std::endl;
        ss << std::endl;
        ss << "   2. Altered source versions must be plainly marked as such, and must" << std::endl;
        ss << "      not be misrepresented as being the original software." << std::endl;
        ss << std::endl;
        ss << "   3. This notice may not be removed or altered from any source" << std::endl;
        ss << "      distribution";
        return ss.str();
    }
}; // class VersionInfo

class Loggers {
    _ELPP_NO_INITIALIZATION(Loggers)
    public:
        static inline Logger* getLogger(const std::string& identifier_) {
        return internal::registeredLoggers->get(identifier_);
    }

    static inline Logger* reConfigureLogger(const std::string& identifier_, const Configurations& configurations_) {
        Logger* logger_ = Loggers::getLogger(identifier_);
        logger_->configure(configurations_);
        return logger_;
    }

    static inline Logger* reConfigureLogger(Logger* logger_, const Configurations& configurations_) {
        if (!logger_) return NULL;
        logger_->configure(configurations_);
        return logger_;
    }

    static inline void setApplicationArguments(int argc, char** argv) {
        internal::registeredLoggers->setApplicationArguments(argc, argv);
    }

    static inline void setApplicationArguments(int argc, const char** argv) {
        internal::registeredLoggers->setApplicationArguments(argc, argv);
    }

    static inline void resetAllLoggersConfigurations(const Configurations& configurations_) {
        for (unsigned int i = 0; i < internal::registeredLoggers->count(); ++i) {
            Logger* l = internal::registeredLoggers->at(i);
            reConfigureLogger(l, configurations_);
        }
    }

    static inline void resetAllLoggersConfigurations(unsigned int configurationType_, const std::string& value_) {
        for (unsigned int i = 0; i < internal::registeredLoggers->count(); ++i) {
            Logger* l = internal::registeredLoggers->at(i);
            l->configurations().setAll(configurationType_, value_);
            l->reconfigure();
        }
    }

    static inline void disableAll(void) {
        resetAllLoggersConfigurations(ConfigurationType::ELPP_Enabled, "false");
    }

    static inline void enableAll(void) {
        resetAllLoggersConfigurations(ConfigurationType::ELPP_Enabled, "true");
    }

    static inline void setFilename(const std::string& logFilename_) {
        resetAllLoggersConfigurations(ConfigurationType::ELPP_Filename, logFilename_);
    }

    static inline void setFilename(Logger* logger_, const std::string& logFilename_) {
        if (!logger_) return;
        logger_->configurations().setAll(ConfigurationType::ELPP_Filename, logFilename_);
    }

    static inline bool performanceTrackingEnabled(void) {
        return performanceLogger()->typedConfigurations_->performanceTracking();
    }

    static inline void disablePerformanceTracking(void) {
        Logger* l = Loggers::performanceLogger();
        l->configurations().set(Level::ELPP_ALL, ConfigurationType::ELPP_PerformanceTracking, "false");
        l->reconfigure();
    }

    static inline void getAllLogIdentifiers(std::vector<std::string>& listOfIds) {
        listOfIds.clear();
        for (unsigned int i = 0; i < internal::registeredLoggers->count(); ++i) {
            listOfIds.push_back(internal::registeredLoggers->at(i)->id());
        }
    }

    static inline Logger* trivialLogger(void) {
        return Loggers::getLogger("trivial");
    }

    static inline Logger* businessLogger(void) {
        return Loggers::getLogger("business");
    }

    static inline Logger* securityLogger(void) {
        return Loggers::getLogger("security");
    }

    static inline Logger* performanceLogger(void) {
        return Loggers::getLogger("performance");
    }

    class ConfigurationsReader {
        _ELPP_NO_INITIALIZATION(ConfigurationsReader)
        public:
            static inline bool enabled(Logger* logger_, unsigned int level_ = Level::ELPP_ALL) {
            return constConf(logger_)->enabled(level_);
        }

        static inline bool toFile(Logger* logger_, unsigned int level_ = Level::ELPP_ALL) {
            return constConf(logger_)->toFile(level_);
        }

        static inline std::string filename(Logger* logger_, unsigned int level_ = Level::ELPP_ALL) {
            return constConf(logger_)->filename(level_);
        }

        static inline bool toStandardOutput(Logger* logger_, unsigned int level_ = Level::ELPP_ALL) {
            return constConf(logger_)->toStandardOutput(level_);
        }

        static inline std::string logFormat(Logger* logger_, unsigned int level_ = Level::ELPP_ALL) {
            return constConf(logger_)->logFormat(level_);
        }

        static inline int millisecondsLength(Logger* logger_, unsigned int level_ = Level::ELPP_ALL) {
            return constConf(logger_)->millisecondsLength(level_);
        }

        static inline bool performanceTracking(Logger* logger_, unsigned int level_ = Level::ELPP_ALL) {
            return constConf(logger_)->performanceTracking(level_);
        }

    private:
        static inline internal::TypedConfigurations* constConf(Logger* logger_) {
            return logger_->typedConfigurations_;
        }
    }; // class ConfigurationsReader
};

//
// Performance tracking macros
//
#if ((!defined(_DISABLE_PERFORMANCE_TRACKING)) || (!defined(_DISABLE_INFO_LOGS)))
#   if _ELPP_OS_UNIX
#      define _ELPP_GET_CURR_TIME(tm) gettimeofday(tm, NULL);
#   elif _ELPP_OS_WINDOWS
#      define _ELPP_GET_CURR_TIME(tm) easyloggingpp::internal::utilities::DateUtilities::gettimeofday(tm);
#   endif
#   define START_FUNCTION_LOG "Executing [" << __func__ << "]"
#   define TIME_OUTPUT "Executed [" << __func__ << "] in [" <<                    \
    easyloggingpp::internal::utilities::DateUtilities::formatMilliSeconds(        \
    easyloggingpp::internal::utilities::DateUtilities::getTimeDifference(functionEndTime, functionStartTime)) << "]"
#   define FUNC_SUB_COMMON_START { timeval functionStartTime, functionEndTime; _ELPP_GET_CURR_TIME(&functionStartTime)
#   define WRITE_FUNC_PERFORMANCE _ELPP_GET_CURR_TIME(&functionEndTime);            \
    if (easyloggingpp::Loggers::performanceTrackingEnabled()) { PINFO << TIME_OUTPUT; }
#   define FUNC_SUB_COMMON_END WRITE_FUNC_PERFORMANCE;
#   define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS FUNC_SUB_COMMON_START
#   define END_SUB FUNC_SUB_COMMON_END }
#   define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS FUNC_SUB_COMMON_START
#   define RETURN(return_value) FUNC_SUB_COMMON_END return return_value;
#   define END_FUNC(return_value) RETURN(return_value) }
#   define MAIN(argc, argv) FUNC(int, main, (argc, argv))
#   define END_MAIN(return_value) FUNC_SUB_COMMON_END; return return_value; }
#   define RETURN_MAIN(exit_status) return exit_status;
#else
#   define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS {
#   define END_SUB }
#   define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS {
#   define END_FUNC(x) return x; }
#   define RETURN(expr) return expr;
#   define MAIN(argc, argv) FUNC(int, main, (argc, argv))
#   define END_MAIN(x) return x; }
#   define RETURN_MAIN(exit_status) return exit_status;
#endif // ((!defined(_DISABLE_PERFORMANCE_TRACKING)) || (!defined(_DISABLE_INFO_LOGS)))

#define _ELPP_LOG_WRITER(_logger, _level) easyloggingpp::internal::Writer(\
    _logger, easyloggingpp::internal::Aspect::Normal, _level, __func__, __FILE__, __LINE__)
#define _ELPP_LOG_WRITER_COND(_c, _logger, _level) if (_c) easyloggingpp::internal::Writer(\
    _logger, easyloggingpp::internal::Aspect::Conditional, _level, __func__, __FILE__, __LINE__, _c)
#define _ELPP_LOG_WRITER_N(_n, _logger, _level) if (easyloggingpp::internal::registeredLoggers->validateCounter(\
    __FILE__, __LINE__, _n)) easyloggingpp::internal::Writer(_logger, easyloggingpp::internal::Aspect::Interval,\
    _level, __func__, __FILE__, __LINE__, true, 0, _n)
//
// Custom loggers
//
// Undef any exising custom logger macros
#if defined(CINFO)
#   undef CINFO
#endif
#if defined(CWARNING)
#   undef CWARNING
#endif
#if defined(CDEBUG)
#   undef CDEBUG
#endif
#if defined(CERROR)
#   undef CERROR
#endif
#if defined(CFATAL)
#   undef CFATAL
#endif
#if defined(CQA)
#   undef CQA
#endif
#if defined(CTRACE)
#   undef CTRACE
#endif
#if defined(CVERBOSE)
#   undef CVERBOSE
#endif
// Normal logs
#define CINFO(loggerId) _ELPP_LOG_WRITER(loggerId, easyloggingpp::Level::ELPP_INFO)
#define CWARNING(loggerId) _ELPP_LOG_WRITER(loggerId, easyloggingpp::Level::ELPP_WARNING)
#define CDEBUG(loggerId) _ELPP_LOG_WRITER(loggerId, easyloggingpp::Level::ELPP_DEBUG)
#define CERROR(loggerId) _ELPP_LOG_WRITER(loggerId, easyloggingpp::Level::ELPP_ERROR)
#define CFATAL(loggerId) _ELPP_LOG_WRITER(loggerId, easyloggingpp::Level::ELPP_FATAL)
#define CQA(loggerId) _ELPP_LOG_WRITER(loggerId, easyloggingpp::Level::ELPP_QA)
#define CTRACE(loggerId) _ELPP_LOG_WRITER(loggerId, easyloggingpp::Level::ELPP_TRACE)
#define CVERBOSE(vlevel_, loggerId) easyloggingpp::internal::Writer(loggerId, easyloggingpp::internal::Aspect::Normal,       \
    easyloggingpp::Level::ELPP_VERBOSE, __func__, __FILE__, __LINE__, true, vlevel_)
// Conditional logs
#define CINFO_IF(condition_, loggerId) _ELPP_LOG_WRITER_COND(condition_, loggerId, easyloggingpp::Level::ELPP_INFO)
#define CWARNING_IF(condition_, loggerId) _ELPP_LOG_WRITER_COND(condition_, loggerId, easyloggingpp::Level::ELPP_WARNING)
#define CDEBUG_IF(condition_, loggerId) _ELPP_LOG_WRITER_COND(condition_, loggerId, easyloggingpp::Level::ELPP_DEBUG)
#define CERROR_IF(condition_, loggerId) _ELPP_LOG_WRITER_COND(condition_, loggerId, easyloggingpp::Level::ELPP_ERROR)
#define CFATAL_IF(condition_, loggerId) _ELPP_LOG_WRITER_COND(condition_, loggerId, easyloggingpp::Level::ELPP_FATAL)
#define CQA_IF(condition_, loggerId) _ELPP_LOG_WRITER_COND(condition_, loggerId, easyloggingpp::Level::ELPP_QA)
#define CTRACE_IF(condition_, loggerId) _ELPP_LOG_WRITER_COND(condition_, loggerId, easyloggingpp::Level::ELPP_TRACE)
#define CVERBOSE_IF(condition_, vlevel_, loggerId) if (condition_) easyloggingpp::internal::Writer(loggerId, easyloggingpp::internal::Aspect::Conditional,     \
    easyloggingpp::Level::ELPP_VERBOSE, __func__, __FILE__, __LINE__, condition_, vlevel_)
// Interval logs
#define CINFO_EVERY_N(interval_, loggerId) _ELPP_LOG_WRITER_N(interval_, loggerId, easyloggingpp::Level::ELPP_INFO)
#define CWARNING_EVERY_N(interval_, loggerId) _ELPP_LOG_WRITER_N(interval_, loggerId, easyloggingpp::Level::ELPP_WARNING)
#define CDEBUG_EVERY_N(interval_, loggerId) _ELPP_LOG_WRITER_N(interval_, loggerId, easyloggingpp::Level::ELPP_DEBUG)
#define CERROR_EVERY_N(interval_, loggerId) _ELPP_LOG_WRITER_N(interval_, loggerId, easyloggingpp::Level::ELPP_ERROR)
#define CFATAL_EVERY_N(interval_, loggerId) _ELPP_LOG_WRITER_N(interval_, loggerId, easyloggingpp::Level::ELPP_FATAL)
#define CQA_EVERY_N(interval_, loggerId) _ELPP_LOG_WRITER_N(interval_, loggerId, easyloggingpp::Level::ELPP_QA)
#define CTRACE_EVERY_N(interval_, loggerId) _ELPP_LOG_WRITER_N(interval_, loggerId, easyloggingpp::Level::ELPP_TRACE)
#define CVERBOSE_EVERY_N(interval_, vlevel_, loggerId) if (easyloggingpp::internal::registeredLoggers->validateCounter(__FILE__, __LINE__, interval_)) \
    easyloggingpp::internal::Writer(loggerId, easyloggingpp::internal::Aspect::Interval,   \
    easyloggingpp::Level::ELPP_VERBOSE, __func__, __FILE__, __LINE__, true, vlevel_, interval_)
//
// default Loggers
//
// undef any existing default logger macros
#if defined(LINFO)
#   undef LINFO
#endif
#if defined(LWARNING)
#   undef LWARNING
#endif
#if defined(LDEBUG)
#   undef LDEBUG
#endif
#if defined(LERROR)
#   undef LERROR
#endif
#if defined(LFATAL)
#   undef LFATAL
#endif
#if defined(LQA)
#   undef LQA
#endif
#if defined(LTRACE)
#   undef LTRACE
#endif
#if defined(LVERBOSE)
#   undef LVERBOSE
#endif
// Normal logs
#define LINFO CINFO("trivial")
#define LWARNING CWARNING("trivial")
#define LDEBUG CDEBUG("trivial")
#define LERROR CERROR("trivial")
#define LFATAL CFATAL("trivial")
#define LQA CQA("trivial")
#define LTRACE CTRACE("trivial")
#define LVERBOSE(level) CVERBOSE(level, "trivial")
// Conditional logs
#define LINFO_IF(condition) CINFO_IF(condition, "trivial")
#define LWARNING_IF(condition) CWARNING_IF(condition, "trivial")
#define LDEBUG_IF(condition) CDEBUG_IF(condition, "trivial")
#define LERROR_IF(condition) CERROR_IF(condition, "trivial")
#define LFATAL_IF(condition) CFATAL_IF(condition, "trivial")
#define LQA_IF(condition) CQA_IF(condition, "trivial")
#define LTRACE_IF(condition) CTRACE_IF(condition, "trivial")
#define LVERBOSE_IF(condition, level) CVERBOSE_IF(condition, level, "trivial")
// Interval logs
#define LINFO_EVERY_N(n) CINFO_EVERY_N(n, "trivial")
#define LWARNING_EVERY_N(n) CWARNING_EVERY_N(n, "trivial")
#define LDEBUG_EVERY_N(n) CDEBUG_EVERY_N(n, "trivial")
#define LERROR_EVERY_N(n) CERROR_EVERY_N(n, "trivial")
#define LFATAL_EVERY_N(n) CFATAL_EVERY_N(n, "trivial")
#define LQA_EVERY_N(n) CQA_EVERY_N(n, "trivial")
#define LTRACE_EVERY_N(n) CTRACE_EVERY_N(n, "trivial")
#define LVERBOSE_EVERY_N(n, level) CVERBOSE_EVERY_N(n, level, "trivial")
// undef any exising business logger macros
#if defined(BINFO)
#   undef BINFO
#endif
#if defined(BWARNING)
#   undef BWARNING
#endif
#if defined(BDEBUG)
#   undef BDEBUG
#endif
#if defined(BERROR)
#   undef BERROR
#endif
#if defined(BFATAL)
#   undef BFATAL
#endif
#if defined(BQA)
#   undef BQA
#endif
#if defined(BTRACE)
#   undef BTRACE
#endif
#if defined(BVERBOSE)
#   undef BVERBOSE
#endif
//
// business Loggers
//
// Normal logs
#define BINFO CINFO("business")
#define BWARNING CWARNING("business")
#define BDEBUG CDEBUG("business")
#define BERROR CERROR("business")
#define BFATAL CFATAL("business")
#define BQA CQA("business")
#define BTRACE CTRACE("business")
#define BVERBOSE(level) CVERBOSE(level, "business")
// Conditional logs
#define BINFO_IF(condition) CINFO_IF(condition, "business")
#define BWARNING_IF(condition) CWARNING_IF(condition, "business")
#define BDEBUG_IF(condition) CDEBUG_IF(condition, "business")
#define BERROR_IF(condition) CERROR_IF(condition, "business")
#define BFATAL_IF(condition) CFATAL_IF(condition, "business")
#define BQA_IF(condition) CQA_IF(condition, "business")
#define BTRACE_IF(condition) CTRACE_IF(condition, "business")
#define BVERBOSE_IF(condition, level) CVERBOSE_IF(condition, level, "business")
// Interval logs
#define BINFO_EVERY_N(n) CINFO_EVERY_N(n, "business")
#define BWARNING_EVERY_N(n) CWARNING_EVERY_N(n, "business")
#define BDEBUG_EVERY_N(n) CDEBUG_EVERY_N(n, "business")
#define BERROR_EVERY_N(n) CERROR_EVERY_N(n, "business")
#define BFATAL_EVERY_N(n) CFATAL_EVERY_N(n, "business")
#define BQA_EVERY_N(n) CQA_EVERY_N(n, "business")
#define BTRACE_EVERY_N(n) CTRACE_EVERY_N(n, "business")
#define BVERBOSE_EVERY_N(n, level) CVERBOSE_EVERY_N(n, level, "business")
//
// security Loggers
//
// undef any existing security logger macros
#if defined(SINFO)
#   undef SINFO
#endif
#if defined(SWARNING)
#   undef SWARNING
#endif
#if defined(SDEBUG)
#   undef SDEBUG
#endif
#if defined(SERROR)
#   undef SERROR
#endif
#if defined(SFATAL)
#   undef SFATAL
#endif
#if defined(SQA)
#   undef SQA
#endif
#if defined(STRACE)
#   undef STRACE
#endif
#if defined(SVERBOSE)
#   undef SVERBOSE
#endif
// Normal logs
#define SINFO CINFO("security")
#define SWARNING CWARNING("security")
#define SDEBUG CDEBUG("security")
#define SERROR CERROR("security")
#define SFATAL CFATAL("security")
#define SQA CQA("security")
#define STRACE CTRACE("security")
#define SVERBOSE(level) CVERBOSE(level, "security")
// Conditional logs
#define SINFO_IF(condition) CINFO_IF(condition, "security")
#define SWARNING_IF(condition) CWARNING_IF(condition, "security")
#define SDEBUG_IF(condition) CDEBUG_IF(condition, "security")
#define SERROR_IF(condition) CERROR_IF(condition, "security")
#define SFATAL_IF(condition) CFATAL_IF(condition, "security")
#define SQA_IF(condition) CQA_IF(condition, "security")
#define STRACE_IF(condition) CQA_IF(condition, "security")
#define SVERBOSE_IF(condition, level) CVERBOSE_IF(condition, level, "security")
// Interval logs
#define SINFO_EVERY_N(n) CINFO_EVERY_N(n, "security")
#define SWARNING_EVERY_N(n) CWARNING_EVERY_N(n, "security")
#define SDEBUG_EVERY_N(n) CDEBUG_EVERY_N(n, "security")
#define SERROR_EVERY_N(n) CERROR_EVERY_N(n, "security")
#define SFATAL_EVERY_N(n) CFATAL_EVERY_N(n, "security")
#define SQA_EVERY_N(n) CQA_EVERY_N(n, "security")
#define STRACE_EVERY_N(n) CTRACE_EVERY_N(n, "security")
#define SVERBOSE_EVERY_N(n, level) CVERBOSE_EVERY_N(n, level, "security")
//
// performance Loggers
//
// undef any existing performance logger macros
#if defined(PINFO)
#   undef PINFO
#endif
#if defined(PWARNING)
#   undef PWARNING
#endif
#if defined(PDEBUG)
#   undef PDEBUG
#endif
#if defined(PERROR)
#   undef PERROR
#endif
#if defined(PFATAL)
#   undef PFATAL
#endif
#if defined(PQA)
#   undef PQA
#endif
#if defined(PTRACE)
#   undef PTRACE
#endif
#if defined(PVERBOSE)
#   undef PVERBOSE
#endif
#undef NON_EXISTING_MACRO
// Normal logs
#define PINFO CINFO("performance")
#define PWARNING CWARNING("performance")
#define PDEBUG CDEBUG("performance")
#define PERROR CERROR("performance")
#define PFATAL CFATAL("performance")
#define PQA CQA("performance")
#define PTRACE CTRACE("performance")
#define PVERBOSE(level) CVERBOSE(level, "performance")
// Conditional logs
#define PINFO_IF(condition) CINFO_IF(condition, "performance")
#define PWARNING_IF(condition) CWARNING_IF(condition, "performance")
#define PDEBUG_IF(condition) CDEBUG_IF(condition, "performance")
#define PERROR_IF(condition) CERROR_IF(condition, "performance")
#define PFATAL_IF(condition) CFATAL_IF(condition, "performance")
#define PQA_IF(condition) CQA_IF(condition, "performance")
#define PTRACE_IF(condition) CQA_IF(condition, "performance")
#define PVERBOSE_IF(condition, level) CVERBOSE_IF(condition, level, "performance")
// Interval logs
#define PINFO_EVERY_N(n) CINFO_EVERY_N(n, "performance")
#define PWARNING_EVERY_N(n) CWARNING_EVERY_N(n, "performance")
#define PDEBUG_EVERY_N(n) CDEBUG_EVERY_N(n, "performance")
#define PERROR_EVERY_N(n) CERROR_EVERY_N(n, "performance")
#define PFATAL_EVERY_N(n) CFATAL_EVERY_N(n, "performance")
#define PQA_EVERY_N(n) CQA_EVERY_N(n, "performance")
#define PTRACE_EVERY_N(n) CTRACE_EVERY_N(n, "performance")
#define PVERBOSE_EVERY_N(n, level) CVERBOSE_EVERY_N(n, level, "performance")
// Undefine macros that are not needed anymore
#undef _ELPP_ASSEMBLY_SUPPORTED
#undef _ELPP_STREAM
#undef _ELPP_MUTEX_LOCK_GNU_ASM
#undef _ELPP_MUTEX_UNLOCK_GNU_ASM
#undef _ELPP_ENABLE_MUTEX
#undef _ELPP_OS_UNIX
#undef _ELPP_OS_WINDOWS
#undef _ELPP_OS_LINUX
#undef ELPP_StringUtils
#undef _ELPP_NO_INITIALIZATION
#undef _ELPP_NO_COPY
#undef _ENABLE_EASYLOGGING
#undef __EASYLOGGINGPP_SUPPRESS_UNSED
#undef _ELPP_DEBUG_LOG
#undef _ELPP_INFO_LOG
#undef _ELPP_WARNING_LOG
#undef _ELPP_ERROR_LOG
#undef _ELPP_FATAL_LOG
#undef _ELPP_QA_LOG
#undef _ELPP_VERBOSE_LOG
#undef _ELPP_TRACE_LOG

#if !defined(_INITIALIZE_EASYLOGGINGPP)
#define _INITIALIZE_EASYLOGGINGPP                         \
    namespace easyloggingpp {                             \
    namespace internal {                                  \
    SmartPointer<RegisteredLoggers> registeredLoggers(    \
    new RegisteredLoggers());                             \
}                                                     \
}
#endif // !defined(_INITIALIZE_EASYLOGGINGPP)
#define _START_EASYLOGGINGPP(argc, argv) easyloggingpp::Loggers::setApplicationArguments(argc, argv);
#define _ELPP_COUNTER easyloggingpp::internal::registeredLoggers->counters()->get(__FILE__, __LINE__)
#define _ELPP_COUNTER_POSITION (_ELPP_COUNTER == NULL ? 0 : _ELPP_COUNTER->position())

} // easyloggingpp
#endif // EASYLOGGINGPP_H
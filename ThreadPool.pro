TEMPLATE = app
CONFIG += console
CONFIG += object_parallel_to_source
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += src/
QMAKE_CXXFLAGS += -std=c++14
LIBS += -lpthread

SOURCES += \
    src/Tests/QueueBuffer/QueueBufferTest.cpp \
    src/Tests/TaskThread/TaskThreadTest.cpp \
    src/Tests/TaskThread/Tests.cpp \
    src/Tests/ThreadPool/Tests.cpp \
    src/Tests/ThreadPool/ThreadPoolTest.cpp \
    src/Tests/AllTests.cpp \
    src/Tests/main.cpp \
    src/Descriptor.cpp \
    src/Mutex.cpp \
    src/QueueThread.cpp \
    src/Semaphore.cpp \
    src/TaskId.cpp \
    src/TaskThread.cpp \
    src/Thread.cpp \
    src/ThreadPool.cpp

HEADERS += \
    src/Templates/Iterator.hpp \
    src/Templates/Locker.hpp \
    src/Templates/PthreadObject.hpp \
    src/Templates/QueueBuffer.hpp \
    src/Templates/RwLockQueueBuffer.hpp \
    src/Templates/Traits.hpp \
    src/Templates/UniquePointer.hpp \
    src/Tests/QueueBuffer/QueueBufferTest.hpp \
    src/Tests/QueueBuffer/Tests.hpp \
    src/Tests/TaskThread/TaskThreadTest.hpp \
    src/Tests/TaskThread/Tests.hpp \
    src/Tests/ThreadPool/Tests.hpp \
    src/Tests/ThreadPool/ThreadPoolTest.hpp \
    src/Tests/AllTests.hpp \
    src/Tests/Test.hpp \
    src/Tests/TextStyle.hpp \
    src/AbstractTask.hpp \
    src/Descriptor.hpp \
    src/Mutex.hpp \
    src/QueueThread.hpp \
    src/Semaphore.hpp \
    src/TaskId.hpp \
    src/TaskThread.hpp \
    src/Thread.hpp \
    src/ThreadPool.hpp \
    src/Types.hpp

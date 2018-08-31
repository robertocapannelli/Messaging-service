cmake_minimum_required(VERSION 3.10)
project(messaging-service C)

include_directories(/usr/local/bin/sqlite3)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -ldl -Wall -Wextra -O2")

set(UTILS
        database/utils.c
        database/utils.h)

set(AUTH
        auth/login.c
        auth/login.h)

set(DB_USER
        database/user/user.c
        database/user/user.h)

set(DB_MESSAGE
        database/message/message.c
        database/message/message.h)

set(DB_UTILS
        database/utils.h
        database/utils.c)

#Executables
add_executable(main
        server/server.c)

add_executable(client
        client/client.c)

add_executable(db
        database/connection.c
        database/connection.h
        ${DB_USER}
        ${DB_MESSAGE}
        ${UTILS})

add_executable(auth
        ${AUTH}
        ${DB_USER}
        ${DB_UTILS})

#Link libs to the target
target_link_libraries(db LINK_PUBLIC sqlite3)

target_link_libraries(auth LINK_PUBLIC sqlite3)
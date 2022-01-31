set(DeocoinTools_INCLUDE_DIRS
    ${DeocoinFramework_INCLUDE_DIRS}
    "${CMAKE_CURRENT_LIST_DIR}"
)

set(DeocoinTools_INCLUDE_DIRS ${DeocoinTools_INCLUDE_DIRS} PARENT_SCOPE)

# DeocoinTools

add_custom_target(DeocoinTools)
add_dependencies(DeocoinTools
    DeocoinTools::ConnectivityTool
    DeocoinTools::Daemon
    DeocoinTools::Miner
    DeocoinTools::Optimizer
    DeocoinTools::PaymentGateService
    DeocoinTools::SimpleWallet
)

# DeocoinTools::BinaryInfo # NOTE: Ignore this. It's not a target.

# DeocoinTools::ConnectivityTool

set(DeocoinTools_ConnectivityTool_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/ConnectivityTool/ConnectivityTool.cpp"
)

if(WIN32)
    list(APPEND DeocoinTools_ConnectivityTool_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/BinaryInfo/connectivity_tool.rc"
    )
endif()

set(DeocoinTools_ConnectivityTool_LIBS
    Boost::program_options
    DeocoinFramework::Breakpad
    DeocoinFramework::Common
    DeocoinFramework::CryptoNoteCore
    DeocoinFramework::P2p
    DeocoinFramework::Rpc
    DeocoinFramework::Serialization
    DeocoinFramework::System
)

if(WIN32)
    list(APPEND DeocoinTools_ConnectivityTool_LIBS ws2_32)
endif()

add_executable(DeocoinTools_ConnectivityTool ${DeocoinTools_ConnectivityTool_SOURCES})
add_executable(DeocoinTools::ConnectivityTool ALIAS DeocoinTools_ConnectivityTool)
target_include_directories(DeocoinTools_ConnectivityTool PRIVATE ${DeocoinTools_INCLUDE_DIRS})
target_link_libraries(DeocoinTools_ConnectivityTool ${DeocoinTools_ConnectivityTool_LIBS})
set_target_properties(DeocoinTools_ConnectivityTool PROPERTIES OUTPUT_NAME "connectivity_tool")

# DeocoinTools::Daemon

set(DeocoinTools_Daemon_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Daemon/Daemon.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Daemon/DaemonCommandsHandler.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Daemon/DaemonCommandsHandler.h"
)

if(WIN32)
    list(APPEND DeocoinTools_Daemon_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/BinaryInfo/daemon.rc"
    )
endif()

set(DeocoinTools_Daemon_LIBS
    Boost::filesystem
    DeocoinFramework::Breakpad
    DeocoinFramework::Common
    DeocoinFramework::CryptoNoteCore
    DeocoinFramework::Global
    DeocoinFramework::Logging
    DeocoinFramework::P2p
    DeocoinFramework::Rpc
    DeocoinFramework::Serialization
    DeocoinFramework::System
)

add_executable(DeocoinTools_Daemon ${DeocoinTools_Daemon_SOURCES})
add_executable(DeocoinTools::Daemon ALIAS DeocoinTools_Daemon)
target_include_directories(DeocoinTools_Daemon PRIVATE ${DeocoinTools_INCLUDE_DIRS})
target_link_libraries(DeocoinTools_Daemon PRIVATE ${DeocoinTools_Daemon_LIBS})
set_target_properties(DeocoinTools_Daemon PROPERTIES OUTPUT_NAME "deocoind")

# DeocoinTools::Miner

set(DeocoinTools_Miner_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Miner/BlockchainMonitor.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Miner/BlockchainMonitor.h"
    "${CMAKE_CURRENT_LIST_DIR}/Miner/Miner.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Miner/Miner.h"
    "${CMAKE_CURRENT_LIST_DIR}/Miner/MinerEvent.h"
    "${CMAKE_CURRENT_LIST_DIR}/Miner/MinerManager.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Miner/MinerManager.h"
    "${CMAKE_CURRENT_LIST_DIR}/Miner/MiningConfig.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Miner/MiningConfig.h"
    "${CMAKE_CURRENT_LIST_DIR}/Miner/main.cpp"
)

if(WIN32)
    list(APPEND DeocoinTools_Miner_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/BinaryInfo/miner.rc"
    )
endif()

set(DeocoinTools_Miner_LIBS
    Boost::program_options
    DeocoinFramework::Breakpad
    DeocoinFramework::Common
    DeocoinFramework::CryptoNoteCore
    DeocoinFramework::Logging
    DeocoinFramework::Rpc
    DeocoinFramework::Serialization
    DeocoinFramework::System
)

if(WIN32)
    list(APPEND DeocoinTools_Miner_LIBS ws2_32)
endif()

add_executable(DeocoinTools_Miner ${DeocoinTools_Miner_SOURCES})
add_executable(DeocoinTools::Miner ALIAS DeocoinTools_Miner)
target_include_directories(DeocoinTools_Miner PRIVATE ${DeocoinTools_INCLUDE_DIRS})
target_link_libraries(DeocoinTools_Miner PRIVATE ${DeocoinTools_Miner_LIBS})
set_target_properties(DeocoinTools_Miner PROPERTIES OUTPUT_NAME "miner")

# DeocoinTools::Optimizer

set(DeocoinTools_Optimizer_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Optimizer/Optimizer.cpp"
)

if(WIN32)
    list(APPEND DeocoinTools_Optimizer_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/BinaryInfo/optimizer.rc"
    )
endif()

set(DeocoinTools_Optimizer_LIBS
    Boost::filesystem
    Boost::program_options
    DeocoinFramework::Breakpad
    DeocoinFramework::Common
    DeocoinFramework::CryptoNoteCore
    DeocoinFramework::Global
    DeocoinFramework::InProcessNode
    DeocoinFramework::Logging
    DeocoinFramework::Rpc
    DeocoinFramework::System
)

if(WIN32)
    list(APPEND DeocoinTools_Optimizer_LIBS ws2_32)
endif()

add_executable(DeocoinTools_Optimizer ${DeocoinTools_Optimizer_SOURCES})
add_executable(DeocoinTools::Optimizer ALIAS DeocoinTools_Optimizer)
target_include_directories(DeocoinTools_Optimizer PRIVATE ${DeocoinTools_INCLUDE_DIRS})
target_link_libraries(DeocoinTools_Optimizer ${DeocoinTools_Optimizer_LIBS})
set_target_properties(DeocoinTools_Optimizer PROPERTIES OUTPUT_NAME "optimizer")

# DeocoinTools::PaymentGateService

set(DeocoinTools_PaymentGateService_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGateService/ConfigurationManager.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGateService/ConfigurationManager.h"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGateService/PaymentGateService.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGateService/PaymentGateService.h"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGateService/PaymentServiceConfiguration.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGateService/PaymentServiceConfiguration.h"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGateService/RpcNodeConfiguration.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGateService/RpcNodeConfiguration.h"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGateService/main.cpp"
)

if(WIN32)
    list(APPEND DeocoinTools_PaymentGateService_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/BinaryInfo/walletd.rc"
    )
endif()

set(DeocoinTools_PaymentGateService_LIBS
    Boost::filesystem
    Boost::program_options
    DeocoinFramework::Breakpad
    DeocoinFramework::Common
    DeocoinFramework::CryptoNoteCore
    DeocoinFramework::Global
    DeocoinFramework::InProcessNode
    DeocoinFramework::Logging
    DeocoinFramework::Rpc
    DeocoinFramework::System
)

add_executable(DeocoinTools_PaymentGateService ${DeocoinTools_PaymentGateService_SOURCES})
add_executable(DeocoinTools::PaymentGateService ALIAS DeocoinTools_PaymentGateService)
target_include_directories(DeocoinTools_PaymentGateService PRIVATE ${DeocoinTools_INCLUDE_DIRS})
target_link_libraries(DeocoinTools_PaymentGateService ${DeocoinTools_PaymentGateService_LIBS})
set_target_properties(DeocoinTools_PaymentGateService PROPERTIES OUTPUT_NAME "walletd")

# DeocoinTools::SimpleWallet

set(DeocoinTools_SimpleWallet_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/SimpleWallet/PasswordContainer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SimpleWallet/PasswordContainer.h"
    "${CMAKE_CURRENT_LIST_DIR}/SimpleWallet/SimpleWallet.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SimpleWallet/SimpleWallet.h"
)

if(WIN32)
    list(APPEND DeocoinTools_SimpleWallet_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/BinaryInfo/simplewallet.rc"
    )
endif()

set(DeocoinTools_SimpleWallet_LIBS
    Boost::filesystem
    Boost::program_options
    DeocoinFramework::Breakpad
    DeocoinFramework::Common
    DeocoinFramework::Global
    DeocoinFramework::Logging
    DeocoinFramework::NodeRpcProxy
    DeocoinFramework::Rpc
    DeocoinFramework::Serialization
    DeocoinFramework::Wallet
)

if(WIN32)
    list(APPEND DeocoinTools_SimpleWallet_LIBS ws2_32)
endif()

add_executable(DeocoinTools_SimpleWallet ${DeocoinTools_SimpleWallet_SOURCES})
add_executable(DeocoinTools::SimpleWallet ALIAS DeocoinTools_SimpleWallet)
target_include_directories(DeocoinTools_SimpleWallet PRIVATE ${DeocoinTools_INCLUDE_DIRS})
target_link_libraries(DeocoinTools_SimpleWallet ${DeocoinTools_SimpleWallet_LIBS})
set_target_properties(DeocoinTools_SimpleWallet PROPERTIES OUTPUT_NAME "simplewallet")

# Installation

install(TARGETS
            DeocoinTools_ConnectivityTool
            DeocoinTools_Daemon
            DeocoinTools_Miner
            DeocoinTools_Optimizer
            DeocoinTools_PaymentGateService
            DeocoinTools_SimpleWallet
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static
)
